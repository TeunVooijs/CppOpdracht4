// file koffiebord.h


int leesgetal (int bovengrens);

class bordvakje {
  public:
    bool geopend;
    int aantal;           //     7 0 1
    bordvakje* buren[8];  //     6   2
    bordvakje ( );        //     5 4 3
    // TODO
};//bordvakje

class koffiebord {
  private:
    bordvakje* ingang;
    int hoogte, breedte;
    // TODO
  public:
    koffiebord ( );
    ~koffiebord ( );
    void drukaf ( );
    // TODO
};//koffiebord
