#!/bin/bash

echo ""
echo "Install basic tools"
sudo apt-get install build-essential checkinstall cmake pkg-config yasm -y

echo ""
echo "Install cppunit dependencies"
sudo apt-get install libcppunit-dev g++-4.9 -y

echo ""
echo "Install opencv"
sudo apt-get install libopencv-dev -y
