import google.protobuf.text_format as text_format
import numpy
import collections
import google.protobuf.text_format as text_format

import nnabla.utils.converter
from nnabla.utils import nnabla_pb2

result_nums = {}


def save_result(inputs, outputs, func_name, func_args, func_kwargs):
    if func_name is None:
        return

    for category_name, category in nnabla.utils.converter.get_category_info().items():
        if func_name in category:
            function = category[func_name]

    if func_name not in result_nums:
        result_nums[func_name] = 0

    save_filename = '{}_{:03d}.nntxt'.format(func_name, result_nums[func_name])

    nnp = nnabla_pb2.NNablaProtoBuf()
    net = nnp.network.add()
    net.name = 'network1'
    net.batch_size = 1

    func = net.function.add()
    func.name = func_name
    func.type = func_name

    # Prepare input
    func_inputs = []
    data_names = []
    parameter_names = []
    for n, i in enumerate(inputs):
        if i is not None:
            input_name, input_info = list(function['inputs'].items())[n]
            func_inputs.append(input_name)
            var = net.variable.add()
            var.name = input_name
            if 'parameter' in input_info and input_info['parameter']:
                parameter_names.append(input_name)

                var.type = 'Parameter'
                shape = list(i.d.shape)[:]
                if func.name == 'BatchNormalization':
                    shape = [1] + shape
                var.shape.dim.extend(shape)

                param = nnp.parameter.add()
                param.variable_name = input_name
                param.shape.dim.extend(shape)
                param.data.extend(i.d.flatten())

            else:
                i.d.flatten().tofile('{}_{:03d}_input_{}_{}.bin'.format(
                    func_name, result_nums[func_name], i.d.dtype, n))

                data_names.append(input_name)

                var.type = 'Buffer'
                shape = list(i.d.shape)[:]
                shape = [1] + shape
                var.shape.dim.extend(shape)

    func.input.extend(func_inputs)

    # Prepare output
    func_outputs = []
    for n, o in enumerate(outputs):
        output_name = 'y{}'.format(n)
        func_outputs.append(output_name)
        var = net.variable.add()
        var.name = output_name
        var.type = 'Buffer'
        shape = list(o.d.shape)[:]
        shape = [-1] + shape
        var.shape.dim.extend(shape)
        o.d.flatten().tofile('{}_{:03d}_output_{}.bin'.format(
            func_name, result_nums[func_name], n))

    func.output.extend(func_outputs)

    # Prepare argument
    if 'arguments' in function:
        for n, (arg_name, arg) in enumerate(function['arguments'].items()):
            param = eval('func.{}_param'.format(function['snake_name']))
            a = func_args[n]
            if a is not None:
                if 'axis' in arg_name:
                    a += 1

                if 'axes' in arg_name:

                    if isinstance(a, tuple) or isinstance(a, list):
                        a = list(a)
                    else:
                        a = [a]
                    a = [x + 1 for x in a]

                if isinstance(a, tuple) or isinstance(a, list):
                    if arg['type'] == 'Shape':
                        exec('param.{}.dim.extend(list(a))'.format(arg_name))
                    else:
                        exec('param.{}.extend(a)'.format(arg_name))
                elif isinstance(a, numpy.ndarray):
                    a = a.flatten()
                    if arg['type'] == 'Shape':
                        if function['snake_name'] == 'broadcast':
                            exec('param.{}.dim.extend([1] + list(a))'.format(arg_name))
                        else:
                            exec('param.{}.dim.extend(list(a))'.format(arg_name))
                    else:
                        exec('param.{}.extend(a)'.format(arg_name))
                else:
                    if 'repeated' in arg['type']:
                        exec('param.{}.extend([a])'.format(arg_name))
                    elif arg['type'] == 'string':
                        exec('param.{} = "{}"'.format(arg_name, a))
                    else:
                        if arg_name == 'base_axis':
                            a = a + 1
                        exec('param.{} = {}'.format(arg_name, a))

    # Prepare executor
    exe = nnp.executor.add()
    exe.name = 'inference'
    exe.network_name = 'network1'
    for d in data_names:
        dat = exe.data_variable.add()
        dat.variable_name = d
        dat.data_name = d

    for o in func_outputs:
        out = exe.output_variable.add()
        out.variable_name = o
        out.data_name = o

    for p in parameter_names:
        par = exe.parameter_variable.add()
        par.variable_name = p

    with open(save_filename, 'w') as f:
        text_format.PrintMessage(nnp, f)
    result_nums[func_name] += 1
