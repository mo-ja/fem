#pragma once
#include "main.hpp"
#include "element/element.hpp"
#include "node/node.hpp"
#include "material/material.hpp"
#include "bc/displacement.hpp"
#include "bc/force.hpp"

class object{
public:
  int dim = 2;
  std::vector<element*> Elements;
  std::vector<node*> Nodes;
  std::vector<displacement*> displacements;
  std::vector<force*> forces;
  std::map<uint32_t, uint32_t> nn2NodesInd;
  std::map<uint32_t, uint32_t> en2ElementsInd;
  std::map<std::string, material*> materials;

  object();
  void add_elem(element* elem);
  void add_elem(std::string matname, std::vector<uint32_t> nivec, uint32_t en);
  void add_node(node* node);
  void add_material(material* _mp);
  void add_displacement(displacement* _dp);
  void add_force(force* _fp);
  node* nn2np(uint32_t nn);
  element* en2ep(uint32_t en);
  void test();

  //properties
  size_t NoN(){return Nodes.size();};
  size_t NoE(){return Elements.size();};
  size_t DOF(){return Nodes.size() * dim;};
};
