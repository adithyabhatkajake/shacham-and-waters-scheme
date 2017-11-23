#!/bin/bash

if [ ! `id -u` -eq 0 ];
then 
    echo "Must be run as root!" > /dev/stderr
    exit 1
fi

if [ ! -d deps ];
then
    mkdir deps
fi

cd deps

if [ ! -d reed-solomon ];
then
    git clone https://github.com/tierney/reed-solomon.git
fi     

cd reed-solomon 

./autogen.sh && ./configure && make #&& make install 

if [ ! $? -eq 0 ];
then
    echo "Unable to configure reed solomon library" > /dev/stderr
    exit 2
fi

cd -

if [ ! -d pbc-0.5.14 ];
then 
    if [ ! -f pbc-0.5.14.tar.gz ];
    then
        wget https://crypto.stanford.edu/pbc/files/pbc-0.5.14.tar.gz 
        tar -xf pbc-0.5.14.tar.gz 
    fi
fi

cd pbc-0.5.14 

./configure && make #&& make install 

if [ ! $? -eq 0 ];
then
    echo "Unable to configure PBC library" > /dev/stderr
    exit 3
fi

cd -