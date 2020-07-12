#include "process/process.hpp"
#include "object/object.hpp"
#include "main.hpp"

process::process(std::string _name, double _time_e, double _dt): name(_name), time_e(_time_e), dt(_dt)
{
  return;
}

process::~process()
{
  return;
}

void process::take_a_step(){
  dcovector qM_a(OBJ.DOF());
  dgematrix KM_a(OBJ.DOF(), OBJ.DOF());
  dcovector fM_a(OBJ.DOF());
  fM_a.zero();
  BOOST_FOREACH(auto ie, OBJ.Elements){
    ie->calc_K_and_qint(KM_a, qM_a);
  }
  dcovector rM_a = qM_a - fM_a;
  consider_temperature(rM_a, KM_a);
  std::flog  << "rM_a="<<rM_a;
  std::flog  << "KM_a="<<KM_a;
  while(sqrt( dot(rM_a, rM_a) )>1e-6*dot(qM_a, qM_a)){
    KM_a.dgesv(rM_a);
    distribute_temperature(rM_a);
    fM_a.zero();
    KM_a.zero();
    BOOST_FOREACH(auto ie, OBJ.Elements){
      ie->calc_K_and_qint(KM_a, qM_a);
    }
    rM_a = qM_a - fM_a;
    consider_temperature(rM_a, KM_a);
  }
  
  return;
}

void process::consider_temperature(dcovector& r, dgematrix& K){
  BOOST_FOREACH(auto tp, OBJ.temperatures){
    BOOST_FOREACH(auto inn, tp->nn){
      auto np = OBJ.nn2np(inn);
      for(size_t i=0; i < OBJ.DOF(); i++){
        K(np->nn_ind, i)=0;
        r(i) -= K(i, np->nn_ind)*tp->value;
        K(i, np->nn_ind)=0;
      }
      K(np->nn_ind, np->nn_ind) = 1;
      r(np->nn_ind) = tp->value;     
    }
  }
  return;
}
void process::distribute_temperature(dcovector r){
  BOOST_FOREACH(auto inp, OBJ.Nodes){
    inp->T_a = r(inp->nn_ind);
    std::flog << inp->nn <<":" << r(inp->nn_ind) << std::endl;
  }
  return;
}
