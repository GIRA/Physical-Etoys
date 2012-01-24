import re

def configure(bootstrapper, in_file, out_file = None):

    if not out_file:
        out_file = in_file[:-3] # Blindly remove the '.in' suffix

    def evaluate(exp):
        if bootstrapper: # Useless 'if', required to import 'bootstrapper' in this scope
            pass
        m = "bootstrapper." + exp.group(0)[4:-5]
        return eval(m)

    with open(in_file, "r") as in_file:
        with open(out_file, "w") as out_file:
            for l in in_file.readlines():
                out_file.write(re.sub(r"<py>.*?</py>", evaluate, l))

