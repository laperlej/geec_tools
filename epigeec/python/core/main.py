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

import argparse
import logging
import os.path
import subprocess
import sys
import tempfile

import make_matrix

EPI_DIR = os.path.dirname(os.path.dirname(os.path.dirname(os.path.realpath(__file__))))
BIN_DIR = os.path.join(EPI_DIR, "bin")
BW_TO_HDF5_PATH = os.path.join(BIN_DIR, "bw_to_hdf5")
BG_TO_HDF5_PATH = os.path.join(BIN_DIR, "bg_to_hdf5")
FILTER_PATH = os.path.join(BIN_DIR, "filter")
CORR_PATH = os.path.join(BIN_DIR, "correlation")

def tmp_name():
    fd, temp_path = tempfile.mkstemp()
    os.close(fd)
    os.remove(temp_path)
    return temp_path

def make_all_filter(tmp, chrom):
    for line in chrom:
       line = line.strip()
       if line:
           line = line.split()
           tmp.write("{0}\t{1}\t{2}\n".format(line[0], "0", line[1]))

def get_hdf5_converter(args):
    if args.bw:
        exe = BW_TO_HDF5_PATH
    elif args.bg:
        exe = BG_TO_HDF5_PATH
    else:
        print "No file type switch provided use -bg or -bw"
        sys.exit(1)
    return exe

def to_hdf5(args):
    exe = get_hdf5_converter(args)
    command = [exe,
                 args.signal,
                 args.chrom_sizes,
                 args.bin,
                 args.hdf5]
    subprocess.call(command)

def hdf5_filter(args):
    if args.include:
        include = args.include
    else:
        include = tmp_name()
        make_all_filter(open(include, 'w'), open(args.chrom_sizes))
    if args.exclude:
        exclude = args.exclude
    else:
        exclude = tmp_name()
        open(exclude, 'w')
    command = [FILTER_PATH,
                 args.signal,
                 args.chrom_sizes,
                 args.bin,
                 args.hdf5,
                 include,
                 exclude]
    subprocess.call(command)

def corr(args):
    corr_path = tmp_name()
    #call correlation
    command = [CORR_PATH,
                 args.list,
                 args.chrom_sizes,
                 args.bin,
                 corr_path]
    subprocess.call(command)

    #call make_matrix
    make_matrix.main(args.list, corr_path, args.mat)
    subprocess.call(command)

def make_parser():
    parser = argparse.ArgumentParser(description = "description")
    subparsers = parser.add_subparsers(help = "sub-command help")

    parser_hdf5 = subparsers.add_parser("hdf5", help="hdf5 help")
    parser_hdf5.set_defaults(func=to_hdf5)
    group = parser_hdf5.add_mutually_exclusive_group(required=True)
    group.add_argument("-bw", action='store_true')
    group.add_argument("-bg", action='store_true')
    parser_hdf5.add_argument("signal")
    parser_hdf5.add_argument("chrom_sizes")
    parser_hdf5.add_argument("bin")
    parser_hdf5.add_argument("hdf5")

    parser_filter = subparsers.add_parser("filter", help="filter help")
    parser_filter.set_defaults(func=hdf5_filter)
    parser_filter.add_argument("signal")
    parser_filter.add_argument("chrom_sizes")
    parser_filter.add_argument("bin")
    parser_filter.add_argument("hdf5")
    parser_filter.add_argument("--include", "-i")
    parser_filter.add_argument("--exclude", "-e")

    parser_corr = subparsers.add_parser("corr", help="corr help")
    parser_corr.set_defaults(func=corr)
    parser_corr.add_argument("list")
    parser_corr.add_argument("chrom_sizes")
    parser_corr.add_argument("bin")
    parser_corr.add_argument("mat")
   
    return parser

 
def main():
    parser = make_parser()
    args = parser.parse_args()
    args.func(args)


if __name__ == "__main__":
    main()
