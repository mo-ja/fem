#pragma once
#include "main.hpp"

class bc{
public:
  std::vector<int> nn;//node IDs
  double value;
  
  bc(std::vector<int> _nn, double _value);
};
