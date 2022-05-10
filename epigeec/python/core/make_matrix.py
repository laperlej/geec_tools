#!/usr/bin/env python2
# Copyright (C) 2015 Jonathan Laperle. All Rights Reserved.
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# =============================================================================


from __future__ import absolute_import, division, print_function
from builtins import range, zip

import json
import numpy as np
import pandas as pd
import sys
import argparse

"""
18cd442ee1fa03df74517335ed2ed92d:a0f380a52e792f65b96c41ad5fdfd8e8   chr1,-0.091218  chr10,-0.120059 chr11,-0.085029 chr12,0.962397  chr13,0.038357  chr14,0.908901  chr15,-0.060206 chr16,-0.109638 chr17,-0.091413 chr18,0.03692chr19,-0.113141    chr2,0.999374   chr3,-0.076656  chr4,-0.194520  chr5,-0.087904  chr6,0.821275   chr7,-0.099522  chr8,-0.004072  chr9,0.997895   chrX,0.172631   chrY,0.712472
"""

class Matrix(object):
    def __init__(self, *args):
        if len(args) == 1:
            self.init_nn(*args)
        elif len(args) == 3:
            self.init_nm(*args)
        else:
            exit()

    def init_nn(self, nn):
        dframe = pd.read_csv(nn, delimiter='\t', index_col=0)
        self.desc = dframe.index.name
        #dframe.index.name = None
        self.labels = sorted(dframe.columns.values.tolist())
        self.index = dict(zip(self.labels, range(len(self.labels))))
        self.size = len(self.labels)
        self.matrix = np.nan_to_num(dframe.sort(axis=0).sort(axis=1).as_matrix())

    def init_nm(self, nn, nm, mm):
        nn_dframe = pd.read_csv(nn, delimiter='\t', index_col=0)
        nm_dframe = pd.read_csv(nm, delimiter='\t', index_col=0)
        mm_dframe = pd.read_csv(mm, delimiter='\t', index_col=0)
        self.desc = nn_dframe.index.name
        #nn_dframe.index.name = None
        #nm_dframe.index.name = None
        #mm_dframe.index.name = None

        nm_dframe = nm_dframe.rename(columns={c:c[:32] for c in nm_dframe.columns})

        nn_labels = nn_dframe.columns.values.tolist()
        mm_labels = mm_dframe.columns.values.tolist()
        self.labels = sorted(nn_labels + mm_labels)
        self.index = dict(zip(self.labels, range(len(self.labels))))
        self.size = len(self.labels)

        #merge matrices
        tmp1 = pd.concat([nn_dframe, nm_dframe], axis=1)
        tmp2 = pd.concat([mm_dframe, nm_dframe])
        self.matrix = np.nan_to_num(tmp3.sort_index(axis=0).sort_index(axis=1).as_matrix())

    def __getitem__(self, labels):
        x_label, y_label = labels
        x = self.index.get(x_label)
        y = self.index.get(y_label)
        return self.matrix[x, y]

    def __setitem__(self, labels, value):
        x_label, y_label = labels
        x = self.index.get(x_label)
        y = self.index.get(y_label)
        self.matrix[x, y] = value
        self.matrix[y, x] = value

    def convert_labels(self, meta):
        for i in range(len(self.labels)):
            token = meta.get("datasets", {}).get(self.labels[i][:32], {})
            if token:
                self.labels[i] = "{0}".format(token.get("file_name", ""))


    def __str__(self):
        s = ""
        if self.desc is not None:
            s += self.desc
        s += '\t' + '\t'.join(self.labels) + '\n'
        for i in range(self.size):
            s += self.labels[i] + '\t' + '\t'.join(["{0:.4f}".format(v) for v in self.matrix[i]]) + '\n'
        return s

def listjson2dictjson(old_json):
    new_json = {"datasets":{}}
    for token in old_json.get("datasets", []):
        new_json["datasets"][token["md5sum"]] = token
    return new_json

def parse_args(argv):
    parser = argparse.ArgumentParser()
    parser.add_argument('-nm')
    parser.add_argument('-mm')
    parser.add_argument('-meta')
    parser.add_argument('matrix_nn')
    parser.add_argument('output_path')
    args = parser.parse_args(argv)
    return args

def main(argv):
    args = parse_args(argv)
    if args.nm is None and args.mm is None:
        matrix = Matrix(args.matrix_nn)
    else:
        matrix = Matrix(args.matrix_nn, args.nm, args.mm)
    if args.meta is not None:
        matrix.convert_labels(listjson2dictjson(json.load(open(args.meta))))
    with open(args.output_path, 'w') as output_file:
        output_file.write(str(matrix))

def cli():
    main(sys.argv[1:])

if __name__ == '__main__':
    cli()
