from collections import OrderedDict
import importlib
import os
import json
import re
import subprocess


class CodeGenerator:
    def __init__(self):
        self.get_function_info()

    def get_function_info(self):
        with open(os.path.join(os.path.dirname(os.path.abspath(__file__)),
                               'function_info.json'), 'r') as f:
            self.info = json.loads(f.read(), object_pairs_hook=OrderedDict)

    def generate(self, name):
        output_filename = os.path.abspath(os.path.join(
            os.path.dirname(os.path.abspath(__file__)), '..', '..', name))

        template = os.path.abspath(
            os.path.join(os.path.dirname(
                os.path.abspath(__file__)),
                'generators',
                'template_' + name.replace('/', '_')))

        generator_module = 'generators.generator_' + \
            name.replace('/', '_').replace('.', '_')
        generator = importlib.import_module(generator_module)
        contents = generator.generate(open(template).read(), self.info)
        with open(output_filename, 'w') as f:
            f.write(contents)
        subprocess.run(['clang-format', '-i', '--style=llvm', output_filename])
        print('Generated [{}].'.format(os.path.basename(output_filename)))

    def generate_all(self):
        self.generate('include/nnablart/network.h')
        self.generate('include/nnablart/functions.h')


CodeGenerator().generate_all()
