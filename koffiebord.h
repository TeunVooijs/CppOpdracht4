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

};//bordvakje
 
class koffiebord {
private: // voor moeilijke zooi
  bordvakje* vorige;
  bordvakje* readcoord(int i, int j); 
  // Loopt naar een coordinaat en geeft adres terug
  void koffie_eerste_zet();
  void doe_zet(int i, int j); 
  // Regelt alles wanneer de computer of persoon een zet doet
  bordvakje* maakrij(); //om rij aan te maken
  bool klaar(); 
  void ritsen(); // Ritst rijen van het bord aan elkaar
  void flood_fill(bordvakje* pos); // Opent aanliggende nul-vakjes
  void koffies(); // Plaatst en berekent de koffies
  void closed(); // Berekent het aantal gesloten vakjes
  void af(); // Wanneer een koffie is gevonden
  int aantal_koffies; // Koffies in het bord
  int zetten; // Het aantal zetten van dit spel
  int gesloten_vakjes; // Alle nog gesloten vakjes, naast de flags
  int geopende_vakjes, controle_geopende_vakjes;
  int aantal_runs, zetten_tot_af;
  void compzet(int i, int j);
  bordvakje* bouwbord();
  void crunner();
  bool comp_dood;
  bool comp = false;

  // TODO
public: //Hieronder voor spelen
  bordvakje* ingang;
  bordvakje* nieuwste;
  int hoogte, breedte, percentage, aantal_vakjes;
  // void afmetingen(); // Vraagt de afmetingen op
  void eind_zet(); // Na een zet wordt gecontroleerd of de speler gewonnen heeft
  void legenda();
  bordvakje* copybord();
  bool spel_eind;
  void markzet();
  void choofd(koffiebord* & runner);
  koffiebord (int h, int b, int p);
  ~koffiebord ( );
  void drukaf ( );
  void zet();
  void czet();
  // TODO
};//koffiebord