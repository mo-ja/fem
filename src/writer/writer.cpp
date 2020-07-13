#include "writer/writer.hpp"
#include "object/object.hpp"

writer::writer(std::string exo_path){
  int CPU_word_size = sizeof(double);
  int IO_word_size = 4;
  exoid = ex_create(exo_path.c_str(), EX_CLOBBER, &CPU_word_size, &IO_word_size);
  ex_put_init(exoid,
              exo_path.c_str(),//title
              3,//num_dimension
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
  std::vector<double> x_coord, y_coord, z_coord;
  std::vector<int> nind2nn;
  char* coordName[3];
  coordName[0] = "xcoor";
  coordName[1] = "ycoor";
  coordName[2] = "zcoor";
  BOOST_FOREACH(auto inp, OBJ.Nodes){
    x_coord.push_back(inp->x_0(0));
    y_coord.push_back(inp->x_0(1));
    z_coord.push_back(inp->x_0(2));
    nind2nn.push_back(inp->nn);
    std::flog << inp->x_0(0) << " " << inp->x_0(1) << " " <<  inp->x_0(2) <<" "<<inp->nn << " " << std::endl;
  }
  ex_put_coord(exoid, x_coord.data(), y_coord.data(),z_coord.data());
  ex_put_coord_names(exoid, coordName);
  ex_put_node_num_map(exoid, nind2nn.data());
  
  //write element information
  std::vector<int> connectivity;
  std::vector<int> eind2en;
  // this function should be re-designed depending on the homogenates
  ex_put_elem_block(exoid,
                    1,
                    "TETRA",
                    OBJ.Elements.size(),
                    4,
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

  // Write Output Datas
  ex_put_variable_param(exoid,
                        EX_NODAL,
                        1
                        );
  char* node_var_name[1] = {"Temperature"};
  ex_put_variable_names(exoid, EX_NODAL, 1, node_var_name);

  
  ex_put_variable_param(exoid,
                        EX_ELEM_BLOCK,
                        4
                        );
  char* elem_var_name[4] = {"Heat Flux x", "Heat Flux y","Heat Flux z","Heat Flux Magnitude"};
  ex_put_variable_names(exoid, EX_ELEM_BLOCK, 4, elem_var_name);
  

  ex_put_elem_var_tab(exoid,
                      1,
                      4,
                      (std::vector<int>(1, 1)).data()
                      );
  
  return;
}

void writer::write_nodal_value(int time_step){
  std::vector<double> v;
  BOOST_FOREACH(node* inp, OBJ.Nodes){
    v.push_back(inp->T_a);
  }
  ex_put_nodal_var(exoid, time_step, 1, OBJ.Nodes.size(), v.data());
}

void writer::write_element_value(int time_step){
  std::vector<double> vx;
  std::vector<double> vy;
  std::vector<double> vz;
  std::vector<double> vmag;
  BOOST_FOREACH(element* iep, OBJ.Elements){
    dcovec3 x = iep->q_a;
    vx.push_back(x(0));
    vy.push_back(x(1));
    vz.push_back(x(2));
    vmag.push_back(sqrt(dot3(x, x)));
  }
  ex_put_elem_var(exoid, time_step, 1, 1, OBJ.Elements.size(), vx.data());
  ex_put_elem_var(exoid, time_step, 2, 1, OBJ.Elements.size(), vy.data());
  ex_put_elem_var(exoid, time_step, 3, 1, OBJ.Elements.size(), vz.data());
  ex_put_elem_var(exoid, time_step, 4, 1, OBJ.Elements.size(), vmag.data());
}


void writer::write_state(int time_step){
  std::flog << "write state @" << time_step;
  ex_put_time(exoid, time_step+1, &time_step);
  write_nodal_value(time_step);
  write_element_value(time_step);
  std::flog << "... Done"<<std::endl;
}
