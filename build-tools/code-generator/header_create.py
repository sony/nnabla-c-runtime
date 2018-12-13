from os.path import abspath, dirname, join
import argparse
import yaml
import template

here = abspath(dirname(abspath(__file__)))
base = abspath(join(here, '../..'))


def get_func_list():
    func_list = []
    with open(join(here, 'functions.yaml'), 'r') as f:
        info = yaml.load(f)
        for cn, cat in info.items():
            for fn, func in cat.items():
                for t in func['func_type']:
                    if t == 'None':
                        break
                    elif t == 'ALL':
                        func_list.append(fn)
                        func_list.append(fn+'_FLOAT32')
                        func_list.append(fn+'_GENERIC')
                    elif t == 'FLOAT32':
                        func_list.append(fn)
                        func_list.append(fn+'_FLOAT32')
                    elif t == 'FIXED8' or t == 'FIXED16':
                        func_list.append(fn)
                        func_list.append(fn+'_GENERIC')
    return list(set(func_list))


def generate(func_list):
    defines = []
    func_list = [x.upper() for x in func_list]
    func_list.sort()
    for n in func_list:
        defines.append('#define CONFIG_{} 1'.format(n))
    with open(join(base, 'include/nnablart/config.h'), 'w') as f:
        f.write(template.config_defines.format('\n'.join(defines)))


if __name__ == '__main__':
    func_list = get_func_list()
    generate(func_list)
