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
                            defines.append('    {}_{}_{},'.format(name.upper(), an.upper(), t.upper()))
                        defines.append('    END_OF_{}_{}'.format(name.upper(), an.upper()))
                        defines.append('}} {}_{}_value_t;'.format(name, an))
                        defines.append('')
                defines.append('typedef struct {')
                argstrings = []

                for an, arg in func['argument'].items():

                    if arg['Type'] == 'bool':
                        argstrings.append('uint8_t {}'.format(an))
                        defines.append('  uint8_t {};'.format(an))

                    elif arg['Type'] == 'double' or arg['Type'] == 'float':
                        argstrings.append('float {}'.format(an))
                        defines.append('  float {};'.format(an))

                    elif arg['Type'] == 'int64':
                        argstrings.append('int32_t {}'.format(an))
                        defines.append('  int32_t {};'.format(an))

                    elif arg['Type'] == 'repeated int64' or arg['Type'] == 'Shape':
                        argstrings.append('rt_list_t {}'.format(an))
                        defines.append(
                            '  rt_list_t {}; ///< Original type is [{}]'.format(an, arg['Type']))

                    elif arg['Type'] == 'string':
                        argstrings.append('{0}_{1}_value_t {1}'.format(name, an))
                        defines.append('{0}_{1}_value_t {1};'.format(name, an))

                defines.append('  void* local_context;')
                defines.append('}} {}_config_t;'.format(name))
                defines.append(
                    'void init_{0}_config({0}_config_t* config, {1});'.format(name, ','.join(argstrings)))
                defines.append(
                    'void allocate_{}_local_context(rt_function_t* f);'.format(name))
                defines.append(
                    'void free_{}_local_context(rt_function_t* f);'.format(name))

            defines.append('void exec_{}(rt_function_t* f);'.format(name))
            defines.append('')
        defines.append('')

    return string.format(FUNCTION_DEFINES='\n'.join(defines))
