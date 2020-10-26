#include "cpp/cpp.hpp"

int main(int, char**)
{
  int i;
  int j=1;
  int k=i+j;
  int l=i+1+j;

  CL_CPP::Expression e(1);
  CL_CPP::GenericVariable<int> f;
  CL_CPP::GenericVariable<int> g(e);
  CL_CPP::GenericVariable<int> h;
   
//--  CL_CPP::GenericVariable<int> f(1), g, H(f);
//--
//--  f+1;
//--  1+f;
//--  1+f+1;
//--  1+2+f+2+1;
//--//  1*f;
//--
//--  +f;
//--
//--  if(f+1);
  
  return 0;
}
