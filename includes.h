#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <fstream>
#include <Windows.h>
#include <string>
#include <filesystem>
#include <sstream>
#include <thread>
#include <chrono>
using namespace std;
using namespace cv;
using namespace filesystem;
using namespace std::chrono;

char getValue(int pVal);
COORD position = { 0, 0 };
HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);