#ifndef psll_h
#define psll_h
#include "sll.h"
#include <stdexcept>
#include <stddef.h>
#include <iostream>
namespace cop3530{
  template <typename E>
  class PSLL : public SLL<E> {
    private:
      struct node{
        E data;
        node* next;
      };
    public:
      PSLL();
      void insert( E element, size_t position ) override; //kinda done
      void push_back( E element ) override;
      void push_front (E element ) override;
      E replace( E element, size_t position ) override; //done needs testing
      E remove( size_t position ) override; //kinda done
      E pop_back() override;
      E pop_front() override;
      E item_at( size_t position ) override;
      E peek_back() override;
      E peek_front() override;
      bool is_empty() override; //done
      bool is_full() override;
      size_t length(node* node);
      size_t length() override;//done
      void clear() override;
      void print(std::ostream &ostream) override;
      E *const contents() override;
      bool contains(E element,  bool(*equals_function)(E,E)) override;
      void reallocate();

      ~PSLL() override;

      node* head;
      node* tail;
      // node* current;
      node* free;
      // node* temp;
      // node* helper;
  };

  template <typename E>
  PSLL<E>::PSLL(){
    // head = new node;
    // head->next = NULL;
    // tail = head;
    head = NULL;
    tail = NULL;
    // free = NULL;
  }

  template <typename E>
  PSLL<E>::~PSLL(){
    this->clear();
  }


  template <typename E>
  E *const PSLL<E>::contents(){
    E *const array = new E[this->length()];
    node* current = head;
    for(size_t i = 0; i<this->length(); i++){
      array[i] = current->data;
      current = current->next;
    }
    return array;
  }

