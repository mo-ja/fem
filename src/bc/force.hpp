#pragma once
#include "bc/bc.hpp"

class force: public bc
{
public:
  force(std::vector<int> _nn, int _direction, double _value);
};
