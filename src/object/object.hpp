#pragma once
#include "main.hpp"
#include "element/element.hpp"
#include "node/node.hpp"
#include "material/material.hpp"
#include "bc/temperature.hpp"
//#include "bc/displacement.hpp"
//#include "bc/force.hpp"
#include "table/table.hpp"

class object{
public:
  int dim = 1;
  std::vector<element*> Elements;
  std::vector<node*> Nodes;
  std::vector<temperature*> temperatures;
  //std::vector<force*> forces;
  std::map<uint32_t, uint32_t> nn2NodesInd;
  std::map<uint32_t, uint32_t> en2ElementsInd;
  std::map<std::string, material*> materials;
  std::map<std::string, table<double, double>> tables;
  
  object();
  void add_elem(element* elem);
  void add_elem(std::string matname, std::vector<int> nivec, uint32_t en);
  void add_node(node* node);
  void add_material(material* _mp);
  void add_temperature(temperature* _dp);
  //void add_force(force* _fp);
  //void add_tables(table* _tp);
  node* nn2np(uint32_t nn);
  element* en2ep(uint32_t en);
  void test();

  //properties
  size_t NoN(){return Nodes.size();};
  size_t NoE(){return Elements.size();};
  size_t DOF(){return Nodes.size() * dim;};
};
