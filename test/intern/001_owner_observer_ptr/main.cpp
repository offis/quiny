#include "quiny/utils/utils.hpp"

#include <iostream>

#include <cassert>

using namespace quiny::utils;


class Base
{
  public:
    explicit 
    Base(int i) : m_i(i) {}
    
    virtual
    ~Base() {}
    
    virtual
    int
    classId() const { return 1; }
    
    int   m_i;
};

class Derived : public Base
{
  public:
    explicit
    Derived(int i) : Base(i) {}
    
    virtual
    ~Derived() {}
    
    virtual
    int
    classId() const { return 2;}
};

template<typename T>
struct Sink
{
  explicit Sink(owner_ptr<T> s) : m_ptr(s) {}
  
  owner_ptr<T> m_ptr;
};    

int myFunc(owner_ptr<const Base> xyz)
{
  return xyz->classId();
}

int sc_main(int, char**)
{
  {
    // Start with an initialised owner
    owner_ptr<int> i(new int);

    *i = 2;

    // Did the assignment work?
    assert(2 == *i);


    // Let's add an observer (by initialisation)
    observer_ptr<int> j(i);

    // Check that i and j are non-NULL
    assert(i);
    assert(j);


    // Assign something to j and check if it also affected i
    *j = 3;  
    assert(3 == *j);
    assert(3 == *i);


    // Change the owner (by initialisation)
    owner_ptr<int> k(i);

    // Check if i lost the target and that k and j are valid
    assert(!i);
    assert(3 == *k);
    assert(j);
    assert(3 == *j);

    // Check if k and j are referring to the same target
    *k = 4;
    assert(4 == *j);
    *j = 5;
    assert(5 == *k);

    // Remove the observer
    j.toNull();
    assert(!j);
    assert(k);

    // Test polymorphic pointers
    owner_ptr<Base> p_b(new Base(4));
    owner_ptr<Base> p_d(new Derived(5));

    assert(4 == p_b->m_i);
    assert(5 == p_d->m_i);
    assert(1 == p_b->classId());
    assert(2 == p_d->classId());

    owner_ptr<Base> p_b2(p_b);
    owner_ptr<Base> p_d2(p_d);

    assert(!p_b);
    assert(!p_d);
    assert(4 == p_b2->m_i);
    assert(5 == p_d2->m_i);
    assert(1 == p_b2->classId());
    assert(2 == p_d2->classId());

    // Test pointer to const elements
    owner_ptr<const Base> p_cb(new Base(6));
    owner_ptr<const Base> p_cd(new Derived(7));

    assert(6 == p_cb->m_i);
    assert(7 == p_cd->m_i);
    assert(1 == p_cb->classId());
    assert(2 == p_cd->classId());

    Base *p_base = new Base(8);
    Derived *p_derived = new Derived(9);

    owner_ptr<const Base> p_cb2(p_base);
    owner_ptr<const Base> p_cd2(p_derived);

    assert(8 == p_cb2->m_i);
    assert(9 == p_cd2->m_i);
    assert(1 == p_cb2->classId());
    assert(2 == p_cd2->classId());

    // Init from sub classes
    owner_ptr<const Base> p2_b(p_cd2);

    assert(9 == p2_b->m_i);
    assert(2 == p2_b->classId());
    assert(!p_cd2);

    // Destroy via Sink
    {
      Sink<const Base> sink(p2_b);
    }
    assert(!p2_b);

    assert(p_cb2);
    assert(1 == myFunc(p_cb2));
    // Note the pointer will be consumed by myFunc
    assert(!p_cb2);

    // Mix owner_ptrs with different types
    Derived *p_derived2 = new Derived(10);
    owner_ptr<const Derived> p3_d(p_derived2);

    // Check assignments
    owner_ptr<const Base> p3_b(new Base(11));  

    assert(!p2_b);

    p2_b = p3_b;

    assert(p2_b);
    assert(!p3_b);
    assert(11 == p2_b->m_i);

    p2_b = p2_b;

    assert(p2_b);
    assert(11 == p2_b->m_i);

    p3_b = p2_b = p2_b;

    assert(p3_b);
    assert(!p2_b);
    assert(11 == p3_b->m_i);

    // Check default ctor  
    owner_ptr<const Base> p_defaultCtor;
    assert(!p_defaultCtor);

    p_defaultCtor = p3_b;

    assert(!p3_b);
    assert(11 == p_defaultCtor->m_i);

    // Add observers
    observer_ptr<const Base> obs1(p_defaultCtor);

    assert(obs1);
    assert(p_defaultCtor);
    assert(11 == obs1->m_i);

    observer_ptr<const Base> obs2, obs3;

    assert(!obs2);
    assert(!obs3);

    obs2 = p_defaultCtor;
    obs3 = obs1;

    assert(obs2 && obs3 && 11 == obs2->m_i && 11 == obs3->m_i);  

    obs3 = obs3;

    assert(obs3 && 11 == obs3->m_i);
    assert(obs1 == obs2 && obs2 == obs3 && obs1 == obs3);

    // Try to get the pointer out of the owner

    obs1.toNull();
    obs2.toNull();
    obs3.toNull();

    const Base *fromOwner = p_defaultCtor.release();

    assert(!p_defaultCtor);

    // Mixing owner_ptr with different type

    owner_ptr<const Derived> p4_d(new Derived(12)),
                             p4_d2(new Derived(13));

    owner_ptr<const Base> p4_b(p4_d),
                          p4_b2;

    p4_b2 = p4_d2;

    assert(p4_b && 2 == p4_b->classId() && 12 == p4_b->m_i);
    assert(p4_b2 && 2 == p4_b2->classId() && 13 == p4_b2->m_i);


    // Mixing owner and observer with different types

    owner_ptr<const Derived> p5_d(new Derived(14)),
                             p5_d2(new Derived(15));

    observer_ptr<const Base> obs5_b1(p5_d),
                             obs5_b2;

    obs5_b2 = p5_d2;                           

    assert(p5_d && p5_d2);
    assert(obs5_b1 && 2 == obs5_b1->classId() && 14 == obs5_b1->m_i);
    assert(obs5_b2 && 2 == obs5_b2->classId() && 15 == obs5_b2->m_i);

    owner_ptr<Derived> p5_d3(new Derived(14));
    observer_ptr<Derived> obs5_d1(p5_d3);
    observer_ptr<Base> obs5_b3(obs5_d1);
    
    assert(p5_d3 && obs5_d1 && obs5_b3);
    assert(2 == p5_d3->classId() && 14 == p5_d3->m_i &&
           2 == obs5_d1->classId() && 14 == obs5_d1->m_i &&
           2 == obs5_b3->classId() && 14 == obs5_b3->m_i );
           

    // Dynamic casts of owners

    owner_ptr<const Base> p6_b(new Derived(16)),
                          p6_b2(new Derived(17));


    owner_ptr<const Derived>  p6_d(p6_b.dyn_cast<const Derived>()),
                              p6_d2;

    p6_d2 = p6_b2.dyn_cast<const Derived>();

    assert(p6_d && 2 == p6_d->classId() && 16 == p6_d->m_i);
    assert(p6_d2 && 2 == p6_d2->classId() && 17 == p6_d2->m_i);
    assert(!p6_b);
    assert(!p6_b2);

    // Dynamic casts of observers

    owner_ptr<const Derived> p7_d(new Derived(18)),
                             p7_d2(new Derived(19));

    observer_ptr<const Base> p7_obs(p7_d),
                             p7_obs2;

    p7_obs2 = p7_d2;

    observer_ptr<const Derived> p7_obs3(p7_obs.dyn_cast<const Derived>()),
                                p7_obs4;

    p7_obs4 = p7_obs2.dyn_cast<const Derived>();

    assert(p7_obs3 && 2 == p7_obs3->classId() && 18 == p7_obs3->m_i);
    assert(p7_obs4 && 2 == p7_obs4->classId() && 19 == p7_obs4->m_i);

    assert(p7_d && p7_d2 && p7_obs && p7_obs2);

    p7_obs3.toNull();
    p7_obs4.toNull();
    
    // End of local block in order to kill all owners and observers above
  }

  // Dynamic casts which fail

  owner_ptr<const Base> p8_b(new Base(20));
  
  owner_ptr<const Derived> p8_d(p8_b.dyn_cast<const Derived>());

  assert(p8_b && !p8_d);
  assert(1 == p8_b->classId() && 20 == p8_b->m_i);

  observer_ptr<const Base> obs8_b(p8_b);
  observer_ptr<const Derived> obs8_d(obs8_b.dyn_cast<const Derived>());
  
  assert(!obs8_d);
  assert(obs8_b && 1 == obs8_b->classId() && 20 == obs8_b->m_i);

  obs8_b.toNull();
  

  // Test owner_ptr_list
  {
    owner_ptr_list<Base>  list1;
    
    assert(list1.empty());
    
    owner_ptr<Base> asfd(new Base(100));
    list1.push_back(asfd);
    
    assert(!list1.empty());
  
    observer_iter<Base> it=list1.begin(),
                        it2;
      
    assert(it.valid());
    assert(it);
    
    assert(!it2.valid());
    
    it2=list1.begin();

    assert(it2);

    observer_ptr<Base> bl = *it2;
    
    assert(bl);
    assert(bl->m_i == 100);
    assert(it2->m_i == 100);

    ++it2;
    
    assert(!it2);
    
    owner_ptr<Base> pd(new Derived(101));
    list1.push_back(pd);
    
    it2 = list1.begin();
    
    assert(it2->m_i == 100);
    
    ++it2;
    
    assert(it2->m_i == 101);
    assert(it2->classId() == 2);
    
    int i=0;
    for (observer_iter<Base> it3=list1.begin(); it3; ++it3, ++i)
    {
      assert(it3->m_i == (100+i));
    }
    
  }

  std::cout << "Congratulations! No assertion failed." << std::endl;

  return 0;
}
