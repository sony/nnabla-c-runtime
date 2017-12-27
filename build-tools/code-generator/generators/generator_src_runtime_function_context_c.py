def generate(string, info):
    l1 = []
    for cn, cat in info.items():
        for fn, func in cat.items():
            l1.append(
                '    case NN_FUNCTION_{}: {{ // {}'.format(func['snakecase_name'].upper(), fn))
            l1.append('      func.exec_func = exec_{};'.format(
                func['snakecase_name']))
            if 'argument' in func:
                l1.append(
                    '      nn_function_{0}_t *f = (nn_function_{0}_t*)function;'.format(func['snakecase_name']))
                l1.append(
                    '      {0}_config_t *conf = malloc(sizeof({0}_config_t));'.format(func['snakecase_name']))

                for an, arg in func['argument'].items():
                    if arg['Type'] == 'bool':
                        l1.append('      conf->{0} = f->{0};'.format(an))
                    elif arg['Type'] == 'double' or arg['Type'] == 'float':
                        l1.append('      conf->{0} = f->{0};'.format(an))
                    elif arg['Type'] == 'int64':
                        l1.append('      conf->{0} = f->{0};'.format(an))
                    elif arg['Type'] == 'repeated int64' or arg['Type'] == 'Shape':
                        l1.append(
                            '      conf->{0} = create_rt_list_from_nn_list(n, f->{0});'.format(an))
                    elif arg['Type'] == 'string':
                        l1.append('      conf->{0} = f->{0};'.format(an))
                l1.append('      func.func.config = conf;')
            l1.append('      allocate_{}_local_context(&func.func);'.format(
                func['snakecase_name']))
            l1.append('    } break;')
            l1.append('')

    l2 = []
    for cn, cat in info.items():
        for fn, func in cat.items():
            l2.append(
                '    case NN_FUNCTION_{}: {{ // {}'.format(func['snakecase_name'].upper(), fn))
            l2.append('      free_{}_local_context(&func.func);'.format(
                func['snakecase_name']))
            if 'argument' in func:
                l2.append('      free(func.func.config);')
            l2.append('    } break;')
            l2.append('')

    return string.format('\n'.join(l1), '\n'.join(l2))
