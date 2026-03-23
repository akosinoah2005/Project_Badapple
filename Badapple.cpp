#include "includes.h"

//480x360 video dimension


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
void ConvertFrames(string folder,int checkframe) {
	
		std::filesystem::create_directories(folder);
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

			message = " ";
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
			path = folder + "/" + to_string(Convertframe) + ".txt";
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

void Display(string folder) {

	system("cls");
	int checkframe = 0;
	for (auto const& dir_entry : std::filesystem::directory_iterator{ "badapple" }) {

		COORD position = { 0, 0 };
		HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(output, position);
		std::cout << "--------------fetching frames--------------" << endl;
		std::cout << "No. of frames:" + to_string(++checkframe) << std::endl;
	}
	std::cout << "Done" << endl;


	int writeframe = 0;
	string badapple = "";


	using dsec = duration<double>;

	auto invFpsLimit = duration_cast<system_clock::duration>(dsec{ 1.0 / 30.0 });
	auto m_BeginFrame = system_clock::now();
	auto m_EndFrame = m_BeginFrame + invFpsLimit;
	unsigned frame_count_per_second = 0;
	auto prev_time_in_seconds = time_point_cast<seconds>(m_BeginFrame);
	while (writeframe < checkframe)
	{
		++writeframe;

		COORD position = { 0,0 };
		HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(output, position);

		ifstream read(folder + "/" + to_string(writeframe) + ".txt");
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
		resize(imgGrey, imgResize, Size(156, 46));//156 46 old & 120x30
	
			for (int k = 0; k < imgResize.rows; k++) {
				for (int j = 0; j < imgResize.cols; j++) {
					//getPixelValue
					pixelvalue = (int)imgResize.at<uchar>(k, j);
					message += getValue(pixelvalue);
				}
				message += '\n';
			}

			std::cout << message<<"frame to ascii: " + to_string(i);
			message = " ";

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