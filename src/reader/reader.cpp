#pragma once
#include "reader/reader.hpp"
#include "object/object.hpp"
#include "process/process.hpp"
//#include <string>

reader::reader(std::string _filename): filename(_filename){
  initialize();
  return;
}

reader::~reader(){
  ifs.close();
  return;
}

void reader::initialize(){
  ifs = std::ifstream(filename);
  if(ifs.fail()){
    std::cout << "file cannot open" << std::endl;
    exit(1);
  }
  std::cout << "input file " << filename << " opened." << std::endl;
  //read();
  return;
}

void reader::read(){
  std::string str;
  while(std::getline(ifs, str, ';'))
    {
      //std::cout << "at getline beginning." << std::endl;
      std::string channel = push_param(&str);
      clean_string(&channel, ' '); //remove \n and space
      clean_string(&channel, '\n'); //remove \n and space
      if(channel==""){
        //std::cout << "empty line" << std::endl;
      }
      else if(channel=="elastic")
        {
          std::string matname = push_param(&str);
          std::string kname = str;
          OBJ.add_material(new elastic(matname, kname));
      }
      else if(channel=="node")
        {
          //std::cout << "channnel " << " is node. param=" << str  << std::endl;
          uint32_t nn = stoi(push_param(&str));
          double x = stod(push_param(&str));
          double y = stod(str);
          //std::cout << "nn = " << nn << " x= " << x << " y = " <<  y  << std::endl;
          CPPL::dcovector x_0(2);
          x_0(0) = x; x_0(1) = y;
          //std::cout <<"x_0=" <<  x_0;
          OBJ.add_node(new node(x_0, nn));
          //std::cout << "nn = " << nn << " x= " << OBJ.Nodes[OBJ.Nodes.size() - 1] -> x_0(0) << " y = " <<  OBJ.Nodes[OBJ.Nodes.size() - 1] -> x_0(1)  << std::endl;
        }
      else if(channel == "tria")
        {
          //std::cout << "channnel " << "is tria"  << std::endl;        
          std::string matname = push_param(&str);
          uint32_t en = stoi(push_param(&str));
          uint32_t nn1 = stoi(push_param(&str));
          uint32_t nn2 = stoi(push_param(&str));
          uint32_t nn3 = stoi(str);
          std::vector<uint32_t> nivec = {nn1, nn2, nn3};
          OBJ.add_elem(matname, nivec, en);
          //std::cout << "en = " << en << " nn1= " << nn1 << " nn2 = " << nn2<< " nn3 = " << nn3  << std::endl;
        }
      else if(channel == "displacement")
        {
          //std::cout << "channnel " << "is tria"  << std::endl;        
          //std::string param = push_param(&str);
          uint32_t nn = stoi(push_param(&str));
          uint32_t dir = stoi(push_param(&str));
          uint32_t value = stoi(str);
          //uint32_t nn3 = stoi(str);
          std::vector<int> nnvec = {nn};
          OBJ.add_displacement(new displacement(nnvec, dir, value));
          //std::cout << "en = " << en << " nn1= " << nn1 << " nn2 = " << nn2<< " nn3 = " << nn3  << std::endl;
        }
      else if(channel == "force")
        {
          //std::cout << "channnel " << "is tria"  << std::endl;        
          //std::string param = push_param(&str);
          uint32_t nn = stoi(push_param(&str));
          uint32_t dir = stoi(push_param(&str));
          uint32_t value = stoi(str);
          //uint32_t nn3 = stoi(str);
          std::vector<int> nnvec = {nn};
          OBJ.add_force(new force(nnvec, dir, value));
          //std::cout << "en = " << en << " nn1= " << nn1 << " nn2 = " << nn2<< " nn3 = " << nn3  << std::endl;
        }
      else if(channel == "process")
        {
          //std::cout << "channnel " << "is tria"  << std::endl;        
          //std::string param = push_param(&str);
          std::string name = push_param(&str);
          double t_end = stod(push_param(&str));
          double dt = stod(str);
          pp.push_back(new process(name, t_end, dt));
          //std::cout << "en = " << en << " nn1= " << nn1 << " nn2 = " << nn2<< " nn3 = " << nn3  << std::endl;
        }
      else if(channel == "table")
        {
          std::string name = push_param(&str);
          int n = stoi(str);
          table<double, double> t(name);
          //std::cout << "channnel " << "is table:"<<name << " " << n  << std::endl;                  
          for(size_t i = 0; i<n;i++){
            std::getline(ifs, str, ';');
            double x = stod(push_param(&str));
            double y = stod(str);
            //std::cout << x << " " << y << std::endl;
            t.add_value(x, y);
          }
          OBJ.tables[name] = t;
        }
      else
        {
          std::cout << "channnel " << channel << " is not defined." << std::endl;
          exit(1);
        }
      
    }
  std::flog << "Number of Nodes = " << OBJ.Nodes.size() << std::endl;  
  std::flog << "Number of Elements = " << OBJ.Elements.size() << std::endl;  
  std::flog << "Number of DOF = " << OBJ.Nodes.size() * OBJ.Elements[0] -> dim << std::endl  << std::endl  << std::endl << std::endl;  
}

