// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_UTILS_OBSERVER_PTR_INCLUDED
#define QUINY_UTILS_OBSERVER_PTR_INCLUDED

#include <quiny/utils/debug.hpp>

namespace quiny { namespace utils
{

  template<typename T> class owner_ptr;

  template<typename T>
  class observer_ptr
  {
    public:

      // Default: create NULL pointer
      observer_ptr();

      // Conversion from int -- anything except 0 will cause an error
      observer_ptr(int i);
          
      template<typename SubClass_t>
      observer_ptr(const owner_ptr<SubClass_t> &src);

      observer_ptr(const observer_ptr &src);
      
      template<typename SubClass_t>
      observer_ptr(const observer_ptr<SubClass_t> &src);

      ~observer_ptr();
    
      // Set this to NULL (no effect if already NULL)
      void 
      toNull();
    
      // Assignment will register this as additional observer
      observer_ptr&
      operator = (const observer_ptr &src);
      
      template<typename SubClass_t>
      observer_ptr&
      operator = (const observer_ptr<SubClass_t> &src);


      // Access the target object
      // See note about const-ness in owner_ptr's operator ->
      T* 
      operator -> () const;
      
      T&
      operator * () const;
      
      
      // Convert to bool, false means NULL
      operator 
      bool () const;

      // TODO: Make template
      // Are two observers pointing to the same target
      bool
      operator == (const observer_ptr &rhs) const;

      // Only valid for test for 0
      bool
      operator == (int i) const;

      // Dynamic cast of this
      // If this can by cast from T to SubClass_t, i.e. a dynamic_cast<SubClass_t>(target)
      // does not yield 0, we return an additional observer containing the target with 
      // the specified type.
      // If the dynamic_cast fails, a NULL observer_ptr is returned.
      template<typename SubClass_t>
      observer_ptr<SubClass_t>
      dyn_cast() const;


    private:
    
      friend class owner_ptr<T>;
      template<class SubClass_t> friend class observer_ptr;
      
      // Refer to the owner_ptr class definition for details about an owner_ptr's const-ness
      const owner_ptr<T>   *m_owner;

      observer_ptr<T>      *m_prevObserver,
                           *m_nextObserver;
                        
                        
  };

  
  // ===============================================================================================
  // IMPLEMENTATION
  // ===============================================================================================

  template<typename T>
  observer_ptr<T>::
  observer_ptr()
  : m_owner(0),
    m_prevObserver(0),
    m_nextObserver(0)
  {
  }  

  template<typename T>
  observer_ptr<T>::
  observer_ptr(int i)
  : m_owner(0),
    m_prevObserver(0),
    m_nextObserver(0)
  {
    if (i!=0)
    {
      EXIT_WITH_ERROR("Initialising observer_ptr from non-zero integer")
    }
  }  

  template<typename T>
  template<typename SubClass_t>
  observer_ptr<T>::
  observer_ptr(const owner_ptr<SubClass_t> &src)
  : m_owner(
      // See converting copy ctor of owner_ptr
      reinterpret_cast<const owner_ptr<T>*>(static_cast<const void*>(&src))
    ),
    m_prevObserver(0),
    m_nextObserver(
      reinterpret_cast<observer_ptr<T>*>(static_cast<void*>(src.m_firstObserver))
    )
  {
    src.m_firstObserver = reinterpret_cast<observer_ptr<SubClass_t>*>(static_cast<void*>(this));
  }  

  // Insert this into the front of the chain
  template<typename T>
  observer_ptr<T>::
  observer_ptr(const observer_ptr &src)
  : m_owner(src.m_owner),
    m_prevObserver(0),
    m_nextObserver( (src.m_owner == 0 ? 0 : (src.m_owner->m_firstObserver) ))
  {
    if (m_owner != 0)
    {
      if (m_owner->m_firstObserver != 0)
      {
        // the owner had at least one observer
        // => fix that one
        m_owner->m_firstObserver->m_prevObserver = this;
      }
      m_owner->m_firstObserver = this;
    }
  }

  // Insert this into the front of the chain
  template<typename T>
  template<typename SubClass_t>
  observer_ptr<T>::
  observer_ptr(const observer_ptr<SubClass_t> &src)
  : m_owner(reinterpret_cast<const owner_ptr<T>*>(static_cast<const void*>(src.m_owner))),
    m_prevObserver(0),
    m_nextObserver( (src.m_owner == 0 ? 0 : 
      reinterpret_cast<observer_ptr<T>*>(static_cast<void*>(src.m_owner->m_firstObserver))

    ))
  {
    if (m_owner != 0)
    {
      if (m_owner->m_firstObserver != 0)
      {
        // the owner had at least one observer
        // => fix that one
        m_owner->m_firstObserver->m_prevObserver = this;
      }
      m_owner->m_firstObserver = this;
    }
  }
  
