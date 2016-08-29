import sys
import re
from numpy import *
import config

#min
#max
#moyenne
#ecart-type
#1er
#2e (mediane) 
#3e quartile.
#nb 0


class ChromSize(object):
    def  __init__(self, path):
        self.chroms = {}
        with open(path) as chrom_sizes:
            for line in chrom_sizes:
                if line:
                    chrom, chrom_size = line.split()
                    self.chroms[chrom] = int(chrom_size)
        self.genome_size = 0


    def size(self, bin_size):
        if self.genome_size:
            return self.genome_size
        else:
            for chrom_size in self.chroms.itervalues():
                self.genome_size += (chrom_size + bin_size - 1) / bin_size
        return self.genome_size


def getstats(content, chrom_sizes, isGroup=False):
    c = array(content)
    cmin = min(content)
    cmax = max(content)
    cavg = mean(c)
    cstd = std(c)
    if isGroup:
        total_len = chrom_sizes.size(BIN_SIZE)
        c0 = content.count(0.0)/float(total_len)
    else:
        c0 = content.count(0.0)/float(len(content))
    c1 = percentile(c, 25)
    c2 = median(c)
    c3 = percentile(c, 75)
    return [cmin,cmax,cavg,cstd,c0,c1,c2,c3]


def reader(filename, chrom_sizes):
    y_flag=False
    group=""
    dataset=""
    group_content = []
    dataset_content = []
    with open(filename, 'r') as file:
        for line in file:
            if "GROUP" in line:
                if dataset_content:
                    stats = getstats(dataset_content, chrom_sizes)
                    if "chrY" not in dataset:
                        print_stats(stats, group, dataset)
                        group_content += dataset_content
                    dataset_content=[]
                if group_content:
                    stats = getstats(group_content, chrom_sizes, True)
                    print_stats(stats, group, "all")
                    group_content = []
                group = re.search('GROUP "(.*)" {', line).group(1)
            elif "DATASET" in line:
                if dataset_content:
                    stats = getstats(dataset_content, chrom_sizes)
                    if "chrY" not in dataset:
                        print_stats(stats, group, dataset)
                        group_content += dataset_content
                    dataset_content=[]
                dataset = re.search('DATASET "(.*)" {', line).group(1)
            elif line.strip().startswith("("):
                line = line.split("): ")[1]
                for score in line.split(","):
                    score = score.strip()
                    if score:
                        dataset_content.append(float(score))
    if dataset_content:
        stats = getstats(dataset_content, chrom_sizes)
        if "chrY" not in dataset:
            print_stats(stats, group, dataset)
            group_content += dataset_content
        dataset_content=[]
    if group_content:
        stats = getstats(group_content, chrom_sizes, True)
        print_stats(stats, group, "all")
        group_content = []

def print_stats(stats, group, dataset):
    data = "\t".join(str(stat) for stat in stats)
    print "%s/%s\t%s" % (group, dataset, data)

if __name__ == '__main__':
    HDF5_DUMP = sys.argv[1]
    ASSEMBLY = sys.argv[2]
    BIN_SIZE = int(sys.argv[3])

    print "\t".join(["name", "min", "max", "mean", "stdev", "pct 0", "25th pct", "median", "75th pct"])
    reader(HDF5_DUMP, ChromSize(config.CHROM_SIZE[ASSEMBLY]))
