#pragma once
#include "material/material.hpp"
//#include "table/table.hpp"

class elastic: public material
{
public:
  double E;
  double nu;
  double lambda;
  double mu;
  double K;
  std::string kname;
  
  
  elastic(std::string _matname, double _E, double _nu);
  elastic(std::string _matname, std::string _kname);
  ~elastic();
  void calc_T(CPPL::dgematrix F_a, CPPL::dgematrix& T_a);
  void calc_T_C(CPPL::dgematrix F_a, CPPL::dgematrix& T_a, CPPL::dgematrix& C);
  double calc_k(double temp);
  double calc_dk_dt(double temp);
};
