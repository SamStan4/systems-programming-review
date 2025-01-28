#!/usr/bin/env bash

if [ -f exe ]; then
    rm exe
fi

gcc main.c -o exe

if [ -f exe ]; then
    ./exe
    rm exe
fi