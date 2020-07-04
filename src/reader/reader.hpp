#pragma once
#include "node/node.hpp"
#include "element/element.hpp"
#include "material/elastic.hpp"

class reader{
public:
  ///////////////
  // variables //
  ///////////////
  std::string filename; //file name for input file
  std::ifstream ifs; //input file stream

  /////////////////////
  // member function //
  /////////////////////
  reader(std::string _filename); // constructor
  ~reader(); // destructor
  void initialize();
  void read();
  
  
};
