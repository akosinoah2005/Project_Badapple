#include "includes.h"

//480x360 video dimension
//Ñ@#W$9876543210?!abc;:+=-,._ 
//string Colors = " .-+*wGHM#&%@"; old

static char getValue(int pVal) {
	const double denumerator = 255.0 / 20.0;
	int density = pVal/ denumerator;	

	string Colors = " _.,-=+:;cba!?0123456789$W#@";
	
	return Colors[density==255?density-1:density];
}

int  main() {
	
	string file_name = " ";
	do {
		system("cls");

		cout << "Provide a video file(drag/type): ";
		file_name = " ";
		getline(cin, file_name);

		if (!exists(file_name)) {
			cout << "File does not exist";
			Sleep(1000);
		}
		

	} while (!exists(file_name));
	
	
	VideoCapture cap(file_name);
	
	//get max frames
	double maxFrames = cap.get(CAP_PROP_FRAME_COUNT);;
	string message = "";
	int pixelvalue = 0;
	
	Mat img{};
	Mat imgGrey{};
	Mat imgResize{};
	

	using dsec = duration<double>;
	auto invFpsLimit = duration_cast<system_clock::duration>(dsec{ 1.0 / 30.0 });
	auto m_BeginFrame = system_clock::now();
	auto m_EndFrame = m_BeginFrame + invFpsLimit;
	unsigned frame_count_per_second = 0;
	auto prev_time_in_seconds = time_point_cast<seconds>(m_BeginFrame);

	for (int i = 0; i < maxFrames;i++) {
		

		SetConsoleCursorPosition(output, position);
	
		cap.read(img);
		
		
		cvtColor(img, imgGrey, COLOR_BGR2GRAY);
		resize(imgGrey, imgResize, Size(156, 35));//156 46 old & 120x30
	
			for (int k = 0; k < imgResize.rows; k++) {
				for (int j = 0; j < imgResize.cols; j++) {
					//getPixelValue
					pixelvalue = (int)imgResize.at<uchar>(k, j);
					message += getValue(pixelvalue);
				}
				message += '\n';
			}

			std::cout << message<<"frame to ascii: " + to_string(i);
			
			message = "";
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