import google.protobuf.text_format as text_format

result_nums = {}


def callback(name, nnp, inputs, outputs):
    if name not in result_nums:
        result_nums[name] = 0

    save_filename = '{}_{:03d}.nntxt'.format(name, result_nums[name])

    for n, i in enumerate(inputs):
        i.tofile('{}_{:03d}_input_{}.bin'.format(
            name, result_nums[name], n))
    for n, o in enumerate(outputs):
        o.tofile('{}_{:03d}_output_{}.bin'.format(
            name, result_nums[name], n))
    with open(save_filename, 'w') as f:
        text_format.PrintMessage(nnp, f)
    result_nums[name] += 1
