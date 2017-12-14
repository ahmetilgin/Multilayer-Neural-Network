#include "headers/noron.h"
#include <time.h>
#include <iostream>
using namespace std;


Noron::Noron(int x)
{
    girisAgirligi = new double[x];
    for(int i = 0; i < x ; i++){
        girisAgirligi[i] = rand()% 5;
        //cout<<"Atanan Ağırlıklar: "<< girisAgirligi[i]<<"  ";
    }
    //cout<<endl;

}
Noron::Noron()
{
    girisAgirligi = new double[NORONGIRISSAYISI];
    for(int i = 0; i < NORONGIRISSAYISI ; i++){
        girisAgirligi[i] = rand()% 5;
        //cout<<"Atanan Ağırlıklar: "<< girisAgirligi[i]<<"  ";
    }
    //cout<<endl;

}


void Noron::agirliklariEkrandaGoster(){
    for(int i = 0; i < 3;i++){
        cout<<  girisAgirligi[i] << ' ';
    }
    cout <<endl;
}

void Noron::noronCikislariSetle(double x){
    cikis=x ;
    //Net çıkış sigmoid fonksiyonundan geçiriliyor.
    // cout<<"Sigmoid sonucu: " <<sigmoidFonksiyonu( cikis)<<endl;
    // cout<<"FnetFonksiyonu Sonucu : "<<fnetFonksiyonu(sigmoidFonksiyonu( cikis))<<endl;
    // netCikis = basamakFonksiyonu( cikis);
    netCikis = surekliFonksiyon(x);
    //cout<<"Net:: "<<netCikis<<endl;

}
double Noron::getGirisAgirligi(int index){
    return  girisAgirligi[index];
}
double Noron::getNoronCikis(){
    return  cikis;
}

double Noron::getNetCikis(){
    return  netCikis;
}


double Noron::basamakFonksiyonu(double x){
    if(x < 0 ) return -1.0;
    else return 1.0; // eşit 0 durumu da 1 döndürüyor.
}
double Noron::fnetFonksiyonu(double x){
    return (0.5) * x;
}


void Noron::setGirisAgirliklari(double x,int index){
    girisAgirligi[index] = x;
}
double Noron::surekliFonksiyon(double x){
    //double sonuc = (1-exp(-2*x))/(1+exp(-2*x));
    double sonuc = 1 / (1 + exp(-x));
    //cout<<"SONUC::  "<<sonuc<<endl;
    //cout<<"Surekli Fonksiyon Çıkışı:: "<<sonuc<<endl;
    return sonuc;
}
