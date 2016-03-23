import kent
import utils
import config
import os
import tempfile

class BigWig(object):
    def __init__(self, path, md5sum, assembly='hg19'):
        self.path = path
        self.md5sum = md5sum
        self.assembly = assembly
        self._info = self._get_info()

    def _get_info(self):
        path = self.path
        if ':' in path:
            path = self.symlink()
        info = kent.big_wig_info(path)
        if info is not None:
            info = dict([line.split(": ") for line in info.split('\n') if line])
        else:
            info = {}
        return info

    def symlink(self):
        #TODO do away with tempnam
        #new_path = os.tempnam(config.TMP_DIR)
        new_path = os.path.join(os.path.dirname(self.path), os.path.basename(self.path).replace(':','_'))
        os.symlink(self.path, new_path)
        return new_path

    def isValid(self):
        return bool(self._info)

    def get_index_size(self):
        index_size = self._info.get("primaryIndexSize", "-1")
        index_size = utils.string_to_num(index_size)
        return index_size

    def has_large_index(self, max_size=10**7):
        return self.get_index_size() > max_size

    def bwbgbw(self):
        bg_path = utils.change_path(self.path, config.TMP_DIR, '.bedGraph')
        new_path = utils.change_dir(self.path, config.TMP_DIR)
        chrom_size = config.CHROM_SIZE[self.assembly]

        err_code = kent.bwbgbw(self.path, bg_path, new_path, chrom_size)
        if err_code:
            info = {}
        else:
            self.path = new_path
