# - Find CCFITS

# Defines the following variables:
# CCFITS_INCLUDE_DIRS    - Location of CCFITS's include directory.
# CCFITS_LIBRARIES       - Location of CCFITS's libraries
# CCFITS_FOUND           - True if CCFITS has been located

#=============================================================================
# Copyright 2012 Brian Kloppenborg
#
#  This code is licensed under the MIT License.  See the FindMULTINEST.cmake script
#  for the text of the license.
#
# The MIT License
#
# License for the specific language governing rights and limitations under
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
#=============================================================================

FIND_PACKAGE(CFITSIO REQUIRED)

FIND_PATH(CCFITS_INCLUDE_DIR CCfits.h
    HINTS /usr/include/CCfits)

FIND_LIBRARY(CCFITS_LIBRARY NAMES libCCfits.so libCCfits.a)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CCFITS DEFAULT_MSG CCFITS_LIBRARY CCFITS_INCLUDE_DIR)

# Export the names:
IF(CCFITS_FOUND AND CFITSIO_FOUND)
    SET(CCFITS_INCLUDE_DIRS ${CCFITS_INCLUDE_DIR} ${CFITSIO_INCLUDE_DIRS})
    SET(CCFITS_LIBRARIES ${CCFITS_LIBRARY} ${CFITSIO_LIBRARIES})
ENDIF(CCFITS_FOUND AND CFITSIO_FOUND)

MARK_AS_ADVANCED(CCFITS_LIBRARY CCFITS_INCLUDE_DIR CCFITS_INCLUDE_DIRS CCFITS_LIBRARIES)
