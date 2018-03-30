def generate(string, info):
    l1 = []
    for cn, cat in info.items():
        for fn, func in cat.items():
            l1.append(
                '    case NN_FUNCTION_{}: {{ // {}'.format(func['snake_name'].upper(), fn))
            l1.append('      func.exec_func = exec_{};'.format(
                func['snake_name']))
            if 'arguments' in func and len(func['arguments']) > 0:
                l1.append(
                    '      nn_function_{0}_t *f = (nn_function_{0}_t*)function;'.format(func['snake_name']))
                l1.append(
                    '      {0}_local_context_t *ctx = malloc(sizeof({0}_local_context_t));'.format(func['snake_name']))

                for an, arg in func['arguments'].items():
                    if arg['type'] == 'bool':
                        l1.append('      ctx->{0} = f->{0};'.format(an))
                    elif arg['type'] == 'double' or arg['type'] == 'float':
                        l1.append('      ctx->{0} = f->{0};'.format(an))
                    elif arg['type'] == 'int64':
                        l1.append('      ctx->{0} = f->{0};'.format(an))
                    elif arg['type'] == 'repeated int64' or arg['type'] == 'Shape':
                        l1.append(
                            '      ctx->{0} = create_rt_list_from_nn_list(n, f->{0});'.format(an))
                    elif arg['type'] == 'string':
                        l1.append('      ctx->{0} = f->{0};'.format(an))
                l1.append('      func.func.local_context = ctx;')
            l1.append('      allocate_{}_local_context(&func.func);'.format(
                func['snake_name']))
            l1.append('    } break;')
            l1.append('')

    l2 = []
    for cn, cat in info.items():
        for fn, func in cat.items():
            l2.append(
                '    case NN_FUNCTION_{}: {{ // {}'.format(func['snake_name'].upper(), fn))
            l2.append('      free_{}_local_context(&func.func);'.format(
                func['snake_name']))
            if 'arguments' in func:
                l2.append('      free(func.func.local_context);')
            l2.append('    } break;')
            l2.append('')

    return string.format('\n'.join(l1), '\n'.join(l2))
