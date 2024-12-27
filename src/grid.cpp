#include"grid.h"
#include"colors.h"
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
// Bloğun gridin dışına çıkıp çıkmadığını kontrol eder 
bool Grid::IsCellOutside(int row, int column)
{
    if(row>=0 && row<numRows && column>=0 && column<numCols)
    {
        return false;
    }
    return true;
}
