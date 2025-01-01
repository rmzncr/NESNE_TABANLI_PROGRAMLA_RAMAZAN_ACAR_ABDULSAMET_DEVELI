#pragma once
#include "grid.h"
#include "block.h"
using namespace std;
class Game
{
public:
    Game();
    ~Game();//yıkıcı fonksiyon	
    void Draw();
    void HandleInput();
    void MoveBlockDown();
    bool GameOver;//oyunun sonunda blokların üst üste binmesin diye
    int score;
    Music music;

private:
    void MoveBLockLeft();
    void MoveBLockRight();
    Block GetRandomBlock();
    vector<Block> GetAllBlocks();
    Grid grid;
    vector<Block> blocks;
    Block currentBlock;//şu anki blok
    Block nextBlock;//sonraki blok
    bool IsBlockOutside();  
    void RotateBlock();
    void UpdateScore(int linesCleared, int moveDownPoints);//score günceller
    void LockBlock();
    bool BlocksFits();//blokların boş bir hücre üstünde olup olmadığını kontrol eder
    void Reset();
    Sound rotateSound;
    Sound clearSound;
};