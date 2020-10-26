// 2006-03-23, Thorsten Schubert, OFFIS

#ifndef QUINY_UTILS_OBSERVER_ITER_INCLUDED
#define QUINY_UTILS_OBSERVER_ITER_INCLUDED

#include <quiny/utils/observer_ptr.hpp>
#include <quiny/utils/impl/Node.hpp>

namespace quiny { namespace utils 
{
  template <typename> class owner_ptr_list;

  // Iterator for accessing an owner_ptr_list (in the role of an observer)
  template<typename T>
  class observer_iter
  {
    public:
    
      typedef T target_t;

      // Default: create an invalid iter
      observer_iter();

      // true: can be deref'd
      bool
      valid() const;
      
      // same as valid
      operator bool () const;

      bool
      isFront() const;

      void
      setFront();

      // true: points to the last *valid* element
      bool
      isBack() const;

      void
      setBack();

      observer_iter
      operator ++ ();

      observer_ptr<T>
      operator * () const;

      T* 
      operator -> () const;


    private:
      friend class owner_ptr_list<T>;
      typedef typename owner_ptr_list<T>::Node Node;

      observer_iter(Node *node);

      Node  *m_Node;

  };


  // ===============================================================================================
  // IMPLEMENTATION
  // ===============================================================================================
  
  template<typename T>
  observer_iter<T>::
  observer_iter()
  : m_Node(0)
  {  
  }

  template<typename T>
  observer_iter<T>::
  observer_iter(Node *node)
  : m_Node(node)
  {  
  }

  template<typename T>
  bool
  observer_iter<T>::
  valid() const
  {
    return m_Node != 0;
  }

  template<typename T>
  observer_iter<T>::
  operator bool () const
  {
    return valid();
  }
  
  template<typename T>
  bool
  observer_iter<T>::
  isFront() const
  {
    return m_Node != 0 && m_Node->prev == 0;
  }

  template<typename T>
  void
  observer_iter<T>::
  setFront()
  {
    if (m_Node == 0)
    {
      return ;
    }
    
    m_Node = m_Node->head();
  }

  template<typename T>
  bool
  observer_iter<T>::
  isBack() const
  {
    return m_Node != 0 && m_Node->next == 0;
  }
  
  template<typename T>
  void
  observer_iter<T>::
  setBack()
  {
    if (m_Node == 0)
    {
      return ;
    }
    
    m_Node = m_Node->tail();
  }
  
  template<typename T>
  observer_iter<T>
  observer_iter<T>::
  operator ++ ()
  {
    if (m_Node != 0 )
    {
      m_Node = m_Node->m_next;
    }
    
    return *this;
  }

  template<typename T>
  observer_ptr<T>
  observer_iter<T>::
  operator * () const
  {
    if (m_Node==0)
    {
      EXIT_WITH_ERROR("Dereferencing invalid observer_iter")
    }
    
    return observer_ptr<T>(m_Node->m_data);
  }

  template<typename T>
  T*
  observer_iter<T>::
  operator -> () const
  {
    if (m_Node==0)
    {
      EXIT_WITH_ERROR("Dereferencing invalid observer_iter with operator -> ()")
    }
    
    return m_Node->m_data.operator -> ();
  }

}}

#endif
