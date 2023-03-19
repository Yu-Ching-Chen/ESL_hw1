#include <cmath>

#include "Filter.h"

Filter::Filter(sc_module_name n) : sc_module(n) {
  SC_THREAD(do_filter);
  sensitive << i_clk.pos();
  dont_initialize();
  reset_signal_is(i_rst, false);
}

// sobel mask
const float mean_mask[MASK_Y][MASK_X] = {{0.1, 0.1, 0.1}, {0.1, 0.2, 0.1}, {0.1, 0.1, 0.1}};

void Filter::do_filter() {
  while (true) {

    if (i_next_row.read()) {

      int l = 0; // median buffer x index
      int m = 0; // midian buffer y index

      // row 1
      int i = 0;
      for (int w = 0; w < MASK_Y; ++w) {
        for (int v = 0; v < MASK_X; ++v) {
          in_buf_r[v][w] = i_r.read();
          in_buf_g[v][w] = i_g.read();
          in_buf_b[v][w] = i_b.read();
          val_r[3 * w + v] = in_buf_r[v][w];
          val_g[3 * w + v] = in_buf_g[v][w];
          val_b[3 * w + v] = in_buf_b[v][w];
          mem_access_cnt++;
        }
      }
      std::sort(val_r, val_r + 9);
      std::sort(val_g, val_g + 9);
      std::sort(val_b, val_b + 9);

      median_buf_r[l][m] = val_r[4];
      median_buf_g[l][m] = val_g[4];
      median_buf_b[l][m] = val_b[4];
      
      i = i + 1;
      l++;

      while (i < 3) {
        for (int w = 0; w < MASK_Y; ++w) {
          for (int v = 0; v < MASK_X; ++v) {
            if (v == MASK_X - 1) {
              in_buf_r[v][w] = i_r.read();
              in_buf_g[v][w] = i_g.read();
              in_buf_b[v][w] = i_b.read();
              mem_access_cnt++;
            } else {
              in_buf_r[v][w] = in_buf_r[v + 1][w];
              in_buf_g[v][w] = in_buf_g[v + 1][w];
              in_buf_b[v][w] = in_buf_b[v + 1][w];
            }
            val_r[3 * w + v] = in_buf_r[v][w];
            val_g[3 * w + v] = in_buf_g[v][w];
            val_b[3 * w + v] = in_buf_b[v][w];
          }
        }
        std::sort(val_r, val_r + 9);
        std::sort(val_g, val_g + 9);
        std::sort(val_b, val_b + 9);

        median_buf_r[l][m] = val_r[4];
        median_buf_g[l][m] = val_g[4];
        median_buf_b[l][m] = val_b[4];

        i = i + 1;
        l++;
      }

      m++;
      l--;
      // row 2
      for (int w = 0; w < MASK_Y; ++w) {
        for (int v = 0; v < MASK_X; ++v) {
            if (w == MASK_Y - 1) {
              in_buf_r[v][w] = i_r.read();
              in_buf_g[v][w] = i_g.read();
              in_buf_b[v][w] = i_b.read();
              mem_access_cnt++;
            } else {
              in_buf_r[v][w] = in_buf_r[v][w + 1];
              in_buf_g[v][w] = in_buf_g[v][w + 1];
              in_buf_b[v][w] = in_buf_b[v][w + 1];
            }
            val_r[3 * w + v] = in_buf_r[v][w];
            val_g[3 * w + v] = in_buf_g[v][w];
            val_b[3 * w + v] = in_buf_b[v][w];
        }
      }
      std::sort(val_r, val_r + 9);
      std::sort(val_g, val_g + 9);
      std::sort(val_b, val_b + 9);

      median_buf_r[l][m] = val_r[4];
      median_buf_g[l][m] = val_g[4];
      median_buf_b[l][m] = val_b[4];

      i = i + 1; // i = 4
      l--;

      while (i < 6) {
        for (int w = 0; w < MASK_Y; ++w) {
          for (int v = MASK_X - 1; v >= 0; --v) {
            if (v == 0) {
              in_buf_r[v][w] = i_r.read();
              in_buf_g[v][w] = i_g.read();
              in_buf_b[v][w] = i_b.read();
              mem_access_cnt++;
            } else {
              in_buf_r[v][w] = in_buf_r[v - 1][w];
              in_buf_g[v][w] = in_buf_g[v - 1][w];
              in_buf_b[v][w] = in_buf_b[v - 1][w];
            }
            
            val_r[3 * w + v] = in_buf_r[v][w];
            val_g[3 * w + v] = in_buf_g[v][w];
            val_b[3 * w + v] = in_buf_b[v][w];
                  
          }
        }
        std::sort(val_r, val_r + 9);
        std::sort(val_g, val_g + 9);
        std::sort(val_b, val_b + 9);

        median_buf_r[l][m] = val_r[4];
        median_buf_g[l][m] = val_g[4];
        median_buf_b[l][m] = val_b[4];

        i = i + 1;
        l--;
      }

      m++;
      l++;

      // row 3
      for (int w = 0; w < MASK_Y; ++w) {
        for (int v = 0; v < MASK_X; ++v) {
            if (w == MASK_Y - 1) {
              in_buf_r[v][w] = i_r.read();
              in_buf_g[v][w] = i_g.read();
              in_buf_b[v][w] = i_b.read();
              mem_access_cnt++;
            } else {
              in_buf_r[v][w] = in_buf_r[v][w + 1];
              in_buf_g[v][w] = in_buf_g[v][w + 1];
              in_buf_b[v][w] = in_buf_b[v][w + 1];
            }
            val_r[3 * w + v] = in_buf_r[v][w];
            val_g[3 * w + v] = in_buf_g[v][w];
            val_b[3 * w + v] = in_buf_b[v][w];
        }
      }
      std::sort(val_r, val_r + 9);
      std::sort(val_g, val_g + 9);
      std::sort(val_b, val_b + 9);

      median_buf_r[l][m] = val_r[4];
      median_buf_g[l][m] = val_g[4];
      median_buf_b[l][m] = val_b[4];

      i = i + 1; // i = 7
      l++;

      while (i < 9) {
        for (int w = 0; w < MASK_Y; ++w) {
          for (int v = 0; v < MASK_X; ++v) {
            if (v == MASK_X - 1) {
              in_buf_r[v][w] = i_r.read();
              in_buf_g[v][w] = i_g.read();
              in_buf_b[v][w] = i_b.read();
              mem_access_cnt++;
            } else {
              in_buf_r[v][w] = in_buf_r[v + 1][w];
              in_buf_g[v][w] = in_buf_g[v + 1][w];
              in_buf_b[v][w] = in_buf_b[v + 1][w];
            }
            val_r[3 * w + v] = in_buf_r[v][w];
            val_g[3 * w + v] = in_buf_g[v][w];
            val_b[3 * w + v] = in_buf_b[v][w];
          }
        }
        std::sort(val_r, val_r + 9);
        std::sort(val_g, val_g + 9);
        std::sort(val_b, val_b + 9);

        median_buf_r[l][m] = val_r[4];
        median_buf_g[l][m] = val_g[4];
        median_buf_b[l][m] = val_b[4];
        i = i + 1;
        l++;
      }
    } else {
      for (int w = 0; w < MASK_Y; ++w) {
        for (int v = 0; v < MASK_X - 1; ++v) {
          median_buf_r[v][w] = median_buf_r[v + 1][w];
          median_buf_g[v][w] = median_buf_g[v + 1][w];
          median_buf_b[v][w] = median_buf_b[v + 1][w];
        }
      }
      int l = MASK_X - 1; // median buffer x index
      int m = 0; // midian buffer y index

      for (m = 0; m < MASK_Y; ++m) {
        if (m == 0) {
          for (int w = 0; w < MASK_Y; ++w) {
            for (int v = 0; v < MASK_X; ++v) {
              in_buf_r[v][w] = i_r.read();
              in_buf_g[v][w] = i_g.read();
              in_buf_b[v][w] = i_b.read();
              mem_access_cnt++;
              val_r[3 * w + v] = in_buf_r[v][w];
              val_g[3 * w + v] = in_buf_g[v][w];
              val_b[3 * w + v] = in_buf_b[v][w];
            }
          }
        } else {
          for (int w = 0; w < MASK_Y; ++w) {
            for (int v = 0; v < MASK_X; ++v) {
                if (w == MASK_Y - 1) {
                  in_buf_r[v][w] = i_r.read();
                  in_buf_g[v][w] = i_g.read();
                  in_buf_b[v][w] = i_b.read();
                  mem_access_cnt++;
                } else {
                  in_buf_r[v][w] = in_buf_r[v][w + 1];
                  in_buf_g[v][w] = in_buf_g[v][w + 1];
                  in_buf_b[v][w] = in_buf_b[v][w + 1];
                }
                val_r[3 * w + v] = in_buf_r[v][w];
                val_g[3 * w + v] = in_buf_g[v][w];
                val_b[3 * w + v] = in_buf_b[v][w];
            }
          }
        }
        std::sort(val_r, val_r + 9);
        std::sort(val_g, val_g + 9);
        std::sort(val_b, val_b + 9);

        median_buf_r[l][m] = val_r[4];
        median_buf_g[l][m] = val_g[4];
        median_buf_b[l][m] = val_b[4];
      }
    }

    mean_r = 0;
    mean_g = 0;
    mean_b = 0;
    for (int w = 0; w < MASK_Y; ++w) {
      for (int v = 0; v < MASK_X; ++v) {
        mean_r = mean_r + (median_buf_r[v][w] * mean_mask[w][v]);
        mean_g = mean_g + (median_buf_g[v][w] * mean_mask[w][v]);
        mean_b = mean_b + (median_buf_b[v][w] * mean_mask[w][v]);
      }
    }

    o_r.write(floor(mean_r));
    o_g.write(floor(mean_g));
    o_b.write(floor(mean_b));

    wait(10); //emulate module delay
  }
}
