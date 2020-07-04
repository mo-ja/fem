#pragma once
#include "main.hpp"

class node{
public:

  //member variables
  CPPL::dcovector x_0; //initial position vector
  CPPL::dcovector x;   //position vector at start of the increment
  CPPL::dcovector x_a; //position vector of current step
  size_t nn; //node ID
  
  
  //member  function
  node(CPPL::dcovector _x_0, uint32_t _nn); // constructor
  void initialize();
  
  //property
  CPPL::dcovector u(){return x - x_0;};
  CPPL::dcovector u_a(){return x_a - x_0;};
  
};