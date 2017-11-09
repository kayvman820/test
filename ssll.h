#ifndef ssll_h
#define ssll_h
#include "sll.h"
#include <stdexcept>
#include <stddef.h>
#include <iostream>
#include <iterator>
namespace cop3530{


template <typename E>
class SSLL : public SLL<E> {
private:
    struct node {
        E data;
        node* next;
    };

public:
    SSLL();
    void insert( E element, size_t position ) override; //done-ish**
    void push_back( E element ) override; // done
    void push_front (E element ) override; // done
    E replace( E element, size_t position ) override; //review, but done**
    E remove( size_t position ) override; // kinda done**
    E pop_back() override; // done
    E pop_front() override; // done
    E item_at( size_t position ) override; //done
    E peek_back() override; // done
    E peek_front() override; // done
    bool is_empty() override; // done
    bool is_full() override; //havent done****
    size_t length() override; // done
    void clear() override; //does that mean it deallocates? //kinda done**
    void print (std::ostream &ostream) override; //done
    E *const contents() override; //done
    bool contains(E element,  bool(*equals_function)(E,E)) override; //done


    ~SSLL() override;

    node* head;
    node* tail;

    using size_t = std::size_t; // you may comment out this line if your compiler complains
    using value_type = E;

    // node* current;
    // node* helper;
    // node* temp;


    template <typename DataT>
    class SSLL_Iter
    {
      // type aliases required for C++ iterator compatibility
      using value_type = DataT;
      using reference = DataT&;
      using pointer = DataT*;
      using difference_type = std::ptrdiff_t;
      using iterator_category = std::forward_iterator_tag;

      // type aliases for prettier code
      using self_type = SSLL_Iter;
      using self_reference = SSLL_Iter&;

    private:
      node* here;

    public:
      explicit SSLL_Iter( node* start ) : here( start ) {}
      SSLL_Iter( const SSLL_Iter& src ) : here( src.here ) {}

      reference operator*() const {
        return here->data;
      }
      pointer operator->() const {
        return &(operator*());
      }

      self_reference operator=( SSLL_Iter<DataT> const& src ) {
        if(this == &src){
          return (*this);
        }
        here = src.here;
        return *this;
      }

      self_reference operator++() {
        if(here->next){
          if(here != NULL){
            here = here->next;
          }


        }
        return (*this);
      } // preincrement

      self_type operator++(int) {
        self_type tmp( *this );
        here = here->next;
        return tmp;
      } // postincrement

      bool operator==( SSLL_Iter<DataT> const& rhs ) const {
        return (here == rhs.here);
      }
      bool operator!=( SSLL_Iter<DataT> const& rhs) const {
        return (here != rhs.here);
      }
    };

