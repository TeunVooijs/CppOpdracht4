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
        kar=cin.get();        
        if(count==0){
            firstkar=kar;
            if (kar>='A' && kar <='Z'){
                firstkar2=kar+32;
            }
            else{
                firstkar2=kar-32;
            }
        }
        if((kar==firstkar || kar==firstkar2) && continu==true){
            count+=1;
        }
        else{
            continu=false;
        }

    }
    arr[0]=firstkar;
    arr[1]=count;
}


bool menu(koffiebord & spelerbord){
  cout << "test" << endl;
  return true;

}



int main(){
  koffiebord speler;

  while (true){
      if (menu(speler)){return 0;}
      
  }
  return 0;
  
}





// int main ( ) {
//   koffiebord bla;
//   bla.drukaf();
//   cout << "werkt niet" << endl;
//   return 0;
// }//main
