#!/bin/bash
set -eu

# Allow this script to be invoked from any directory via the relative path to
# this directory.
PARENT_PATH=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )
cd "${PARENT_PATH}"

# Software under test
# The name of the program to be tested.
SUT=lab7

# SUT Constraints
# -n FILENUM
declare -ri FILENUM_MIN=1
declare -ri FILENUM_MAX=99

# Function 'perform_test' stores in this variable the exit code returned from
# the SUT's main() function.
declare -i exit_code=0


##########################################################################
##
##  test_banner "CURRENT_WORKING_DIRECTORY"  "COMMAND_LINE"
##
##########################################################################

function test_banner()
{
    local CURRENT_WORKING_DIRECTORY="${1}"
    local COMMAND_LINE="${2}"

    echo "=========================================================================================="
    echo "> ${CURRENT_WORKING_DIRECTORY}"
    echo "\$ ${COMMAND_LINE}"
    echo "--------------------------------------------------------------------------------------"
}


##########################################################################
##
##  perform_test "COMMAND_LINE"
##
##########################################################################

function perform_test()
{
    local COMMAND_LINE="${1}"

    # Print a pretty banner that visually separates this test from others.
    test_banner "$(pwd -P)" "${COMMAND_LINE}"

set +e
    # Invoke the user's program and record the exit code value returned from
    # the program's main() function.
    eval "${COMMAND_LINE}"
    exit_code=$?
set -e

    # Display the test results
    [[ $exit_code -eq 0 ]] && outcome="PASS" || outcome="FAIL"
    printf "(%s: exit_code=%d, %s)\n" $0 $exit_code $outcome
}


##########################################################################
##
##  main()
##
##########################################################################

# Ensure the SUT is up-to-date
make -C ../ ${SUT}

# Clear the console display
clear

#-------------------------------------------------------------------------
# Test case
# Required command line option '-n FILENUM' is missing
perform_test "../${SUT}"


#-------------------------------------------------------------------------
# Test case
# Required command line option '-n FILENUM' is missing the FILENUM argument.
perform_test "../${SUT} -n"


#-------------------------------------------------------------------------
# Test case
# -n FILENUM argument is invalid (FILENUM < FILENUM_MIN)
perform_test "../${SUT} -n $((FILENUM_MIN - 1))"


#-------------------------------------------------------------------------
# Test case
# -n FILENUM argument is invalid (FILENUM > FILENUM_MAX)
perform_test "../${SUT} -n $((FILENUM_MAX+1))"


#-------------------------------------------------------------------------
# Test cases (multiple)
# Exercise the SUT using the invalid 'raw_data_NN.txt' files provided in folder
# ./raw-data-invalid/, and the valid 'raw_data_NN.txt' files provided in folder
# ./raw-data-valid/.
for data_dir in raw-data-invalid raw-data-valid
do
    pushd "./${data_dir}" >/dev/null

    # Process all of the data files 'raw_data_NN.txt' within the current
    # working directory.
    for rdf in raw_data_*.txt
    do
        # Extract the file number N from the file name: 'raw_data_NN.txt' -> N
        rdf=${rdf#raw_data_}    # Remove prefix 'raw_data_': raw_data_02.txt -> 02.txt
        rdf=${rdf##0}           # Remove leading zero (if present): 02.txt -> 2.txt
        rdf=${rdf%.txt}         # Remove suffix '.txt': 2.txt -> 2

set +e
        # Exercise the SUT using the currently-selected raw data file, and
        # record the exit code returned from SUT's main() function.
        perform_test "../../${SUT} -n ${rdf}"
set -e

    done

    popd >/dev/null
done
