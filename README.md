**Warning! This library is in development and is incomplete!**  

# mpl
Simple motion planning library in C++

## Dependencies

### Compiler
This requires c++17. While g++-8 supports c++17 (and is default on Ubuntu 18.04), g++-10 is required and earlier version do not appear to work. To check the version of gcc and g++:
```
g++ --version
gcc --version
```

To update the compiler:
```
sudo apt update
sudo apt install gcc-10
sudo apt install g++-10
```

To switch compiler, you can link to `update-alternative` as follows:
```
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 7
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-7 7
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-10 10
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-10 10
```

To choose the default for `gcc` or `g++`:
```
update-alternatives --config gcc
update-alternatives --config g++
```

### MatPlot++
[Matplot++ v1.0.1](https://github.com/alandefreitas/matplotplusplus/releases) is required for visualization, but in the future, this requirement will be optional. For now, build and install Matplot++ from source. See details [here](https://alandefreitas.github.io/matplotplusplus/integration/install/build-from-source/build-and-install/), or you can build and install as follows:
```
wget https://github.com/alandefreitas/matplotplusplus/archive/v1.0.1.tar.gz
tar -zxvf v1.0.1.tar.gz
cd matplotplusplus-1.0.1
mkdir build
cd build
cmake ..
make
make install
```
