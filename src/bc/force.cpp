#include "bc/force.hpp"
#include "bc/bc.hpp"

force::force(std::vector<int> _nn, int _direction, double _value):bc(_nn, _direction, _value)
{
  return;
}
