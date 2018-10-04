#include <systemc.h>

SC_MODULE(SimpleAdderRtl) {
  sc_in_clk Clk;
  sc_in<bool> Clr;
  
  sc_in<bool> InVld;
  sc_in<sc_lv<32>> a;
  sc_in<sc_lv<32>> b;
  
  sc_out<bool> OutVld;
  sc_out<sc_lv<32>> c;

  sc_uint<32> sum;
  
  void add() {
    if (Clr.read() == 1) {
      OutVld.write(0);
    }
    else if (InVld.read() == 1) {
      sum = a.read().to_uint() + b.read().to_uint();

      c.write(sum);
      OutVld.write(1);
    }
    else {
      OutVld.write(0);
    }
  }

  void print_sum() {
    if (OutVld.read() == 1) {
      cout<<"@" << sc_time_stamp() <<
	" :: SUM "<< sum <<endl;
    }
  }
  
  SC_CTOR(SimpleAdderRtl) {
    SC_METHOD(add);
    sensitive << Clk.pos();
    // Level Sensitive method
    SC_METHOD(print_sum);
    sensitive << Clk.pos();
  } // End of Constructor
};
      
      