    using iterator = SSLL_Iter<E>;
    using const_iterator = SSLL_Iter<E const>;
    iterator begin() {
      SSLL_Iter<E> iter = SSLL_Iter<E>(head);
      return iter;
    }
    iterator end() {
      SSLL_Iter<E> end = SSLL_Iter<E>(tail->next);
      return end;
    }
    // iterator end() { return SSLL_Iter iter; }



};



template <typename E>
SSLL<E>::SSLL(){
  head = NULL;
  tail = NULL;
}

template <typename E>
SSLL<E>::~SSLL(){
  this->clear();
}

template <typename E>
bool SSLL<E>::is_full(){
  return false;
}



//needs testing
template <typename E>
E *const SSLL<E>::contents(){
  E *const array = new E[this->length()];
  node* current = head;
  for(size_t i = 0; i<this->length(); i++){
    array[i] = current->data;
    current = current->next;
  }
  return array;
}

//needs testing
template <typename E>
bool SSLL<E>::contains(E element, bool(*equals_function)(E,E) ){
  node* current = head;
  while(current){
    bool results = equals_function(element, current->data);
    if(results)
      return true;
    current = current->next;
  }
  return false;
}

template <typename E>
E SSLL<E>::replace(E element, size_t position){

  node* current;
  node* temp;
  node* previous;

  if(position > (this->length()-1) || position < 0){
    throw std::runtime_error("Position is out of bounds of linked list");
  }

  if(head == NULL && tail == NULL)
  {
    printf("Empty list");
  }

  if(position == 0){
    current = head;
    E stuff = current->data;
    current->data = element;
    return stuff;
  }

  else if(position == this->length()){
    current = head;
    while(current){
      temp = current;
      current = current->next;
    }
    E stuff = current->data; //or temp->data
    current->data = element;
    return stuff;
  }

  else{
    size_t i = 0;
    current = head;
    while (i!=position){
      i++;
      temp = current;
      current = current->next;
    }
    E stuff = current->data;
    current->data = element;
    return stuff;

  }

}




//needs testing
template <typename E>
void SSLL<E>::print (std::ostream &ostream){

  if(is_empty()){
    printf("<empty list>");
  }
  else{
    //may not need std::
      node* current = head;
      ostream << "[ ";
      while(current){
        ostream << current->data;
        if(current->next){
          ostream << ", ";
        }
        current = current->next;
      }
      ostream << "]";
    }

}



template <typename E>
void SSLL<E>::clear(){
  head = NULL;
  tail = NULL;
}

template <typename E>
E SSLL<E>::peek_front(){
  if(this->is_empty()){
    throw std::runtime_error("List is empty");
  }
  return head->data;
}

template <typename E>
E SSLL<E>::peek_back(){
  if(this->is_empty()){
    throw std::runtime_error("List is empty");
  }
  return tail->data;
}




template <typename E>
E SSLL<E>::item_at( size_t position){
  if(position > (this->length()-1) || position < 0){
    throw std::runtime_error("Position is out of bounds of linked list");
  }
  else{
    node* current = head;
    for(size_t i = 0; i< position; i++){
        current = current->next;
      }
      return current->data;
    }
}



template <typename E>
bool SSLL<E>::is_empty(){
  if(head == NULL && tail == NULL)
    return true;
  return false;
}

template <typename E>
E SSLL<E>::pop_front(){
  if(this->is_empty()){
    throw std::runtime_error("List is empty");
  }
  E stuff = head->data;
  node* temp = head;
  if(head->next == NULL){
    head = tail = NULL;
  }
  else{
    head = head->next;
  }
  // E stuff = temp->data;
  delete temp;
  return stuff;
}

template <typename E>
E SSLL<E>::pop_back(){
  if(this->is_empty()){
    throw std::runtime_error("List is empty");
  }

  E stuff = tail->data;
  node* temp = tail;
  node* current = head;
  if(head->next == NULL){
    head = tail = NULL;
  }
  else{
    while( current ){
      if(current->next == tail){
        tail=current;
        current->next=NULL;
      }
      current = current->next;
    }
  }
  delete temp;
  return stuff;
}

template <typename E>
void SSLL<E>::push_back( E element){
  node* temp = new node;
  temp->data = element;
  temp->next = NULL;
  if(this->is_empty()){
    head = tail = temp;
  }
  else{
    tail->next = temp;
    tail = temp;
  }
}


template <typename E>
void SSLL<E>::push_front( E element){
  node* temp = new node;
  temp->data = element;
  if(this->is_empty()){
    head = tail = temp;
    head->next = NULL;
  }
  else{
    temp->next=head;
    head = temp;
  }
}

template <typename E>
E SSLL<E>::remove( size_t position ){
  size_t len = length();
  if(position > (len-1) || position < 0){
    throw std::runtime_error("Position is out of bounds of linked list");
  }

  if(is_empty()){
    throw std::runtime_error("List is empty");
  }

  node* current = head;
  node* previous = head;
  for(size_t i = 0; i < position; i++){
    previous = current;
    current = current->next;
  }
  E stuff = current->data;
  current = previous->next;
  previous->next=current->next;
  if(position == (len-1)){
    tail = previous;
  }
  return stuff;

  // node* current;
  // node* temp;
  // node* previous;
  //
  // if(position == 0){
  //   E stuff = head->data;
  //   temp = head;
  //   head = head->next;
  //   delete temp;
  //   return stuff;
  //   // node* remove = new node;
  //   // remove = head;
  //   // E stuff = remove->data;
  //   // head = head->next;
  //   // delete remove;
  // }
  //
  // if (position == (this->length())){
  //   current = head;
  //   //possibly not needed
  //   while(current){
  //     previous = current;
  //     current = current->next;
  //   }
  //   tail = previous;
  //   E stuff = current->data;
  //   previous->next=NULL;
  //   delete current;
  //   return stuff;
  // }
  // else{
  //   current = head;
  //   for (size_t i = 0; i<position; i++){
  //     previous = current;
  //     current = current->next;
  //   }
  //   E stuff = current->data;
  //   current = previous->next;
  //   previous->next=current->next;
  //   delete current;
  //   return stuff;
}


template <typename E>
void SSLL<E>::insert( E element, size_t position ){
  // if(position > (this->length()-1) || position < 0){
  //   throw std::runtime_error("Position is out of bounds of linked list");
  // }
  node* current;
  node* previous;
  node* temp;
  size_t len = length();

if(position > len)
  throw std::runtime_error("Position is out of bounds of linked list");

if(position < 0)
  throw std::runtime_error("Position is out of bounds of linked list");

if(this->is_empty())
{
  head = new node;
  head->data = element;
  head->next = NULL;
  tail = head;
  return;
}


else{
  if(position == 0){
    push_front(element);
}

//changed this logic

//fix this use push_back();
  else if(position == len){
    push_back(element);
  }

  else{
    size_t i = 0;
    current = head;
    while(i!=position){
      i++;
      previous = current;
      current = current->next;
      }
    temp = new node;
  // previous->next = temp;
    temp->data = element;
    temp->next = current;
    previous->next = temp;
    return;
    }
  }
}


template <typename E>
size_t SSLL<E>::length(){
  size_t len = 0;
  node* curr = head;
  while( curr ){
    len++;
    curr = curr->next;
  }
  return len;
}

}

#endif
// size_t main(){
//   // cop3530::SSLL<> mySSLL();
//   SSLL<int> mySSLL();
//   // mySSLL.insert(1, 1);
//   // mySSLL.insert(2,2);
//   // mySSLL.insert(3,3);
// }
