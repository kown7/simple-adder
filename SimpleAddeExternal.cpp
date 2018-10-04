#ifndef _SCGENMOD_SimpleAdder_
#define _SCGENMOD_SimpleAdder_

#include "systemc.h"

class SimpleAdder : public sc_foreign_module
{
public:
    sc_in<sc_logic> clk;
    sc_in<sc_logic> clr;
    sc_in<sc_logic> invld;
    sc_in<sc_lv<32> > a;
    sc_in<sc_lv<32> > b;
    sc_out<sc_logic> outvld;
    sc_out<sc_lv<32> > c;


    SimpleAdder(sc_module_name nm, const char* hdl_name)
     : sc_foreign_module(nm),
       clk("clk"),
       clr("clr"),
       invld("invld"),
       a("a"),
       b("b"),
       outvld("outvld"),
       c("c")
    {
        elaborate_foreign_module(hdl_name);
    }
    ~SimpleAdder()
    {}

};

#endif

