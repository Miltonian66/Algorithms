#pragma once
#include "Interfaces.h"
#include <iostream>

class ASomeKey : public Comparable, public Equalable, public Stringable{

};

class ConcreteKey : public ASomeKey{
private:
   int value;
public:
   ConcreteKey(int value) :value(value){
   }
   bool operator<(Comparable const &other) override{
      ConcreteKey const *oth = dynamic_cast<ConcreteKey const *>(&other);
      if(!oth)
         return false;
      return value < oth->value;
   }
   bool operator==(Equalable const &other) override{
      ConcreteKey const *oth = dynamic_cast<ConcreteKey const *>(&other);
      if(!oth)
         return false;
      return oth->value == value;
   }
   std::string toString() override{
      return std::to_string(value);
   }
};

void interfacesExample(){
   ConcreteKey k1(23), k2(42);
   ASomeKey &ak1 = k1, &ak2 = k2;
   Comparable &ck1 = ak1, &ck2 = ak2;
   Equalable &ek1 = ak1, &ek2 = ak2;
   Stringable &sk1 = ak1, &sk2 = ak2;
   std::cout << "With concrete type: " << std::endl;
   std::cout << "k1 == k2 is " << (k1 == k2) << "; k1 < k2 is " << (k1 < k2) << "; k1 = " << k1.toString()
      << "; k2 = " << k2.toString() << std::endl << "Same thing with abstract type reference: " << std::endl;
   std::cout << "k1 == k2 is " << (ak1 == ak2) << "; k1 < k2 is " << (ak1 < ak2) << "; k1 = " << ak1.toString()
      << "; k2 = " << ak2.toString() << std::endl << "Even with interface type reference: " << std::endl;
   std::cout << "k1 == k2 is " << (ek1 == ek2) << "; k1 < k2 is " << (ck1 < ck2) << "; k1 = " << sk1.toString()
      << "; k2 = " << sk2.toString() << std::endl;
}