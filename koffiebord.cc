#include <ctime>
#include "stdlib.h"
#include <iostream>
#include "koffiebord.h"
using namespace std;



bordvakje::bordvakje ( ) {
  srand(time(NULL));
  geopend = true;
  marked = false;
  aantal_buren = 0;

  for (int i = 0; i < 8; i++){
    buren[i]=nullptr;
  }
  


}//bordvakje::bordvakje

koffiebord::koffiebord ( ) {
  ingang = nullptr;
  vorige = nullptr;
  afmetingen();
  bouwbord();
  koffies();



}//koffiebord::koffiebord

koffiebord::~koffiebord ( ) {
  // TODO
}//koffiebord::~koffiebord 

void koffiebord::drukaf ( ) {
  bordvakje* hulp;
  bordvakje* start;
  start = ingang;
  
  hulp = start;
  if(hulp){
  for (int i = 0; i < hoogte; i++){
    for (int j = 0; j < breedte; j++){
      if(hulp){
        if(!hulp -> geopend){
          cout << ". ";
        }
        else if(hulp -> geopend == true && hulp -> marked == true){
          cout << "X ";
        }
        else if (hulp -> geopend == true && hulp -> marked == false){
          cout << hulp -> aantal_buren << " ";
        }
      }
      hulp = hulp -> buren[2];
    }

    if (start -> buren[4]){
      start = start->buren[4];
    }
    
    hulp = start;
    cout << endl;
  }}
  else{
    cout << "is leeg" << endl;
  }
}//koffiebord::drukaf



bordvakje* koffiebord::readcoord(int i, int j){ // i = x-as j = y-as
  int verschil=i-j;
  bordvakje* mover;
  mover = ingang;
// als er een verschil is verplaatst het eerst het aantal stappen dat
// overlapt schuin 
// verschil=i-j
// wanneer verschil is >0 dan i>j en j is het aantal schuine stappen
// wanneer verschil is <0 dan j>i en i is het aantal schuine stappen
// maak een rest
// verplaats in richting bij i of j is groter
  if (verschil>0){ // i is groter en dus verplaatsing naar rechts
    for (int g = 0; g < j; g++){ // schuine verplaatsing
      mover = mover -> buren[3];
    }
    for (int h = 0; h < verschil; h++){ // overige zijwaardse verplaatsing
      mover = mover -> buren[2];
    }
  }
  else if (verschil<0){ // j isw groter dus verplaatsing naar beneden
    for (int g = 0; g < i; g++){ // schuine verplaatsing
      mover = mover -> buren[3];
    }
    for (int h = 0; h < verschil*-1; h++){ // overige hoogte verplaatsing
      mover = mover -> buren[4]; 
    }
  }
  else{ // i=j en dus alleen schuine verplaatsing
    for (int g = 0; g < i; g++){
      mover = mover -> buren[3];
    }
  }
  // mover -> marked = true;
  return mover;
}



void koffiebord::open(){
  int xcord;
  int ycord;

  cout << "Geef de x coordinaat van het vakje dat je wil openen: ";
  xcord=read_num(2);
  cout << "Geef de y coordinaat van het vakje dat je wil openen: ";
  ycord=read_num(2);

  readcoord(xcord,ycord);
}



void koffiebord::verwijder_bord(){
  bordvakje* verwijderaar;
  bordvakje* hulp_verwijder = ingang ;

  while (hulp_verwijder -> buren[4]){
    hulp_verwijder = hulp_verwijder -> buren[4];
    cout << "moved" << endl;
  }

  verwijderaar=hulp_verwijder;
  
  while (hulp_verwijder){
    while (hulp_verwijder -> buren[2]){
      verwijderaar=hulp_verwijder;
      
      while (verwijderaar -> buren[2]){
        verwijderaar = verwijderaar -> buren[2];
      }
      delete verwijderaar;
    }
    verwijderaar = hulp_verwijder;
    hulp_verwijder = hulp_verwijder -> buren[0];
    delete verwijderaar;
  }
}



void koffiebord::checker(){
  bordvakje* koffiechecker=ingang;

  for (int g = 0; g < breedte; g++){
    for (int h = 0; h < hoogte; h++){
      if (koffiechecker->marked){
        for (int k = 0; k < 7; k++){
          koffiechecker -> buren[k] -> aantal_buren++;
        }
      }
      koffiechecker=koffiechecker->buren[2];
    }
    koffiechecker=koffiechecker->buren[4];
  }
  
}

// Voor opvragen hoogte en breedte
void koffiebord::afmetingen(){
  cout << "Hoogte: ";
  hoogte = read_num(4);
  cout << "Breedte: ";
  breedte = read_num(4);
  cout << "Percentage gevuld: ";
  percentage = read_num(2);

}


void koffiebord::koffies(){
  srand(time(0));
  int xkoffie,ykoffie;
  int aantalkoffies, controle=0;
  bordvakje* schenker;


  aantalkoffies=(percentage*hoogte*breedte)/100;
  
  while (aantalkoffies!=controle){
    xkoffie=rand() % (breedte);
    ykoffie=rand() % (hoogte);
    schenker = readcoord(xkoffie,ykoffie);
    
    if (schenker -> marked == false){
      schenker -> marked = true;
      
      for (int h = 0; h < 8; h++){
        if (schenker -> buren[h]){
          schenker -> buren[h] -> aantal_buren++;
        }
      }
      controle++;
    } 

  }
}



void koffiebord::maakrij(){    
  bordvakje* p;
  bordvakje* hulp;
  vorige = ingang;
  hulp = nullptr;
  

  for (int i = 0; i < breedte; i++){
    p = new bordvakje;

    p -> buren[2] = hulp;

    if (p -> buren[2])
      p -> buren[2] -> buren[6] = p;
    
    hulp = p;
  }

  ingang = hulp;
}

void koffiebord::bouwbord(){
  for (int i = 0; i < hoogte; i++){
    maakrij();
    ritsen();
  }

}

void koffiebord::ritsen(){
  bordvakje* hulp;
  hulp = ingang;

  while (vorige){
    vorige -> buren[0] = hulp;
    vorige -> buren[1] = hulp -> buren [2];
    vorige -> buren[7] = hulp -> buren [6];
    hulp -> buren[4] = vorige;
    hulp -> buren[3] = vorige -> buren [2];
    hulp -> buren[5] = vorige -> buren [6];
    hulp = hulp -> buren[2];
    vorige = vorige -> buren[2];
  }
}

void koffiebord::speelbord(){
  bordvakje* hulper;
  bordvakje* starter;
  // bordvakje* hulper2;
  starter = ingang;
  // int printje;

  // if (hulp->marked==false){
  //   printje =1;
  // }
  while (starter -> buren[4]){
    starter = starter -> buren[4];
    // cout << printje << endl;
  }
  hulper = starter;
  // int L=1;

  for (int i = 0; i < hoogte; i++){
    for (int j = 0; j < breedte; j++){
      // hulper2 = hulper;
      // if(hulper2){
      for (int k = 0; k < 8; k++){
        if (hulper -> buren[k]){
          hulper -> buren[k] -> aantal_buren++;
        }
        // if (hulper -> buren[k]!=nullptr){
        //   hulper -> aantal_buren = L;
        // }
      
      }
      // L++;
      // hulper -> aantal_buren = L;      
      hulper = hulper -> buren[2];
    }
    // L=1;
    if (starter -> buren[0])
    {
      starter = starter -> buren[0];
    }
    
    hulper = starter;
  }

}




void koffiebord::zet(){



}

void koffiebord::czet(){



}

// TODO
