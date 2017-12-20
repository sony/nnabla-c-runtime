def generate(string, info):
    funcid = 0
    dump = []
    typenames = []
    for cn, cat in info.items():
        for fn, func in cat.items():
            typenames.append('  "{}",'.format(fn))
            if 'argument' in func:
                dump.append(
                    '    case NN_FUNCTION_{}: {{ // {}'.format(func['snakecase_name'].upper(), fn))
                dump.append(
                    '      nn_function_{0}_t *f = (nn_function_{0}_t*)func;'.format(func['snakecase_name']))
                for an, arg in func['argument'].items():
                    if arg['Type'] == 'bool':
                        dump.append(
                            '      printf("NNB: Function argument {0}: %d\\n", f->{0});'.format(an))
                    elif arg['Type'] == 'double' or arg['Type'] == 'float':
                        dump.append(
                            '      printf("NNB: Function argument {0}: %f\\n", f->{0});'.format(an))
                    elif arg['Type'] == 'int64':
                        dump.append(
                            '      printf("NNB: Function argument {0}: %d\\n", f->{0});'.format(an))
                    elif arg['Type'] == 'repeated int64' or arg['Type'] == 'Shape':
                        dump.append(
                            '      printf("NNB: Function argument {}: (");'.format(an))
                        dump.append(
                            '      list = (int*)NN_GET(net, f->{}.list);'.format(an))
                        dump.append(
                            '      for(i = 0; i < f->{}.size; i++) {{'.format(an))
                        dump.append('        printf(" %d", *(list + i));')
                        dump.append('      }')
                        dump.append('      printf(" )\\n");')
                    elif arg['Type'] == 'string':
                        dump.append(
                            '      printf("NNB: Function argument {0}: %d\\n", f->{0});'.format(an))

                dump.append('    } break;')
            funcid += 1
    return string.format(typenames='\n'.join(typenames), dump='\n'.join(dump))
