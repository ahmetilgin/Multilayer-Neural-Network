#include "headers/siniragi.h"
#include <thread>
#include <time.h>
#include <unistd.h>
unsigned int microseconds = 100;

SinirAgi::SinirAgi()
{
    Noktalar nokta;
    nokta.setDegerler(0,0.5);
    nokta.setDegerler(1,0.5);
    nokta.setDegerler(2,-1);
    Sinif[0].noktaEkle(nokta);
    nokta.setDegerler(0,0.5);
    nokta.setDegerler(1,0.0);
    nokta.setDegerler(2,-1);
    Sinif[1].noktaEkle(nokta);


    nokta.setDegerler(0,-0.5);
    nokta.setDegerler(1,0.5);
    nokta.setDegerler(2,-1);
    Sinif[1].noktaEkle(nokta);
    nokta.setDegerler(0,-0.5);
    nokta.setDegerler(1,0);
    nokta.setDegerler(2,-1);
    Sinif[0].noktaEkle(nokta);
    katmandakiNoronlar[0] = 2;
    katmandakiNoronlar[1] = 1;
    Sinif[0].beklenenDegerSet(1);
    Sinif[1].beklenenDegerSet(-1);


}





void SinirAgi::ogrenmeBaslat(){

    do{
        setHata(0);
        for(int i = 0; i < SINIFSAYISI ; i++){
            if(Sinif[i].getOrnekSayisi()>0){
                for(int j = 0; j < Sinif[i].getOrnekSayisi();j++){
                    ileriYonluHesaplama(i,j);
                }
                usleep(microseconds);
            }
        }
    }
    while(hataliysamDuzelt());
}


void SinirAgi::ileriYonluHesaplama(int sinifIndex,int ornekIndex){

    Noktalar ornek;
    double toplam= 0;
    // Giris ve Ara katman arası çıktı
    // İ indexine sahip sınıftan j indexine sahip örneği al
    ornek = Sinif[sinifIndex].sinifaAitNoktaGet(ornekIndex);
    //cout<<"Verilen Ornek: "<<endl;
    //ornek.noktalarEkranaBas();

    for(int iKatman = 0; iKatman < KATMANSAYISI;iKatman++){
        int katmanDakiNoronSayisi = getKatmandakiNoronSayisi(iKatman);

        for(int iNoron = 0; iNoron <katmanDakiNoronSayisi ; iNoron++){
            // girisle noron arasında ki ağırlığın çarpımı ve çıkış hesabı
            if(iKatman == girisKatmani){
                for(int iCarpim = 0; iCarpim < GIRISSAYISI; iCarpim++){
                    toplam += ornek.getDegerler(iCarpim) * noron[iKatman][iNoron].getGirisAgirligi(iCarpim);
                }

                //cout<<"Verilen Ornek için toplam = "<<toplam<<" "<<endl;
                //toplam = noron[iKatman][iNoron].sigmoidFonksiyonu(toplam);
                noron[iKatman][iNoron].noronCikislariSetle(toplam);
                //cout<<"Sınıf No:  "<<sinifIndex<<endl;
                //cout<<"Bu norona Ait  "<<iNoron<<" Çıkış "<<toplam<<endl;
                toplam = 0;
            }
            if(iKatman == cikisKatmani){
                int iCarpim;
                int katmanDakiNoronSayisi = getKatmandakiNoronSayisi(iKatman);
                for(iCarpim = 0; iCarpim < katmanDakiNoronSayisi;iCarpim++){
                    toplam +=noron[iKatman-1][iCarpim].getNetCikis() * noron[iKatman][iNoron].getGirisAgirligi(iCarpim);
                }
                toplam += (-1) * noron[iKatman][iNoron].getGirisAgirligi(iCarpim+1);
                noron[iKatman][iNoron].noronCikislariSetle(toplam);
                toplam = 0;
                cout<<"Net Çıkış:"<<noron[iKatman][iNoron].getNetCikis()<<endl;
                cout<<"Beklenen-cikan: "<<Sinif[sinifIndex].beklenenDegerGet(0) - noron[iKatman][iNoron].getNetCikis()<<endl;
                cout<<"Beklenen - cikanın karesi :"<<pow(Sinif[sinifIndex].beklenenDegerGet(0) - noron[iKatman][iNoron].getNetCikis(),2)<<endl;
                 cout<<"Beklenen - cikanın karesi :"<<(1.0/2.0)*pow(Sinif[sinifIndex].beklenenDegerGet(0) - noron[iKatman][iNoron].getNetCikis(),2)<<endl;
                cout<<getHataMiktari()+((1.0/2.0)*pow(Sinif[sinifIndex].beklenenDegerGet(0) - noron[iKatman][iNoron].getNetCikis(),2))<<endl;
                setHata(getHataMiktari()+((1.0/2.0)*pow(Sinif[sinifIndex].beklenenDegerGet(0) - noron[iKatman][iNoron].getNetCikis(),2)));
                cout<<"Hata Miktari: "<<getHataMiktari()<<endl;
            }
        }
    }
}







