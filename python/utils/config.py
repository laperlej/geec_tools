import os.path

#directories
MODULE_DIR = os.path.dirname(os.path.dirname(os.path.realpath(__file__)))
TMP_DIR = '/home/laperlej/mntHome/tmp/'
IHEC_DIR = '/nfs3_ib/10.4.217.32'

#executables
TO_HDF5 = os.path.join(os.path.dirname(MODULE_DIR),
                   'bin',
                   'to_hdf5')
FILTER = os.path.join(os.path.dirname(MODULE_DIR),
                   'bin',
                   'filter')
CORRELATION = os.path.join(os.path.dirname(MODULE_DIR),
                   'bin',
                   'correlation')
MAKE_MATRIX = os.path.join(MODULE_DIR,
                   'make_matrix.py')
BWI = os.path.join(os.path.dirname(MODULE_DIR),
                   'bin',
                   'bigWigInfo')
BG_TO_BW = os.path.join(os.path.dirname(MODULE_DIR),
                        'bin',
                        'bedGraphToBigWig')
BW_TO_BG = os.path.join(os.path.dirname(MODULE_DIR),
                        'bin',
                        'bigWigToBedGraph')

#chrom sizes
CHROM_SIZE = {
    'hg19': os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'chrom_sizes',
                         'hg19noY.chrom.sizes'),
    'mm10': os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'chrom_sizes',
                         'mm10noY.chrom.sizes'),
    'hg38': os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'chrom_sizes',
                         'hg38noY.chrom.sizes'),
    'sacCer3': os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'chrom_sizes',
                         'sacCer3.chrom.sizes'),
}

#regions
REGION={'hg19': {'all': os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'region',
                         'hg19.all.bed'),
                 'blacklisted': os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'region',
                         'hg19.exclude.bed'),
                 'none': os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'region',
                         'none.bed')},
        'mm10': {'all': os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'region',
                         'mm10.all.bed'),
                 'blacklisted': os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'region',
                         'mm10.exclude.bed'),
                 'none': os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'region',
                         'none.bed')},
        'hg38': {'all': os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'region',
                         'hg38.all.bed'),
                 'blacklisted': os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'region',
                         'hg38.exclude.bed'),
                 'none': os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'region',
                         'none.bed')},
        'sacCer3': {'all': os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'region',
                         'sacCer3.all.bed'),
                 'none': os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'region',
                         'none.bed')},
}

#precalculated
HDF5 = {'hg19': {'10000': {'all' :{'blacklisted' : os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'public',
                         'hg19_10kb_all_blklst.list'),
                                   'none': os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'public',
                         'hg19_10kb_all_none.list')}}},
         'sacCer3': {'1000': {'all' :{'none': os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'public',
                         'sacCer3_1kb_all_none.list')}}},
}
