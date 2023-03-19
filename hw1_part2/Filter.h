#ifndef SOBEL_FILTER_H_
#define SOBEL_FILTER_H_
#include <systemc>
using namespace sc_core;

#include "filter_def.h"

class Filter : public sc_module {
public:
  sc_in_clk i_clk;
  sc_in<bool> i_rst;
  sc_in<bool> i_next_row;
  sc_fifo_in<unsigned char> i_r;
  sc_fifo_in<unsigned char> i_g;
  sc_fifo_in<unsigned char> i_b;
  sc_fifo_out<int> o_r;
  sc_fifo_out<int> o_g;
  sc_fifo_out<int> o_b;
  int mem_access_cnt;

  SC_HAS_PROCESS(Filter);
  Filter(sc_module_name n);
  ~Filter() = default;

private:
  void do_filter();
  unsigned char val_r[MASK_N];
  unsigned char val_g[MASK_N];
  unsigned char val_b[MASK_N];
  unsigned char in_buf_r[MASK_X][MASK_Y];
  unsigned char in_buf_g[MASK_X][MASK_Y];
  unsigned char in_buf_b[MASK_X][MASK_Y];
  unsigned char median_buf_r[MASK_X][MASK_Y];
  unsigned char median_buf_g[MASK_X][MASK_Y];
  unsigned char median_buf_b[MASK_X][MASK_Y];
  float mean_r;
  float mean_g;
  float mean_b;
};
#endif
