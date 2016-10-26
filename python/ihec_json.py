"""
"""

import json
import sys


class IhecJson(object):
    """
    """
    def __init__(self, ihec_json_file):
        self.content = self.load(ihec_json_file)

    def load(self, ihec_json_file):
        """
        """
        ihec_json = json.load(ihec_json_file)
        hub_description = ihec_json['hub_description']
        datasets = ihec_json['datasets']

        parsed_datasets = []

        #ihec_root = "/nfs3_ib/10.4.217.32/home/genomicdata/ihec_datasets/"\
        #            "2016-04/"

        publishing_group = hub_description["publishing_group"]
        releasing_group = hub_description["releasing_group"]
        assembly = hub_description["assembly"]
        count = 0
        for data in datasets.itervalues():
            ihecdata = data["ihec_data_portal"]
            assay = ihecdata["assay"]
            assay_category = ihecdata["assay_category"]
            cell_type = ihecdata["cell_type"]
            cell_type_category = ihecdata["cell_type_category"]
            file_name = ihecdata["local_files"]["signal"]["file_name"]
            md5sum = ihecdata["local_files"]["signal"]["md5sum"]
            unique_id = count
            #file_path = '/'.join([ihec_root, 
            #                      releasing_group.lower(),
            #                      file_name])
            parsed_dataset = {
                "assembly": assembly,
                "publishing_group": publishing_group,
                "releasing_group": releasing_group,
                "assay": assay,
                "assay_category": assay_category,
                "cell_type": cell_type,
                "cell_type_category": cell_type_category,
                "file_name": file_name,
                "md5sum": md5sum,
                "id": unique_id,
             #   "file_path": file_path
            }
            parsed_datasets.append(parsed_dataset)
        return parsed_datasets

    def __str__(self):
        """
        """
        return json.dumps({"datasets":self.content})


def main():
    """
    """
    ihec_json_path = sys.argv[1]
    print IhecJson(open(ihec_json_path))

if __name__ == "__main__":
    main()
