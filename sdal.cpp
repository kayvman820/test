#include "sll.h"
#include <stdexcept>
#include <stddef.h>
#include <iostream>
namespace cop3530{
  template<typename E>
  class SDAL : public SLL<E> {
    private:
      E *data;
      size_t tail;
      size_t array_size;
      // struct node{
      //   E data;
      //   node* next;
      // };
    public:

      SDAL(size_t size = 50);
      void insert( E element, size_t position ) override;
      void push_back( E element ) override;
      void push_front (E element ) override;
      E replace( E element, size_t position ) override;
      E remove( size_t position ) override;
      E pop_back() override;
      E pop_front() override;
      E item_at( size_t position ) override;
      E peek_back() override;
      E peek_front() override;
      bool is_empty() override;
      bool is_full() override;
      size_t length() override;
      void clear() override;
      void print (std::ostream &ostream) override;
      E *const contents() override;
      bool contains(E element,  bool(*equals_function)(E,E)) override;
      bool check_length();
      void reallocate();
      size_t calculate();
      size_t size();
      size_t return_tail();

      // size_t arraysize = 50; //may want to set to private....

      ~SDAL() override;
  };



  template <typename E>
  SDAL<E>::SDAL(size_t size) : array_size(size)
  {
    data = new E[array_size];
    tail = 0;
  }

  template <typename E>
  size_t SDAL<E>::size(){
    return array_size;
  }

  template <typename E>
  size_t SDAL<E>::return_tail(){
    return tail;
  }

  template <typename E>
  SDAL<E>::~SDAL(){
    delete [] data;
  }

  template <typename E>
  bool SDAL<E>::check_length(){
    size_t len = length();
    if(array_size >= 100 && len < (array_size/2))
      return true;
    return false;
  }


  template <typename E>
  bool SDAL<E>::is_full(){
    if(tail == (array_size-1)){
      return true;
    }
    return false;
  }

  template <typename E>
  size_t SDAL<E>::calculate(){
    size_t new_size;
    if(check_length())
      new_size = (array_size*(.75));
    else if(is_full())
      new_size = (array_size*(1.50));
    return new_size;
  }

  template <typename E>
  void SDAL<E>::reallocate(){
    array_size = calculate();
    size_t len = length();


    E *new_data = new E[array_size];
    for(size_t i = 0; i < len; i++){
      new_data[i] = data[i];
    }
    delete [] data;
    // data = NULL;
    data = new_data;
    // data[len] = element;
    // tail = len;
  }

  template <typename E>
  E SDAL<E>::peek_front(){
    return data[0];
  }

  template <typename E>
  E SDAL<E>::peek_back(){
    return data[tail];
  }

  template <typename E>
  void SDAL<E>::clear(){
    tail = 0;
  }

  template <typename E>
  bool SDAL<E>::is_empty(){
    if(tail==0)
      return true;
    return false;
  }

  template <typename E>
  bool SDAL<E>::contains(E element,  bool(*equals_function)(E,E)){
      size_t len = length();
      for(size_t i = 0; i< len; i++){
        bool results = equals_function(element, data[i]);
        if(results)
          return true;
        }
      return false;
    }


  template <typename E>
  E* const SDAL<E>::contents(){
    size_t len = length();
    E *const array = new E[len];
    for(size_t i = 0; i<len; i++){
      array[i] = data[i];
    }
    return array;
  }



  template <typename E>
  void SDAL<E>::print(std::ostream &ostream){

    if(is_empty()){
      printf("<empty list>");
    }
    else{
        size_t len = length();
        for(size_t i = 0; i < len; i++){
          ostream << "[ " << data[i] << "], ";
        }
      }

  }

  template <typename E>
  //have to shift elements in remove....
  E SDAL<E>::remove(size_t position){
    E stuff = data[position];
    if(position == tail){
      tail--;
      // E stuff = data[position];
      return stuff;
    }
    else{
      // E stuff = data[position];
      for(size_t i = position; i <= tail; i++){
        data[i]=data[i+1];
      }
      return stuff;
    }
  }

