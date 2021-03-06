#!/bin/bash -f
# ****************************************************************************
# Vivado (TM) v2020.2 (64-bit)
#
# Filename    : elaborate.sh
# Simulator   : Xilinx Vivado Simulator
# Description : Script for elaborating the compiled design
#
# Generated by Vivado on Wed Feb 10 14:03:24 CST 2021
# SW Build 3064766 on Wed Nov 18 09:12:47 MST 2020
#
# Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
#
# usage: elaborate.sh
#
# ****************************************************************************
set -Eeuo pipefail
# elaborate design
echo "xelab -wto 9d80afa0b95643f59c84a87333d5f053 --incr --debug typical --relax --mt 8 -L xil_defaultlib -L secureip --snapshot mod_m_up_dn_count_tb_behav xil_defaultlib.mod_m_up_dn_count_tb -log elaborate.log"
xelab -wto 9d80afa0b95643f59c84a87333d5f053 --incr --debug typical --relax --mt 8 -L xil_defaultlib -L secureip --snapshot mod_m_up_dn_count_tb_behav xil_defaultlib.mod_m_up_dn_count_tb -log elaborate.log

