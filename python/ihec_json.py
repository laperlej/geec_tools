import json
import kent
import utils
from bigwig import BigWig

class IhecJson(object):
    def __init__(self, json_path):
        self.path = json_path
        with open(json_path) as json_file:
            self.json = json.loads(json_file.read())
        self.datasets = self._load_datasets()

    def _load_datasets(self):
        datasets = {}
        for dataset in self.json['dataset']:
            if dataset['qcTrackInternalFilePath']:
                path = dataset['qcTrackInternalFilePath']
                path = utils.add_ihec_dir(path)
                md5sum = dataset['qcTrackMd5']
                bigwig = BigWig(path, md5sum)
                datasets[md5sum] = bigwig
        return datasets
