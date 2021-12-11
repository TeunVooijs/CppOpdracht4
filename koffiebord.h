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
  // Loopt naar een coordinaat en geeft adres terug
  void koffie_eerste_zet();
  void doe_zet(int i, int j); 
  // Regelt alles wanneer de computer of persoon een zet doet
  void maakrij(); //om rij aan te maken
  bool klaar(); 
  void afmetingen(); // Vraagt de afmetingen op
  void ritsen(); // Ritst rijen van het bord aan elkaar
  void flood_fill(bordvakje* pos); // Opent aanliggende nul-vakjes
  void koffies(); // Plaatst en berekent de koffies
  void closed(); // Berekent het aantal gesloten vakjes
  void af(); // Wanneer een koffie is gevonden
  void eind_zet(); // Na een zet wordt gecontroleerd of de speler gewonnen heeft
  int aantal_koffies; // Koffies in het bord
  int hoogte, breedte, percentage, aantal_vakjes;
  int zetten; // Het aantal zetten van dit spel
  int gesloten_vakjes; // Alle nog gesloten vakjes, naast de flags
  int geopende_vakjes, controle_geopende_vakjes;
  
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