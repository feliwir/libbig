# Purpose of this project
This project is aimed at reading big archives used in several games from EA games. Those archives can be created/edited by a tool 
called "FinalBig". The project is used in my apt_player and might be helpful for others for usage.

# Build status
[![Build Status](https://travis-ci.org/feliwir/libbig.svg?branch=master)](https://travis-ci.org/feliwir/libbig)
[![Build status](https://ci.appveyor.com/api/projects/status/e4rk2pd7dljs1777?svg=true)](https://ci.appveyor.com/project/feliwir/libapt)

# How to build

```sh
$ mkdir build && cd build
$ cmake ..
$ cmake --build .
```

# How to use the library

```c++
#include <libbig/manager.hpp>
#include <iostream>

int main(int argc,char** argv)
{
    //create a manager instance
    libbig::Manager mngr;
    //add an archive
    mngr.AddBig(argv[1]);
    //load an entry from the archive
    std::string entry = mngr.GetEntry(argv[2]);
    //display content to console
    std::cout << entry << std::endl;
    return 0;
}
```

# Game list
- BIG4 format:
BFME, BFME II, BFME II Rise of the Witchking
- BIGF format: 
Command and Conquer
