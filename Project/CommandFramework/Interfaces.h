#pragma once
#include <string>

class Comparable{
public:
   virtual bool operator<(Comparable const &other) = 0;
};

class Equalable{
public:
   virtual bool operator==(Equalable const &other) = 0;
};

class Stringable{
public:
   virtual std::string toString() = 0;
};

class Additivable{
public:
   //result might be dynamicly allocated
   //up to user to keep it safe
   virtual Additivable *operator+(const Additivable &other) = 0;
};



