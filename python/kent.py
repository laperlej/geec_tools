import subprocess
import config
import utils
import os.path

def big_wig_info(path):
    """
    sample ouput:
        version: 4
        isCompressed: yes
        isSwapped: 0
        primaryDataSize: 18,938,073
        primaryIndexSize: 210,968
        zoomLevels: 9
        chromCount: 84
        basesCovered: 652,348,431
        mean: 6.035622
        min: 1.140000
        max: 285.989990
        std: 25.408247
    """
    try:
        info = subprocess.check_output([config.BWI, path], stderr=subprocess.STDOUT)
    except subprocess.CalledProcessError:
        print("BWINFO error : {0}".format(path))
        info = None
    return info

def bwbgbw(bw_path1, bg_path, bw_path2, chrom_size):
    if os.path.exists(bw_path2):
        return 0

    if not os.path.exists(bg_path):
        return_code = bw_to_bg(bw_path1, bg_path)
        if return_code:
            return 1

    return_code = bg_to_bw(bg_path, bw_path2, chrom_size)
    if return_code:
        return 1

    return 0

def bw_to_bg(bw_path, bg_path):
    try:
        info = subprocess.check_output([config.BW_TO_BG,
                                        bw_path,
                                        bg_path],
                                        stderr=subprocess.STDOUT)
        return 0
    except subprocess.CalledProcessError:
        print("BW2BG error : {0}".format(bw_path))
        return 1

def bg_to_bw(bg_path, bw_path, chrom_size):
    print ' '.join([config.BG_TO_BW, bg_path, chrom_size, bw_path])
    try:
        info = subprocess.check_output([config.BG_TO_BW,
                                        bg_path,
                                        chrom_size,
                                        bw_path],
                                        stderr=subprocess.STDOUT)
        return 0
    except subprocess.CalledProcessError:
        print("BG2BW error : {0}".format(bw_path))
        return 1
