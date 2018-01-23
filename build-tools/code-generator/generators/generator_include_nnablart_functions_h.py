def generate(string, info):
    defines = []
    for cn, cat in info.items():
        defines.append(
            '////////////////////////////////////////////////////////////////////////////////')
        defines.append('// {}'.format(cn))
        defines.append(
            '////////////////////////////////////////////////////////////////////////////////')
        defines.append('')
        for fn, func in cat.items():
            defines.append('// {}'.format(fn))
            name = func['snakecase_name']
            if 'argument' in func:

                for an, arg in func['argument'].items():
                    if 'TypeSelection' in arg:
                        defines.append('typedef enum {')
                        for t in arg['TypeSelection']:
                            defines.append('    {}_{}_{},'.format(
                                name.upper(), an.upper(), t.upper()))
                        defines.append('    END_OF_{}_{}'.format(
                            name.upper(), an.upper()))
                        defines.append('}} {}_{}_value_t;'.format(name, an))
                        defines.append('')
                defines.append('typedef struct {')

                for an, arg in func['argument'].items():

                    if arg['Type'] == 'bool':
                        defines.append('  uint8_t {};'.format(an))

                    elif arg['Type'] == 'double' or arg['Type'] == 'float':
                        defines.append('  float {};'.format(an))

                    elif arg['Type'] == 'int64':
                        defines.append('  int32_t {};'.format(an))

                    elif arg['Type'] == 'repeated int64' or arg['Type'] == 'Shape':
                        defines.append(
                            '  rt_list_t {}; ///< Original type is [{}]'.format(an, arg['Type']))

                    elif arg['Type'] == 'string':
                        defines.append('{0}_{1}_value_t {1};'.format(name, an))

                defines.append('  void* private;')
                defines.append('}} {}_local_context_t;'.format(name))
            defines.append('')
            defines.append(
                'rt_function_error_t allocate_{}_local_context(rt_function_t* f);'.format(name))
            defines.append(
                'rt_function_error_t free_{}_local_context(rt_function_t* f);'.format(name))
            defines.append('rt_function_error_t exec_{}(rt_function_t* f);'.format(name))
            defines.append('')
        defines.append('')

    return string.format(FUNCTION_DEFINES='\n'.join(defines))
