#pragma once
#include "main.hpp"
#include "bc/bc.hpp"
#include "bc/temperature.hpp"

class process{
public:
  std::string name;
  double time_b, time_e;
  double dt;
  
  process(std::string _name, double _time_b, double _time_e);
  ~process(void);
  void take_a_step(void);
  void consider_displacement(CPPL::dcovector& residual, CPPL::dgematrix& Kmat);
  void consider_temperature(dcovector& r, dgematrix& K);
  void distribute_temperature(dcovector r);    
};
