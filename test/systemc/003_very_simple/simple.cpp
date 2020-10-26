#ifndef SYNTHESIS
  #include <systemc.h>
  #define END_IF  
  #define END_WHILE
  #define CTOR_END
#else  
  #include "systemc_synth.h"
#endif


SC_MODULE(Counter)
{
  sc_in<bool>   	    pi_bClk;
  sc_in<bool>         pi_bReset;
  
  void main();

  SC_CTOR(Counter) :
    pi_bClk("pi_bClk"),
    pi_bReset("pi_bReset")
  {
    SC_METHOD(main);
    //sensitive_pos << pi_bClk;
    sensitive << pi_bClk.pos();

  }
};

void 
Counter::main()
{
  if (pi_bReset.read() == true)
  {
    ;
  } 
  else
  {
    ;
  } 
  END_IF
}


int sc_main(int, char**)
{

  sc_signal<bool> m_bClk("m_bClk");
  sc_signal<bool> m_bReset("m_bReset");

  sc_uint<8> myByte;  
  sc_uint<8> myByte2=255;
  //myByte2.toInt() + 1;
  sc_uint<8> myByte3 = myByte+myByte2;
//  cout << myByte2+1 << endl;
//  int myInt = myByte2;
  cpp_dt::Int myInt = myByte2,
              myInt2 = myInt*myInt;
  
  Counter c("c");

  cpp_stmt::If(myByte3 < myByte2);
  {
    sc_uint<8> myByte4 = myByte+myByte2;
  }
  cpp_stmt::ThenEnd();

  c.pi_bClk(m_bClk);
  c.pi_bReset(m_bReset);

  return 0;
}
