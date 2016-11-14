"""
"<a href='http://www.ncbi.nlm.nih.gov/sra?term=SRX006117' target=_blank>SRX006117</a>": {
  "analysis_attributes": {
    "alignment_software": "Pash",
    "alignment_software_version": "3.0"
  },
  "browser": {
    "signal": [
      {
        "big_data_url": "http://genboree.org/REST/v1/grp/Epigenomics%20Roadmap%20Repository/db/Release%209%20Repository/trk/H1%3AH3K4me3%20A/bigWig?gbKey=1tvb0fa2",
        "md5sum": "54e25d744c953c62578cbbdf605c16ba",
        "md5sum_computed": "54e25d744c953c62578cbbdf605c16ba",
        "primary": true
      }
    ]
  },
  "experiment_attributes": {
    "experiment_id": "<a href='http://www.ncbi.nlm.nih.gov/sra?term=SRX006117' target=_blank>SRX006117</a>",
    "experiment_type": "Histone_H3K4me3"
  },
  "ihec_data_portal": {
    "assay": "H3K4me3",
    "assay_category": "Histone Modifications",
    "cell_type": "H1",
    "cell_type_category": "ES Cells"
  },
  "other_attributes": {
    "experiment_geo_id": "<a href='http://www.ncbi.nlm.nih.gov/geo/query/acc.cgi?acc=GSM410808' target=_blank>GSM410808</a>",
    "lab": "UCSF-UBC-UCD"
  },
  "raw_data_url": null,
  "sample_id": "SRS003451_H1EScd1-me3K4-A_424"
},

"hub_description": {
  "assembly": "hg19",
  "date": "2016-11-08",
  "description": "Data hub generated by the IHEC Data Portal, with the following parameters: {'data_release_id': '5'}",
  "email": "info@epigenomesportal.ca",
  "publishing_group": "Roadmap",
  "releasing_group": "Roadmap",
  "taxon_id": 9606
},
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

        publishing_group = hub_description["publishing_group"]
        releasing_group = hub_description.get("releasing_group", publishing_group)
        assembly = hub_description["assembly"]
        count = 0
        for data in datasets.itervalues():
            ihecdata = data.get("ihec_data_portal", {})
            assay = ihecdata.get("assay", "N/A")
            assay_category = ihecdata.get("assay_category", "N/A")
            cell_type = ihecdata.get("cell_type", "N/A")
            cell_type_category = ihecdata.get("cell_type_category", "N/A")

            #signal type priority
            #signal merged have no name, need to use forward
            for signal_type in ["methylation_profile", "signal_forward", "signal_unstranded", "signal"]:
                signal_data = data.get("browser", {}).get(signal_type, [{}])[0]
                if signal_data:
                    break

            file_name = signal_data["big_data_url"].split("/")[-1]
            md5sum = signal_data["md5sum"]
            unique_id = count
            count += 1
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
            }
            parsed_dataset["virtual"] = bool(signal_type == "signal_forward")
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
