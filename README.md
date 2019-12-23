# tfObjectDetection
This project is an attempt to build an object detection system using Tensorflow for C++ and OpenCV. The project is built for linux, specifically pop os! v18.04. The installation process should be identical for Ubuntu 18.04. 

## Dependencies
1. Tensorflow: Installed from [here](https://www.tensorflow.org/install/lang_c)
2. OpenCV: Installed by running sudo apt-get install libopencv-dev

## Running
To run the testing file, you run:
g++ testing.cpp -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_videoio
