void read_char(int arr[]);
int read_num(int aantal);

class bordvakje {
public:
  bool marked;
  bool geopend;
  bool flag;

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
  bordvakje* coordchecker();
  void koffie_eerste_zet();
  void doe_zet(int i, int j);
  void maakrij(); //om rij aan te maken
  bool klaar();
  void afmetingen();
  void ritsen();
  void flood_fill(bordvakje* pos);
  void koffies();
  void aantal_gesloten();
  void af();
  void eind_zet();
  int aantal_koffies;
  int hoogte, breedte, percentage, aantal_vakjes;
  int countk; int steps;
  int zetten;
  int gesloten_vakjes, controle_geopende_vakjes;
  int geopende_vakjes;
  
  // TODO
public: //Hieronder voor spelen
  void legenda();
  void open();
  void markzet();
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