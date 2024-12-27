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
    }
}
//sola hareket etme
void Game::MoveBLockLeft()
{
    currentBlock.Move(-1,0);
    if(IsBlockOutside())//dışına çıktığında tekrar sağa hareket etmesi için
    {
        currentBlock.Move(1,0);
    }
}
//sağa hareket etme
void Game::MoveBLockRight()
{
    currentBlock.Move(1,0);
    if(IsBlockOutside())
    {
        currentBlock.Move(-1,0);
    }
}
//aşağı hareket etme
void Game::MoveBlockDown()
{
    currentBlock.Move(0,1);
    if(IsBlockOutside())
    {
        currentBlock.Move(0,-1);
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
