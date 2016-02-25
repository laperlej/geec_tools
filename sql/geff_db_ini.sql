INSERT OR REPLACE INTO Assembly VALUES (NULL, 'hg19', 'human');
INSERT OR REPLACE INTO Assembly VALUES (NULL, 'mm10', 'mouse');

INSERT OR REPLACE INTO ChromSize VALUES (NULL, 'All', 'Resource/chrom_sizes/hg19ext.chrom.sizes', 1);
INSERT OR REPLACE INTO ChromSize VALUES (NULL, 'Canon', 'Resource/chrom_sizes/hg19.chrom.sizes', 1);
INSERT OR REPLACE INTO ChromSize VALUES (NULL, 'CanonNoY', 'Resource/chrom_sizes/hg19noY.chrom.sizes', 1);
INSERT OR REPLACE INTO ChromSize VALUES (NULL, 'All', 'Resource/chrom_sizes/mm10ext.chrom.sizes', 2);
INSERT OR REPLACE INTO ChromSize VALUES (NULL, 'Canon', 'Resource/chrom_sizes/mm10.chrom.sizes', 2);
INSERT OR REPLACE INTO ChromSize VALUES (NULL, 'CanonNoY', 'Resource/chrom_sizes/mm10noY.chrom.sizes', 2);

INSERT OR REPLACE INTO Hdf5File VALUES (NULL, 'Resource/hdf5/hg19.hdf5');
INSERT OR REPLACE INTO ZscoreFile VALUES (NULL, 'Resource/zscore/hg19.zscore');
INSERT OR REPLACE INTO CorrelationFile VALUES (NULL, 'Resource/corr/hg19.corr');
INSERT OR REPLACE INTO MatrixFile VALUES (NULL, 'Resource/matrix/hg19.mat');

INSERT OR REPLACE INTO Hdf5File VALUES (NULL, 'Resource/hdf5/mm10.hdf5');
INSERT OR REPLACE INTO ZscoreFile VALUES (NULL, 'Resource/zscore/mm10.zscore');
INSERT OR REPLACE INTO CorrelationFile VALUES (NULL, 'Resource/corr/mm10.corr');
INSERT OR REPLACE INTO MatrixFile VALUES (NULL, 'Resource/matrix/mm10.mat');

INSERT OR REPLACE INTO Region VALUES (NULL, 'Resource/region/hg19.all.bed', 1);
INSERT OR REPLACE INTO Region VALUES (NULL, 'Resource/region/hg19.exclude.bed', 1);
INSERT OR REPLACE INTO Region VALUES (NULL, 'Resource/region/none.bed', 1);
INSERT OR REPLACE INTO Region VALUES (NULL, 'Resource/region/hg19.all.bed', 2);
INSERT OR REPLACE INTO Region VALUES (NULL, 'Resource/region/hg19.exclude.bed', 2);
INSERT OR REPLACE INTO Region VALUES (NULL, 'Resource/region/none.bed', 2);
