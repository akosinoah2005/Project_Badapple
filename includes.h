#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
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

void ConvertFrames(string folder, int checkframe);
char getValue(int pVal);
void Display(string folder);
COORD position = { 0, 0 };
HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);