/*!
 * Copyright (c) 2016 by Contributors
 */
#include <string>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <cassert>
#include "../include/MxNetCpp.h"
#include "../network_def.hpp"

using namespace mxnet::cpp;

int main() {
  int batch_size = 32;
  int seq_len = 129;
  int num_hidden = 512;
  int num_embed = 256;
  int num_lstm_layer = 3;
  // int num_round = 21;
  mx_float learning_rate = 0.01;
  mx_float wd = 0.00001;
  /*int clip_gradient = 1;*/
  /*int update_period = 1;*/
  int input_size = 77 + 1;
  int num_label = input_size;

  Symbol rnn_sym = lstm_unroll(num_lstm_layer, seq_len, input_size,
                               num_hidden, num_embed, num_label, 0.0);

  std::map<std::string, NDArray> args_map;
  args_map["data"] = NDArray(Shape(batch_size, seq_len), Context::cpu());
  args_map["softmax_label"] = NDArray(Shape(batch_size, seq_len), Context::cpu());

  for (int i = 0; i < num_lstm_layer; i++) {
    args_map["l" + std::to_string(i) + "_init_c"] =
        NDArray(Shape(batch_size, num_hidden), Context::cpu());
    args_map["l" + std::to_string(i) + "_init_h"] =
        NDArray(Shape(batch_size, num_hidden), Context::cpu());
  }

  rnn_sym.InferArgsMap(Context::cpu(), &args_map, args_map);
  Executor * exec = rnn_sym.SimpleBind(Context::cpu(), args_map);
}
