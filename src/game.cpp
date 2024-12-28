#include "game.h"
#include<random>
#include "blocks.cpp"
using namespace std;

Game::Game()
{
    grid = Grid();
    blocks=GetAllBlocks();
    currentBlock=GetRandomBlock();//rastgele bir blok seçilir
    nextBlock=GetRandomBlock();//rastgele bir blok seçilir
}

//blokları random atamak için kullanılır
Block Game:: GetRandomBlock()
{
    if(blocks.empty())//eğer blok kalmadıysa
    {
        blocks=GetAllBlocks();//blokları tekrar oluşturur
    }
    int randomIndex=rand()%blocks.size();//0 dan 6 ya akadar rastgele değer
    Block block=blocks[randomIndex];
    blocks.erase(blocks.begin()+randomIndex);//seçilen bloğu listeden çıkarır
    return block;//seçilen bloğu döndürür
}

vector<Block> Game:: GetAllBlocks()
{
    return {IBlock(),JBlock(),LBlock(),OBlock(),SBlock(),TBlock(),ZBlock()};
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw();
}
//oyuncunun tuşlar ile blokların hareketini sağlaması

void Game::HandleInput()
{
    int keyPress=GetKeyPressed();
    switch (keyPress)
    {
    case KEY_LEFT:
        MoveBLockLeft();
        break;
    case KEY_RIGHT:
        MoveBLockRight();
        break;
    case KEY_DOWN:
        MoveBlockDown();
        break;
    case KEY_UP://bloğun dönüşünü sağlar
        RotateBlock();
        break;
    }
}
//sola hareket etme
void Game::MoveBLockLeft()
{
    currentBlock.Move(-1,0);
    if(IsBlockOutside()|| BlocksFits()==false)//dışına çıktığında tekrar sağa hareket etmesi için
    {
        currentBlock.Move(1,0);
    }
}
//sağa hareket etme
void Game::MoveBLockRight()
{
    currentBlock.Move(1,0);
    if(IsBlockOutside()|| BlocksFits()==false)
    {
        currentBlock.Move(-1,0);
    }
}
//aşağı hareket etme
void Game::MoveBlockDown()
{
    currentBlock.Move(0,1);
    if(IsBlockOutside()|| BlocksFits()==false)//dışına çıktığında tekrar yukarı hareket etmesi için
    {
        currentBlock.Move(0,-1);
        LockBlock();
    }
}

bool Game::IsBlockOutside()
{
    vector<Position> tiles=currentBlock.GetCellPositions();
    //blok girdinin dışında mı değil mi
    for(Position item:tiles)
    {
        if(grid.IsCellOutside(item.row,item.column))
        {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock()//bloğun dönme durumunu değiştirir
{
    currentBlock.Rotate();
    if(IsBlockOutside()|| BlocksFits()==false)
    {
        currentBlock.UndoRotaion();//bloğun dışarı çıkması durumunda eski haline getirir
    }

}
//bloklar en aşağı indiğinde sabitlenmesi için kullanılır
void Game::LockBlock()
{
    vector<Position> tiles= currentBlock.GetCellPositions();
    for(Position item:tiles)
    {
        grid.grid[item.row][item.column]=currentBlock.id;
    }
    currentBlock=nextBlock;
    nextBlock=GetRandomBlock();
    grid.ClearFullRows();
}

bool Game::BlocksFits()
{
    vector<Position> tiles=currentBlock.GetCellPositions();
    for(Position item:tiles)
    {
        if(grid.IsCellEmpty(item.row,item.column)==false)
        {
            return false;
        }
    }
    return true;//hücreler boş ise true döndürür
}
