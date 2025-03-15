sudo rm -rf build .cache

mkdir build && cd build
cmake _DCMAKE_BUILD_TYPE=Release ..
sudo make -j install
