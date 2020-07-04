#include "bc/displacement.hpp"
#include "bc/bc.hpp"

displacement::displacement(std::vector<int> _nn, int _direction, double _value):bc(_nn, _direction, _value)
{
  return;
}
