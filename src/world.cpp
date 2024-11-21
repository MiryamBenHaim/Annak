#include "world.h"
using namespace std;

vector<vector<Square>> World::board(0);

void World::addTiles(vector<vector<int>> myTiles)
{
    vector<int> sizeTile = Configuration::conf["Sizes"]["Tile"];
    vector<Square> tempVec;
    shared_ptr<Place> tempPlace;

    //loop for initialing the board vector
    for (int x = 0; x < myTiles.size(); x++) {
        tempVec.clear();
        for (int i = 0; i < sizeTile[1]; i++) {
            if (i == 0) {
                for (int j = 0; j < myTiles[x].size(); j++) {
                    tempPlace.reset(new Tile(myTiles[x][j]));
                    Square tempS(_Tile, tempPlace);
                    for (int z = 0; z < sizeTile[0]; z++) {
                        tempVec.push_back(tempS);
                    }
                }
            }
            board.push_back(tempVec);
        }
    }
}

void World::printBoard()
{
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {

            Place* p;
            p = board[i][j].place.get();

            if (Tile* t = dynamic_cast<Tile*>(p))
                cout << t->tileType << "  ";
            else
                cout << "*  ";
        }
        cout << endl;
    }
    cout << endl;
}