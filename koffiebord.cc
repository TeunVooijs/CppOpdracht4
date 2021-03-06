#include <ctime>
#include <iostream>
#include <fstream>
#include "stdlib.h"
#include "koffiebord.h"
// #include "stapel.h"
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

koffiebord::koffiebord (int h, int b, int p) {
  spel_eind = false;
  srand(time(NULL));
  ingang = nullptr;
  vorige = nullptr;
  hoogte = h;
  breedte = b;
  percentage = p;
  // afmetingen(); // Vraagt afmetingen en percentage voor nieuwe bord op
  ingang = bouwbord(); // Maakt het bord
  cout << "Test 2" << endl;
  koffies(); // Plaatst de koffies
  zetten=0;
  gesloten_vakjes=0;
  geopende_vakjes=0;
  controle_geopende_vakjes=(breedte*hoogte)-aantal_koffies;
  aantal_vakjes= breedte * hoogte;
}//koffiebord::koffiebord

koffiebord::~koffiebord(){
  bordvakje* deleter;
  bordvakje* hulp_deleter;
  
  while (ingang -> buren[4]){
    ingang = ingang -> buren[4];
  }
  while (ingang){
    hulp_deleter = ingang;
    ingang = ingang -> buren[0];
    while (hulp_deleter){
      deleter = hulp_deleter;
      hulp_deleter = hulp_deleter -> buren[2];
      delete deleter;
    }
  }
}//koffiebord::~koffiebord 

bordvakje* koffiebord::copybord(){
  bordvakje* stap_bord = bouwbord();
  bordvakje* stap_bord_ingang = stap_bord;
  bordvakje* col_fol_stap;
  bordvakje* col_fol_main;
  bordvakje* copier_stap;
  bordvakje* copier_main;

  col_fol_main = ingang;
  col_fol_stap = stap_bord_ingang;
  cout << ingang << endl;
  while (col_fol_main){
    copier_main = col_fol_main;
    copier_stap = col_fol_stap;
    while (copier_main){
      copier_stap -> aantal_buren = copier_main -> aantal_buren;
      copier_stap -> marked = copier_main -> marked;
      copier_stap -> flag = copier_main -> flag;
      copier_stap -> geopend = copier_main -> geopend;
      cout << copier_stap << endl;
      copier_stap = copier_stap -> buren[2];
      copier_main = copier_main -> buren[2];
    }
    col_fol_main = col_fol_main -> buren[4];
    col_fol_stap = col_fol_stap -> buren[4];

  }

  return stap_bord_ingang;

}



