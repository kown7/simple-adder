#include <systemc.h>

class SimpleAdderRtl : public sc_module {
public:
  sc_in_clk Clk;
  sc_in<bool> Clr;
  
  sc_in<bool> InVld;
  sc_in<sc_lv<32>> a;
  sc_in<sc_lv<32>> b;
  
  sc_out<bool> OutVld;
  sc_out<sc_lv<32>> c;

  sc_uint<32> sum;
  
  void add();
  void print_sum();
  SimpleAdderRtl(const sc_module_name& nm);
};
      
      
