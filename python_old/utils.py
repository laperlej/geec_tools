import config
import tempfile
import os.path

def string_to_num(number, sep=','):
    total = 0
    number = number.split(sep)
    number.reverse()
    for i in range(len(number)):
        total += int(number[i]) * (1000**i)
    return total

def add_ihec_dir(path):
    if path.startswith('/'):
        path = path[1:]
    return os.path.join(config.IHEC_DIR, path)

def change_path(path, directory, ext):
    path = change_dir(path, directory)
    return change_ext(path, ext)

def change_dir(path, directory):
    name = os.path.basename(path)
    return os.path.join(directory, name)

def change_ext(path, ext):
    root, _ = os.path.splitext(path)
    return root + ext

def parse_chroms(chrom_size):
    chroms = {}
    with open(chrom_size, 'r') as chr_size:
        for line in chr_size:
            if line:
                chroms[line.split()[0]] = True
    return chroms

def filter_bedgraph(input_bg, chrom_size, output_bg):
    chroms = parse_chroms(chrom_size)
    bg_out = open(output_bg, 'w')
    with open(input_bg, 'r') as bg_in:
        for line in bg_in:
            if chroms.get(line.split()[0], False):
                bg_out.write(line)
    bg_out.close()
