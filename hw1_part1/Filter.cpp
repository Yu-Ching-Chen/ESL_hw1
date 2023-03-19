#include <cmath>

#include "Filter.h"

Filter::Filter(sc_module_name n) : sc_module(n) {
  SC_THREAD(do_filter);
  sensitive << i_clk.pos();
  dont_initialize();
  reset_signal_is(i_rst, false);
}

// sobel mask
const float mean_mask[MASK_N] = {0.1, 0.1, 0.1, 0.1, 0.2, 0.1, 0.1, 0.1, 0.1};

void Filter::do_filter() {
  while (true) {

    mean_r = 0;
    mean_g = 0;
    mean_b = 0;

    for (unsigned int i = 0; i < MASK_N; ++i) {
      for (unsigned int v = 0; v < MASK_N; ++v) {
          val_r[v] = i_r.read();
          val_g[v] = i_g.read();
          val_b[v] = i_b.read();
          mem_access_cnt++;
      }
      std::sort(val_r, val_r + 9);
      std::sort(val_g, val_g + 9);
      std::sort(val_b, val_b + 9);

      mean_r = mean_r + val_r[4] * mean_mask[i];
      mean_g = mean_g + val_g[4] * mean_mask[i];
      mean_b = mean_b + val_b[4] * mean_mask[i];
    }

    o_r.write(floor(mean_r));
    o_g.write(floor(mean_g));
    o_b.write(floor(mean_b));
    wait(10); //emulate module delay
  }
}
