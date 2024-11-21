#ifndef __MOUSE_EVENTS__
#define __MOUSE_EVENTS__

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "capacities.h"
#include "car.h"
#include "city.h"
#include "configuration.h"
#include "helicopter.h"
#include "images.h"
#include "movies.h"
#include "person.h"
#include "place.h"
#include "resources.h"
#include "road.h"
#include "square.h"
#include "tile.h"
#include "truck.h"
#include "vehicle.h"
#include "village_city.h"
#include "village.h"
#include "world.h"

#include "input_functions.h"

void showResources(cv::Point points[]);

void moveTheMovies(cv::Point points[]);

void CallBackFunc(int event, int x, int y, int flags, void* userdata);

#endif // __MOUSE_EVENTS__