#include <systemc.h>

#include "SimpleAdderRtl.hpp"


int sc_main (int argc, char* argv[]) {
  sc_clock Clk("mainclock", 100, SC_NS);
  sc_signal<bool> Clr;
  sc_signal<bool> InVld;
  sc_signal<sc_lv<32>> a;
  sc_signal<sc_lv<32>> b;
  sc_signal<bool> OutVld;
  sc_signal<sc_lv<32>> c;

  SimpleAdderRtl sa("SimpleAdderRTL");
  sa.Clk(Clk);
  sa.Clr(Clr);
  sa.InVld(InVld);
  sa.a(a);
  sa.b(b);
  sa.OutVld(OutVld);
  sa.c(c);

  Clr.write(0);
  sc_start(10, SC_US);

  a = 32;
  b = 15;
  InVld.write(1);
  sc_start(100, SC_NS);
  InVld.write(0);
  sc_start(10, SC_US);
  
  a = 456777;
  b = 234;
  InVld.write(1);
  sc_start(100, SC_NS);
  assert(OutVld.read() == 1);
  assert(c.read() == 456777 + 234);
  InVld.write(0);
  sc_start(10, SC_US);


  sc_stop();
  return 0;
}
