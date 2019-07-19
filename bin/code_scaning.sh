#!/usr/bin/env bash
# !/bin/bash

function scan_dir(){
  for tmp_name in `ls ${1}`; do
    file_name=$1"/"${tmp_name}
    echo ${file_name}
    if [[ -d ${file_name} ]]; then
        python cpplint.py ${file_name}/*
    elif [["${file_name##*.}"="cpp"]];then
        python cpplint.py ${file_name}
    fi
  done
}
dir_name="../src"
scan_dir ${dir_name}
