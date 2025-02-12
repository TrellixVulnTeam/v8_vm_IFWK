#!/bin/bash
#
# Copyright 2018 the MetaHash project authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

# Command line parameters:
# The only one parameter is a folder for running test (must be)
# e.g. run-tests.bat out\win\debug_x64_sharedlibs

# Export depot_tools
. $(dirname "$0")/export-depot-tools.sh

# Check and get depots_tools
$(dirname "$0")/check-and-get-depot-tools.sh
errcode=$?
if [ $errcode -ne 0 ]; then
  echo "------- Running of tests failed ($(date '+%d.%m.%Y %H:%M:%S')) -------"
  exit $errcode
fi

# Go into a root folder of source codes
cd $(dirname "$0")/../../../..

echo "Run tests (folder: $1; $(date '+%d.%m.%Y %H:%M:%S'))..."

# Run tests
python tools/run-tests.py --outdir $1
errcode=$?
if [ $errcode -ne 0 ]; then
  echo "------- Running of tests failed ($(date '+%d.%m.%Y %H:%M:%S')) -------"
  exit $errcode
fi

echo "------- Running of tests is successful ($(date '+%d.%m.%Y %H:%M:%S')) -------"

exit 0
