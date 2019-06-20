#!/bin/bash

COMPILE_FLAGS='-std=c++11 -fsplit-stack -O2'

GLOBAL_INCLUDE_REGEX="^ *#include *<.*> *$"
APP_SOURCE=main.cpp
CHECKER_SOURCE=checker.cpp
SUBMIT_SOURCE=submit.cpp
APP_NAME=a.out
CHEKER_NAME=b.out
CHEKER_ITERATIONS=10000
CHEKER_PIPE_NAME=checker_fifo
APP_OUTPUT=output.txt
APP_INPUT=input.txt
MEM_LIMIT=4048000
DELIM='-------------------------------------------'

FileRemoveIfExists() {
    if [ -f $1 ]
    then
        printf 'Removing %s\n' $1
        rm $1
    fi
}

FileCreateIfAbsent() {
    if ! [ -f $1 ]
    then
        printf 'Creating %s\n' $1
        touch $1
    fi
}

CreateIOFiles() {
    FileCreateIfAbsent $APP_INPUT
    FileCreateIfAbsent $APP_OUTPUT
}


DoRunApp() {
    if ! [ -f $APP_SOURCE ]
    then
        printf 'Missing source code file %s!\n' $APP_SOURCE
        return
    fi
    CreateIOFiles
    FileRemoveIfExists $APP_NAME

    ulimit -v $MEM_LIMIT
    printf 'Running preprocessor for %s\n' $APP_SOURCE
    grep -E "$GLOBAL_INCLUDE_REGEX" $APP_SOURCE > $SUBMIT_SOURCE
    echo '' >> $SUBMIT_SOURCE
    grep -E -v "$GLOBAL_INCLUDE_REGEX" $APP_SOURCE | g++ -E - >> $SUBMIT_SOURCE
    rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi

    printf 'Building %s\n' $APP_SOURCE
    g++ $COMPILE_FLAGS $APP_SOURCE -o $APP_NAME
    rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi

    printf 'Running %s\n' $APP_NAME 
    local STARTTIME=$(date +%s%N)
    ./$APP_NAME < $APP_INPUT > $APP_OUTPUT 
    local ENDTIME=$(date +%s%N)
    printf 'Run time: %d ms\n' $(( $(($ENDTIME - $STARTTIME)) / 1000000 ))
    printf '%s stdout:\n' $APP_NAME
    printf '%s\n' $DELIM 
    cat $APP_OUTPUT 
    printf '\n%s\n' $DELIM 
}

DoRunIneractive() {
    FileRemoveIfExists $APP_NAME

    ulimit -v $MEM_LIMIT
    printf 'Building %s\n' $APP_SOURCE
    g++ $COMPILE_FLAGS $APP_SOURCE -o $APP_NAME
    rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi

    printf 'Building %s\n' $CHEKER_NAME
    g++ $COMPILE_FLAGS $CHECKER_SOURCE -o $CHEKER_NAME
    rc=$?; if [[ $rc != 0 ]]; then exit $rc; fi

    if [[ ! -p $CHEKER_PIPE_NAME ]]
    then
        printf 'Creating %s\n' $CHEKER_PIPE_NAME
        mkfifo $CHEKER_PIPE_NAME
    fi

    printf 'Running app along with checker\n' 
    printf '%s\n' $DELIM 
    for ((i=0; i<CHEKER_ITERATIONS; i++))
    do
        (./$APP_NAME < $CHEKER_PIPE_NAME) | (./$CHEKER_NAME > $CHEKER_PIPE_NAME)
        rc=$?; if [[ $rc != 0 ]]; then break; fi
        printf '%s\n' $DELIM 
    done
}

DoClear() {
    FileRemoveIfExists $APP_NAME
    FileRemoveIfExists $APP_INPUT
    FileRemoveIfExists $APP_OUTPUT
    FileRemoveIfExists $APP_SOURCE
}

DoCreate() {
    CreateIOFiles
    if [ -f $APP_SOURCE ]
    then
        printf 'Source code file %s already exists\n' $APP_SOURCE
    else
        FileCreateIfAbsent $APP_SOURCE
        cp ../Templates/main.cpp $APP_SOURCE
    fi
}

DoReset() {
    DoClear
    DoCreate
}

case $1 in
    run|'')
        DoRunApp
        ;;
    clear)
        DoClear
        ;;
    create)
        DoCreate
        ;;
    reset)
        DoReset
        ;;
    interactive)
        DoRunIneractive
        ;;
    *)
        printf '%s: Unknown command\n' "$1" 
        ;;
esac
