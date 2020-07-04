#pragma once
#include "main.hpp"

class bc{
public:
  std::vector<int> nn;//node IDs
  int direction;
  double value;

  bc(std::vector<int> _nn, int _direction, double _value);
};
