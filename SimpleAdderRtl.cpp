#include <systemc.h>

SC_MODULE(SimpleAdderRtl) {
  sc_in_clk Clk;
  sc_in_bool Clr;
  
  sc_in_bool InVld;
  sc_in<sc_lv<32>> a;
  sc_in<sc_lv<32>> b;
  
  sc_out_bool OutVld;
  sc_out<sc_lv<32>> c;

  sc_uint<32> sum;
  
  void add() {
    if (Clr.read() == 1) {
      sc_out.write(0);
    }
    else if (InVld.read() == 1) {
      sum = a.to_uint() + b.to_uint();

      c.write(sum);
      OutVld.write(1);
    }
    else {
      OutVld.write(0);
    }
  }

  void print_sum() {
    cout<<"@" << sc_time_stamp() <<
      " :: SUM "<< sum <<endl;
  }
  
  SC_CTOR(first_counter) {
    SC_METHOD(add);
    sensitive << clock.pos();
    // Level Sensitive method
    SC_METHOD(print_sum);
    sensitive << sum;
  } // End of Constructor
}
      
      
