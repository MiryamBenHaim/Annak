#ifndef __images__
#define __images__

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "place.h"
#include "world.h"
#include "square.h"
#include "village.h"
#include "city.h"
#include "car.h"
#include "truck.h"
#include "helicopter.h"

class Images {
public:

    static cv::Mat openMat(std::string path);

    static int sizeSquare;

    static cv::Mat img;

    static cv::Mat originImg;

    static cv::Mat getMat(std::string matName);

    static void fillSquare(int x, int y);

    static void fillOriginSquare(int x, int y);

    static void generateBoardImage();

    static void write(cv::Mat img, std::string whatToWrite, int x, int y);
};

#endif // __images__