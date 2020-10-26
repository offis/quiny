// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_UTILS_OWNER_POINTER_INCLUDED
#define QUINY_UTILS_OWNER_POINTER_INCLUDED

#include "quiny/utils/debug.hpp"

// for operator <<
#include <ostream>
#include <typeinfo>

namespace quiny { namespace utils 
{

  // A pointer class similar to std::auto_ptr

  // The owner_ptr 'owns' the (heap) object being pointed to, i.e.
  // destroying the owner_ptr will destroy the object. 
  // Passing an owner_ptr to another owner_ptr (either by initialisation or assignment)
  // will cause the source object to lose the pointer, i.e. it will contain a NULL pointer
  // after the operation.
  // Note: There should never be two owner_ptrs pointing to the same object!

  // TODO: Maybe add a global monitor which ensures this.
  
  // In addition there is a observer_ptr which can be derived from an owner_ptr. 
  // The owner must live longer than its observers -- otherwise an error will be raised.
  // Therefore the owner keeps track of its observers. 

  // Remark: const-ness of an observer_ptr means that one cannot let it point to
  //         a different target -- the (fixed) target, however, can be modified, provided
  //         the target type is not const itself. Note, that adding or removing observers
  //         is allowed for const owner_ptrs.
  
  // ATTENTION: DO NOT TRY TO PUT owner_ptrs INTO STL CONTAINERS (vector<..>, list<..>, ..)
  //            This will probably fail due to lack of proper copy semantics

  template<typename T> class owner_ptr;
  template<typename T> class observer_ptr;

  template<typename T>
  class owner_ptr
  {    
    public:
      typedef T target_t;
      
      // Create an owner_ptr from an ordinary pointer. We make this one explicit, so that the
      // user explicitly has to state that an owner_ptr shall be created. By doing so we hope
      // to lower the risk of unintentional creation of multiple owner_ptrs to the same 
      // target.
      explicit
      owner_ptr(T *target=0);
      
      // Copy ctors will 'steal' src's target
      owner_ptr(owner_ptr &src);
      
      template<typename SubClass_t>
      owner_ptr(owner_ptr<SubClass_t> &);
      
      ~owner_ptr();
      
      // Assignment will also steal src's target
      // Assignment to a non-NULL owner_ptr will destroy the target, i.e. 
      // is equivalent to first destroy the owner and the create and initialise a new one.
      owner_ptr&
      operator = (owner_ptr &src);
      
      template<typename SubClass_t>
      owner_ptr&
      operator = (owner_ptr<SubClass_t> &src);
      
      // Access the target object. 
      // Note, that dereferencing the pointer and changing the target does not affect
      // the pointer's const-ness. Therefore it is valid to return non-const pointers
      // or references.
      // However, it would be a bad idea to delete the object return here.
      T*
      operator -> () const;
      
      T&
      operator * () const;
      
      
      // Convert to bool, false means NULL
      operator 
      bool () const;
      
      // We don't want a friend operator <<, hence we provide a public method, which inserts
      // this into the given stream
      std::ostream& 
      streamInto(std::ostream &os) const;
      
      // Clone the target object. This method implies the availability of a clone method
      // in T. Cloning a NULL target will return a NULL pointer
      owner_ptr<T>
      clone() const;
      
      // Get back the target pointer and set this one's to NULL.
      // Note: this must not have any observers when doing so
      T*
      release();
      
      // Dynamic cast of this
      // If this can by cast from T to SubClass_t, i.e. a dynamic_cast<SubClass_t>(m_target)
      // does not yield 0, we return an owner containing the target with the specified type
      // and consequentliy this loses its ownership, i.e. it is NULL afterwards.
      // If the dynamic_cast fails, this is left unchanged and a NULL owner_ptr is returned.
      template<typename SubClass_t>
      owner_ptr<SubClass_t>
      dyn_cast();
      
    private:

      template<class SubClass_t> friend class owner_ptr;      
      template<class SubClass_t> friend class observer_ptr;
    
      T                *m_target;
      