void SinirAgi::InitNetwork(){

    for(int i = 0 ; i < KATMANSAYISI; i++){
        int katmandakiNoronSayilari = katmandakiNoronlar[i];
        cout<<i<<". "<<"Katmanda Bulunan Noron Sayisi : "<<katmandakiNoronSayilari<<endl;
        for(int j = 0; j < katmandakiNoronSayilari; j++){
            if(i == girisKatmani){
                Noron girisNoronlari;
                noron[i].push_back(girisNoronlari);
            }
            if(i == cikisKatmani){
                Noron cikisNoronlari(3);
                noron[i].push_back(cikisNoronlari);
            }
        }
    }
}








void SinirAgi::printStandartSapma(int index){
    for(int i = 0; i < GIRISSAYISI;i++){
        cout<<standartSapma[index][i]<<" ";
    }
    cout<<endl;
}

int SinirAgi::getKatmandakiNoronSayisi(int x)
{
    return katmandakiNoronlar[x];
}

void SinirAgi::setHata(double suAnkiHata){
    suAnkiHataMiktari = suAnkiHata;
}



double SinirAgi::getHataMiktari(){
    return suAnkiHataMiktari;
}



double SinirAgi::getBeklenenHataMiktari(){
    return beklenenHataMiktari;
}

void SinirAgi::setBeklenenHataOrani(double miktar)
{
    beklenenHataMiktari = miktar;
}




double SinirAgi::hataliysamDuzelt(){
    return (mutlakDegerAl(suAnkiHataMiktari) > beklenenHataMiktari) ? 1 : 0;
}




double SinirAgi::mutlakDegerAl(double x){
    return (x < 0) ? -x:x;
}

void SinirAgi::veriSetiniNormalizeEt(){

    standartSapmaHesabi();

    double farklar=0;
    for(int iSinif =0 ; iSinif < SINIFSAYISI ;iSinif++){
        printStandartSapma(iSinif);
    }

    for(int iSinif =0 ; iSinif < SINIFSAYISI ;iSinif++){
        int ornekSayisi = Sinif[iSinif].getOrnekSayisi();
        if(ornekSayisi != 0){
            Noktalar noktam;
            if(ornekSayisi != 0) {
                for(int iOrnek = 0; iOrnek < ornekSayisi;iOrnek++){
                    noktam = Sinif[iSinif].sinifaAitNoktaGet(iOrnek);
                    //cout<<"Verilen Nokta"<<endl;
                    noktam.noktalarEkranaBas();
                    for(int iKoordinat = 0; iKoordinat< GIRISSAYISI-1;iKoordinat++){
                        if(standartSapma[iSinif][iKoordinat] != 0){
                            farklar = (noktam.getDegerler(iKoordinat) - ortalama[iSinif][iKoordinat])/standartSapma[iSinif][iKoordinat];
                            //cout<<"Yeni Değer"<<farklar<<endl;
                            noktam.setDegerler(iKoordinat,farklar);
                        }
                    }
                    Sinif[iSinif].sinifaAitNoktaSet(iOrnek,noktam);
                }
            }
        }
    }

}


void SinirAgi::standartSapmaHesabi(){
    ortalamaHesabi();
    double toplam = 0;
    double uzakliklarinKaresi;
    for(int iSinif =0 ; iSinif < SINIFSAYISI ;iSinif++){
        int ornekSayisi = Sinif[iSinif].getOrnekSayisi();
        if(ornekSayisi != 0) {
            for(int iKoordinat = 0; iKoordinat < GIRISSAYISI;iKoordinat++){
                for(int jOrnek = 0; jOrnek < ornekSayisi;jOrnek++){
                    Noktalar noktam;
                    noktam = Sinif[iSinif].sinifaAitNoktaGet(jOrnek);
                    //cout<<"Ornek:" <<noktam.getDegerler(iKoordinat)<<endl;
                    //cout<<"Ortalamaya Olan Uzaklığının Karesi :"<<pow(noktam.getDegerler(iKoordinat)-ortalama[iSinif][iKoordinat],2)<<endl;
                    //cout<<"Ortalamaya olan Uzaklığı: "<<noktam.getDegerler(iKoordinat)-ortalama[iSinif][iKoordinat]<<endl;
                    //cout<<"Ortalaması: "<<ortalama[iSinif][iKoordinat]<<endl;
                    uzakliklarinKaresi = pow(noktam.getDegerler(iKoordinat)-ortalama[iSinif][iKoordinat],2);
                    toplam += uzakliklarinKaresi;
                }
                toplam = sqrt(toplam/(ornekSayisi-1));
                //                //cout<<"Standart Sapma Toplam2: "<<toplam<<endl;
                standartSapma[iSinif][iKoordinat] = toplam;
                toplam = 0;
            }
        }
    }


}
void SinirAgi::ortalamaHesabi(){

    for(int iSinif = 0; iSinif<SINIFSAYISI;iSinif++){
        int ornekSayisi = Sinif[iSinif].getOrnekSayisi();
        if(ornekSayisi != 0) {
            for(int iKoordinat = 0; iKoordinat < GIRISSAYISI;iKoordinat++){
                ortalama[iSinif][iKoordinat] = 0;
                for(int jOrnek = 0; jOrnek < ornekSayisi;jOrnek++){
                    Noktalar noktam = Sinif[iSinif].sinifaAitNoktaGet(jOrnek);
                    ortalama[iSinif][iKoordinat] += noktam.getDegerler(iKoordinat);
                }
                ortalama[iSinif][iKoordinat] /= ornekSayisi;
            }
        }
    }
}



