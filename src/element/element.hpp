#pragma once
#include "main.hpp"
#include "node/node.hpp"
#include "material/material.hpp"

class element{
public:
  //variables
  std::vector<node*> Np; //node pointer
  material* mp; //material pointer
  uint32_t en; //element ID
  unsigned int NoN = 4; //Number of Node for triangle
  unsigned int dim = 3; //dimension
  CPPL::dgematrix F_a; //deformation gradient
  CPPL::dgematrix T_a; //deformation gradient
  CPPL::dgematrix E_a; //deformation gradient
  CPPL::dgematrix Phi_0; // spatial derivative of shape function at initial state
  std::vector<CPPL::dcovector> Phi_a; // spatial derivative of shape function at initial state
  CPPL::dgematrix X_0;
  double S_0;//area
  double S_a;//area after deformation
  
  //member function
  element(material* _mp, std::vector<node*> _Np, uint32_t _en); // constructor
  void initialize();
  void calc_fint();
  CPPL::dcovector calc_fint_and_Kmat();
  //void calc_fint();
};
