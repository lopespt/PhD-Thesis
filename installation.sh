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

#install vtk v6.1.0
cd /tmp
git clone https://github.com/Kitware/VTK.git
cd VTK
git checkout tags/v6.1.0
mkdir vtkBuild
cd vtkBuild
cmake ..
make -j10
sudo make install
