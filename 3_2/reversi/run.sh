#!/bin/bash

set -o pipefail
set -o errexit

WK_DIR=$(cd `dirname $0`; pwd)

computer="$WK_DIR/bin/computer"
player="$WK_DIR/bin/player"
log_dir="$WK_DIR/log/judge"

map="$WK_DIR/data/map.txt"

cd $WK_DIR

ulimit -s 524288

if [ ! -d $WK_DIR/bin ]; then
    mkdir $WK_DIR/bin
fi

if [ ! -d $WK_DIR/log ]; then
    mkdir $WK_DIR/log
fi

if [ ! -d $WK_DIR/log/judge ]; then
    mkdir $WK_DIR/log/judge
fi

if [ ! -d $WK_DIR/log/player0 ]; then
    mkdir $WK_DIR/log/player0
fi

if [ ! -d $WK_DIR/log/player1 ]; then
    mkdir $WK_DIR/log/player1
fi

if [ ! -f $WK_DIR/code/player.h ]; then
    exit -1
fi

make -s check_computer || exit -1
./bin/check_computer "$map"
make -s check_player || exit -1
./bin/check_player "$map"
make -s computer || exit -1
make -s player || exit -1
./bin/judge --data_file="$map" --player_red="$computer" --player_blue="$player" --log_dir="$log_dir" --visible || exit -1
