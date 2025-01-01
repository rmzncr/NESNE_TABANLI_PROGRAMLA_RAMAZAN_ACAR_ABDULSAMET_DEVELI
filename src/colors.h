#pragma once
#include<raylib.h>
#include<vector>
using namespace std;
//const program yürütüldüğü takdirde değiştirilemeyecek sabitlerdir
extern const Color darkGrey;// extern anahtar kelimesi ile tanımlanan değişkenler başka bir dosyada tanımlanmıştır
extern const Color green;
extern const Color red;
extern const Color orange;
extern const Color yellow;
extern const Color purple;
extern const Color cyan;
extern const Color blue;
extern const Color lightBlue;
extern const Color darkBlue;
vector<Color> GetCellColors();//tüm hücre renklerini döndürür

