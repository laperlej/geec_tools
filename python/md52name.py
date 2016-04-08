import sys
import os.path

def parse_list_file(file_path):
    word_dict = {}
    with open(file_path, 'r') as ofile:
        for line in ofile:
            if line:
                line = line.strip()
                line = line.split('\t')
                word_dict[line[1]] = os.path.basename(line[0])
    return word_dict


def main():
    list_path = sys.argv[1]
    input_path = sys.argv[2]
    output_path = sys.argv[3]

    word_dict = parse_list_file(list_path)
    with open(input_path, 'r') as input_file:
        input_text = input_file.read()
    for md5sum, filename in word_dict.iteritems():
        input_text = input_text.replace(md5sum, filename)
    with open(output_path, 'w') as output_file:
        output_file.write(input_text)

if __name__ == '__main__':
    main()
