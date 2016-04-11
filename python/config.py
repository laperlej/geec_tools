import os.path

#directories
MODULE_DIR = os.path.dirname(os.path.realpath(__file__))
TMP_DIR = '/home/laperlej/mntHome/tmp/'
IHEC_DIR = '/nfs3_ib/10.4.217.32'

#executables
TO_HDF5 = os.path.join(os.path.dirname(MODULE_DIR),
                   'bin',
                   'to_hdf5')
TO_ZSCORE = os.path.join(os.path.dirname(MODULE_DIR),
                   'bin',
                   'to_zscore')
CORRELATION = os.path.join(os.path.dirname(MODULE_DIR),
                   'bin',
                   'correlation_nm')
COMPLETE_MATRIX = os.path.join(MODULE_DIR,
                   'complete_matrix.py')
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
                         'hg19ext.chrom.sizes'),
    'mm10': os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'chrom_sizes',
                         'mm10ext.chrom.sizes'),
    'hg38': os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'chrom_sizes',
                         'hg38ext.chrom.sizes')
}

#regions
REGION={'hg19': {'all': os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'region',
                         'hg19.all.bed'),
                 'blacklisted': os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'region',
                         'hg19.exclude.bed')},
        'mm10': {'all': os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'region',
                         'mm10.all.bed'),
                 'blacklisted': os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'region',
                         'mm10.exclude.bed')},
        'hg38': {'all': os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'region',
                         'hg38.all.bed'),
                 'blacklisted': os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'region',
                         'hg38.exclude.bed')}
}

#precalculated
ZSCORE = {'hg19': {'10000': {'all' :{'blacklisted' : os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'zscore',
                         'hg19.zscore')}}}}
MATRIX = {'hg19': {'10000': {'all' :{'blacklisted' : os.path.join(os.path.dirname(MODULE_DIR),
                         'resource',
                         'mat',
                         'hg19.mat')}}}}
