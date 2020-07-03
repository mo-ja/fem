#include "process/process.hpp"
#include "object/object.hpp"

process::process(std::string _name, double _time_e, double _dt): name(_name), time_e(_time_e), dt(_dt)
{
  return;
}

process::~process()
{
  return;
}

void process::take_a_step(){
  CPPL::dcovector f_int(OBJ.DOF());
  CPPL::dcovector f_ext(OBJ.DOF());
  return;
}

void process::consider_displacement(CPPL::dcovector& residual, CPPL::dgematrix& Kmat){
  BOOST_FOREACH(auto dp, OBJ.displacements){
    BOOST_FOREACH(auto inn, dp->nn){
      size_t col = inn * OBJ.dim + dp->direction;
      residual(col) = dp->value;
      for(size_t i=0; i < OBJ.DOF(); i++){
        Kmat(col, i)=0;
        residual(i) -= Kmat(i, col)*dp->value;
      }
      Kmat(col,col) = 1;
    }
  }
  return;
}
