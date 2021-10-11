# rscreatelg - Realsense Video Creator for Looking Glass Portrait

**Author:** Alessandro de Oliveira Faria (A.K.A. CABELO)

## About the project

This software was created for generate video holographic for the Looking Glass holographic displays. I am not associated with the Looking Glass Factory and devoloped in my freetime this project for to use Looking Glass in GNU/lINUXI. I use the opencv library and admire camera realsense as well as the amazing new holographic display technology created by [Looking Glass Factory] (https://lookingglassfactory.com/).

[![Donate](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=EW4QKQ89PLRLJ)

## About the Repository
This repository is to provide an alpha version of the project for anyone who wants to try it out. Please be aware that this alpha version may contain errors. If you find a bug or have any ideas to improve it, open an issue in this repository with a detailed description. Thanks for your help and have fun mixing your holograms! 


## Building 

### Dependencies

Below are the dependencies of this project: 

1. [librealsense](https://github.com/IntelRealSense/librealsense)
1. [libopencv](https://github.com/opencv/opencv/)

### Clone the project

Clone the repository at desired location:

``` bash
# git clone https://github.com/cabelo/rscreatelg
```

### Build the project

Now execute 


``` bash
$ cd rscreatelg
$ /usr/bin/c++  main.cpp `pkg-config --cflags opencv4` `pkg-config --libs opencv4`  -lrealsense2 -o rscreatelg
$ ./rscreatelg

```

### To Do

- [x] Push first commit to GitHub
- [ ] Better code in c++
- [ ] Depth Cleaning
- [ ] Config resolution
- [ ] Parameterize file name
- [ ] Select algorithm of semantic segmantation
- [ ] Create package .rpm and .deb
- [ ] Create documantation 
- [ ] Create HTML page
- [ ] Broadcast via network in real time


![](img/pg01.jpg)

![](img/pg02.jpg)


### The final result

Bellow an example created in my machine with OpenSUSE Leap 15.3.

contact : Alessandro de Oliveira Faria (A.K.A.CABELO) cabelo@opensuse.org

[![Demonstration](http://img.youtube.com/vi/a8YUKWCKe4o/0.jpg)](http://www.youtube.com/watch?v=a8YUKWCKe4o "Video created in Linux to Looking Glass")
