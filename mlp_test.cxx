
#include "mlp.hpp"
#include "test_data.hpp"

using namespace mxnet::cpp;

int main() {

  MLPNative m = MLPNative();
  int lsize[1] = {10};
  m.setLayers(lsize, 1, 2);
  char * act[1] = {"tanh"};
  m.setAct(act);
  m.setData(aptr_x, 101, 60);
  m.setLabel(aptr_y, 101);
  m.build_mlp();
  Symbol pred;
  for (int i = 0; i < 100; i++) {
    pred = m.train();
    std::cout << m.compAccuracy(pred) << std::endl;
  }
      
      //m.train();
  //std::cout << m.compAccuracy(pred) << std::endl;
  //pred = m.train();
  //std::cout << m.compAccuracy(pred) << std::endl;
}
