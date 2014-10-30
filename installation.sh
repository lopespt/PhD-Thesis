#Enable C++11

echo 2 | sudo update-alternatives --config gcc
#Install cmake
dir=$PWD
cd /tmp
wget http://www.cmake.org/files/v3.0/cmake-3.0.2.tar.gz -O cmake.tar.gz
tar -xzf cmake.tar.gz
cd cmake-3.0.2
./bootstrap
make -j5
sudo make install
cd $dir

#vtk dependencies
sudo apt-get install libX11-dev libXt-dev libgl1-mesa-dev libosmesa6-dev libglu1-mesa-dev


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
