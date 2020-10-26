// 2006-03-23, Thorsten Schubert, OFFIS

#ifndef QUINY_UTILS_IMPL_NODE_INCLUDED
#define QUINY_UTILS_IMPL_NODE_INCLUDED


namespace quiny { namespace utils { namespace impl
{

  template<typename T>
  struct Node
  {
    typedef T Value_t;
  
    T      m_data;
    Node  *m_prev;
    Node  *m_next;

    Node(T data, 
         Node *prev=0, 
         Node *next=0);

    // Find the first node of the whole chain
    Node*
    head() const;

    // Find the last node of the whole chain
    Node*
    tail() const;
  };


  // ===============================================================================================
  // IMPLEMENTATION
  // ===============================================================================================

  template<typename T>
  Node<T>::
  Node(T data, 
       Node *prev, 
       Node *next)
  : m_data(data)
  , m_prev(prev)
  , m_next(next)
  {
  }

  template<typename T>
  Node<T>*
  Node<T>::
  head() const
  {
    Node *currentNode=this,
         *prevNode=this->m_prev;
  
    while (prevNode)
    {
      currentNode = prevNode;
      prevNode=currentNode->m_prev;
    }

    return currentNode;  
  }

  template<typename T>
  Node<T>*
  Node<T>::
  tail() const
  {
    Node  *currentNode=this,
          *nextNode=this->m_next;
  
    while (nextNode)
    {
      currentNode = nextNode;
      nextNode=currentNode->m_next;
    }

    return currentNode;  
  }


}}}

#endif
