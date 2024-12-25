#pragma once // derlemede yalnızca bir kez yer alır
#include<vector>
#include<raylib.h>
using namespace std;
class Grid{

    public:
        Grid();//constructor
        void Initialize();
        void Print();
        void Draw();
        int grid[20][10];

    private:
        vector<Color> GetCellColors();
        int numRows;//satır sayısı
        int numCols;//sütun sayısı
        int cellSize;// hücre boyutu
        vector<Color> colors;

};