  template <typename E>
  bool PSLL<E>::contains(E element, bool(*equals_function)(E,E) ){
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
  void PSLL<E>::print (std::ostream &ostream){

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
  void PSLL<E>::clear(){
    head = tail = NULL;
  }

  template <typename E>
  E PSLL<E>::peek_front(){
    return head->data;
  }

  template <typename E>
  E PSLL<E>::peek_back(){
    return tail->data;
  }

//configure for pool
  template <typename E>
  E PSLL<E>::pop_front(){
    if(this->is_empty()){
      throw std::runtime_error("List is empty");
    }

    E stuff = head->data;
    node* temp = head;

    if(head->next == NULL){
      temp->next = free;
      free = temp;
      head = tail = NULL;
      return stuff;
    }
    else{
      head = head->next;
      temp->next = free;
      free = temp;
      return stuff;
    }
  }
//done
  template <typename E>
  E PSLL<E>::pop_back(){
    if(this->is_empty()){
      throw std::runtime_error("List is empty");
    }

    E stuff = tail->data;
    node* prev = head;
    node* temp;
    //for when you pop the last element, reset tail and head to null, put node to free list
    if(head->next == NULL){
      temp = head;
      temp->next = free;
      free = temp;
      head = tail = NULL;
      return stuff;
    }
    // still printing out 1 for length! need to figure this out
    else{
    while( prev ){
      // if((prev->next) == tail || prev->next== NULL)
      //works fine without 2nd contingency on initial testing
      if((prev->next) == tail)
        break;
      prev=prev->next;
    }
    temp = tail;
    tail = prev;
    temp->next = free;
    free = temp;
    tail->next = NULL;
    return stuff;
  }
}
//done
  template <typename E>
  void PSLL<E>::push_back( E element){
    node* temp;
    if(free){
      temp = free;
      free=free->next;
      temp->data=element;
    }
    else{
      temp = new node;
      temp->data = element;
    }

    if(is_empty()){
      head = tail = temp;
      head->next = NULL;
    }

    else{
      tail->next=temp;
      tail = temp;
      tail->next = NULL;
    }
  }
//done
  template <typename E>
  void PSLL<E>::push_front( E element){
    node* temp;

    if(free){
      temp = free;
      free = free->next;
      temp->data = element;
    }
    else{
      temp = new node;
      temp->data = element;
    }
    if(is_empty()){
      head = tail = temp;
      head->next = NULL;
    }
    else{
      temp->next = head;
      head = temp;
    }

  }
//test
  template <typename E>
  E PSLL<E>::item_at( size_t position){
    if(position > this->length() || position < 0){
      throw std::runtime_error("Position is out of bounds of linked list");
    }
    else{
      node* current = head;
      for(size_t i = 0; i<= position; i++){
          current = current->next;
        }
        return current->data;
      }
  }


  template <typename E>
  bool PSLL<E>::is_empty(){
    if(head == NULL && tail == NULL){
      return true;
    }
    return false;
  }

  template <typename E>
  bool PSLL<E>::is_full(){
    return false;
  }
//test
  template <typename E>
  void PSLL<E>::reallocate(){
    node* current = free;
    size_t len = length(head);
    size_t lenFree = length(free);
    while(lenFree != (100/2)){
      lenFree--;
      free = free->next;
      delete current;
      current = free;
    }
  }
//test
  template <typename E>
  void PSLL<E>::insert(E element, size_t position){
    node* curr;
    node* temp;
    node* prev;

    if(position > (this->length()) || position < 0){
      throw std::runtime_error("Position is out of bounds of linked list");
    }
    size_t len = length(head);
    size_t lenFree = length(free);
    if(len >= 100 && lenFree > (100/2)){
      reallocate(); //test
    }

    if(position == 0){
      push_front(element);
    }

    else if(position == (this->length())){
      push_back(element);
    }

    else{
      if(free){
        temp = free;
        free = free->next;
      }
      else{
        temp = new node;
      }
      temp->data = element;
      prev = curr = head;
      for(size_t i = 0; i<position; ++i){
        prev = curr;
        curr = curr->next;
      }
      prev->next = temp;
      temp->next=curr;

    }



    // if(is_empty() && !free){
    //   temp = new node;
    //   head = tail = temp;
    //   head->data = element;
    //   head->next = NULL;
    // }


    //
    // if(free){ //if there's a free node
    //   // temp = free;
    //   // free = free->next; //point to next free node in list
    //   if(position == 0){
    //     push_front(element);
    //     // current = head;
    //     // temp->next = current;
    //     // temp->data = element;
    //     // head = temp;
    //   }
    //   else if (position == len){
    //     push_back(element);
    //     // current = head;
    //     // while(current){
    //     //   previous = current;
    //     //   current = current->next;
    //     // }
    //     // previous->next = temp;
    //     // temp->next = current;
    //     // temp->data = element;
    //     // tail = current;
    //   }
    //   else{
    //     temp = free;
    //     free = free->next;
    //     size_t i = 0;
    //     current = head;
    //     while(i!=position){
    //       i++;
    //       // if(current->next == NULL)
    //       //   break;
    //       previous = current;
    //       current = current->next;
    //     }
    //     previous->next = temp;
    //     temp->data = element;
    //     temp->next = current;
    //   }
    //
    // }
    // else{
    //   // temp = new node;
    //   size_t i = 0;
    //   if(position == 0){
    //     push_front(element);
    //     // current = head;
    //     // temp->next = current;
    //     // temp->data = element;
    //     // head = temp;
    //   }
    //   else if (position == this->length()){
    //     push_back(element);
    //     // current = head;
    //     // while(current){
    //     //   previous = current;
    //     //   current = current->next;
    //     // }
    //     // previous->next = temp;
    //     // temp->data = element;
    //     // temp->next = current;
    //     // tail = current;
    //   }
    //   else{
    //     temp = new node;
    //     current = head;
    //     while(i!=position){
    //       i++;
    //       previous = current;
    //       current=current->next;
    //     }
    //     previous->next = temp;
    //     temp->data = element;
    //     temp->next = current;
    //   }
    // }
  }

//done
  template <typename E>
  E PSLL<E>::remove(size_t position){

    if(position > this->length() || position < 0){
      throw std::runtime_error("Position is out of bounds of linked list");
    }

    if(this->is_empty()){
      throw std::runtime_error("List is empty");
    }
    node* curr = head;
    node* prev = head;
    if(prev->next == NULL){
      E stuff = curr->data;
      curr->next = free;
      head = tail = prev = NULL;
      free = curr;
      return stuff;
    }
    else{
      for(size_t i = 0; i < position; ++i){
        prev = curr;
        curr = curr->next;
      }
      E stuff = curr->data;
      if(prev->next == curr->next){
        prev = prev->next;
        head = prev;
      }
      else{
        prev->next = curr->next;
      }

      if(prev->next == NULL){
        tail = prev;
      }
      curr->next = free;
      free = curr;
      return stuff;
  }
}

//done
  template <typename E>
  E PSLL<E>::replace(E element, size_t position){
    if(position > this->length() || position < 0){
      throw std::runtime_error("Position is out of bounds of linked list");
    }

    if(is_empty()){
      throw std::runtime_error("List is empty");
    }
    node* curr = head;
    for(size_t i = 0; i<position; ++i){
      curr = curr->next;
    }
    E stuff = curr->data;
    curr->data = element;
    return stuff;

  }



  template <typename E>
  size_t PSLL<E>::length(node* n){
    size_t len = 0;
    node* curr = n;
    while( curr ){
      len++;
      curr = curr->next;
    }
    return len;
  }

  template <typename E>
  size_t PSLL<E>::length(){
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
// int main(){}
