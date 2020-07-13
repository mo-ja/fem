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

  std::flog << "elem:" << en<< " Vol="<<V_0<<std::endl;

  Phi_0 = std::vector<dcovec3>(4);
  for(int i=0;i<4;i++){
    Phi_0[i] = cross3(X_0[(2+i)%4] - X_0[3-i], X_0[(5-i)%4] - X_0[3-i])/6./V_0;
    std::flog << "Phi_0["<<i<<"]="<<Phi_0[i];
  }
  return;
}

void element::calc_qint(dcovector &qM_a){
  double T = 0;
  for(size_t i=0;i<NoN;i++){
    T +=  Np[i]-> T_a/NoN;
  }
  double k = mp->calc_k(T);
  q_a.zero();
  for(size_t i=0;i<NoN;i++){
    q_a += Np[i]-> T_a * Phi_0[i];
  }
  q_a *= k*V_0;
  dcovector qint(NoN);
  for(size_t i=0;i<NoN;i++){
    qint(i) = dot3(Phi_0[i], q_a);
  }
  contribute_qM_a(qint, qM_a);
  return;
}

void element::calc_K_and_qint(dgematrix &KM_a, dcovector &qM_a){
  double T = 0;
  for(size_t i=0;i<NoN;i++){
    T +=  Np[i]-> T_a/NoN;
  }
  double k = mp->calc_k(T);
  q_a.zero();
  for(size_t i=0;i<NoN;i++){
    q_a += Np[i]-> T_a * Phi_0[i];
  }
  q_a *= k*V_0;
  dcovector qint(NoN);
  for(size_t i=0;i<NoN;i++){
    qint(i) = dot3(Phi_0[i], q_a);
  }
  
  // KI
  dgematrix KI(NoN, NoN);
  for(size_t i=0;i<NoN;i++){
    for(size_t j=0;j<NoN;j++){
      KI(i, j) = dot3(Phi_0[i], Phi_0[j])*k*V_0;
    }
  }
  
  //KII
  double dk_dt = mp->calc_dk_dt(T);
  dgematrix KII(NoN, NoN);
  for(size_t i=0;i<NoN;i++){
    for(size_t j=0;j<NoN;j++){
      KII(i, j) = qint(i)/k/NoN * dk_dt;
    }
  }
  contribute_qM_a(qint, qM_a);
  contribute_KM_a(KI+KII, KM_a);
  std::flog << "k="<<k << " dk_dt="<<dk_dt<<std::endl;
  return;
}

void element::contribute_qM_a(dcovector qint, dcovector &qM_a){
  for(size_t i = 0;i<NoN;i++){
    qM_a(Np[i]->nn_ind) += qint(i);
  }
  return ;
}

void element::contribute_KM_a(dgematrix K, dgematrix &KM_a){
  for(size_t i=0;i<NoN;i++){
    for(size_t j=0;j<NoN;j++){
      KM_a(Np[i]->nn_ind, Np[j]->nn_ind) += K(i, j);
    }
  }
  return ;
}

