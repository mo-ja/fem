#pragma once
#include "cpplapack.h"
#include "main.hpp"


class material{
public:
  std::string matname;

  material(std::string _matname);
  ~material();
  virtual void calc_T(CPPL::dgematrix F_a, CPPL::dgematrix& T_a)=0;
  virtual double calc_k(double temp)=0;
  virtual double calc_dk_dt(double temp)=0;
  virtual void calc_T_C(CPPL::dgematrix F_a,CPPL::dgematrix& T_a, CPPL::dgematrix& C)=0;
};
