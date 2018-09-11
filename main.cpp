#include <math.h>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

Mat fisheye2pano(const Mat& img) {

    int Cx = img.cols / 2;
    int Cy = img.rows / 2;
    // iner and outer radius
    float R1, R2;
    R1 = img.cols / 6.0;
    R2 = img.cols / 2.0;

    // source and destination image sizes
    int Wd = 2.0 * ((R2 + R1) / 2) * M_PI;
    int Hd = R2 - R1;
    int Ws = img.cols;
    int Hs = img.rows;
    Mat pano(Hd, Wd, img.type());

    // specify maps for transforming the source image
    Mat xmap(pano.size(), CV_32FC1);
    Mat ymap(pano.size(), CV_32FC1);
    for (int i = 0; i < pano.rows; i++) {
        float* _xmap = xmap.ptr<float>(i);
        float* _ymap = ymap.ptr<float>(i);
        for (int j = 0; j < pano.cols; j++) {
            // 	[r theta] coordinates in the fisheye image
            float r = float(i) / float(Hd) * (R2 - R1) + R1;
            float theta = float(j) / float(Wd) * 2.0 * M_PI;
            *_xmap++ = static_cast<float>(Cx + r * sin(theta));
            *_ymap++ = static_cast<float>(Cy + r * cos(theta));
        }
    }

    // apply a generic geometrical transformation
    remap(img, pano, xmap, ymap, CV_INTER_LINEAR);
    imshow("remap", pano);
    waitKey();
    return pano;
}

int main() {
    Mat img = imread("fisheye3.jpg");
    fisheye2pano(img);

    return 0;
}
