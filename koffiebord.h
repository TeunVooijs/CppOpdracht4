// file koffiebord.h

void read_char(int arr[]);
int read_num(int aantal);

class bordvakje {
public:
  bool marked;
  bool geopend;

  bordvakje* prev; 
  int aantal_buren;     //     7 0 1
  bordvakje* buren[8];  //     6   2
  bordvakje ( );        //     5 4 3
  int x,y;

};//bordvakje
 
class koffiebord {
private: // voor moeilijke zooi
  bordvakje* ingang;
  bordvakje* vorige;
  bordvakje* readcoord(int i, int j);
  void maakrij(); //om rij aan te maken
  bool klaar();
  void afmetingen();
  void ritsen();
  
  int hoogte, breedte;
  int countk; int steps;
  
  
  // TODO
public: //Hieronder voor spelen
  void checker();
  void open();
  void bouwbord();
  void speelbord();
  void verwijder_bord();
  koffiebord ( );
  ~koffiebord ( );
  void drukaf ( );
  void zet();
  void czet();
  // TODO
};//koffiebord