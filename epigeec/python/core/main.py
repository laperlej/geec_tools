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

import parser
import sys

from error import ValidationError, MultiError

 
def main():
    try:
        epigeec_parser = parser.make_parser()
        args = epigeec_parser.parse_args()
        args.func(args)
    except (ValueError, IOError, ValidationError, MultiError) as e:
        sys.exit(e)


if __name__ == "__main__":
    main()