      // See the remark about const-ness above.
      mutable
      observer_ptr<T>  *m_firstObserver;
      
      // Change the observers' owner to this after stealing the target from another owner_ptr
      void
      fixObservers();
      
      // Helper for passing owner_ptr to and from functions. 
      // It must be ensured, that the helper cannot be misused to create duplicates of
      // of owner_ptrs. 
      // As the struct is private, nobody can get explicit access to an owner_ptr_ref. It is
      // only created implicitly and cannot be intercepted.
      // (It seems that the problem arises due to the non-const copy ctor. However, it is not 
      //  100% clear to me, why this is a problem. Probably, because it is necessary to copy
      //  the parameters into local variables and therefore the object must have proper copy
      //  semantics, which the raw ower_ptrs do not have.)
      struct owner_ptr_ref
      {
        // When creating this one, ensure that src loses its ownership
        // There is exactly one place where owner_ptr_refs are created: the conversion operator
        // of owner_ptr
        explicit
        owner_ptr_ref(T* target, observer_ptr<T> *firstObserver);

        T                *m_target;
        observer_ptr<T>  *m_firstObserver;
      };
      
    public:
      // More public methods, which are not intended for direct use, but which will 
      // be automagically invoked when necessary
      
      // Construct an owner_ptr from an owner_ptr_ref
      owner_ptr(const owner_ptr_ref &src);

      // Assign from owner_ptr_ref
      owner_ptr &
      operator = (const owner_ptr_ref &src);
      
      //Convert to an owner_ptr_ref
      operator owner_ptr_ref ();
      
  };

  template<typename T>
  std::ostream&
  operator << (std::ostream &os, const owner_ptr<T> &p)
  {
    return p.streamInto(os);
  }
  
  // ===============================================================================================
  // IMPLEMENTATION
  // ===============================================================================================

  template<typename T>
  owner_ptr<T>::
  owner_ptr(T* target)
  : m_target(target),
    m_firstObserver(0)
  {
  }
  
  template<typename T>
  owner_ptr<T>::
  owner_ptr(owner_ptr &src)
  : m_target(src.m_target),
    m_firstObserver(src.m_firstObserver)
  {
    src.m_target=0;
    src.m_firstObserver=0;
    fixObservers();
  }

  template<typename T>
  template<typename SubClass_t>
  owner_ptr<T>::
  owner_ptr(owner_ptr<SubClass_t> &src)
  : m_target(src.m_target),
    m_firstObserver(
    
    // Now things are getting ugly, because the observer type does not match
    // Maybe it would help to add two base classes owner_ptr_base and observer_ptr_base
    // and handle the pointers between owner and observer there. However, this way we
    // probably would need more casts, because the typeinfomation is lost.
    
    // This construct should be safe as long as nobody changes the representation of the
    // oberver_ptr<SubClass_t> -- for example by template specialisation. The compatibility
    // of T and SubClass_t is already ensured by the initialisation of the target pointer.

    // We need the intermediate void* in order to make the compiler happy
      reinterpret_cast<observer_ptr<T>*>(static_cast<void*>(src.m_firstObserver))
    )
  {       
    src.m_target=0;
    src.m_firstObserver=0;
    fixObservers();
  }
  
  template<typename T>
  owner_ptr<T>::
  ~owner_ptr()
  {
    if (m_firstObserver != 0)
    {
      EXIT_WITH_ERROR("Deleting owner_ptr which still has observers. " << *this);
    }
    
    delete m_target;
  }
  
  template<typename T>
  owner_ptr<T>&
  owner_ptr<T>::
  operator = (owner_ptr &src)
  {
    if (&src == this)
    {
      return *this;
    }
  
    if (m_firstObserver != 0)
    {
      EXIT_WITH_ERROR("Assignment to a non-NULL owner_ptr which still has observers. " 
                      << *this);
    }
    
    if (m_target == src.m_target && m_target != 0)
    {
      EXIT_WITH_ERROR("Detected two different owner_ptrs with the same target: " 
                      "p1: " << *this <<
                      ", p2: " << src );
    }
    
    delete m_target;
    m_target = src.m_target;
    src.m_target = 0;
    
    m_firstObserver = src.m_firstObserver;
    src.m_firstObserver = 0;
    fixObservers();
    
    return *this;
  }

