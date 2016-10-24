#include <iostream>
#include <opencv2/opencv.hpp>  //ͷ�ļ�
#include <opencv2/xfeatures2d.hpp>
using namespace cv;  //����cv�����ռ�
using namespace std;

int main()
{
	//Create SIFT class pointer
	Ptr<Feature2D> f2d = xfeatures2d::SIFT::create();
	//����ͼƬ
	Mat img_1 = imread("IMG_20161019_110136_1.jpg");
	Mat img_2 = imread("IMG_20161019_110143.jpg");
	//Detect the keypoints
	vector<KeyPoint> keypoints_1, keypoints_2;
	f2d->detect(img_1, keypoints_1);
	f2d->detect(img_2, keypoints_2);
	//Calculate descriptors (feature vectors)
	Mat descriptors_1, descriptors_2;
	f2d->compute(img_1, keypoints_1, descriptors_1);
	f2d->compute(img_2, keypoints_2, descriptors_2);
	//Matching descriptor vector using BFMatcher
	BFMatcher matcher;
	vector<DMatch> matches;
	matcher.match(descriptors_1, descriptors_2, matches);
	//����ƥ����Ĺؼ���
	Mat img_matches;
	drawMatches(img_1, keypoints_1, img_2, keypoints_2, matches, img_matches);
	imshow("��matchͼ��", img_matches);
	//�ȴ����ⰴ������
	waitKey(0);
}