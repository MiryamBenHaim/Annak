#include "images.h"
using namespace std;
using namespace cv;

int Images::sizeSquare = 30;

Mat Images::originImg = Images::openMat("../resources/pictures/black_background.jpg");
Mat Images::img = Images::originImg;

Mat Images::openMat(string path)
{
    string image_path = samples::findFile(path);
    Mat img = imread(image_path, IMREAD_COLOR);

    if (img.empty()) {
        cout << "Could not read the image: " << image_path << endl;
        return Mat();
    }
    return img;
}

void Images::write(Mat img, string whatToWrite, int x, int y) {
    putText(img,
        whatToWrite,
        Point(x, y),
        FONT_HERSHEY_DUPLEX,
        0.5 * (sizeSquare / 20),
        CV_RGB(0, 0, 0), //font color
        1 * (sizeSquare / 20));
}

Mat Images::getMat(const string matName)
{
    static unordered_map<string, Mat> matMap = {
        {"Ground", openMat("../resources/pictures/TILES/tile_ground.png")},
        {"Water", openMat("../resources/pictures/TILES/tile_water.png")},
        {"Forest", openMat("../resources/pictures/TILES/tile_forest.png")},
        {"Field", openMat("../resources/pictures/TILES/tile_field.png")},
        {"Road", openMat("../resources/pictures/TILES/tile_road.png")},
        {"BlocksMine", openMat("../resources/pictures/TILES/tile_blocks_mine.png")},
        {"IronMine", openMat("../resources/pictures/TILES/tile_iron_mine.png")},
        {"City", openMat("../resources/pictures/Settlements/city.png")},
        {"Village", openMat("../resources/pictures/Settlements/village.png")},
        {"People", openMat("../resources/pictures/People/WALKING ASTRONOUT/0.png")},
        {"Car", openMat("../resources/pictures/VEHICLES/Audi.png")},
        {"Truck", openMat("../resources/pictures/VEHICLES/truck.png")},
        {"Helicopter", openMat("../resources/pictures/VEHICLES/helicopter.png")},
    };
    auto it = matMap.find(matName);
    return it->second;
}

void Images::fillSquare(int x, int y)
{
    shared_ptr<Place> place = World::board[x][y].place;
    Mat m;
    Position size = { -1, -1 };
    string type;

    if (dynamic_cast<Village*>(place.get())) {
        type = "Village";
    }
    else if(dynamic_cast<City*>(place.get())) {
        type = "City";
    }
    else if (World::board[x][y].person != nullptr) {
        type = "People";
        m = Images::getMat("People");
        size = { 1, 1 };
    }
    else if (shared_ptr<Vehicle> v = World::board[x][y].vehicle) {
        if (dynamic_cast<Helicopter*>(v.get()))
            type = "Helicopter";
        if (dynamic_cast<Car*>(v.get()))
            type = "Car";
        else if (dynamic_cast<Truck*>(v.get()))
            type = "Truck";
    }
    else if (Tile* t = dynamic_cast<Tile*>(place.get())) {
        m = Images::getMat(Configuration::Tiles[t->tileType - 1]);
        size = { 1, 1 };
    }
    else if (dynamic_cast<Road*>(place.get())) {
        m = Images::getMat("Road");
        size = { 1, 1 };
    }
        

    if (size.first == -1) {
        m = Images::getMat(type);
        size = Configuration::conf["Sizes"][type];
    }
    int tempSizeSquare = sizeSquare - ((size.first == 1) ? 1 : 0);
    resize(m, m, Size(tempSizeSquare * size.second, tempSizeSquare * size.first));
    //cout << "pos: [" << pos.first << ", " << pos.second << "], a : " << pos.second * Images::sizeSquare << ", b: " << pos.first * Images::sizeSquare << ", c: " << m.cols << ", d: " << m.rows << endl;

    Rect tempRect(y * Images::sizeSquare, x * Images::sizeSquare, m.cols, m.rows);
    if (type != "People" && type != "Truck" && type != "Car" && type != "Helicopter") {
        m.copyTo(originImg(tempRect));
        originImg(tempRect).copyTo(img(tempRect));
    }
    else {
        m.copyTo(img(tempRect));
    }
        
}

void Images::fillOriginSquare(int x, int y)
{
    Rect tempRect(y * Images::sizeSquare, x * Images::sizeSquare, sizeSquare, sizeSquare);
    originImg(tempRect).copyTo(img(tempRect));
}

void Images::generateBoardImage()
{
    int speir = 0;
    int maxRows = World::board.size(), maxCols = (World::board[0].size() / 5) + speir, i, j;
    resize(originImg, originImg, Size(maxCols * 5 * sizeSquare, maxRows * sizeSquare + 1));
    resize(img, img, Size(maxCols * 5 * sizeSquare, maxRows * sizeSquare));

    for (i = 0; i < World::board.size(); i++) {

        for (j = 0; j < World::board[i].size(); j++) {

            /*if (maxCols * 5 < j) {
                maxCols *= 2;
                resize(img, img, Size(maxCols * 5 * sizeSquare, maxRows * 5 * sizeSquare));
            }*/

            /*if (!dynamic_cast<VillageCity*>(w.board[i][j].place.get()) ||
                (i == 0 && j == 0) ||
                ((i != 0 && !dynamic_cast<VillageCity*>(w.board[i - 1][j].place.get())) &&
                (j != 0 && !dynamic_cast<VillageCity*>(w.board[i][j - 1].place.get()))))*/
            fillSquare(i, j);
            if (i == 0 && j % 5 == 0)
                write(Images::originImg, to_string(j + 1), j * sizeSquare -2, 15 * (sizeSquare / 20));
        }

        if (i % 5 == 0) {
            write(Images::originImg, to_string(i + 1), -2, i * sizeSquare + 15 * (sizeSquare / 20));
            line(originImg, Point(0, i * sizeSquare - 2), Point(originImg.cols, i * sizeSquare - 2), Scalar(255, 255, 255), 2);
        }
            
    }

    for (int j = 5; j < originImg.cols; j += 5) {
        line(originImg, Point(sizeSquare * j - 2, 0), Point(sizeSquare * j - 2, originImg.rows), Scalar(255, 255, 255), 2);
    }
    originImg.copyTo(img);
}