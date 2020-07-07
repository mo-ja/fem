#include "element.hpp"

element::element(material* _mp, std::vector<node*> _Np, uint32_t _en):
  mp(_mp), Np(_Np), en(_en){
  if(Np.size()!=NoN){
    std::cout << "[error] Number of node must be " << NoN <<" for elem " << en << "."<< std::endl;
    exit(1);
  }
  initialize();
  return;
}

void element::initialize(){
  //std::cout << "[initialization] elem " << en << "." << std::endl;
  X_0 = CPPL::dgematrix(dim, NoN);
  for(size_t i=0; i<NoN; i++){
    for(size_t j=0; j<dim; j++){
      X_0(j, i) = Np[i]->x_0(j);
    }
  }
  /*
  //std::cout << X_0;
  CPPL::dgematrix mov(NoN, dim);
  mov(0, 0) = 1;  mov(0, 1) = 0;
  mov(1, 0) = 0;  mov(1, 1) = 1;
  mov(2, 0) = -1;  mov(2, 1) = -1;

  CPPL::dgematrix Psi = X_0*mov;
  S_0 = (Psi(0,0)*Psi(1,1) - Psi(0,1)*Psi(1,0)) * 0.5;
  //Phi_0 = mov * Psi;
  Phi_0 = mov*CPPL::i(Psi);
  //std::cout << "[initialization] elem " << en << "." <<" S = " << S_0 << std::endl << "Phi_0 = " << Phi_0;
  */
  return;
}

void element::calc_fint(){
  CPPL::dgematrix X_a(dim, NoN);
  for(size_t i=0; i<NoN; i++){
    for(size_t j=0; j<dim; j++){
      X_a(j, i) = Np[i]->x_a(j);
    }
  }
  F_a = X_a * Phi_0;
  double J_a = ( F_a(0,0)* F_a(1,1) - F_a(0,1) * F_a(1,0) );
  S_a = J_a * S_0;
  mp->calc_T(F_a, T_a);
  std::flog << T_a;
}

// void element::translate_nodes(CPPL::dcovector du){
//   BOOST_FOREACH(auto inp, Np){
//     inp->x = inp->x_0 + du;
//   }
//   return;
// }


