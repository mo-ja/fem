#pragma once
#include "material/material.hpp"

class elastic: public material
{
public:
  double E;
  double nu;
  double lambda;
  double mu;
  double K;

  elastic(std::string _matname, double _E, double _nu);
  ~elastic();
  void calc_T(CPPL::dgematrix F_a, CPPL::dgematrix& T_a);
  void calc_T_C(CPPL::dgematrix F_a, CPPL::dgematrix& T_a, CPPL::dgematrix& C);
};
