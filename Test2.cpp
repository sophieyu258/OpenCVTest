#include "common.h"

// OpenCV includes
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

int main(int argc, const char** argv)
{

	String videoFile = sVideoInMP4;

	VideoCapture cap; // open the default camera
	if (videoFile != "")
		cap.open(videoFile);
	else
		cap.open(0);
	if (!cap.isOpened()) // check if we succeeded
		return -1;

	auto dFrameCount = cap.get(CV_CAP_PROP_FRAME_COUNT);
	std::cout << "Total Frame count: " << dFrameCount << std::endl;
	double dFrame = dFrameCount * 0.1;

	FileStorage fs("test.yml", FileStorage::WRITE);
	fs << "frameCount" << dFrameCount;
	fs << "gotoFrame" << dFrame;
	Mat m1 = Mat::eye(2, 3, CV_32F);
	fs << "matTest" << m1;
	fs.release();

	FileStorage fs2("test.yml", FileStorage::READ);
	Mat m2;
	fs2["matTest"] >> m2;
	std::cout << m2 << std::endl;

	cap.set(CAP_PROP_POS_FRAMES, dFrame);
	//cap.set(CAP_PROP_POS_MSEC, 60000);
	Mat frame;
	cap >> frame; // get a new frame from camera
	imwrite("captured.jpg", frame);
	imshow("FRAME", frame);
	waitKey(0);

	//namedWindow("Video", 1);
	//for (;;)
	//{
	//	Mat frame;
	//	cap >> frame; // get a new frame from camera
	//	imshow("Video", frame);
	//	if (waitKey(30) >= 0) break;
	//}

	// Release the camera or video cap
	cap.release();
	return 0;
}