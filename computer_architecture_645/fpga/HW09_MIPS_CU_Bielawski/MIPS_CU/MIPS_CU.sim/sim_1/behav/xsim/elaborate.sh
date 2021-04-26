#!/bin/bash -f
# ****************************************************************************
# Vivado (TM) v2020.2 (64-bit)
#
# Filename    : elaborate.sh
# Simulator   : Xilinx Vivado Simulator
# Description : Script for elaborating the compiled design
#
# Generated by Vivado on Mon Apr 19 15:45:32 CDT 2021
# SW Build 3064766 on Wed Nov 18 09:12:47 MST 2020
#
# Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
#
# usage: elaborate.sh
#
# ****************************************************************************
set -Eeuo pipefail
# elaborate design
echo "xelab -wto 555e0205de2e4f348bbd50bbf0992f75 --incr --debug typical --relax --mt 8 -L xil_defaultlib -L secureip --snapshot cu_tb_behav xil_defaultlib.cu_tb -log elaborate.log"
xelab -wto 555e0205de2e4f348bbd50bbf0992f75 --incr --debug typical --relax --mt 8 -L xil_defaultlib -L secureip --snapshot cu_tb_behav xil_defaultlib.cu_tb -log elaborate.log