void koffiebord::drukaf ( ) {
  bordvakje* hulp;
  bordvakje* start;
  start = ingang;
  hulp = start;

  if (start){  
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
  }
  else{
    cout << "Leeg" << endl;
  }
  cout << ingang << endl;
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



void koffiebord::flood_fill(bordvakje* pos){
  pos -> geopend = true;

  for (int i = 0; i < 8; i++)
  {
    if (pos -> buren[i]){
      if (pos -> buren [i] -> aantal_buren == 0 && pos -> buren[i] -> geopend == false){
        flood_fill(pos -> buren[i]);
      }
      else{
        geopende_vakjes++;
        pos -> buren[i] -> geopend = true;
      }
    }
  }
}

// // Voor opvragen hoogte en breedte
// void koffiebord::afmetingen(){
//   cout << "Hoogte: ";
//   hoogte = read_num(4);
//   cout << "Breedte: ";
//   breedte = read_num(4);
//   cout << "Percentage gevuld: ";
//   percentage = read_num(3);
// }



void koffiebord::koffies(){
  srand(time(0));
  int xkoffie,ykoffie;
  int controle=0;
  bordvakje* schenker;
  aantal_koffies=(percentage*hoogte*breedte)/100;
  if (aantal_koffies == 0)
    aantal_koffies = 1;

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


bordvakje* koffiebord::maakrij(){    
  bordvakje* p;
  bordvakje* hulp;
  vorige = nieuwste;
  hulp = nullptr;
  for (int i = 0; i < breedte; i++){
    p = new bordvakje;
    p -> buren[2] = hulp;

    if (p -> buren[2])
      p -> buren[2] -> buren[6] = p;
    hulp = p;
  }
  nieuwste = hulp;
  return nieuwste;


}

bordvakje* koffiebord::bouwbord(){
  bordvakje* hulp;
  for (int i = 0; i < hoogte; i++){
    hulp = maakrij();
    ritsen();
  }
  return hulp;
}

void koffiebord::ritsen(){
  bordvakje* hulp;
  hulp = nieuwste;
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

void koffiebord::closed(){
  bordvakje* start = ingang;
  bordvakje* hulp = start;
  gesloten_vakjes = 0;

  while (start){
    hulp = start;
    while (hulp){
      if (hulp -> geopend == false && hulp -> flag == false){
        gesloten_vakjes++; // Wanneer een vakje dicht is en geen flag
      } // word het aantal gesloten vakjes 1 meer
      hulp = hulp -> buren[2];
    }
    start = start -> buren[4];
  }
}

void koffiebord::koffie_eerste_zet(){
  bordvakje* col_fol = ingang; // volgt linker kolom
  bordvakje* placer_pos = col_fol;
  int vrije_plekken = aantal_vakjes - aantal_koffies;  
  int rand_koffie = 0, controle = 0;
  rand_koffie = rand() % vrije_plekken;
  
  while (true){
    while (col_fol){
      placer_pos = col_fol;
      while (placer_pos){
        if (placer_pos -> marked == false){
          controle++;
        }
        if (controle == rand_koffie){
          break;
        }
        else{
          placer_pos = placer_pos -> buren[2];     
        }
      }
      if (controle == rand_koffie)
        break;
      col_fol = col_fol -> buren[4];
    }
    if (controle == rand_koffie)
      break;
  }
  placer_pos -> marked = true;
  
  for (int i = 0; i < 8; i++){
    if (placer_pos -> buren[i])
      placer_pos -> buren[i] -> aantal_buren++;
  }
}


// void koffiebord::choofd(){
//   crunner();
// }

// void koffiebord::cdruk(){
//   for (int j = 0; j < 20; j++){
//     ofstream output ("U:\\Semester1\\ProgrammeerMethoden\\Opdracht4\\output.txt", ios::out);
    
//     output.put(max_zet[j]);
    
//     output.close();
    
//   }
// }

void koffiebord::crunner(){
  comp = true;
  comp_dood = false;
  zetten_tot_af = 0;

  while (comp_dood == false){
    czet();
    zetten_tot_af++;
    if (zetten_tot_af >=19){
      comp_dood = true;
    }
    cout << zetten_tot_af << endl;
  }
  

}

void koffiebord::af(){
  bordvakje* col_fol = ingang;
  bordvakje* opener;
  cout << "Sorry je bent af, je hebt een koffie geraakt" << endl;

  opener = col_fol;
  while (col_fol != nullptr){
    while (opener != nullptr){
      opener -> geopend = true;
      opener = opener -> buren[2];
    }   
    col_fol = col_fol -> buren[4];
    opener = col_fol;
  }
  spel_eind = true;
}


void koffiebord::czet(){
  closed();
  bordvakje* pos_zet;
  bordvakje* col_fol = ingang;
  int pos_rand = 0;
  int controle = -1;
  int x_pos = 0, y_pos = 0;
  pos_rand = rand() % (gesloten_vakjes-1);
  
  while (true){
    while (col_fol){
      pos_zet = col_fol;
      x_pos=0;
      while (pos_zet){
        if (pos_zet -> geopend == false && pos_zet -> flag == false){
          controle++;
        }
        if (controle == pos_rand){
          break;
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
    if (controle == pos_rand)
      break;
  }
  if (comp == true)
    compzet(x_pos,y_pos);
  else
    doe_zet(x_pos,y_pos);
}

void koffiebord::compzet(int i, int j){
  bordvakje* keuze;
  keuze = readcoord(i,j);

  if (keuze -> marked == true && zetten_tot_af != 0 ){
    comp_dood = true;
  }
  if (zetten_tot_af == 0 && keuze -> marked == true){
    koffie_eerste_zet();
    
    keuze -> marked = false;
    for (int i = 0; i < 8; i++){
      if (keuze -> buren[i])     
        keuze -> buren[i] -> aantal_buren--;
    }
    keuze -> geopend = true;
  }
  else if (keuze -> aantal_buren == 0){
    flood_fill(keuze);
  }
  else{
    keuze -> geopend = true;
  }
}


// Als eerste zet een koffie is moet het de koffie_eerste_zet functie runnen 
// Als een zet al open is of flag moet er worden
//
void koffiebord::doe_zet(int i, int j){
  bordvakje* keuze;
  keuze = readcoord(i,j);


  if (keuze -> marked == true && zetten != 0 && keuze -> flag == false){
    zetten++;
    af();
  }
  else if (zetten == 0 && keuze -> marked == true){
    koffie_eerste_zet();
    
    keuze -> marked = false;
    for (int i = 0; i < 8; i++){
      if (keuze -> buren[i])     
        keuze -> buren[i] -> aantal_buren--;
    }
    keuze -> geopend = true;
  }
  
  if (keuze -> flag == true){
    cout << "Deze plek is gemarkeerd" << endl;
    zetten--; 
  }
  
  if (keuze -> aantal_buren == 0 && keuze -> marked == false){
    flood_fill(keuze);
  }
  else{
    keuze -> geopend = true;
  }
  zetten++;
}

void koffiebord::eind_zet(){
  bordvakje* col_fol = ingang;
  bordvakje* checker;
  int controle = 0;

  while (col_fol){
    checker = col_fol;
    while (checker){
      if (checker -> geopend == false || checker -> flag == true){
        controle++;
      }
      checker = checker -> buren[2];
    }
    col_fol = col_fol -> buren[4];
  }
  if (controle == aantal_koffies){
    cout << "Je hebt niet verloren :| )";
    spel_eind = true;
  }
  
  

  


}


/*
10
10
10
r
r
r

*/
// TODO
