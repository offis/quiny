/* This example is taken from the PINAPA paper moy05
   - changed style with astyle
   - commented out wait() in the sc_method (line 34 in the original)

 */

#include "systemc.h"
 #include <iostream>
 #include <vector>

struct module1 : public sc_module
{
  sc_out<bool> port;
  bool m_val;
  void code1 ()
  {
    if (m_val)
    {
      port.write(true);
    }
  }
  SC_HAS_PROCESS(module1);
  module1(sc_module_name name, bool val)
      : sc_module(name), m_val(val)
  {
    // register "void code1()"
    // as an SC_THREAD
    SC_THREAD(code1);
  }
};

struct module2 : public sc_module
{
  sc_in<bool> ports[2];
  void code2 ()
  {
    std::cout << "module2.code2"
    << std::endl;
    int x = ports[1].read();
    for(int i = 0; i < 2; i++)
    {
      sc_in<bool> & port = ports[i];
      if (port.read())
      {
        std::cout << "module2.code2: exit"
        << std::endl;
      }
      //wait(); // wait with no argument.
      // Use static sensitivity list.
    }
  }
  SC_HAS_PROCESS(module2);
  module2(sc_module_name name)
      : sc_module(name)
  {
    // register "void code2()"
    // as an SC_METHOD
    SC_METHOD(code2);
    dont_initialize();
    // static sensitivity list for code2
    sensitive << ports[0];
    sensitive << ports[1];
  }
};

int sc_main(int argc, char ** argv)
{
  bool init1 = true;
  bool init2 = true;
  if (argc > 2)
  {
    init1 = !strcmp(argv[1], "true");
    init2 = !strcmp(argv[2], "true");
  }
  sc_signal<bool> signal1, signal2;
  // instantiate modules
  module1 * instance1_1 =
    new module1("instance1_1", init1);
  module1 * instance1_2 =
    new module1("instance1_2", init2);
  module2 * instance2 =
    new module2("instance2");
  // connect the modules
  instance1_1->port.bind(signal1);
  instance1_2->port.bind(signal2);
  instance2->ports[0].bind(signal1);
  instance2->ports[1].bind(signal2);
  sc_start(-1);
}
