
#include <iostream>
#include <string>
#include <cassert>

#include "quiny/ir/Type.hpp"
#include "quiny/collector/TypeHelper.hpp"


using namespace std;



using quiny::collector::TypeHelper;

template<typename T>
string
getTypeName()
{
  TypeHelper<T> th;
  return th.getType()->getName();
}

int sc_main(int, char**)
{

#define ASSERT_TYPE(typ) assert(getTypeName<typ>() == string(#typ));
#define PRINT_TYPE(typ) cout << getTypeName<typ>() << endl;


#define ASSERT_TYPE_CV(typ)\
  ASSERT_TYPE(typ)\
  ASSERT_TYPE(const typ)\
  ASSERT_TYPE(volatile typ)\
  ASSERT_TYPE(const volatile typ)

  ASSERT_TYPE_CV(bool)
  ASSERT_TYPE_CV(char)
  ASSERT_TYPE_CV(wchar_t)
  ASSERT_TYPE_CV(signed char)
  ASSERT_TYPE_CV(unsigned char)
  ASSERT_TYPE_CV(short)
  ASSERT_TYPE_CV(unsigned short)
  ASSERT_TYPE_CV(int)
  ASSERT_TYPE_CV(unsigned int)
  ASSERT_TYPE_CV(long)
  ASSERT_TYPE_CV(unsigned long)
  ASSERT_TYPE_CV(long long)
  ASSERT_TYPE_CV(float)
  ASSERT_TYPE_CV(double)
  ASSERT_TYPE_CV(long double)

  std::cout << "Congratulations! No assertion failed." << std::endl; 
  return 0;
}
