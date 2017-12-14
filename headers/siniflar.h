﻿#ifndef SINIFLAR_H
#define SINIFLAR_H
#include <iostream>
#include "noktalar.h"
#include <vector>
using namespace std;
#define SINIFSAYISI 2

class Siniflar
{
    vector <Noktalar> sinifaAitNoktalar;
    int kacinciSinif;
    int ornekSayisi = 0;
    double beklenenDeger;
public:
    Siniflar();


    void noktaEkle(Noktalar nokta);
    void sinifAitNoktalariGoster();
    void beklenenDegerSet(int deger);
    double beklenenDegerGet(int x);
    Noktalar sinifaAitNoktaGet(int index);
    int getOrnekSayisi();
    void beklenenDegerleriEkranaBas(int sinifSayisi);
    void sinifaAitNoktaSet(int index,Noktalar nokta);



};

#endif // SINIFLAR_H
