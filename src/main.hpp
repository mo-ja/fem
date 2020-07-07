#pragma once
#include "cpplapack.h"
#include <iostream>
#include <vector>
#include <algorithm>
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
template<class T, class U> class table;

typedef CPPL::dcovector_small<2> dcovec2;
typedef CPPL::dcovector_small<3> dcovec3;

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

inline dcovec3 cross3(dcovec3 a, dcovec3 b){
  return dcovec3(a(1)*b(2)-a(2)*b(1), a(2)*b(0)-a(0)*b(2), a(0)*b(1)-a(1)*b(0));
}
inline double dot3(dcovec3 a, dcovec3 b){
  return a(0)*b(0) + a(1)*b(1) + a(2)*b(2);
}
