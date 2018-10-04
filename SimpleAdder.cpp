#include <systemc.h>


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
  SimpleAdderIf(sc_module_name name) :
    sc_channel(name),
    has_value(0) {};
  
  void add(int a, int b) {
    if (has_value) { wait(read_ev); }
    c = a + b;
    has_value = 1;
    write_ev.notify();
  }

  int get() {
    if (not has_value) { wait(write_ev); }
    int l = c;
    has_value = 0;
    read_ev.notify();    
    return l;
  }

private:
  int c;

  bool has_value;
  sc_event read_ev;
  sc_event write_ev;
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
       for(int i = 0; i < 2; i++) {
         out->add(in_a[i], in_b[i]);
       }
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

       while (c) {
         c = in->get();
         cout << c << flush;
       }
     }
};

class top : public sc_module
{
   public:
     SimpleAdderIf *sa;
     producer *prod_inst;
     consumer *cons_inst;

     top(sc_module_name name) : sc_module(name)
     {
       sa = new SimpleAdderIf("SimpleAdderIf1");
       
       prod_inst = new producer("Producer");
       prod_inst->out(*sa);

       cons_inst = new consumer("Consumer");
       cons_inst->in(*sa);
     }
};
				    

int sc_main (int, char *[]) {
   top top1("Top1");
   sc_start();
   return 0;
}
