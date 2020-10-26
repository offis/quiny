// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_UTILS_OWNER_PTR_LIST_INCLUDED
#define QUINY_UTILS_OWNER_PTR_LIST_INCLUDED

#include <quiny/utils/debug.hpp>
#include <quiny/utils/impl/Node.hpp>
#include <quiny/utils/owner_ptr.hpp>
#include <quiny/utils/observer_ptr.hpp>
#include <quiny/utils/observer_iter.hpp>

namespace quiny { namespace utils
{

  // A container for ower_ptrs
  
  // Note: an owner_ptr_list cannot contain NULL pointers

  // Status:  quick hack, quite unfinished
  
  template<typename T>
  class owner_ptr_list
  {
    protected:
      typedef impl::Node<owner_ptr<T> > Node;
  
    public:
    
      typedef T target_t;      
    
      // Default: create an empty list
      owner_ptr_list();
      
      // Destroy this list (and consequently the objects pointed to by the owner_ptrs)
      ~owner_ptr_list();
    
      bool
      empty() const;
      
      int
      size() const;
      
      void
      push_back(owner_ptr<T> p);
      
      observer_ptr<T>
      back() const;      
      
      observer_iter<T>
      begin() const;
    
    protected:
      
      friend class observer_iter<T>;
          
      Node   *m_head;
      Node   *m_tail;    
  };



  // ===============================================================================================
  // IMPLEMENTATION
  // ===============================================================================================

  template<typename T>
  owner_ptr_list<T>::
  owner_ptr_list()
  : m_head(0)
  , m_tail(0)
  {
  }

  template<typename T>
  owner_ptr_list<T>::
  ~owner_ptr_list()
  {
    Node  *currentNode=m_head,
          *nextNode;
             
    while(currentNode != 0)
    {
      nextNode = currentNode->m_next;
      currentNode->m_prev=0;
      currentNode->m_next=0;
      delete currentNode;
      currentNode = nextNode;
    }
  }

  template<typename T>
  bool
  owner_ptr_list<T>::
  empty() const
  {
    return m_head == 0;
  }

  template<typename T>
  int
  owner_ptr_list<T>::
  size() const
  {
    int result = 0;
    Node  *currentNode=m_head;
             
    while(currentNode != 0)
    {
      ++result;
      currentNode = currentNode->m_next;
    }
    
    return result;
  }
  
  template<typename T>
  void
  owner_ptr_list<T>::
  push_back(owner_ptr<T> p)
  {
    if (p)
    {    
      Node *newNode = new Node(p, m_tail, 0);
      
      if (m_tail != 0)
      {
        m_tail->m_next = newNode;
      }
      
      m_tail = newNode;
      
      if (m_head == 0)
      {
        m_head = newNode;
      }
    }
  } 

  template<typename T>
  observer_ptr<T>
  owner_ptr_list<T>::
  back() const
  {
    if (m_tail == 0)
    {
      EXIT_WITH_ERROR("Called back() on empty owner_ptr_list.");
    }
    return observer_ptr<T>(m_tail->m_data);
  }  
  
  template<typename T>
  observer_iter<T>
  owner_ptr_list<T>::
  begin() const
  {
    return observer_iter<T>(m_head);
  }
  
}}

#endif
