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
            name = func['snake_name']
            if 'arguments' in func and len(func['arguments']) > 0:

                for an, arg in func['arguments'].items():
                    print("XXXXXXXXXXXXX")
                    if 'available_values' in arg:
                        print("XXXXXXXXXXXXXZZZZZZZZZZZZZXS")
                        defines.append('typedef enum {')
                        for t in arg['available_values']:
                            defines.append('    {}_{}_{},'.format(
                                name.upper(), an.upper(), t.upper()))
                        defines.append('    END_OF_{}_{}'.format(
                            name.upper(), an.upper()))
                        defines.append('}} {}_{}_value_t;'.format(name, an))
                        defines.append('')
                defines.append('typedef struct {')

                for an, arg in func['arguments'].items():

                    if arg['type'] == 'bool':
                        defines.append('  uint8_t {};'.format(an))

                    elif arg['type'] == 'double' or arg['type'] == 'float':
                        defines.append('  float {};'.format(an))

                    elif arg['type'] == 'int64':
                        defines.append('  int32_t {};'.format(an))

                    elif arg['type'] == 'repeated int64' or arg['type'] == 'Shape':
                        defines.append(
                            '  rt_list_t {}; ///< Original type is [{}]'.format(an, arg['type']))

                    elif arg['type'] == 'string':
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
