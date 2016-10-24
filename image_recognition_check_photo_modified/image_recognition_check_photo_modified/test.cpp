#include <opencv2\highgui.hpp>
#include <opencv2\opencv.hpp>//imread等cv::的函数//C的库都有cv_开头
#include <opencv2\xfeatures2d\nonfree.hpp>
//#include "opencv2\features2d.hpp"
#include <iostream>
using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

int main()
{
	Mat input1 = imread("IMG_20161019_110136_1.jpg", 1);
	Mat input2 = imread("IMG_20161019_110143.jpg", 1);

	Ptr<SIFT> detector = SiftFeatureDetector::create();
	//SIFT detector;//SIFT类是一个静态类，不能直接使用实例
	//detector.create();

	vector<KeyPoint> keypoint1, keypoint2;

	detector->detect(input1, keypoint1);

	Mat output1;
	drawKeypoints(input1, keypoint1, output1);
	imshow("sift_result1.jpg", output1);
	imwrite("sift_result1.jpg", output1);


	//SiftDescriptorExtractor extractor;//实际上SiftDescriptorExtractor与SiftFeatureDetector是相同的
	detector->detect(input2, keypoint2);

	Mat output2;
	drawKeypoints(input2, keypoint2, output2);
	imshow("sift_result2.jpg", output2);
	imwrite("sift_result2.jpg", output2);


	Mat descriptor1, descriptor2;
	detector->compute(input1, keypoint1, descriptor1);
	detector->compute(input2, keypoint2, descriptor2);

	BFMatcher matcher(NORM_L2);

	vector<DMatch> matches;
	Mat img_matches;



	matcher.match(descriptor1, descriptor2, matches);

	drawMatches(input1, keypoint1, input2, keypoint2, matches, img_matches);
	imshow("matches", img_matches);
	imwrite("matches.jpg", img_matches);

	waitKey();


}