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

//480x360 video dimension
using namespace std;
using namespace cv;
using namespace filesystem;

static char getValue(int pVal) {
	if (pVal < 28) { return ' '; }
	if (pVal < 38) { return '.'; }
	if (pVal < 57) { return '-'; }
	if (pVal < 76) { return '+'; }
	if (pVal < 95) { return '*'; }
	if (pVal < 114) { return 'w'; }
	if (pVal < 133) { return 'G'; }
	if (pVal < 152) { return 'H'; }
	if (pVal < 171) { return 'M'; }
	if (pVal < 190) { return '#'; }
	if (pVal < 209) { return '&'; }
	if (pVal < 228) { return '%'; }
	if (pVal < 256) { return '@'; }
	
	return ' ';
}

int  main() {

	system("pause");

	const std::filesystem::path sandbox{ "../Project_Badapple/final"};

	int checkframe = 0;
	//get the number of frames
	for (auto const& dir_entry : std::filesystem::directory_iterator{ "badapple"}) {

		COORD position = { 0, 0 };
		HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(output, position);
		std::cout << "--------------fetching frames--------------" << endl;
		std::cout << "No. of frames:" + to_string(++checkframe) << std::endl;
	}
	std::cout << "Done" << endl;

	//Convert the frame to ascii art(.txt) files
	if (!std::filesystem::is_directory("final(156x40)")) {
		std::filesystem::create_directories("final(156x40)");
		string path = "";
		Mat img{};
		Mat imgGrey{};
		Mat imgResize{};
		POINT p;

		string message = "";
		int pixelvalue = 0;
		int Convertframe = 0;
		GetCursorPos(&p);
		bool stop = 1;
		while (Convertframe < checkframe) {

			message = "";
			Convertframe++;

			//changing image resolution and converting to GScale
			path = "badapple/" + to_string(Convertframe) + ".png";
			img = imread(path);
			cvtColor(img, imgGrey, COLOR_BGR2GRAY);
			resize(imgGrey, imgResize, Size(156, 40));//156 46 old & 120x30

			COORD position = { 0,0 };
			HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleCursorPosition(output, position);



			std::cout << "--------------Converting Frames--------------" << endl;
			path = "final(156x40)/" + to_string(Convertframe) + ".txt";
			ofstream file(path);

			for (int i = 0; i < imgResize.rows; i++) {
				for (int j = 0; j < imgResize.cols; j++) {

					pixelvalue = (int)imgResize.at<uchar>(i, j);
					message += getValue(pixelvalue);
				}
				message += '\n';
			}

			std::cout << "frame to ascii: " + to_string(Convertframe) + " converted" << endl;
			file << message;
			if (stop) {
				system("cls");
				stop = 0;
			}
			file.close();
		}
	}


	std::cout << "--------------Press Anything To Play--------------" << endl;
	system("pause");
	int writeframe = 0;
	string badapple = "";

	using namespace std::chrono;
	using dsec = duration<double>;

	auto invFpsLimit = duration_cast<system_clock::duration>(dsec{ 1.0 / 30.0 });
	auto m_BeginFrame = system_clock::now();
	auto m_EndFrame = m_BeginFrame + invFpsLimit;
	unsigned frame_count_per_second = 0;
	auto prev_time_in_seconds = time_point_cast<seconds>(m_BeginFrame);
	while (writeframe < checkframe)
	{
		// Do drawing work ...
		++writeframe;

		COORD position = { 0,0 };
		HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(output, position);

		ifstream read("final(156x40)/" + to_string(writeframe) + ".txt");
		stringstream buffer;
		buffer << read.rdbuf();
		badapple = buffer.str();

		cout << badapple << "Frame Count:" << writeframe;


		
		read.close();
		// This part is just measuring if we're keeping the frame rate.
		// It is not necessary to keep the frame rate.
		auto time_in_seconds = time_point_cast<seconds>(system_clock::now());
		++frame_count_per_second;
		if (time_in_seconds > prev_time_in_seconds)
		{
			frame_count_per_second = 0;
			prev_time_in_seconds = time_in_seconds;
		}

		// This part keeps the frame rate.
		std::this_thread::sleep_until(m_EndFrame);
		m_BeginFrame = m_EndFrame;
		m_EndFrame = m_BeginFrame + invFpsLimit;
	}


	
	std::cout << ":D - Wanoh";
	Sleep(3000);

	return 0;
}

//" .-+*wGHM#&%@"