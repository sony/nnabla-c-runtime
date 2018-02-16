import json
import hashlib


def generate(string, info):
    m = hashlib.md5()
    m.update(json.dumps(info).encode('utf-8'))
    defines = []
    enums = []
    for cn, cat in info.items():
        for fn, func in cat.items():
            enums.append(
                '  NN_FUNCTION_{},    ///< {}'.format(func['snakecase_name'].upper(), fn))

            defines.append('/// @brief {} function.'.format(fn))
            defines.append('/// @{')
            defines.append('typedef struct {')
            defines.append(
                '  nn_function_type_t type; ///< Common: type of function.')
            defines.append(
                '  nn_list_t inputs;        ///< Common: List of input variables.')
            defines.append(
                '  nn_list_t outputs;       ///< Common: List of output variables.')
            if 'argument' in func and len(func['argument']) > 0:
                defines.append('  // End of common part.')
                for an, arg in func['argument'].items():
                    if arg['Type'] == 'bool':
                        defines.append('  uint8_t {};'.format(an))
                    elif arg['Type'] == 'double' or arg['Type'] == 'float':
                        defines.append('  float {};'.format(an))
                    elif arg['Type'] == 'int64':
                        defines.append('  int32_t {};'.format(an))
                    elif arg['Type'] == 'repeated int64' or arg['Type'] == 'Shape':
                        defines.append(
                            '  nn_list_t {};  ///< Original type is [{}]'.format(an, arg['Type']))
                    elif arg['Type'] == 'string':
                        defines.append(
                            '  uint32_t {};  ///< Original type is [{}]'.format(an, arg['Type']))
            defines.append('}} nn_function_{}_t;'.format(
                func['snakecase_name']))
            defines.append('')
            defines.append('/// @}')
            defines.append('')
    return string.format(BINARY_VERSION=m.hexdigest(),
                         FUNCTION_ENUMS='\n'.join(enums),
                         FUNCTION_DEFINES='\n'.join(defines))
