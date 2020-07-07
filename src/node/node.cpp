#include "node.hpp"
node::node(dcovec3 _x_0,uint32_t _nn)
{
  //std::cout <<"node "<< _nn  <<" x_0 = " << _x_0 <<std::endl; 
  x_0 = _x_0;
  nn = _nn;
  //x = _x_0;
  //x_a = _x_0;
  initialize();
  return;
}

void node::initialize(){
  //std::cout <<"node "<< nn  <<" x_0 = " << x_0 <<std::endl;
  return;
}
