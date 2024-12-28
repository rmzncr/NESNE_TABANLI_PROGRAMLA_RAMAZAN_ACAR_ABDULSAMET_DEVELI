#include"block.h"
using namespace std;
Block::Block(){
cellSize=30;
rotationState=0;
colors=GetCellColors();//ekrana blok çizmek için renkleri içeren bir vektör
rowOffset=0;
columnOffset=0;
}


void Block::Draw()
{
    vector<Position> tiles = GetCellPositions();//bloğun dönme durumuna göre hücre pozisyonlarını alır
    for(Position item:tiles)//her hücre için 
    {
        DrawRectangle(item.column*cellSize+1, item.row*cellSize+1, cellSize-1, cellSize-1, colors[id]);//hücreyi çizer
    }


}
void Block:: Move(int columns,int rows)
{
    rowOffset+=rows;
    columnOffset+=columns;
}

vector<Position> Block::GetCellPositions()//offset işlemi sonrasında blokların güncel konum bilgisi
{
    vector<Position> tiles=cells[rotationState];//taşınanları tutacak yeni bir boş vektör
    vector<Position> movedTiles;
    for(Position item: tiles)
    {
        Position newPos=Position(item.row+rowOffset,item.column+columnOffset);
        movedTiles.push_back(newPos);//yeni konumu vektöre getirir

    }
    return movedTiles;

}
//bloğun dönme durumunu değiştirir
void Block::Rotate()
{
    rotationState++;
    if(rotationState==(int)cells.size())
    {
        rotationState=0;
    }


}

void Block::UndoRotaion()
{
    rotationState--;
    if(rotationState<0)
    {
        rotationState=cells.size()-1;
    }
}
