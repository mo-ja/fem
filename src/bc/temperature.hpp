#pragma once
#include "bc/bc.hpp"
//#include "main.hpp"

class temperature: public bc
{
public:
  temperature(std::vector<int> _nn, double _value);
};
