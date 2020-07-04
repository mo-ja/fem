#include "material/elastic.hpp"

elastic::elastic(std::string _matname, double _E, double _nu):
  material(_matname), E(_E), nu(_nu)
{
  K = E/3/(1-2*nu);
  mu = E/2/(1+nu);
  lambda = E*nu/(1+nu)/(1-2*nu);
  std::flog << "================ " << matname << " ================" <<std::endl;
  std::flog << "E =\t\t " << E <<std::endl;
  std::flog << "nu =\t\t " << nu <<std::endl;
  std::flog << "K =\t\t " << K <<std::endl;
  std::flog << "lame1 =\t " << lambda <<std::endl;
  std::flog << "G =\t\t " << mu <<std::endl;
  std::flog << "================ " << matname << " ================" <<std::endl <<std::endl<<std::endl;
  return;
}
elastic::elastic(std::string _matname, std::string _kname):
  material(_matname), kname(_kname)
{
  std::flog << "================ " << matname << " ================" <<std::endl;
  std::flog << "temperature table:" << kname <<std::endl;
  std::flog << "================ " << matname << " ================" <<std::endl <<std::endl<<std::endl;
  return;
}


void elastic::calc_T(CPPL::dgematrix F_a, CPPL::dgematrix& T_a){
  T_a = F_a * 0;
  CPPL::dgematrix E_a = 0.5 * (F_a + t(F_a));
  double e_v =0;
  for(size_t i=0; i<F_a.m; i++){
    E_a(i, i) += -1.0;
    e_v += E_a(i, i);
  }
  for(size_t i=0; i<F_a.m; i++){
    for(size_t j=0; j< F_a.n; j++){
      T_a(i, j) = 2 * mu * E_a(i, j);
      if(i==j)T_a(i, j) += lambda * e_v;
    }
  }
  return;
}
void elastic::calc_T_C(CPPL::dgematrix F_a, CPPL::dgematrix& T_a, CPPL::dgematrix& C){
  return;
}
