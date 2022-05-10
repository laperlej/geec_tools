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
        for dataset in self.datasets:
            label = dataset["md5sum"]
            print "{0}".format(label)


def main():
    """
    """
    geec_json_path = sys.argv[1]
    geec_json = GeecJson(open(geec_json_path))
    geec_json.input_file()

if __name__ == "__main__":
    main()
