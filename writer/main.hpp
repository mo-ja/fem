#pragma once
#include "cpplapack.h"
#include <iostream>
#include "boost/foreach.hpp"
#include "boost/filesystem.hpp"
#include "exodusII.h"
//#include "exodusII_int.h"
//#include "node/node.cpp"

class object;
class node;
class element;
class reader;
class material;
class elastic;
class writer;
class process;
class bc;
class displacement;
class force;


extern std::vector<process*> processes;
extern object OBJ;
extern std::vector<process*> pp;
;
namespace std{
  extern ofstream flog;
  extern ofstream fsta;
}
namespace fs = boost::filesystem;

inline void clean_string(std::string* str, char trimed){
  str->erase(remove(str->begin(), str->end(), trimed), str->end());
  //str->erase(remove(str->begin(), str->end(), '\n'), str->end());
}

inline std::string push_param(std::string* str){
  size_t ind = str->find(',');
  if(ind == std::string::npos){
    return "";
  }
  std::string str2 = str->substr(0, ind);
  str->erase(0, ind + 1);
  return str2;
}

