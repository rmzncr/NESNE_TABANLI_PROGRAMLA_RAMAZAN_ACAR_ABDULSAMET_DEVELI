#pragma once
#include "grid.h"
#include "block.h"
using namespace std;
class Game
{
public:
    Game();
    Block GetRandomBlock();
    vector<Block> GetAllBlocks();
    void Draw();
    void HandleInput();
    void MoveBLockLeft();
    void MoveBLockRight();
    void MoveBlockDown();
    Grid grid;

private:
    vector<Block> blocks;
    Block currentBlock;//şu anki blok
    Block nextBlock;//sonraki blok
    bool IsBlockOutside();  
    void RotateBlock();
    void LockBlock();
    bool BlocksFits();//blokların boş bir hücre üstünde olup olmadığını kontrol eder

};