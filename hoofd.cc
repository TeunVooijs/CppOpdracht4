// file hoofd.cc
#include <iostream>
#include "koffiebord.h"
using namespace std;

void read_char(int arr[])
{
	char kar = '\0';
	char firstkar, firstkar2;
	bool continu = true;
	int count = 0;

	while (kar != '\n'){
		kar = cin.get(); // leest karakter
		if (count == 0)
		{
			firstkar = kar; // eerste karakter wordt opgeslagen
			if (kar >= 'A' && kar <= 'Z')
			{
				firstkar2 = kar + 32; // eerste karakter wordt als normale
			}
			else
			{
				firstkar2 = kar - 32; // en als hoofdletter opgeslagen
			}
		}
		if ((kar == firstkar || kar == firstkar2) && continu == true)
		{
			count += 1; // elke herhaling van eerste karakter wordt opgeteld
		}
		else
		{
			continu = false; // Wanneer er een ander karakter wordt gelezen
		}					 // stopt de functie
	}
	arr[0] = firstkar;
	arr[1] = count;
}

// De read_num funtie wordt gebruikt wanneer de gebruiker een waarde
// als een getal op moet geven
// Wanneer er een max aan deze waarde zit wordt dit als aantal doorgegeven
// dit is de hoeveelheid nummers waaruit het getal mag bestaan
int read_num(int aantal){
	int getal = 0;
	char kar = '\0';
	int numkar;
	bool firstnum = false;
	while (kar != '\n'){
		kar = cin.get();
		if (kar >= '1' && kar <= '9'){
			firstnum = true;
		}
		if (kar >= '0' && kar <= '9' && getal < 100 && aantal >= 1 && firstnum == true){
			numkar = kar - 48;
			getal = getal * 10 + numkar;
			aantal -= 1;
		}
	}
	return getal;
}

void menu(koffiebord *&player_koffiebord){
	int arr[2];

  while (true){
		
    player_koffiebord -> drukaf();
		player_koffiebord -> legenda();
		if (player_koffiebord -> spel_eind == true){
			return;
		}
  	cout << "Wat wilt u doen?" << endl <<
		"Doe [Z]et, [F]lag een plek, [R]andom zet: ";
    read_char(arr);
    switch (arr[0]){
    case 's': case 'S':
      return;
    case 'z': case 'Z':
      player_koffiebord -> zet();
      break;
    case 'f': case 'F':
      player_koffiebord -> markzet();
      break;
    case 'r': case 'R':
      player_koffiebord -> czet();
      break;
    case 'c': case 'C':
      // player_koffiebord -> choofd(player_koffiebord);
      return;
    case 'x': case 'X':
	  	player_koffiebord -> ~koffiebord();
		  player_koffiebord = new koffiebord();
		  break;
		default:
      cout << "Verkeerde letter" << endl;
      break;
    }
		player_koffiebord -> eind_zet();
  }
}

	// case 'c': case 'C':
	//   player_koffiebord -> ~koffiebord();
	//   player_koffiebord = new koffiebord();
	//   break;
// in de main wordt life opgeroepen en wordt na elke verandering
// de matrix en legenda geprint en zal wanneer er niet wordt gestopt het
// menu opkomen
int main(){
	koffiebord *main_koffiebord = new koffiebord;
  int arr[2];


	while (true){

		menu(main_koffiebord);

    cout << "Wil je opnieuw spelen?" << endl <<
		"[J]a of [N]ee: ";
    read_char(arr);
    switch (arr[0]){
    case 'n': case 'N':
      return 0;
    case 'j': case 'J':
			main_koffiebord -> ~koffiebord();
      main_koffiebord = new koffiebord;
      break;
    
    default:
      break;
    }  
  }
			
		return 0;
}