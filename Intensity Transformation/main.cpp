#include<opencv2\core.hpp>
#include<opencv2\highgui.hpp>
#include<opencv2\imgcodecs.hpp>
#include<opencv2\imgproc.hpp>

using namespace cv;

// define class
class IntensityTransformation {
public:
	// member function for image negative : s = 255 - r
	void negative(Mat scr, Mat &dst) {
		dst = 255 - scr;
	}

	/*
	member function for log transformation : s = c.log(1 + r)
	c = 255/ log(rmax + 1)
	*/
	void log_transformation(Mat scr, Mat &dst) {
		double c;
		double r_min, r_max;

		// determine max value in the input image
		minMaxLoc(scr, &r_min, &r_max);
		c = 255 / log(r_max + 1);
		scr.convertTo(scr, CV_32F);
		scr = scr + 1;
		log(scr, dst);
		dst = c*dst;
		dst.convertTo(dst, CV_8UC1);
	}

	/*
	member function for gamma transformation (power-law transformation) : s = c.r^gamma
	c = 255 / rmax^gamma
	*/
	void gamma_transformation(Mat scr, Mat &dst, double gamma) {
		double c;
		double r_min, r_max;
		minMaxLoc(scr, &r_min, &r_max);
		c = 255 / pow(r_max, gamma);
		scr.convertTo(scr, CV_32F);
		pow(scr, gamma, dst);
		dst = c*dst;
		dst.convertTo(dst, CV_8UC1);
	}
};

int main() {
	Mat img, img_negative, img_log, img_gamma;
	double gamma = 2.5;
	img = imread("airship.jpg", 0);
	IntensityTransformation T1;
	T1.negative(img, img_negative);

	namedWindow("negative", WINDOW_AUTOSIZE);
	namedWindow("original", WINDOW_AUTOSIZE);

	imshow("original", img);
	imshow("negative", img_negative);

	T1.log_transformation(img, img_log);
	namedWindow("log", WINDOW_AUTOSIZE);
	imshow("log", img_log);

	T1.gamma_transformation(img, img_gamma, gamma);
	namedWindow("gamma", WINDOW_AUTOSIZE);
	imshow("gamma", img_gamma);

	waitKey(0);

	return 0;
}