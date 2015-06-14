#!/usr/bin/env bash
#Enable C++11

sudo apt-get update
sudo apt-get install -y wget make build-essential
sudo apt-get install -y python
#echo 2 | sudo update-alternatives --config gcc



#install cmake
if [ "`which cmake`" == "" ] ;
then
dir=$PWD
cd /tmp
wget http://www.cmake.org/files/v3.0/cmake-3.0.2.tar.gz -O cmake.tar.gz
tar -xzf cmake.tar.gz
cd cmake-3.0.2
./bootstrap
make -j5
sudo make install
cd $dir
fi;

#vtk dependencies
sudo apt-get install -y  libX11-dev libXt-dev libgl1-mesa-dev libosmesa6-dev libglu1-mesa-dev git

#install vtk v6.1.0
cd /tmp
git clone https://github.com/Kitware/VTK.git
cd VTK
git checkout tags/v6.1.0
mkdir vtkBuild
cd vtkBuild
cmake -DBUILD-TESTING=OFF ..
make -j10
sudo make install

#include opencv
cd /tmp
git clone https://github.com/Itseez/opencv.git
cd opencv
git checkout tags/2.4.10
mkdir opencvBuild
cd opencvBuild
cmake -DBUILD_TESTS=OFF -DBUILD_PERF_TESTS=OFF ..
make -j5
sudo make install

mkdir /tmp/qt
cd /tmp/qt
#sudo apt-get install -y libxcb1 libxcb1-dev libx11-xcb1 libx11-xcb-dev libxcb-keysyms1 libxcb-keysyms1-dev libxcb-image0 libxcb-image0-dev libxcb-shm0 libxcb-shm0-dev libxcb-icccm4 libxcb-icccm4-dev libxcb-sync0 libxcb-sync0-dev libxcb-render-util0 libxcb-render-util0-dev libxcb-xfixes0-dev libxrender-dev libxcb-shape0-dev libxcb-randr0-dev libxcb-glx0-dev
#sudo apt-get install -y libxkbcommon-dev libudev-dev libwayland-dev libpng12-dev libjpeg8-dev libmtdev-dev autotools-dev autoconf automake bison flex libasound2-dev libxext-dev x11proto-xext-dev libxcursor-dev libxfixes-dev x11proto-fixes-dev libffi-dev libsm-dev libxcomposite-dev
#sudo apt-get install -y libxcb1 libxcb1-dev libx11-xcb1 libx11-xcb-dev libxcb-keysyms1 libxcb-keysyms1-dev libxcb-image0 libxcb-image0-dev libxcb-shm0 libxcb-shm0-dev libxcb-icccm4 libxcb-icccm4-dev libxcb-sync0 libxcb-sync0-dev libxcb-xfixes0-dev libxrender-dev libxcb-shape0-dev libxcb-randr0-dev libxcb-render-util0 libxcb-render-util0-dev libxcb-glx0-dev
sudo apt-get install -y libxcb1 libxcb1-dev libx11-xcb1 libx11-xcb-dev libxcb-keysyms1 libxcb-keysyms1-dev libxcb-image0 libxcb-image0-dev libxcb-shm0 libxcb-shm0-dev libxcb-icccm4 libxcb-icccm4-dev libxcb-sync0-dev libxcb-xfixes0-dev libxrender-dev libxcb-shape0-dev libxcb-randr0-dev libxcb-render-util0 libxcb-render-util0-dev libxcb-glx0-dev
wget http://download.qt.io/official_releases/qt/5.4/5.4.2/single/qt-everywhere-opensource-src-5.4.2.tar.gz
tar -xf qt-everywhere-opensource-src-5.4.2.tar.gz
cd qt-everywhere-opensource-src-5.4.2
./configure -opengl -opensource -confirm-license -release -nomake tests -nomake examples
