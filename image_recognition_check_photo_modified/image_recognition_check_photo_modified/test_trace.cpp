#include "core/core.hpp"
#include "highgui/highgui.hpp"
#include "opencv2/tracking.hpp"

using namespace cv;
using namespace std;

int main()
{
	Rect2d roi;
	Mat frame;
	Ptr<Tracker> tracker = Tracker::create("KCF");
	VideoCapture cap("video.avi");
	int fps = cap.get(CAP_PROP_FPS);
	VideoWriter writer("r.avi", CV_FOURCC('D', 'I', 'V', 'X'), fps, Size(704, 576));
	cap >> frame;
	roi = Rect2d(335, 160, 75, 75);
	tracker->init(frame, roi);
	for (;;)
	{
		cap >> frame;
		tracker->update(frame, roi);
		rectangle(frame, roi, Scalar(255, 0, 0), 2, 1);
		writer << frame;
		imshow("tracker", frame);
		if (waitKey(1) == 27)
		{
			cap.release();
			writer.release();
			break;
		}
	}
	return 0;
}