  template<typename T>
  observer_ptr<T>::
  ~observer_ptr()
  {
    this->toNull();
  }
  
  template<typename T>
  void
  observer_ptr<T>::
  toNull()
  {
    if (m_owner != 0)
    {
      if (m_prevObserver != 0)
      {
        // we are in the 'middle' of the chain, i.e. we are not m_owner's firstObserver
        // => short-circuit this element
        m_prevObserver->m_nextObserver = m_nextObserver;
        
        if (m_nextObserver != 0)
        {
          m_nextObserver->m_prevObserver = m_prevObserver;
        }
      }
      else
      {
        // we are m_owner's firstObserver
        if (m_owner->m_firstObserver != this)
        {
          EXIT_WITH_ERROR("Internal observer chain is corrupt.");
        }
        
        m_owner->m_firstObserver = m_nextObserver;
        if (m_nextObserver != 0)
        {
          m_nextObserver->m_prevObserver = 0;
        }
      }
      
      m_owner = 0;
      m_prevObserver = 0;
      m_nextObserver = 0;
    }
  }

  template<typename T>
  observer_ptr<T>&
  observer_ptr<T>::
  operator = (const observer_ptr<T> &src)
  {
    if (this == &src)
    {
      // Self assignment => do nothing.
      return *this;
    }
    
    if (m_owner == src.m_owner)
    {
      // We do have the same owner, i.e. we are effectively refering to
      // the same target => do nothing
      return *this;
    }
  
    this->toNull();
    
    if (!src)
    {
      // src is NULL
      // => finished
      return *this;
    }

    // insert this into the front of the chain
    m_owner = src.m_owner;
    // m_prevObserver is already 0 (toNull())
    m_nextObserver = (src.m_owner == 0 ? 0 : (src.m_owner->m_firstObserver) );

    if (m_owner->m_firstObserver != 0)
    {
      // the owner had at least one observer
      // => fix that one
      m_owner->m_firstObserver->m_prevObserver = this;
    }
    m_owner->m_firstObserver = this;

    return *this; 
  }

  template<typename T>
  template<typename SubClass_t>
  observer_ptr<T>&
  observer_ptr<T>::
  operator = (const observer_ptr<SubClass_t> &src)
  {
    observer_ptr<T> tmp(src);
    return (*this = tmp);
  }
  
  template<typename T>
  T*
  observer_ptr<T>::
  operator -> () const
  {

    if (m_owner == 0 || m_owner->m_target == 0)
    {
      EXIT_WITH_ERROR("Dereferencing NULL observer_ptr.");  // TODO: maybe add << *this
    }

    return m_owner->m_target;
  }
  
  template<typename T>
  T&
  observer_ptr<T>::
  operator * () const
  {
    if (m_owner == 0 || m_owner->m_target == 0)
    {
      EXIT_WITH_ERROR("Dereferencing NULL observer_ptr.");  // TODO: maybe add << *this
    }

    return *m_owner->m_target;
  }

  template<typename T>
  observer_ptr<T>::
  operator bool () const
  {
    return m_owner != 0 && m_owner->m_target != 0;
  }
  
  template<typename T>
  bool
  observer_ptr<T>::
  operator == (const observer_ptr &rhs) const
  {
    // same owner implies same target
    return this->m_owner == rhs.m_owner;
  }

  template<typename T>
  bool
  observer_ptr<T>::
  operator == (int i) const
  {
    if (i!=0)
    {
      EXIT_WITH_ERROR("Comparing observer_ptr with non-zero integer")
    }
    
    return !static_cast<bool>(*this);
  }
  
  template<typename T>
  template<typename SubClass_t>
  observer_ptr<SubClass_t>
  observer_ptr<T>::
  dyn_cast() const
  {
    if (m_owner == 0 || m_owner->m_target == 0)
    {
      return observer_ptr<SubClass_t>();
    }

    SubClass_t *ptmp = dynamic_cast<SubClass_t*>(m_owner->m_target);
    
    if (ptmp == 0)
    {
      return observer_ptr<SubClass_t>();
    }  
    
    observer_ptr<SubClass_t> result;
    
    result.m_owner = reinterpret_cast<const owner_ptr<SubClass_t>*>(static_cast<const void*>(m_owner));

    // Insert result into the front of the observer chain

    result.m_nextObserver = result.m_owner->m_firstObserver;
    
    // Taking the address of the local object result should be uncritical here, because when
    // its deleted, it removes itself from the observer chain.
    result.m_owner->m_firstObserver = &result;
    
    return result;
  }
  
  
}}

#endif
