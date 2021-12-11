// file hoofd.cc
#include <iostream>
#include "koffiebord.h"
using namespace std;

void read_char(int arr[]){
    char kar='\0';
    char firstkar,firstkar2;
    bool continu=true;
    int count=0;

    while(kar!='\n'){
        kar=cin.get(); // leest karakter        
        if(count==0){
            firstkar=kar; // eerste karakter wordt opgeslagen
            if (kar>='A' && kar <='Z'){
                firstkar2=kar+32; // eerste karakter wordt als normale
            }
            else{
                firstkar2=kar-32; // en als hoofdletter opgeslagen
            }
        }
        if((kar==firstkar || kar==firstkar2) && continu==true){
            count+=1; // elke herhaling van eerste karakter wordt opgeteld
        }
        else{
            continu=false;  // Wanneer er een ander karakter wordt gelezen
        }                   //stopt de functie
    }
    arr[0]=firstkar;
    arr[1]=count;
}

// De read_num funtie wordt gebruikt wanneer de gebruiker een waarde
// als een getal op moet geven
// Wanneer er een max aan deze waarde zit wordt dit als aantal doorgegeven
// dit is de hoeveelheid nummers waaruit het getal mag bestaan
int read_num(int aantal){
    int getal=0;
    char kar='\0';
    int numkar;
    bool firstnum=false;
    while (kar!='\n')
    {
        kar=cin.get();
        if(kar>='1' && kar<='9'){
            firstnum=true;
        }
        if (kar>='0' && kar<='9' && getal<100 && aantal>=1 && firstnum==true){
            numkar=kar-48;
            getal=getal*10+numkar;
            aantal-=1;
        }
    }
    return getal;
}


bool menu(koffiebord* & player_koffiebord){
    // 123
    int arr[2];
    cout << "Letter: ";
    
    read_char(arr);
    // main_koffiebord.bouwbord();

        switch (arr[0]){
        case 's': case 'S':
            return true;    
            break;
        case 'h': case 'H':
            // main_koffiebord.speelbord();
            // main_koffiebord.drukaf();
            break;
        case 'm': case 'M':
            // main_koffiebord.readcoord();
            break;
        case 'c': case 'C':
            player_koffiebord -> zet();
            // main_koffiebord.checker();
            // main_koffiebord.checker();
            break;
        // case 'v': case 'V':
            // main_koffiebord.verwijder_bord();
            // break;
        case 'f': case 'F':
            player_koffiebord -> markzet();
            break;
        case 'r': case 'R':
            player_koffiebord -> czet();
            break;
        case 'g': case 'G':
            player_koffiebord -> ~koffiebord();
            player_koffiebord = new koffiebord();
            break;
        // case 'n': case 'N':
        //     break;
        // case 'w':case 'a':case 'z':case 'd':
        //     main_koffiebord.cursor(arr[0],arr[1]);
        //     break;
        default:
        cout << "De lul" << endl;
            break;
        }
    return false;

}


// in de main wordt life opgeroepen en wordt na elke verandering
// de matrix en legenda geprint en zal wanneer er niet wordt gestopt het 
// menu opkomen
int main(){
    koffiebord* main_koffiebord = new koffiebord; 
    // 123
    
    while (true){
        main_koffiebord -> drukaf();
        main_koffiebord -> legenda();

        if (menu(main_koffiebord)){return 0;} 

    }
    return 0;
}