#include "mouse_events.h"
using namespace std;
using namespace cv;

void showResources(Point points[])
{
    Point firstPoint = points[0], secondPoint = points[1];

    int i, endi, j, endj;
    if (firstPoint.y < secondPoint.y) {
        i = firstPoint.y;
        endi = secondPoint.y;
    }
    else {
        i = secondPoint.y;
        endi = firstPoint.y;
    }
    if (firstPoint.x < secondPoint.x) {
        j = firstPoint.x;
        endj = secondPoint.x;
    }
    else {
        j = secondPoint.x;
        endj = firstPoint.x;
    }

    i = i / Images::sizeSquare;
    endi = endi / Images::sizeSquare;
    j = j / Images::sizeSquare;
    endj = endj / Images::sizeSquare;


    Resources tempRes;
    for (; i <= endi; i++) {
        for (int tempJ = j; tempJ <= endj; tempJ++) {

            shared_ptr<Vehicle> v = World::board[i][tempJ].vehicle;

            if (World::board[i][tempJ].person != nullptr) {
                tempRes = tempRes + World::board[i][tempJ].person->r;
                tempRes.res[4]++;
            }
                
            else if (v.get() != nullptr) {

                if (World::board[i][tempJ].dist == -1) {

                    tempRes = tempRes + World::board[i][tempJ].place.get()->r;

                    string type;
                    if (dynamic_cast<Helicopter*>(v.get()))
                        type = "Helicopter";
                    else if (dynamic_cast<Car*>(v.get()))
                        type = "Car";
                    else if (dynamic_cast<Truck*>(v.get()))
                        type = "Truck";

                    Position size = Configuration::conf["Sizes"][type];

                    for (int a = i; a < i + size.second; a++) {
                        for (int b = tempJ; b < tempJ + size.first; b++) {
                            if (a == i && b == tempJ)
                                continue;
                            World::board[a][b].dist++;
                        }
                    }
                }
                else {
                    World::board[i][tempJ].dist--;
                }
            }

            if (dynamic_cast<VillageCity*>(World::board[i][tempJ].place.get())) {

                if (World::board[i][tempJ].dist == -1) {

                    tempRes = tempRes + World::board[i][tempJ].place.get()->r;

                    string type;
                    if (dynamic_cast<Village*>(World::board[i][tempJ].place.get()))
                        type = "Village";
                    else if (dynamic_cast<City*>(World::board[i][tempJ].place.get()))
                        type = "City";

                    Position size = Configuration::conf["Sizes"][type];

                    for (int a = i; a < i + size.second; a++) {
                        for (int b = tempJ; b < tempJ + size.first; b++) {
                            if (a == i && b == tempJ ||
                                World::board[i][tempJ].place.get() != World::board[a][b].place.get())
                                continue;
                            World::board[a][b].dist++;
                        }
                    }
                }
                else {
                    World::board[i][tempJ].dist--;
                }
            }
            else if (dynamic_cast<Tile*>(World::board[i][tempJ].place.get())) {
                if (World::board[i][tempJ].dist == -1) {

                    tempRes = tempRes + World::board[i][tempJ].place.get()->r;

                    Position size = Configuration::conf["Sizes"]["Tile"];

                    for (int a = i; a < i + size.second; a++) {
                        for (int b = tempJ; b < tempJ + size.first; b++) {
                            if (a == i && b == tempJ || 
                                World::board[i][tempJ].place.get() != World::board[a][b].place.get())
                                continue;
                            World::board[a][b].dist++;
                        }
                    }
                }
                else {
                    World::board[i][tempJ].dist--;
                }
            }
        }
    }

    
    Mat resImg(Mat(6 * Images::sizeSquare, 6 * Images::sizeSquare, CV_8UC3));
    resImg = cv::Scalar(190, 215, 216);
    Images::write(resImg, "Resources:", 1 * (Images::sizeSquare / 20), 12 * (Images::sizeSquare / 20));
    
    int index = 0;
    auto arr = Configuration::conf["ResourceTypes"];
    for (auto& elem : arr) {
        string s = string(elem);
        Images::write(resImg, string(elem) + " " + to_string(tempRes.res[index++]), 1 * (Images::sizeSquare / 20), 5 * (Images::sizeSquare / 6) + index * 20);
    }

    Mat tempImg = Images::img.clone();

    Rect tempRect(0, 0, resImg.cols, resImg.cols);


    resImg.copyTo(tempImg(tempRect));
    imshow("Board", tempImg);
    waitKey(0);
}

