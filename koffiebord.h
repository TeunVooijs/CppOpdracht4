// file koffiebord.h


int leesgetal (int bovengrens);

class bordvakje {
public:
  bool marked;
  bool geopend;
  int aantal;           //     7 0 1
  bordvakje* buren[8];  //     6   2
  bordvakje ( );        //     5 4 3
  int x,y;

};//bordvakje

class koffiebord {
private: // voor moeilijke zooi
  bordvakje* ingang;
  bordvakje* readcoord(int i, int j);
  void voegvoor();
  void maakrij(); //om rij aan te maken
  void bouwbord();
  bool klaar();
  int hoogte, breedte;
  int countk; int steps;
  
  
  // TODO
public: //Hieronder voor spelen
  koffiebord ( );
  ~koffiebord ( );
  void drukaf ( );
  void zet();
  void czet();
  // TODO
};//koffiebord
