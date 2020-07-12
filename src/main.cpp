#include "main.hpp"
//#include <iostream>
//class
#include "object/object.hpp"
//#include "element/element.hpp"
//#include "node/node.hpp"
#include "reader/reader.hpp"
#include "writer/writer.hpp"
#include "process/process.hpp"

object OBJ;
std::vector<process*> pp;

namespace std{
  ofstream flog;
  ofstream fstp;
}

int main(int argc, char *argv[])
{
  if(argc < 2){
    std::cout << "[error] Please Specify Input File Name."  << std::endl;
    return 1;
  }
  fs::path ife_path(argv[1]);
  fs::path ofe_dir(ife_path.stem().string() +  ".ofe");
  std::cout<< "Removing old ofe files...";
  fs::remove_all(ofe_dir);
  std::cout<< "Done" << std::endl;
  std::cout<< "Creating old ofe files...";
  fs::create_directories(ofe_dir);
  std::cout<< "Done" << std::endl;
  std::flog.open(ofe_dir.string() +"/" +ife_path.stem().string()+".log");
  std::fstp.open(ofe_dir.string() +"/" +ife_path.stem().string()+".stp");
  
  reader ife(ife_path.string());
  ife.read();
  writer exodus(ofe_dir.string() +"/" +ife_path.stem().string()+".exo");
  exodus.write_initial_state();
  //OBJ->pp.take_step();
  process p("test", 0, 1);
  p.take_a_step();
  return 0;
}
