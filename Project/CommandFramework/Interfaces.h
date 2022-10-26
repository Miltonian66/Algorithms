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