void moveTheMovies(Point points[])
{
    Point firstPoint = points[0], secondPoint = points[1], destPoint = points[2];

    int i, endi, j, endj;
    if (firstPoint.y < secondPoint.y) {
        i = firstPoint.y;
        endi = secondPoint.y;
    }
    else {
        i = secondPoint.y;
        endi = firstPoint.y;
    }
    if (firstPoint.x < secondPoint.x) {
        j = firstPoint.x;
        endj = secondPoint.x;
    }
    else {
        j = secondPoint.x;
        endj = firstPoint.x;
    }

    i = i / Images::sizeSquare;
    endi = endi / Images::sizeSquare;
    j = j / Images::sizeSquare;
    endj = endj / Images::sizeSquare;


    vector<Position> whatToMove;
    for (; i <= endi; i++) {
        for (int tempJ = j; tempJ <= endj; tempJ++) {

            shared_ptr<Vehicle> v = World::board[i][tempJ].vehicle;

            if(World::board[i][tempJ].person != nullptr)
                whatToMove.push_back({ tempJ + 1, i + 1 });

            else if (v.get() != nullptr) {

                if (World::board[i][tempJ].dist == -1) {

                    whatToMove.push_back({ tempJ + 1, i + 1 });

                    string type;
                    if (dynamic_cast<Helicopter*>(v.get()))
                        type = "Helicopter";
                    if (dynamic_cast<Car*>(v.get()))
                        type = "Car";
                    else if (dynamic_cast<Truck*>(v.get()))
                        type = "Truck";

                    Position size = Configuration::conf["Sizes"][type];

                    for (int a = i; a < i + size.second; a++) {
                        for (int b = tempJ; b < tempJ + size.first; b++) {
                            if (a == i && b == tempJ)
                                continue;
                            World::board[a][b].dist = 0;
                        }
                    }
                }
                else {
                    World::board[i][tempJ].dist = -1;
                }
            }
        }
    }

    Position dest = { destPoint.x / Images::sizeSquare + 1, destPoint.y / Images::sizeSquare + 1. };
    int time = 100 * max(World::board.size(), World::board[0].size());
    while (time--) {
        for (auto& elem : whatToMove)
            go(&elem, dest);
            //if(!go(&elem, dest))cout<<"ERROR!!!"<<endl;

        imshow("Board", Images::img);
        waitKey(1);
    }
}

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    static bool draw = false;

    Point* points = (Point*)userdata;

    //Right point in rectangle (click the left mouse button and drag)
    if (event == EVENT_LBUTTONDOWN) {
        cout << "Mouse is EVENT_LBUTTONDOWN - position (" << x << ", " << y << ")" << endl;
        points[0] = {x, y};
        draw = true;
    }
    //drag
    else if (event == EVENT_MOUSEMOVE && draw) {
        //cout << "Mouse is EVENT_MOUSEMOVE - position (" << x << ", " << y << ")" << endl;
        if (x > 0 && y > 0)
            points[1] = { x, y };
    }
    //Left point in rectangle (free the left mouse button)
    else if (event == EVENT_LBUTTONUP) {
        cout << "Mouse is EVENT_LBUTTONUP - position (" << x << ", " << y << ")" << endl;
        if (x > 0 && y > 0) {
            points[1] = { x, y };
            draw = false;
            showResources(points);
            cout << "Finish show resources: (" << x << ", " << y << ")" << endl;
            
        }
        
    }
    //Right click
    else if (event == EVENT_RBUTTONDOWN) {
        cout << "Mouse is Right click - position (" << x << ", " << y << ")" << endl;
        if (x > 0 && y > 0)
            points[2] = { x, y };
        if (points[0].x != -1 && points[1].x != -1)
            moveTheMovies(points);

        draw = false;
    }
}