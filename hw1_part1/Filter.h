#ifndef SOBEL_FILTER_H_
#define SOBEL_FILTER_H_
#include <systemc>
using namespace sc_core;

#include "filter_def.h"

class Filter : public sc_module {
public:
  sc_in_clk i_clk;
  sc_in<bool> i_rst;
  sc_fifo_in<unsigned char> i_r;
  sc_fifo_in<unsigned char> i_g;
  sc_fifo_in<unsigned char> i_b;
  sc_fifo_out<int> o_r;
  sc_fifo_out<int> o_g;
  sc_fifo_out<int> o_b;

  SC_HAS_PROCESS(Filter);
  Filter(sc_module_name n);
  ~Filter() = default;

private:
  void do_filter();
  unsigned char val_r[9];
  unsigned char val_g[9];
  unsigned char val_b[9];
  float mean_r;
  float mean_g;
  float mean_b;
};
#endif
