#include <raylib.h>
#include"game.h"

double lastUpdateTime=0;//oyunun son güncelleme zamanı
//blokların daha yavaş hareket etmesi için kullanılır
bool EventTriggered(double interval)
{
    double currentTime=GetTime();
    if(currentTime-lastUpdateTime>=interval)
    {
        lastUpdateTime=currentTime;
        return true;
    }
    return false;
}
int main() 
{
    Color darkBlue={44,44,127,255};
    
    InitWindow(300,600,"Raylib Tetris");// Kordinat sistemi gibi çizim yapılıyor(x,y)
    //sol üst köşe(0,0)
    //while döngüsü oyun bitene kadar çalışacaktır
    SetTargetFPS(60);//60 fps oyunun her bilgisayarda aynı hızda çalışmasını sağlarız 
   
   Game game=Game();
    while(WindowShouldClose()== false)// esc veya pencerede kapatma tuşuna basılmadığı sürece çalışır
    {
        game.HandleInput();
        if(EventTriggered(0.2))
        {
            game.MoveBlockDown();
        }
        
        BeginDrawing();//boş bir tuval oluşturur 
        ClearBackground(darkBlue);//tuvali darkBlue rengi ile doldurur   
        game.Draw();
        EndDrawing();//tuval çizimini sonlandırır
    }
    {

    }
    CloseWindow();
}