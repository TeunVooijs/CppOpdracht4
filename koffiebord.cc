#include <ctime>
#include "stdlib.h"
#include <iostream>
#include "koffiebord.h"
using namespace std;



bordvakje::bordvakje ( ) {
  geopend = false;
  flag = false;
  marked = false;
  aantal_buren = 0;

  for (int i = 0; i < 8; i++){
    buren[i]=nullptr;
  }
  


}//bordvakje::bordvakje

koffiebord::koffiebord ( ) {
  srand(time(NULL));
  ingang = nullptr;
  vorige = nullptr;
  afmetingen();
  bouwbord();
  koffies();
  zetten=0;
  gesloten_vakjes=0;
  aantal_vakjes= breedte * hoogte;
  

}//koffiebord::koffiebord

koffiebord::~koffiebord ( ) {
  // TODO
}//koffiebord::~koffiebord 

void koffiebord::drukaf ( ) {
  bordvakje* hulp;
  bordvakje* start;
  start = ingang;
  hulp = start;
  cout << "   ";
  for (int i = 0; i < breedte; i++){
    if (i < 10){
      cout << i << "  ";
    }
    else{
      cout << i << " ";
    }
  }
  cout << endl;
  
  // if(hulp){
  for (int i = 0; i < hoogte; i++){
    if(i<10){
      cout << i << "  ";
    }
    else{
      cout << i << " ";
    }
    for (int j = 0; j < breedte; j++){
      
      if(hulp){
        if (hulp -> flag == true){
          cout << "F  ";
        }
        else if(!hulp -> geopend){
          cout << "#  ";
        }
        else if(hulp ->  geopend == true && hulp -> marked == true){
          cout << "X  ";
        }
        else if (hulp -> geopend == true && hulp -> marked == false){
          if (hulp -> aantal_buren == 0){
            cout << ".  ";
          }
          else{
            cout << hulp -> aantal_buren << "  ";
          }
        }
      }
      hulp = hulp -> buren[2];
    }

    if (start -> buren[4]){
      start = start->buren[4];
    }
    
    hulp = start;
    cout << endl;
  }
  // }
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





// void koffiebord::verwijder_bord(){
//   bordvakje* verwijderaar;
//   bordvakje* hulp_verwijder = ingang ;

//   while (hulp_verwijder -> buren[4]){
//     hulp_verwijder = hulp_verwijder -> buren[4];
//     cout << "moved" << endl;
//   }

//   verwijderaar=hulp_verwijder;
  
//   while (hulp_verwijder){
//     while (hulp_verwijder -> buren[2]){
//       verwijderaar=hulp_verwijder;
      
//       while (verwijderaar -> buren[2]){
//         verwijderaar = verwijderaar -> buren[2];
//       }
//       delete verwijderaar;
//     }
//     verwijderaar = hulp_verwijder;
//     hulp_verwijder = hulp_verwijder -> buren[0];
//     delete verwijderaar;
//   }
// }

void koffiebord::flood_fill(bordvakje* pos){
  pos -> geopend = true;

  for (int i = 0; i < 8; i++)
  {
    if (pos -> buren[i]){
      if (pos -> buren [i] -> aantal_buren == 0 && pos -> buren[i] -> geopend == false){
        flood_fill(pos -> buren[i]);
      }
      else{
        pos -> buren[i] -> geopend = true;
      }
    }
  }
}



// Voor opvragen hoogte en breedte
void koffiebord::afmetingen(){
  cout << "Hoogte: ";
  hoogte = read_num(4);
  cout << "Breedte: ";
  breedte = read_num(4);
  cout << "Percentage gevuld: ";
  percentage = read_num(3);

}


void koffiebord::koffies(){
  srand(time(0));
  int xkoffie,ykoffie;
  int controle=0;
  bordvakje* schenker;
  aantal_koffies=(percentage*hoogte*breedte)/100;

  
  
  while (aantal_koffies!=controle){
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

void koffiebord::legenda(){
  cout << "Aantal zetten tot nu toe: "<< zetten << " Aantal koffies: "
  << aantal_koffies << endl;



}

void koffiebord::zet(){
  // bordvakje* keuze;
  int xcord;
  int ycord;

  cout << "Geef de x coordinaat van het vakje dat je wil openen: ";
  xcord=read_num(2);
  cout << "Geef de y coordinaat van het vakje dat je wil openen: ";
  ycord=read_num(2);
  
  doe_zet(xcord,ycord);
  
}

void koffiebord::markzet(){
  bordvakje* keuze;
  int xcord;
  int ycord;

  cout << "Geef de x coordinaat van het vakje dat je wil markeren: ";
  xcord=read_num(2);
  cout << "Geef de y coordinaat van het vakje dat je wil markeren: ";
  ycord=read_num(2);

  keuze = readcoord(xcord,ycord);  

  if (keuze -> geopend == false && keuze -> flag == false){
    keuze -> flag = true;  
  }
  else if (keuze -> flag == true){
    keuze -> flag = false;
  }
  else{
    cout << "Dit vakje is al open" << endl;
  }
}

void koffiebord::aantal_gesloten(){
  bordvakje* start = ingang;
  bordvakje* hulp = start;
  gesloten_vakjes = 0;

  while (start -> buren[4]){
    hulp = start;
    while (hulp -> buren[2]){
      if (hulp -> geopend == false && hulp -> flag == false){
        gesloten_vakjes++;
      }
      hulp = hulp -> buren[2];
    }
    start = start -> buren[4];
  }
}

void koffiebord::koffie_eerste_zet(){
  aantal_gesloten();
  bordvakje* col_fol = ingang; // volgt linker kolom
  bordvakje* placer_pos = col_fol;
  int vrije_plekken = aantal_vakjes - aantal_koffies;  
  int rand_koffie = 0, controle = 0;
  rand_koffie = rand() % vrije_plekken;
  cout << rand_koffie << endl;

  while (true){
    cout << "Hier 1 " << endl;
    while (col_fol){
      cout << "Hier 2 " << endl;
      placer_pos = col_fol;
      while (placer_pos){
        cout << "Hier 3 " << endl;
        if (placer_pos -> marked == false){
          controle++;
        }
        if (controle == rand_koffie){
          cout << "Hier 4" << endl; 
          break;
        }
        else{
          placer_pos = placer_pos -> buren[2];     
        }
        cout << controle << endl;
      }
      if (controle == rand_koffie){
        cout << "Hier 5" << endl;
        break;
      }
      col_fol = col_fol -> buren[4];
    }
    if (controle == rand_koffie)
      break;
  }
  cout << "Hier 6" << endl;
  placer_pos -> marked = true;
  
  for (int i = 0; i < 8; i++){
    if (placer_pos -> buren[i]){  
      placer_pos -> buren[i] -> aantal_buren++;
    }
  }
  cout << "Hier 7" << endl;

}

void koffiebord::af(){
  bordvakje* col_fol = ingang;
  bordvakje* opener;
  int aantal_geopend=0;
  cout << "Sorry je bent af, je hebt een koffie geraakt" << endl;

  opener = col_fol;
  while (col_fol != nullptr){
    while (opener != nullptr){
      opener -> geopend = true;
      aantal_geopend++;
      opener = opener -> buren[2];
    }   
    col_fol = col_fol -> buren[4];
    opener = col_fol;
  }

  cout << aantal_geopend << endl;
}


void koffiebord::czet(){
  aantal_gesloten();
  bordvakje* pos_zet;
  bordvakje* col_fol = ingang;
  int pos_rand = 0;
  int controle = 0;
  int x_pos = 0, y_pos = 0;
  pos_rand = rand() % gesloten_vakjes;
  cout << pos_rand << endl;

  while (true){
    while (col_fol/* -> buren[4]*/){
      pos_zet = col_fol;
      x_pos=0;
      while (pos_zet -> buren[2]){
        if (pos_zet -> geopend == false && pos_zet -> flag == false){
          controle++;
          if (controle == pos_rand){
            break;
          }
        }
        pos_zet = pos_zet -> buren[2];
        x_pos++;
      }
      if (controle == pos_rand){
        break;
      }      
      col_fol = col_fol -> buren[4];
      y_pos++;
    }
    if (controle == pos_rand){
      break;
    }
  }

  doe_zet(x_pos,y_pos);
  // if (zetten==0 && pos_zet -> marked == true){
  //   koffie_eerste_zet();
  //   pos_zet -> marked = false;
  //   for (int i = 0; i < 8; i++){
  //     pos_zet -> buren[i] -> aantal_buren--;
  //   }
  //   pos_zet -> geopend = true;
  // }
  // else if (pos_zet -> marked == true){
  //   af();
  // }
  // else if (pos_zet -> aantal_buren ==0){
  //   flood_fill(pos_zet);
  // }
  // else{
  //   pos_zet -> geopend = true;
  // }
  // zetten++;
}




// void koffiebord::doe_zet(int i, int j){
//   bordvakje* keuze;
  
//   keuze = readcoord(i,j);  
  
//   if (zetten==0 && keuze -> marked == true){
//     koffie_eerste_zet();
//     keuze -> marked = false;
//     for (int i = 0; i < 8; i++){
//       keuze -> buren[i] -> aantal_buren--;
//     }
//     keuze -> geopend = true;
//   }

//   // if (keuze -> flag == true || keuze -> geopend == true && rand == true){
    
//   // }
  
//   if (keuze -> flag == true){
//     cout << "Deze positie is gemarkeerd" << endl;
//   }
//   else if(keuze -> marked == true){
//     af();
//   }
//   else if (keuze -> aantal_buren == 0){
//     flood_fill(keuze);
//   }
//   else{
//     keuze -> geopend = true;
//   }
//   zetten++;
// }
// Als eerste zet een koffie is moet het de koffie_eerste_zet functie runnen 
// Als een zet al open is of flag moet er worden
//


void koffiebord::doe_zet(int i, int j){
  bordvakje* keuze;
  keuze = readcoord(i,j);

  if (zetten == 0 && keuze -> marked == true){
    koffie_eerste_zet();
    
    keuze -> marked = false;
    for (int i = 0; i < 8; i++){
      if (keuze -> buren[i])     
        keuze -> buren[i] -> aantal_buren--;
    }
    keuze -> geopend = true;
  }
  else if (keuze -> flag == true){
    cout << "Deze plek is gemarkeerd" << endl;
    zetten--; 
  }
  else if (keuze -> aantal_buren ==0){
    flood_fill(keuze);
  }
  else if (keuze -> marked == true){
    af();
  }
  else{
    keuze -> geopend = true;
  }
  zetten++;

}

/*
10
10
10
c

*/
// TODO
