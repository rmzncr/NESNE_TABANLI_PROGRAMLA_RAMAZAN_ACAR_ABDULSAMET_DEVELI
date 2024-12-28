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

bool Grid::IsCellEmpty(int row, int column)
{
    if(grid[row][column]==0)
    {
        return true;
    }
    return false;
}
//tüm satırları alttan üste doğru kontrol eder ve dolu olanları siler
int Grid::ClearFullRows()
{
    int completed=0;
    for(int row=numRows-1; row>=0; row--)
    {
        if(IsRowFull(row))
        {
            ClearRow(row);
            completed++;
        }
        else if(completed>0)
        {
            MoveRowDown(row,completed);
        }

    }
    return completed;
}
// satırın dolu olup olmadığını kontrol eder
bool Grid::IsRowFull(int row)
{
   for(int column=0; column<numCols; column++)
   {
       if(grid[row][column]==0)
       {
           return false;
       }
   }
   return true;
}

void Grid::ClearRow(int row)
{
    for(int column=0; column<numCols; column++)
    {
        grid[row][column]=0;
    }
}
//satırlar silindikten sonra yukarıdaki satırları aşağıya doğru kaydırır
void Grid::MoveRowDown(int row, int numRows)
{
    for(int column=0; column<numCols; column++)
    {
        grid[row+numRows][column]=grid[row][column];
        grid[row][column]=0;
    }
}
