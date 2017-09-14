#!/bin/bash

# This script update this working copy to the most up-to-date state

cd $(dirname $0)
git pull
read -p "Please press any key to continue..."

