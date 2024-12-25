#include <raylib.h>
#include"grid.h"
int main() 
{
    Color darkBlue={44,44,127,255};
    
    InitWindow(300,600,"Raylib Tetris");// Kordinat sistemi gibi çizim yapılıyor(x,y)
    //sol üst köşe(0,0)
    //while döngüsü oyun bitene kadar çalışacaktır
    SetTargetFPS(60);//60 fps oyunun her bilgisayarda aynı hızda çalışmasını sağlarız 
   Grid grid=Grid();
   grid.grid[0][0]=1;
   grid.grid[3][5]=4;
   grid.grid[17][8]=7;
   grid.Print();//ızgaralar ekrana yazdırılır
   
   
    while(WindowShouldClose()== false)// esc veya pencerede kapatma tuşuna basılmadığı sürece çalışır
    {
        BeginDrawing();//boş bir tuval oluşturur 
        ClearBackground(darkBlue);//tuvali darkBlue rengi ile doldurur
        grid.Draw();
        
        
        EndDrawing();//tuval çizimini sonlandırır
    }
    {

    }
    CloseWindow();
}