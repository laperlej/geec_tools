class InputManager(object):
    def __init__(self, input_file):
        self.input_tokens = []
        self.load(input_file)

    def load(self, input_file):
        for line in input_file:
            line = line.strip().split("\t")
            if line: self.input_tokens.append(line)

    def __iter__(self):
        return iter(self.input_tokens)