  template<typename T>
  template<typename SubClass_t>
  owner_ptr<T>&
  owner_ptr<T>::
  operator = (owner_ptr<SubClass_t> &src)
  {
    owner_ptr<T> tmp(src);
    
    return (*this = tmp);
  }
  
  template<typename T>
  T*
  owner_ptr<T>::
  operator -> () const
  {
    if (m_target == 0)
    {
      EXIT_WITH_ERROR("Dereferencing NULL owner_pointer. " << *this);
    }
    return m_target;
  }
    
  template<typename T>
  T&
  owner_ptr<T>::
  operator * () const
  {
    if (m_target == 0)
    {
      EXIT_WITH_ERROR("Dereferencing NULL owner_pointer. " << *this);
    }
    return *m_target;
  }

  template<typename T>
  owner_ptr<T>::
  operator bool () const
  {
    return m_target != 0;
  }
  
  template<typename T>
  std::ostream&
  owner_ptr<T>::
  streamInto(std::ostream &os) const
  {
    os << "this : " << std::hex << this 
       << ", m_target : " << m_target
       << ", m_firstObserver : " << m_firstObserver
       << ", T : " << typeid(T).name();
    return os;
  }

  template<typename T>
  void
  owner_ptr<T>::
  fixObservers()
  {
    observer_ptr<T> *currentObserver=m_firstObserver;
    while(currentObserver != 0)
    {
      currentObserver->m_owner = this;
      currentObserver = currentObserver->m_nextObserver;
    }
  }
  
  template<typename T>
  owner_ptr<T>
  owner_ptr<T>::
  clone() const
  {
    if (m_target == 0)
    {
      return 0;
    }
    
    return owner_ptr<T>(m_target->clone());
  }

  template<typename T>
  T*
  owner_ptr<T>::
  release()
  {
    if (m_firstObserver != 0)
    {
      EXIT_WITH_ERROR("Releasing owner_ptr which still has observers. " << *this);
    }
    
    T* result = m_target;
    m_target = 0;
    
    return result;  
  }


  template<typename T>
  owner_ptr<T>::owner_ptr_ref::
  owner_ptr_ref(T *target, observer_ptr<T> *firstObserver)
  : m_target(target),
    m_firstObserver(firstObserver)
  {
  }

  template<typename T>
  owner_ptr<T>::
  owner_ptr(const owner_ptr_ref &src)
  : m_target(src.m_target),
    m_firstObserver(src.m_firstObserver)
  {    
  }

  template<typename T>
  owner_ptr<T> &
  owner_ptr<T>::
  operator = (const owner_ptr_ref &src)
  {
    owner_ptr<T> tmp(src);
    return *this = tmp;
  }

  template<typename T>
  owner_ptr<T>::
  operator typename owner_ptr<T>::owner_ptr_ref ()
  {
    T                *target = m_target;    
    observer_ptr<T>  *firstObserver = m_firstObserver;
    
    m_target = 0;
    m_firstObserver = 0;

    // Handover this to an owner_ptr_ref    
    return owner_ptr_ref(target, firstObserver);
  }

  template<typename T>
  template<typename SubClass_t>
  owner_ptr<SubClass_t>
  owner_ptr<T>::
  dyn_cast()
  {
    SubClass_t *ptmp = dynamic_cast<SubClass_t*>(m_target);
    
    if (ptmp == 0)
    {
      return owner_ptr<SubClass_t>();
    }  
    
    owner_ptr<SubClass_t> result(ptmp);
    result.m_firstObserver = 
      reinterpret_cast<observer_ptr<SubClass_t>*>(static_cast<void*>(m_firstObserver));
    
    m_target = 0;
    m_firstObserver = 0;
    
    result.fixObservers();
    
    return result;
  }

}}

#endif
