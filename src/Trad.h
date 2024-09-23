#ifndef TRAD_H
#define TRAD_H

#include <iostream>

template <typename TYP>
class Trad {
  
public:
  Trad() : rot(0) {};                    // default konstruktor
  Trad( TYP d ) { rot= new Nod(d); };
  Trad( const Trad& t ) { kopiera(t); };   // kopieringskonstruktor
  ~Trad() { delete rot; };
  
  bool tomt() const { return !rot; };
  TYP& varde() const{
    koll();
    return rot->data;
  };
  Trad& v_barn() const{
    koll();
    return *rot->vanster;
  };
  Trad& h_barn() const{
    koll();
    return *rot->hoger;
  };
  Trad& operator= ( const Trad& );
  bool operator== ( const Trad& ) const;
  void skriv_ut() const;

  //mina medlemmar
  //Nod* satt_in(TYP data);
  void satt_in(TYP value);
  bool sok(TYP value);
  
private:
  class Nod {
    friend class Trad<TYP>;
    TYP data;
    Trad *vanster, *hoger;
    Nod( TYP d ) : data( d ), vanster( new Trad ), hoger( new Trad ) {};
    ~Nod()
    {
      delete vanster;
      delete hoger;
    };
  }; // end class Nod

  Nod *rot;
  void koll() const{
    if ( tomt() )
      throw std::range_error( "Trad" );
  }
  void kopiera( const Trad& t );
};

// definitioner

// insättning i träd
template <typename TYP>
//void Trad<TYP>::satt_in(const TYP& value){
//Nod Trad<TYP>::satt_in(const TYP& value){
void Trad<TYP>::satt_in(TYP value){
  if(tomt()){
    rot = new Nod(value);
  }
  else if(value < varde()){
    v_barn().satt_in(value);
  }
  else{
    h_barn().satt_in(value);
  }
}

// sökning i träd
template <typename TYP>
bool Trad<TYP>::sok(TYP value){
  bool result;
  if(tomt()){
    //std::cout << "false" << std::endl;
    result = false;
  }
  else if(value == varde()){
    //std::cout << "true" << std::endl;
    result = true;
  }
  else if(value < varde()){
    result = v_barn().sok(value);
  }
  else{
    result = h_barn().sok(value);
  }
  return result;
}

template <typename TYP>
void Trad<TYP>::kopiera( const Trad<TYP>& t){
  //std::cout << "*** Trad::kopiera\n";
  if (t.tomt())
    rot = 0;
  else
  {
    rot = new Nod( t.varde());
    v_barn().kopiera( t.v_barn());
    h_barn().kopiera( t.h_barn());
  }
}

template <typename TYP>
Trad<TYP>& Trad<TYP>::operator=(const Trad<TYP>& t){
  //std::cout << "*** Trad::operator=\n";
  if(rot != t.rot){
    delete rot;
    kopiera(t);
  }
  return *this;
}

template <typename TYP>
bool Trad<TYP>::operator==(const Trad& t) const{
    // std::cout << "*** Trad::operator==\n";
    return (tomt() && t.tomt()) ||
           (!tomt() && !t.tomt() && varde() == t.varde() &&
            v_barn() == t.v_barn() && h_barn() == t.h_barn());
}

template <typename TYP>
void Trad<TYP>::skriv_ut() const{
  // traversera igenom trädet rekursivt enligt principen "in-order"
  if (!tomt())
  {
    v_barn().skriv_ut();
    std::cout << varde() << ' ';
    h_barn().skriv_ut();
  }
}

#endif /* Trad_h */
