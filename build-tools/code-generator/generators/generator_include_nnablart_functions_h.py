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
            if 'argument' in func:
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
                        argstrings.append('uint32_t {}'.format(an))
                        defines.append(
                            '  uint32_t {};  ///< Original type is [{}]'.format(an, arg['Type']))

                defines.append('  void* local_context;')
                defines.append('}} {}Config;'.format(fn))
                defines.append(
                    'void init{0}Config({0}Config* config, {1});'.format(fn, ','.join(argstrings)))
                defines.append(
                    'void init{}LocalContext(rt_function_t* f);'.format(fn))
                defines.append(
                    'void free{}LocalContext(rt_function_t* f);'.format(fn))

            defines.append('void exec{}(rt_function_t* f);'.format(fn))
            defines.append('')
        defines.append('')

    return string.format(FUNCTION_DEFINES='\n'.join(defines))
