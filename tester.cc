#include <iostream>
using namespace std;

int main(){
  int x=8;
  int y=2;

  while (x!=5){
    if(y!=4){
      y++;
    }
    else if(y==4){
      x=5;
    }
    
    cout << "test" << endl;
  }
  
  return 0;


}