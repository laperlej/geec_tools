to_hdf5="/mnt/parallel_scratch_mp2_wipe_on_august_2016/jacques/laperlej/geec_tools/bin/to_hdf5"
filter="/mnt/parallel_scratch_mp2_wipe_on_august_2016/jacques/laperlej/geec_tools/bin/filter"
correlation="/mnt/parallel_scratch_mp2_wipe_on_august_2016/jacques/laperlej/geec_tools/bin/correlation"
make_matrix="/mnt/parallel_scratch_mp2_wipe_on_august_2016/jacques/laperlej/geec_tools/python/make_matrix.py"


bin=10000
include="/mnt/parallel_scratch_mp2_wipe_on_august_2016/jacques/laperlej/geec_tools/resource/region/hg19.all.bed"
exclude="/mnt/parallel_scratch_mp2_wipe_on_august_2016/jacques/laperlej/geec_tools/resource/region/hg19.exclude.bed"
chrom_sizes="/mnt/parallel_scratch_mp2_wipe_on_august_2016/jacques/laperlej/geec_tools/resource/chrom_sizes/hg19noY.chrom.sizes"

file_list=$1

hdf5_commands=$(mktemp)
filtered_commands=$(mktemp)

while IFS=$'\n' read -r line; do
	IFS=$'\t' read -r bw_file name hdf5_file filter_file <<< "$line"
	echo "$to_hdf5 $bw_file $name $chrom_sizes $hdf5_file $bin" > hdf5_commands
	echo "$filter $hdf5_file $name $filter_file $chrom_sizes $bin $include $exclude" > filtered_commands
done < "$file_list"

cat $hdf5_commands | xargs -I CMD -P 24 bash -c CMD
cat $filtered_commands | xargs -I CMD -P 24 bash -c CMD