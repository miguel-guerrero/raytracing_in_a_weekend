#!/bin/bash

EZ="EZ-Draw-1.2a"

if [ -d "$EZ" ]; then
    echo "EZ-Draw appears to be downloaded"
else
    wget https://pageperso.lis-lab.fr/~edouard.thiel/${EZ}.tgz
    tar xvfz ${EZ}.tgz
    rm -f ${EZ}.tgz
fi
