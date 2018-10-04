#include <systemc.h>

#include "SimpleAdderRtl.hpp"


class AddNumIf : virtual public sc_interface
{
public:
  virtual void add(int a, int b) = 0;
};

class ResNumIf : virtual public sc_interface
{
public:
  virtual int get() = 0;
};


class SimpleAdderIf : public sc_channel, public AddNumIf, public ResNumIf
{
public:
  SimpleAdderIf(sc_module_name name, sc_clock& ClkIn) :
    sc_channel(name),
    has_value(0),
    Clk(ClkIn),
    sa("SimpleAdderRTL")
  {
    sa.Clk(Clk);
    sa.Clr(Clr);
    sa.InVld(InVld);
    sa.a(a);
    sa.b(b);
    sa.OutVld(OutVld);
    sa.c(c);

    Clr.write(0);
  };

  void add(int a_in, int b_in) {
    if (has_value) { wait(read_ev); }
    wait(Clk.posedge_event());

    c_local = a_in + b_in;
    a.write(a_in);
    b.write(b_in);
    InVld.write(1);
    wait(Clk.posedge_event());

    has_value = 1;
    write_ev.notify();
    InVld.write(0);
  }

  int get() {
    if (not has_value) { wait(write_ev); }
    wait(Clk.posedge_event());
    int l = c_local;

    cout<<"@" << sc_time_stamp() << " :: get "<< l <<endl;
    cout<<"@" << sc_time_stamp() << " :: rtl "<< c.read().to_uint() <<endl;
    assert(l == c.read());

    has_value = 0;
    read_ev.notify();
    return l;
  }

private:
  int c_local;

  bool has_value;
  sc_event read_ev;
  sc_event write_ev;


  sc_clock& Clk;
  sc_signal<bool> Clr;
  sc_signal<bool> InVld;
  sc_signal<sc_lv<32>> a;
  sc_signal<sc_lv<32>> b;
  sc_signal<bool> OutVld;
  sc_signal<sc_lv<32>> c;

  SimpleAdderRtl sa;
};


class producer : public sc_module
{
   public:
     sc_port<AddNumIf> out;

     SC_HAS_PROCESS(producer);

     producer(sc_module_name name) : sc_module(name)
     {
       SC_THREAD(main);
     }

     void main()
     {
       int i = 0;
       int in_b[] = { 2, 3 };
       int in_a[] = { 12, 32 };

       wait(500, SC_NS);

       for(int i = 0; i < 2; i++) {
         out->add(in_a[i], in_b[i]);
	 wait(12.4, SC_US);
       }
       cout << "Producer is done" << endl << flush;
     }
};

class consumer : public sc_module
{
   public:
     sc_port<ResNumIf> in;

     SC_HAS_PROCESS(consumer);

     consumer(sc_module_name name) : sc_module(name)
     {
       SC_THREAD(main);
     }

     void main()
     {
       int c = 1;
       cout << endl << endl;

       for(int i = 0; i < 2; i++) {
         c = in->get();
         cout << c << endl << flush;
       }
       cout << "Consumer is done" << endl << flush;
     }
};

class top : public sc_module
{
public:
  sc_clock *clk;
  SimpleAdderIf *sa;
  producer *prod_inst;
  consumer *cons_inst;

  top(sc_module_name name) : sc_module(name)
  {
    typedef top SC_CURRENT_USER_MODULE;

    clk = new sc_clock("mainclock", 100, SC_NS);
    sa = new SimpleAdderIf("SimpleAdderIf1", *clk);

    prod_inst = new producer("Producer");
    prod_inst->out(*sa);

    cons_inst = new consumer("Consumer");
    cons_inst->in(*sa);

    SC_THREAD(clk_timeout);
  }

  void clk_timeout() {
    wait(100, SC_MS);
    sc_stop();
  }
};


int sc_main (int, char *[]) {
  top top1("Top1");
  sc_start();
  return 0;
}
