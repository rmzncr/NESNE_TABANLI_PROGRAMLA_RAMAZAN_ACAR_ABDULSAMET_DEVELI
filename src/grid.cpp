#include"grid.h"
#include<iostream>
using namespace std;
Grid::Grid(){
    numRows=20;
    numCols=10;
    cellSize=30;
    Initialize();
    colors=GetCellColors();
}

void Grid::Initialize(){
    for(int row=0;row<numRows;row++){
        for(int column=0;column<numCols;column++){
            grid[row][column]=0;
        }
    }
}
void Grid::Print(){//gridin durumunu görmek için işe yarar
    for(int row=0;row<numRows;row++){
        for(int column=0;column<numCols;column++){
            cout<<grid[row][column]<<" ";
        }
        cout<<endl;
    }

}
vector<Color> Grid::GetCellColors(){
    const Color darkGrey = {26, 31, 40, 255};
    const Color green = {47, 230, 23, 255};
    const Color red = {232, 18, 18, 255};
    const Color orange = {226, 116, 17, 255};
    const Color yellow = {237, 234, 4, 255};
    const Color purple = {166, 0, 247, 255};
    const Color cyan = {21, 204, 209, 255};
    const Color blue = {13, 64, 216, 255};

    return {darkGrey,green,red,orange,yellow,purple,cyan,blue};
}

void Grid::Draw()
{
    for(int row=0; row<numRows; row++)//ızgaradaki her hücreyi dolaşır ve değerini cellValue atar
    {
        for(int column=0; column<numCols; column++)
        {
            int cellValue = grid[row][column];
            DrawRectangle(column*cellSize+1, row*cellSize+1, cellSize-1, cellSize-1, colors[cellValue]);
        }
    }
}