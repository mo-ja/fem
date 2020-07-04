#include "writer/writer.hpp"
#include "object/object.hpp"

writer::writer(std::string exo_path){
  int CPU_word_size = sizeof(double);
  int IO_word_size = 8;
  exoid = ex_create(exo_path.c_str(), EX_CLOBBER, &CPU_word_size, &IO_word_size);
  ex_put_init(exoid,
              exo_path.c_str(),//title
              OBJ.Elements[0]->dim,//num_dimension
              OBJ.Nodes.size(),//num on nodes
              OBJ.Elements.size(),//num of elements
              1,//num of elem block
              0,//num of node-sets
              0 //num of side-sets
              );
  initialize();
  return;
}

void writer::initialize(){
  return;
}

writer::~writer(){
  std::cout<< "Closing Exodus File...";
  ex_close(exoid);
  std::cout<< "Done" << std::endl;
  return;
}

void writer::write_initial_state(){  
  //write node information
  std::vector<double> x_coord, y_coord;
  std::vector<int> nind2nn;
  char* coordName[2];
  coordName[0] = "xcoor";
  coordName[1] = "ycoor";
  BOOST_FOREACH(auto inp, OBJ.Nodes){
    x_coord.push_back(inp->x_0(0));
    y_coord.push_back(inp->x_0(1));
    nind2nn.push_back(inp->nn);
    std::flog << inp->x_0(0) << " " << inp->x_0(1) << " " <<  inp->nn << " " << std::endl;
  }
  ex_put_coord(exoid, x_coord.data(), y_coord.data(), NULL);
  ex_put_coord_names(exoid, coordName);
  ex_put_node_num_map(exoid, nind2nn.data());
  
  //write element information
  std::vector<int> connectivity;
  std::vector<int> eind2en;
  // this function should be re-designed depending on the homogenates
  ex_put_elem_block(exoid,
                    1,
                    "TRINANGLE",
                    OBJ.Elements.size(),
                    3,
                    0
                    );
  std::flog << "begin element connectivity" << std::endl << std::endl;
  BOOST_FOREACH(auto iep, OBJ.Elements){
    BOOST_FOREACH(auto inp, iep->Np){
      connectivity.push_back(inp->nn);
      //std::flog << inp->x_0(0) << " " << inp->x_0(1) << " " <<  inp->nn << " " << std::endl;
    }
    eind2en.push_back(iep->en);
  }
  ex_put_elem_conn(exoid, 1, connectivity.data());
  ex_put_elem_num_map(exoid, eind2en.data());
  
  return;
}

