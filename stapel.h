const int MAX = 100;


class stapelvakje
{
public:
  stapelvakje* prev;
  int getal;
};

class stapel { // voor maximaal MAX integers
  private:
    stapelvakje* last_in;
  
  public:
    stapel() { 
      last_in=nullptr;
      teller = 0;
    } // constructor
    ~stapel();
    void zetopstapel (koffiebord* player_bord);
    stapelvakje* haalvanstapel ();
    int teller; 

};//stapel
