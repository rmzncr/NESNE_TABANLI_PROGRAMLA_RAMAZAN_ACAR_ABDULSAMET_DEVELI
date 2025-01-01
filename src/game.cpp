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
    GameOver= false;
    score=0;
    InitAudioDevice();//ses efektlerini başlatır
    music=LoadMusicStream("Sounds/music.mp3");// müziği yükler
    PlayMusicStream(music);//müziği başlatır
    rotateSound=LoadSound("Sounds/rotate.mp3");//blokların dönme sesi
    clearSound=LoadSound("Sounds/clear.mp3");//blokların temizlenme sesi

}   
Game::~Game()
{
    UnloadSound(rotateSound);//blokların dönme sesini kapatır
    UnloadSound(clearSound);//blokların temizlenme sesini kapatır
    UnloadMusicStream(music);//müziği kapatır
    CloseAudioDevice();//ses efektlerini kapatır
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
    currentBlock.Draw(11,11);
    switch (nextBlock.id)
    {
    case 3:
        nextBlock.Draw(255,290);//blokların konumunu belirler
        break;
    
    case 4:
        nextBlock.Draw(255,280);//o block ve ıblock için konum belirler
        break;
    default:
        nextBlock.Draw(270,270);
        break;
    }
}
//oyuncunun tuşlar ile blokların hareketini sağlaması

void Game::HandleInput()
{
    int keyPress=GetKeyPressed();
    if(GameOver && keyPress !=0)//oyun bitince tekrardan başlamak için reset atmak gerekir
    {
        GameOver=false;
        Reset();
    }
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
        UpdateScore(0,1);//puanı bir arttırır
        break;
    case KEY_SPACE://bloğun dönüşünü sağlar
        RotateBlock();
        break;
    }
}
//sola hareket etme
void Game::MoveBLockLeft()
{
 if(!GameOver){   
    currentBlock.Move(-1,0);
    if(IsBlockOutside()|| BlocksFits()==false)//dışına çıktığında tekrar sağa hareket etmesi için
    {
        currentBlock.Move(1,0);
    }
 }
}
//sağa hareket etme
void Game::MoveBLockRight()
{
    if(!GameOver){
        currentBlock.Move(1,0);
        if(IsBlockOutside()|| BlocksFits()==false)
        {
         currentBlock.Move(-1,0);
        }
    }
}
//aşağı hareket etme
void Game::MoveBlockDown()
{
    if(!GameOver){
        currentBlock.Move(0,1);
        if(IsBlockOutside()|| BlocksFits()==false)//dışına çıktığında tekrar yukarı hareket etmesi için
        {
            currentBlock.Move(0,-1);
            LockBlock();
        }
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
    if(!GameOver){//oyun sonunda blokların üst üste gelmesin diye
        currentBlock.Rotate();
        if(IsBlockOutside()|| BlocksFits()==false)
        {
            currentBlock.UndoRotaion();//bloğun dışarı çıkması durumunda eski haline getirir
        }
        else
        {
            PlaySound(rotateSound);//blokların dönme sesini çalar
        }
    }

}
void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
    switch(linesCleared)
    {
        case 1:
            score+=100;
            break;
        case 2:
            score+=300;
            break;
        case 3:
            score+=500;
            break;
        default:
            break;
    }
    score+=moveDownPoints;
}
// bloklar en aşağı indiğinde sabitlenmesi için kullanılır
void Game::LockBlock()
{
    vector<Position> tiles= currentBlock.GetCellPositions();
    for(Position item:tiles)
    {
        grid.grid[item.row][item.column]=currentBlock.id;
    }
    currentBlock=nextBlock;
    if(BlocksFits()==false)
    {
        GameOver=true;
    }
    nextBlock=GetRandomBlock();
    int rowCleared= grid.ClearFullRows();
    if(rowCleared>0)// eğer satır temizlendiyse ses çalar
    {
        PlaySound(clearSound);
        UpdateScore(rowCleared,0);// oyuncu yanlızca satır temizlediğinde puan alır
    }
    
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

void Game::Reset()//klavyeden tuşa basıldığında ızgarayı temizler
{
    grid.Initialize();
    blocks=GetAllBlocks();
    currentBlock=GetRandomBlock();
    nextBlock=GetRandomBlock();
    score=0;//puanı sıfırlar
}
