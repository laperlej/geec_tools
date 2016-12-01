import os.path

#directories
MODULE_DIR = os.path.dirname(os.path.dirname(os.path.realpath(__file__)))
TMP_DIR = '/home/laperlej/mntHome/tmp/'
IHEC_DIR = '/nfs3_ib/10.4.217.32'

#executables
def exec_path(exec_name):
    return os.path.join(os.path.dirname(MODULE_DIR), 'bin', exec_name)

TO_HDF5 = exec_path('to_hdf5')
FILTER = exec_path('filter')
CORRELATION = exec_path('correlation')
BWI = exec_path('bigWigInfo')
BG_TO_BW = exec_path('bedGraphToBigWig')
BW_TO_BG = exec_path('bigWigToBedGraph')

MAKE_MATRIX = os.path.join(MODULE_DIR, 'make_matrix.py')

#chrom sizes
def chrom_sizes_path_maker(filename):
    os.path.join(os.path.dirname(MODULE_DIR),'resource','chrom_sizes',filename)

def get_chrom_sizes(assembly):
    if assembly != 'saccer3':
        assembly = assembly + '.noy'
    filename = '{0}.chrom.sizes'.format(assembly)
    return chrom_sizes_path_maker(filename)

#regions
def region_path_maker(filename):
    return os.path.join(os.path.dirname(MODULE_DIR), 'resource', 'region', filename)

def get_region(assembly, content):
    if content == 'none':
        return region_path_maker('none.bed')
    filename = "{0}.{1}.bed".format(assembly.lower(), content.lower())
    return region_path_maker(filename)

#precalculated
def hdf5_list_path_maker(filename):
    os.path.join(os.path.dirname(MODULE_DIR),'resource','public',filename)

def get_hdf5_list(assembly, bin, include, exclude):
    to_human = {'100':'100b',
                '1000':'1kb',
                '10000':'10kb',
                '100000':'100kb'}
    filename = "{0}_{1}_{}_{}.list".format(assembly, to_human[resolution], include, exclude)
    return region_path_maker(filename)
