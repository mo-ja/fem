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
  std::flog << "Begin analysis"<<std::endl;
  fM_a.zero();
  BOOST_FOREACH(auto tp, OBJ.temperatures){
    BOOST_FOREACH(auto inn, tp->nn){
      auto np = OBJ.nn2np(inn);
      np->T_a = tp->value;
    }
  }

  BOOST_FOREACH(auto ie, OBJ.Elements){
    ie->calc_K_and_qint(KM_a, qM_a);
  }
  dcovector rM_a = qM_a - fM_a;
  consider_temperature(rM_a, KM_a);
  dcovector chk;
  chk = rM_a;
  std::flog  << "rM_a="<<rM_a;
  std::flog  << "KM_a="<<KM_a;
  std::flog  << "chk="<<chk;
  int cnt = 1;
  std::flog  << "chk:damax="<<damax(chk) << " abs=" << sqrt(dot(chk, chk)) <<std::endl;
  while(sqrt(dot(rM_a, rM_a))>1e-9){// this criteria should be modified!!!!!!!!!!!!!!!!!!!!!!!!!!!
    std::cout << "iter:" << cnt++ << std::endl;
    KM_a.dgesv(rM_a);
    distribute_temperature(rM_a);
    
    // make new qM_a and KM_a
    KM_a.zero();
    qM_a.zero();
    BOOST_FOREACH(auto ie, OBJ.Elements){
      ie->calc_K_and_qint(KM_a, qM_a);
    }
    rM_a = qM_a - fM_a;
    chk = rM_a;
    consider_temperature(rM_a, KM_a);
    std::flog << "rM_a="<<rM_a;
    //std::flog << "chk="<<chk;

    /*
    // -> calc precise KM_a;
    dgematrix KM_p(OBJ.DOF(), OBJ.DOF());
    dgematrix KM_tmp(OBJ.DOF(), OBJ.DOF());
    dcovector qM_tmp(OBJ.DOF(), OBJ.DOF());
    double eps = 1e-6;
    BOOST_FOREACH(auto np, OBJ.Nodes){
      np->T_a += eps;
      qM_tmp.zero();
      KM_tmp.zero();
      BOOST_FOREACH(auto ie, OBJ.Elements){
        ie->calc_K_and_qint(KM_tmp, qM_tmp);
      }
      std::flog << "qM_tmp=" << qM_tmp;
      std::flog << "qM_a=" << qM_a;
      for(size_t j=0;j<OBJ.DOF();j++){
        KM_p(j, np->nn_ind) = (qM_tmp(j)-qM_a(j))/eps;
      }
      np->T_a -= eps;
    }
    consider_temperature(qM_tmp, KM_p);
    std::flog << "KM_a=" << KM_a;
    std::flog << "KM_p=" << KM_p;
    // <- for calc precise KM_a;
    */
  }
  return;
}

void process::consider_temperature(dcovector& r, dgematrix& K){
  BOOST_FOREACH(auto tp, OBJ.temperatures){
    BOOST_FOREACH(auto inn, tp->nn){
      auto np = OBJ.nn2np(inn);
      for(size_t i=0; i < OBJ.DOF(); i++){
        K(np->nn_ind, i)=0;
        K(i, np->nn_ind)=0;
      }
      K(np->nn_ind, np->nn_ind) = 1;
      r(np->nn_ind) = 0;     
    }
  }
  return;
}
void process::distribute_temperature(dcovector r){
  BOOST_FOREACH(auto inp, OBJ.Nodes){
    inp->T_a -= r(inp->nn_ind);
  }
  BOOST_FOREACH(auto tp, OBJ.temperatures){
    BOOST_FOREACH(auto inn, tp->nn){
      auto np = OBJ.nn2np(inn);
      np->T_a = tp->value;
    }
  }
  BOOST_FOREACH(auto inp, OBJ.Nodes){
    std::flog << inp->nn <<":" << inp->T_a << std::endl;
  }
  return;
}
