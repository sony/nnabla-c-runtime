def generate(string, info):
    l = []
    for cn, cat in info.items():
        for fn, func in cat.items():
            l.append(
                '    case NN_FUNCTION_{}: {{ // {}'.format(func['snakecase_name'].upper(), fn))
            l.append('      WHOAMI("{}\\n");'.format(fn))
            l.append('      func.exec_func = exec_{};'.format(func['snakecase_name']))
            if 'argument' in func:
                l.append(
                    '      nn_function_{0}_t *f = (nn_function_{0}_t*)function;'.format(func['snakecase_name']))
                l.append(
                    '      {0}_config_t *conf = malloc(sizeof({0}_config_t));'.format(func['snakecase_name']))

                for an, arg in func['argument'].items():
                    if arg['Type'] == 'bool':
                        l.append('      conf->{0} = f->{0};'.format(an))
                    elif arg['Type'] == 'double' or arg['Type'] == 'float':
                        l.append('      conf->{0} = f->{0};'.format(an))
                    elif arg['Type'] == 'int64':
                        l.append('      conf->{0} = f->{0};'.format(an))
                    elif arg['Type'] == 'repeated int64' or arg['Type'] == 'Shape':
                        l.append(
                            '      conf->{0} = create_rt_list_from_nn_list(n, f->{0});'.format(an))
                    elif arg['Type'] == 'string':
                        l.append('      conf->{0} = f->{0};'.format(an))
                l.append('      func.func.config = conf;')
            l.append('    } break;')
    return string.format('\n'.join(l))
