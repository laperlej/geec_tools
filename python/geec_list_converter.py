import sys

list_path = sys.argv[1]

tmp_dir = "/home/laperlej/mntHome/tmp"
ihec_dir = "/nfs3_ib/10.4.217.32/home/genomicdata/ihec_datasets/2016-04"
hdf5_dir = "/mnt/parallel_scratch_mp2_wipe_on_august_2016/jacques/laperlej/test/hg19/10kb_all_none"
filtered_dir = "/mnt/parallel_scratch_mp2_wipe_on_august_2016/jacques/laperlej/test/hg19/10kb_all_blklst"

with open(list_path, 'r') as list_file:
	for line in list_file:
		line = line.split()
		raw_path = line[0]
		label = line[1]
		raw_name = raw_path.split("/")[-1]
		hdf5_file_name = "{0}_{1}.hdf5".format(label, hdf5_dir.split("/")[-1])
		filtered_file_name = "{0}_{1}.hdf5".format(label, filtered_dir.split("/")[-1])
		hdf5_path = line[0].replace("/hg19", "").replace(ihec_dir, hdf5_dir).replace(tmp_dir, hdf5_dir).replace(raw_name, hdf5_file_name)
		filtered_path = line[0].replace("/hg19", "").replace(ihec_dir, filtered_dir).replace(tmp_dir, filtered_dir).replace(raw_name, filtered_file_name)
		print "\t".join([raw_path, label, hdf5_path, filtered_path])