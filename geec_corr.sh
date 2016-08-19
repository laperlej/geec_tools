to_hdf5="/mnt/parallel_scratch_mp2_wipe_on_august_2016/jacques/laperlej/geec_tools/bin/to_hdf5"
filter="/mnt/parallel_scratch_mp2_wipe_on_august_2016/jacques/laperlej/geec_tools/bin/filter"
correlation="/mnt/parallel_scratch_mp2_wipe_on_august_2016/jacques/laperlej/geec_tools/bin/correlation"
make_matrix="/mnt/parallel_scratch_mp2_wipe_on_august_2016/jacques/laperlej/geec_tools/python/make_matrix.py"


bin=10000
include="/mnt/parallel_scratch_mp2_wipe_on_august_2016/jacques/laperlej/geec_tools/resource/region/hg19.all.bed"
exclude="/mnt/parallel_scratch_mp2_wipe_on_august_2016/jacques/laperlej/geec_tools/resource/region/hg19.exclude.bed"
chrom_sizes="/mnt/parallel_scratch_mp2_wipe_on_august_2016/jacques/laperlej/geec_tools/resource/chrom_sizes/hg19noY.chrom.sizes"

file_list=$1
results_file=$2
matrix_file=$3

filter_file_list=$(mktemp)
awk 'BEGIN{FS=OFS="\t"}{print $4,$2}' $file_list > $filter_file_list

$correlation $filter_file_list $chrom_sizes $results_file $bin
python $make_matrix $filter_file_list $chrom_sizes $results_file $matrix_file

rm $filter_file_list