def generate(filename, info):
    from mako.template import Template
    from mako import exceptions
    try:
        tmpl = Template(filename=filename)
        output = tmpl.render()
        return output
    except:
        print(exceptions.text_error_template().render())
    return None
