#include "object/object.hpp"

object::object(){
  
}

void object::add_elem(element* elem){
  VERBOSE_REPORT;
  en2ElementsInd[elem->en] = Elements.size();
  Elements.push_back(elem);
}

void object::add_elem(std::string _matname, std::vector<int> nivec, uint32_t en){
  en2ElementsInd[en] = Elements.size();
  std::vector<node*> nodes;
  BOOST_FOREACH(auto inn, nivec){
    nodes.push_back(nn2np(inn));
  }
  //element* el = new element(nodes, en);
  Elements.push_back(new element(materials[_matname], nodes, en));
  //std::cout << "elem id = " << en << std::endl;
  //std::cout << "Elements["<<Elements.size()-1<<"]->en = " << Elements[Elements.size()-1] -> en << std::endl;
}
void object::add_node(node* node){
  nn2NodesInd[node->nn] = Nodes.size();
  Nodes.push_back(node);
}
void object::add_material(material* _mp){
  materials[_mp->matname] = _mp;
}
void object::add_displacement(displacement* _dp){
  displacements.push_back(_dp);
}
void object::add_force(force* _fp){
  forces.push_back(_fp);
}

node* object::nn2np(uint32_t nn){
  return Nodes[nn2NodesInd[nn]];
}
element* object::en2ep(uint32_t en){
  return Elements[en2ElementsInd[en]];
}

void object::test(){

}
