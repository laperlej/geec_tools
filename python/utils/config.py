import os.path

#directories
MODULE_DIR = os.path.dirname(os.path.dirname(os.path.realpath(__file__)))
TMP_DIR = '/home/laperlej/mntHome/tmp/'
IHEC_DIR = '/nfs3_ib/10.4.217.32'
PUBLIC_DATA_ROOT = "/home/laperlej/geec/public"

#executables
def exec_path(exec_name):
    return os.path.join(os.path.dirname(MODULE_DIR), 'bin', exec_name)

BW_TO_HDF5 = exec_path('bw_to_hdf5')
BG_TO_HDF5 = exec_path('bg_to_hdf5')
FILTER = exec_path('filter')
CORRELATION = exec_path('correlation')
CORRELATION_NM = exec_path('correlation_nm')
BWI = exec_path('bigWigInfo')
BG_TO_BW = exec_path('bedGraphToBigWig')
BW_TO_BG = exec_path('bigWigToBedGraph')
WIG_TO_BW = exec_path('wigToBigWig')

MAKE_MATRIX = os.path.join(MODULE_DIR, 'make_matrix.py')
MAKE_MATRIX_NM = os.path.join(MODULE_DIR, 'make_matrix_nm.py')

def analysis_path(script_name):
    return os.path.join(os.path.dirname(MODULE_DIR), 'geec_analysis', script_name)

GEEC_ANNOTATE = analysis_path('geec_annotate.py')
GEEC_ARI = analysis_path('geec_ari.py')
GEEC_SLICE = analysis_path('geec_slice.py')
GEEC_SLICE_FILE_NAME = analysis_path('geec_slice_file_name.py')

#chrom sizes
def chrom_sizes_path_maker(filename):
    return os.path.join(os.path.dirname(MODULE_DIR),'resource','chrom_sizes',filename)

def get_chrom_sizes(assembly):
    assembly = assembly.lower()
    if assembly != 'saccer3':
        assembly = assembly + '.noy'
    else:
        assembly = assembly + '.can'
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
def hdf5_path_maker(path):
    return os.path.join(PUBLIC_DATA_ROOT,path[0], path[1], path[2])

def get_resolution(num):
    to_human = {1:"1bp",
                10:"10bp",
                100: "100bp",
                1000: "1kb",
                10000: "10kb",
                100000: "100kb",
                1000000: "1mb",
                10000000: "10mb",
                100000000: "100mb"}
    return to_human[int(num)]

def get_matrix(assembly, resolution, include, exclude, metric="pearson"):
    filename = "{0}_{1}_{2}_{3}.mat".format(get_resolution(resolution), include, exclude, metric)
    path = [PUBLIC_DATA_ROOT, assembly, filename]
    return os.path.join(*path)

def get_hdf5(md5, assembly, resolution, include, exclude, metric="pearson"):
    ext = {"pearson":"hdf5",
           "spearman":"rank"}
    folder = "{1}_{2}_{3}".format(assembly, get_resolution(resolution), include, exclude)
    path = [assembly, folder, "{0}_{1}.{2}".format(md5, folder,ext[metric])]
    return hdf5_path_maker(path)
