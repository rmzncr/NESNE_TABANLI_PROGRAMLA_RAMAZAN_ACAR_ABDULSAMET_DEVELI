#include <raylib.h>
#include"game.h"
#include"colors.h"
#include<iostream>
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
   
    InitWindow(500,620,"Raylib Tetris");// Kordinat sistemi gibi çizim yapılıyor(x,y)
    //sol üst köşe(0,0)
    //while döngüsü oyun bitene kadar çalışacaktır
    SetTargetFPS(60);//60 fps oyunun her bilgisayarda aynı hızda çalışmasını sağlarız 
   
    Font font=LoadFontEx("Font/monogram.ttf",64,0,0);//Font GPU belleğine yüklenir
   Game game=Game();
    while(WindowShouldClose()== false)// esc veya pencerede kapatma tuşuna basılmadığı sürece çalışır
    {
        UpdateMusicStream(game.music);//müziği günceller
        game.HandleInput();
        if(EventTriggered(0.2))
        {
            game.MoveBlockDown();
        }
        
        BeginDrawing();//boş bir tuval oluşturur 
        ClearBackground(darkBlue);//tuvali darkBlue rengi ile doldurur   
        DrawTextEx(font,"Puan",{365,15},38,2,WHITE);
        DrawTextEx(font,"Sonraki",{340,170},38,2,WHITE);
        if(game.GameOver)
        {
            DrawTextEx(font,"KAYBETTIN",{320,450},38,2,WHITE);

        }
        DrawRectangleRounded({320,55,170,60},0.3,6,lightBlue);

        char scoreText[10];//scoreText değişkeni 10 karakter alabilir
        sprintf(scoreText,"%d",game.score);//scoretext değişkeni yazdırmak istediğimiz metni tutuyor
        Vector2 scoreTextSize=MeasureTextEx(font,scoreText,38,2);//scoreText'in boyutunu alır

        DrawTextEx(font,scoreText,{320+(170-scoreTextSize.x)/2,65},38,2,WHITE);
        DrawRectangleRounded({320,215,170,180},0.3,6,lightBlue);
        
        
        
        
        game.Draw();
        EndDrawing();//tuval çizimini sonlandırır
    }
    {

    }
    CloseWindow();
}