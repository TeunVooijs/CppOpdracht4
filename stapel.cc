#include "koffiebord.h"
#include "stapel.h"
#include <iostream>
using namespace std;


stapel::~stapel ( ) {
  int getal;
  haalvanstapel();
}//stapel::~stapel

void stapel::zetopstapel(koffiebord* player_bord){
  // teller++;
  stapelvakje* breek_deur = new stapelvakje();
  koffiebord* new_bord = new koffiebord(*player_bord);
  cout << new_bord -> ingang << endl;
  new_bord -> ingang = player_bord -> copybord();
  
  breek_deur -> prev = last_in;
  last_in = breek_deur;
  // breek_deur -> getal = teller;
  if (!new_bord){
    cout << "Je kanker moeder" << endl;
  }
  
}//stapel::zetopstapel

stapelvakje* stapel::haalvanstapel(){
  stapelvakje* stink_deur = last_in;
  if (!last_in){
    // return nullptr;
    cout << "Leeg" << endl;  
  } else {
    cout << stink_deur -> getal << endl;
    last_in = stink_deur -> prev;
    delete stink_deur;
  }
  return stink_deur;
}//stapel::haalvanstapel

