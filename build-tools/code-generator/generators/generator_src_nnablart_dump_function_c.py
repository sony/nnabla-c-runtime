def generate(string, info):
    funcid = 0
    dump = []
    typenames = []
    for cn, cat in info.items():
        for fn, func in cat.items():
            typenames.append('  "{}",'.format(fn))
            dump.append(
                '    case NN_FUNCTION_{}: {{ // {}'.format(func['snake_name'].upper(), fn))
            if 'arguments' in func and len(func['arguments']) > 0:
                dump.append(
                    '      nn_function_{0}_t *f = (nn_function_{0}_t*)func;'.format(func['snake_name']))
                for an, arg in func['arguments'].items():
                    if arg['type'] == 'bool':
                        dump.append(
                            '      printf("NNB: Function argument {0}: %d\\n", f->{0});'.format(an))
                    elif arg['type'] == 'double' or arg['type'] == 'float':
                        dump.append(
                            '      printf("NNB: Function argument {0}: %f\\n", f->{0});'.format(an))
                    elif arg['type'] == 'int64':
                        dump.append(
                            '      printf("NNB: Function argument {0}: %d\\n", f->{0});'.format(an))
                    elif arg['type'] == 'repeated int64' or arg['type'] == 'Shape':
                        dump.append(
                            '      printf("NNB: Function argument {}: (");'.format(an))
                        dump.append(
                            '      list = (int*)NN_GET(net, f->{}.list);'.format(an))
                        dump.append(
                            '      for(i = 0; i < f->{}.size; i++) {{'.format(an))
                        dump.append('        printf(" %d", *(list + i));')
                        dump.append('      }')
                        dump.append('      printf(" )\\n");')
                    elif arg['type'] == 'string':
                        dump.append(
                            '      printf("NNB: Function argument {0}: %d\\n", f->{0});'.format(an))

            dump.append('    } break;')
            funcid += 1
    return string.format(typenames='\n'.join(typenames), dump='\n'.join(dump))
