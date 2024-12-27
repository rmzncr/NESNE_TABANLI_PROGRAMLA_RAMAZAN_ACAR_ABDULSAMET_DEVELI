#include <raylib.h>
#include"game.h"
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
        BeginDrawing();//boş bir tuval oluşturur 
        ClearBackground(darkBlue);//tuvali darkBlue rengi ile doldurur   
        game.Draw();
        EndDrawing();//tuval çizimini sonlandırır
    }
    {

    }
    CloseWindow();
}