#!/bin/sh

dir=/home/cppp/CPPP/Repos

cd $dir

if [ ! -d ${dir}/tud-cpp-exercises ]; then
    git clone https://github.com/Echtzeitsysteme/tud-cpp-exercises.git
fi
if [ ! -d ${dir}/tud-cpp-lecture ]; then
    git clone https://github.com/Echtzeitsysteme/tud-cpp-lecture.git
fi

cd tud-cpp-exercises
git pull --depth=1
cd $dir

cd tud-cpp-lecture
git pull --depth=1
cd $dir
