#pragma once
#include <vector>
#include <string>
#include <algorithm>

template<typename T, typename U>
class table{
public:
  std::vector<T> x;
  std::vector<U> y;
  std::string name;
  size_t size;
  
  table(std::string _name);
  table();
  ~table();
  void add_value(T ix, U iy);
  U value(T ix);
};

template<class T, class U>
table<T, U>::table(std::string _name):
  name(_name){
  return;
}

template<class T, class U>
table<T, U>::table()
{
  name = "void";
  return;
}

template<class T, class U>
table<T, U>::~table(){
  return;
}
template<class T, class U>
void table<T, U>::add_value(T ix, U iy){
  x.push_back(ix);
  y.push_back(iy);
  size++;
}
template<class T, class U>
U table<T, U>::value(T ix){
  int ind = std::lower_bound(x.begin(), x.end(), ix) - x.begin();
  if(ind==0){
    return y[0];
  }else if(ind==size){
    return y[size - 1];
  }else{
    return (ix - x[ind-1])/(x[ind] - x[ind - 1]) * (y[ind] - y[ind - 1])  + y[ind - 1];
  }
}
