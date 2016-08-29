import sys
import bigwig

class InputFile(object):
    def __init__(self, file_path):
        self.files = []
        self.names = []
        self.parse_file(file_path)

    def __len__(self):
        return len(self.files)

    def parse_file(self, file_path):
        with open(file_path) as list_file:
            for line in list_file:
                path, name = line.split()
                self.files.append(path)
                self.names.append(name)

    def __getitem__(self, index):
        return self.files[index], self.names[index]

if __name__ == '__main__':
    input_path = sys.argv[1]
    file_list = InputFile(input_path)
    for i in range(len(file_list)):
        path, name = file_list[i]
        bigwig.BigWig(path, name).bwbgbw()
