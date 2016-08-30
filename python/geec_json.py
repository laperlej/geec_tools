"""
"""

import sys
import json
import os

class GeecJson(object):
    """
    """
    def __init__(self, geec_json_file):
        self.datasets = self.load(geec_json_file)

    def load(self, geec_json_file):
        """
        """
        return json.load(geec_json_file)['datasets']

    def input_file(self):
        """
        """
        root = "/mnt/parallel_scratch_mp2_wipe_on_august_2016"\
               "/jacques/laperlej/test/"
        hdf5_dsc = "10kb_all_none"
        filtered_dsc = "10kb_all_blklst"

        for dataset in self.datasets:
            raw_path = dataset["file_path"]
            label = dataset["md5sum"]
            hdf5_path = os.path.join(
                root, 
                dataset["assembly"],
                hdf5_dsc,
                dataset["releasing_group"],
                "{0}_{1}".format(label, hdf5_dsc))
            filtered_path = os.path.join(
                root,
                dataset["assembly"],
                filtered_dsc,
                dataset["releasing_group"],
                "{0}_{1}".format(label, filtered_dsc))
            print "{0}\t{1}\t{2}\t{3}".format(raw_path,
                                              label,
                                              hdf5_path,
                                              filtered_path)


def main():
    """
    """
    geec_json_path = sys.argv[1]
    geec_json = GeecJson(open(geec_json_path))
    geec_json.input_file()

if __name__ == "__main__":
    main()
