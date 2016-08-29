import sys
import json
import sqlite3
import collections
import database

QcTrack = collections.namedtuple('QcTrack',
                                 'track_id '
                                 'md5sum '
                                 'file_path '
                                 'assembly_id '
                                 'assay '
                                 'assay_category '
                                 'cell_type '
                                 'cell_type_category '
                                 'releasing_group '
                                 'institution')

Hdf5Group = collections.namedtuple('Hdf5Group',
                                  'Hdf5GroupId'
                                  'QcTrackId'
                                  'Hdf5FileId'
                                  'BinSize'
                                  'ChromSizeId')

ZscoreGroup = collections.namedtuple('ZscoreGroup',
                                     'ZscoreGroupId'
                                     'Hdf5GroupId'
                                     'ZscoreFileId'
                                     'InclusionId'
                                     'ExclusionId')

def build_track(dataset, assembly_id):
    track_id = None
    path = dataset["qcTrackInternalFilePath"]
    assay = dataset["assay"]
    md5 = dataset["qcTrackMd5"]
    release_group = dataset["releasing_group"]
    assay_category = dataset["assay_category"]
    cell_type = dataset["cell_type"]
    cell_type_category = dataset["cell_type_category"]
    institution = dataset["institution"]
    track = QcTrack(track_id,
                    md5,
                    path,
                    assembly_id,
                    assay,
                    assay_category,
                    cell_type,
                    cell_type_category,
                    release_group,
                    institution)
    return track

class input_file(object):
    def __init__(self):
        self.files = {}

    def load(self, content):
        for line in content:
            if line:
                line = line.split()
                md5sum = line[0]
                path = line[1]
                self.files[md5sum] = path
    def __iter__(self):
        return self.files.__iter__()

    def next(self):
        self.files.next()


def build_tracks(json_content, assembly_id):
    tracks = []
    json_content = open(JSON_PATH).read()
    json_content = json.loads(json_content)
    for dataset in json_content["dataset"]:
        tracks.append(build_track(dataset, assembly_id))
    return tracks

def add_json(json_file, database_path, assembly):
    geff_database = database.Database(database_path)
    json_content = open(json_file).read()
    json_content = json.loads(json_content)
    assembly_id = geff_database.get_id("Assembly", "Name", assembly)
    tracks = build_tracks(json_content, assembly_id)
    geff_database.insert('QcTrack', tracks)

def build_hdf5_group(md5sum, geff_db, hdf5_path, chrom_size, bin_size):
    hdf5_group_id = None
    qc_track_id = geff_db.get_id('QcTrack', 'Md5Sum', md5sum)
    hdf5_file_id = geff_db.get_id('Hdf5File', 'FilePath', hdf5_path)
    bin_size = bin_size
    chrom_size_id = geff_db.get_id('ChromSize','FilePath', chrom_size)
    hdf5_group = Hdf5Group(hdf5_group_id,
                           qc_track_id,
                           hdf5_file_id,
                           bin_size,
                           chrom_size_id)
    return hdf5_group

def build_hdf5_groups(input_file):
    hdf5_groups = []
    for bw in input_file:


    return hdf5_groups

def add_hdf5(input_file, database_path, hdf5_path, chrom_size, bin):
    geff_database = database.Database(database_path)


def add_zscore():
    pass

def print_manual():
    man = """Usage: python bd_script {mode} ...
    modes:
        json:
            {json_file} {database} {assembly}
        hdf5:
            {input_file} {database} {hdf5_file} {chrom_size} {bin}
        zscore:
            {input_file} {database}
    """
    print man

if __name__ == '__main__':
    if len(sys.argv) < 4:
        print print_manual()
        sys.exit(0)
    JSON_PATH = sys.argv[1]
    DB_PATH = sys.argv[2]
    ASSEMBLY = sys.argv[3]
    add_json()
