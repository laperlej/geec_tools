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
import os
import os.path
import subprocess

def get_corr_vals(mat):
    mat.readline()
    vals = []
    for line in mat:
        vals + line.split()[1:]

def launch_to_hdf5(exe_path, sig_path, chrom_path, resolution, hdf5_path):
    command = [exe_path, "hdf5", "-bw", sig_path, chrom_path, resolution, hdf5_path]
    logging.debug(command)
    subprocess.call(command)

def launch_filter(exe_path, hdf5_path, chrom_path, resolution, filtered_path, include_path=None, exclude_path=None):
    command = [exe_path, "filter", hdf5_path, chrom_path, resolution, filtered_path]
    logging.debug(command)
    subprocess.call(command)

def launch_corr(exe_path, list_path, chrom_path, resolution, mat_path):
    command = [exe_path, "correlation", list_path, chrom_path, resolution, mat_path]
    logging.debug(command)
    subprocess.call(command)

def main():
    parser = argparse.ArgumentParser(description='A test script for epigeec')
    parser.add_argument("-v", "--verbose", help="enable debug logs", action="store_true")

    args = parser.parse_args()
    if args.verbose:
        logging.basicConfig(level=logging.DEBUG)

    self_path = os.path.realpath(__file__)

    test_dir = os.path.dirname(self_path)
    files_dir = os.path.join(test_dir, "files")
    sig_dir = os.path.join(files_dir, "signal")
    hdf5_dir = os.path.join(files_dir, "hdf5")
    filtered_dir = os.path.join(files_dir, "filtered")
    epi_dir = os.path.dirname(test_dir)
    bin_dir = os.path.join(epi_dir, "bin")
    resource_dir = os.path.join(epi_dir, "resource")
    chrom_dir = os.path.join(resource_dir, "chrom_sizes")

    epigeec_path = os.path.join(epi_dir, "python", "core", "main.py")
    list_path = os.path.join(test_dir, "test_list.txt")

    sig_path = [os.path.join(sig_dir, "d9f18e91644bacfee3669d577b661d15"),
                   os.path.join(sig_dir, "fd85fe6672c629a116a9b6131883a60b")]
    hdf5_path = [os.path.join(hdf5_dir, "d9f18e91644bacfee3669d577b661d15"),
                 os.path.join(hdf5_dir, "fd85fe6672c629a116a9b6131883a60b")]
    filtered_path = [os.path.join(filtered_dir, "d9f18e91644bacfee3669d577b661d15"),
                     os.path.join(filtered_dir, "fd85fe6672c629a116a9b6131883a60b")]
    mat_path = os.path.join(files_dir, "test.mat")
    chrom_path = os.path.join(chrom_dir, "saccer3.can.chrom.sizes")
    resolution = "10000"

    with open(list_path, 'w') as test_list:
        test_list.write("{0}\n{1}".format(filtered_path[0], filtered_path[1]))

    launch_to_hdf5(epigeec_path, sig_path[0], chrom_path, resolution, hdf5_path[0])
    launch_to_hdf5(epigeec_path, sig_path[1], chrom_path, resolution, hdf5_path[1])
    launch_filter(epigeec_path, hdf5_path[0], chrom_path, resolution, filtered_path[0])
    launch_filter(epigeec_path, hdf5_path[1], chrom_path, resolution, filtered_path[1])

    launch_corr(epigeec_path, list_path, chrom_path, resolution, mat_path)

    result = os.path.join(files_dir, "test.mat")
    expected = os.path.join(files_dir, "expected")
    if get_corr_vals(open(result)) == get_corr_vals(open(expected)):
        print "Success"
    else:
        print "Failed"

    os.remove(hdf5_path[0])
    os.remove(hdf5_path[1])
    os.remove(filtered_path[0])
    os.remove(filtered_path[1])
    os.remove(list_path)
    os.remove(mat_path)


if __name__ == "__main__":
    main()
