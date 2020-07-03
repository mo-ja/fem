#pragma once
#include "bc/bc.hpp"

class displacement: public bc
{
public:
  displacement(std::vector<int> _nn, int _direction, double _value);
};
