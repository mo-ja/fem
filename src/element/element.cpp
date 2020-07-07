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
  std::vector<dcovec3> X_0(NoN);
  for(size_t i=0; i<NoN; i++){
      X_0[i] = Np[i]->x_0;
  }
  V_0 = dot3(cross3(X_0[0] - X_0[3], X_0[1] - X_0[3]), X_0[2] - X_0[3]);
  V_0 = abs(V_0)/6.0;

  //std::flog << "elem:" << en<< " Vol="<<V_0<<std::endl;

  Phi_0 = std::vector<dcovec3>(4);
  for(int i=0;i<4;i++){
    Phi_0[i] = cross3(X_0[(2+i)%4] - X_0[3-i], X_0[(5-i)%4] - X_0[3-i])/6./V_0;
    //std::flog << "Phi_0["<<i<<"]="<<Phi_0[i];
  }
  return;
}

void element::calc_fint(){
  /*
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
  */
}

// void element::translate_nodes(CPPL::dcovector du){
//   BOOST_FOREACH(auto inp, Np){
//     inp->x = inp->x_0 + du;
//   }
//   return;
// }