  template <typename E>
  E SDAL<E>::item_at(size_t position){
    size_t len = length();
    // std::cout << len << " in function" << std::endl;
    if(position >= len){
      throw std::runtime_error("Position is out of bounds of array list"); // not working
    }
    else
      return data[position];
  }


//check for out of bounds position in this, item_at and others
  template <typename E>
  E SDAL<E>::replace(E element, size_t position){
    size_t len = length();
    if(position > len || position == NULL){
      throw std::runtime_error("There is nothing at this poisition to replace with, or your position is a NULL value");
    }
    // if(position == tail){
    //   E stuff = data[position];
    //   // tail++;
    //   data[position] = element;
    //   return stuff;
    // }
    else{
      E stuff = data[position];
      data[position] = element;
      return stuff;
  }
}

template <typename E>
E SDAL<E>::pop_back(){
  E stuff = data[tail];
  tail--;
  return stuff;
}

template <typename E>
E SDAL<E>::pop_front(){
  size_t len = length();
  E stuff = data[0];
  for(size_t i = 1; i<len; i++){
    //shift elements to left
    data[i-1]=data[i];
  }
  return stuff;
}




  template <typename E>
  void SDAL<E>::insert(E element, size_t position){
    // if(position > tail+1){
    //   throw std::runtime_error("Position is out of bounds of dynamic array list");
    // }
    if(is_full()){
      reallocate();
      // insert(element, position);  //should i recursively call? where does the program go after i reallocate?
      //gotta take in the element and insert that.....
    }

    if(check_length()){
      reallocate();
      // insert(element, position);
    }

    // else if(check_length()){
    //   reallocate(); //gotta take in the element and insert that....
    // }
    //what if tail is at the end of the array?

    else{
      if(position == 0){
      //shift elements to the right
        for(size_t i = tail; i > 0; i--){
          data[i+1]=data[i];
        }
        data[position]=element;
        tail = position;
      }
    //what if tail is at the end of the array?
      else if(position == tail){
        data[tail+1]=data[tail];
        tail++;
        data[position]=element;
      }

//what if tail is at the end of the array?
      else{
        for(size_t i = position; i <= tail; i++){
          data[i+1]=data[i];
        }
        data[position]=element;
        tail++;
      }
    }



  }
// check for full
  template <typename E>
  void SDAL<E>::push_front( E element){
    if(is_full() || check_length()){
      reallocate();
      // push_front(element);
    }
    for(size_t i = 0; i < tail; i++){
      data[i+1]=data[i];
    }
    data[0]=element;
    tail++;
  }
//check for full
  template <typename E>
  void SDAL<E>::push_back(E element){
    if(is_full() || check_length()){
      reallocate();
      // push_back(element);
    }
    data[tail+1] = element;
    tail++;
  }


  template <typename E>
  size_t SDAL<E>::length(){
    size_t len = tail;
    return len+1;
  }
}


int main(){
  cop3530::SDAL<int> mySDAL = cop3530::SDAL<int>();
  size_t size = mySDAL.size();
  // size_t size = array_size;

  // cop3530::SDAL<int> mySDAL = cop3530::SDAL<int>(60);

  for(int i = 0; i<size; i++){
    mySDAL.insert((i+1), i);
  }
  // mySDAL.insert(1,0);
  // mySDAL.insert(2,1);
  // mySDAL.insert(3,2);
  // mySDAL.insert(60,61);
  std::cout << mySDAL.peek_front() << std::endl;
  std::cout << mySDAL.peek_back() << std::endl;
  size_t i = 49;
  std::cout << mySDAL.return_tail() << std::endl;
  std::cout << mySDAL.item_at(i) << " outta function" << std::endl;
  size_t p =50;
  std::cout << mySDAL.item_at(p) << " derp outta function" <<  std::endl;
  std::cout << mySDAL.size() << "size before 51 insert" << std::endl;
  mySDAL.insert(51,50);
  std::cout << mySDAL.size() << " size after 51 insert" << std::endl;
  std::cout << mySDAL.peek_back() << std::endl;
  // std::cout << mySDAL.size() << std::endl;
  std::cout << mySDAL.return_tail() << std::endl;
  std::cout << mySDAL.item_at(i) << std::endl;
  //is full test works
}
