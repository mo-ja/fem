#pragma once
#include "main.hpp"

class writer{
public:
  int exoid; //exodus id

  writer(std::string exo_path);
  ~writer();
  void initialize();
  void write_initial_state();
  void write_nodal_value(int time_step);
  void write_state(int time_step);
  
};
