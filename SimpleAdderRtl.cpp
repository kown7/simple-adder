#include "SimpleAdderRtl.hpp"

void SimpleAdderRtl::add() {
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

void SimpleAdderRtl::print_sum() {
  if (OutVld.read() == 1) {
    cout<<"@" << sc_time_stamp() <<
      " :: SUM "<< sum <<endl;
  }
}
  
  
SimpleAdderRtl::SimpleAdderRtl(const sc_module_name& nm) {
  typedef SimpleAdderRtl SC_CURRENT_USER_MODULE;
  SC_METHOD(add);
  sensitive << Clk.pos();
  SC_METHOD(print_sum);
  sensitive << Clk.pos();
} // End of Constructor

      
      
