import sys
import h5py
import numpy as np
import os

test_file = "/Users/Jon/Desktop/hg19/10kb_all_blklst/blueprint/ERS164475.H3K27me3.signal.hdf5"

class InputManager(object):
    def __init__(self, input_file):
        self.input_tokens = []
        self.load(input_file)

    def load(self, input_file):
        for line in input_file:
            line = line.split("\t")
            if line: self.input_tokens.append(line)

    def __iter__(self):
        return iter(self.input_tokens)

class Hdf5(object):
    def __init__(self, path):
        if h5py.is_hdf5(path):
            self.h5 = h5py.File(path,'r')
        else:
            print "not a valid hdf5 file"
            exit(1)

    def get_stats(self):
        c = self.get_content()
        cmin = np.amin(c)
        cmax = np.amax(c)
        cavg = np.mean(c)
        cstd = np.std(c)
        c0 = (c.size - np.count_nonzero(c)) / float(c.size)
        c25 = np.percentile(c, 25)
        cmedian = np.median(c)
        c75 = np.percentile(c, 75)
        return [cmin,cmax,cavg,cstd,c0,c25,cmedian,c75]

    def get_content(self):
        name = self.h5.attrs['hash']
        arrays = [self.h5[name][chrom][:] for chrom in self.h5[name]]
        return np.concatenate(arrays)

def main():
    input_file = sys.argv[1]
    input_manager = InputManager(input_file)
    print "\t".join(["filename","md5", "min", "max", "mean", "stdev", "pct 0", "25th pct", "median", "75th pct"])
    for input_token in input_manager:
        md5 = input_token[1]
        hdf5_file = input_token[3]
        file_name = os.path.basename(hdf5_file)
        hdf5 = Hdf5(hdf5_file)
        stats = hdf5.get_stats()
        data = "\t".join(str(stat) for stat in stats)
        print "%s\t%s\t%s" % (file_name, md5, data)
    print hdf5.get_stats()

if __name__ == '__main__':
    main()