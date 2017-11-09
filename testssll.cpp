#include "ssll.h"
#include <iostream>
#include <stdexcept>
#include <stddef.h>


int main(){
  // cop3530::SSLL<int> mySSLL();
  cop3530::SSLL<int> mySSLL = cop3530::SSLL<int>();
  std::cout << "Testing length of size 0 of SSLL" << std::endl;
  std::cout << mySSLL.length() << " length outside beofre first insert, expecting 0" << std::endl;
  //
  // std::cout << "Push back test" << std::endl;
  // mySSLL.push_back(1);
  // // std::cout << "Pop front expecting 1: " << mySSLL.pop_front << std::endl;
  // mySSLL.push_back(2);
  // mySSLL.push_back(3);
  // mySSLL.push_back(4);
  // mySSLL.print(std::cout);
  // std::cout << std::endl;
  //
  //
  //
  // std::cout << "Pop back test" << std::endl;
  // for(size_t i = mySSLL.length(); i>0; i--){
  //   std::cout << mySSLL.pop_back() << std::endl;
  // }
  // // mySSLL.pop_front();
  // // mySSLL.pop_front();
  //
  // // std::cout << " peek front after pop: " << mySSLL.peek_front() << std::endl;
  // // mySSLL.pop_back();
  // // mySSLL.pop_front();
  //
  // std::cout << "Push front test" << std::endl;
  // mySSLL.push_front(1);
  // mySSLL.push_front(2);
  // mySSLL.push_front(3);
  // mySSLL.push_front(4);
  // mySSLL.print(std::cout);
  // std::cout << std::endl;
  //
  //
  // std::cout << "Pop front test" << std::endl;
  // for(size_t i = mySSLL.length(); i>0; i--){
  //   std::cout << mySSLL.pop_front() << std::endl;
  // }
  //
  mySSLL.push_front(1);
  mySSLL.push_back(2);
  mySSLL.push_back(4);
  mySSLL.insert(3,2);
  mySSLL.insert(0,0);
  mySSLL.insert(5,5);
  mySSLL.print(std::cout);
  std::cout << std::endl;
  std::cout << "length: " << mySSLL.length() << std::endl;

  mySSLL.remove(5);
  mySSLL.remove(0);
  mySSLL.remove(3);
  std::cout << "length: " << mySSLL.length() << std::endl;

  //this will gimme error, expected
  // mySSLL.remove(3);
  //
  mySSLL.print(std::cout);
  std::cout << std::endl;

  mySSLL.replace(4,0);
  mySSLL.replace(9,2);
  mySSLL.print(std::cout);
  std::cout << std::endl;

  std::cout << mySSLL.peek_front() << "peek front before iter" <<  std::endl;
  std::cout << mySSLL.peek_back() << std::endl;

  cop3530::SSLL<int>::iterator iter = mySSLL.begin();
  cop3530::SSLL<int>::iterator end = mySSLL.end();

  std::cout << *iter << "iter peek_front" << std::endl;
  for(; iter!= end; iter++ ){
    std::cout << *iter << std::endl;
  }


  //expecting error
  // mySSLL.replace(4,3);



  // std::cout << "Push and pop back tests" << std::endl;
  // mySSLL.push_back(2);
  // // std::cout << "Pop back expecting 2: " << mySSLL.pop_back() << std::endl;
  //
  // mySSLL.push_back(3);
  // mySSLL.push_back(4);
  // mySSLL.print(std::cout);
  // std::cout << std::endl;



  // mySSLL.insert(1, 0);
  // std::cout << mySSLL.length() << " length outside #1" << std::endl;
  // std::cout << mySSLL.peek_front() << " peek front exptecting 1" << std::endl;
  // mySSLL.insert(2,0);
  // std::cout << mySSLL.length() << " length outside #2 " << std::endl;
  // std::cout << mySSLL.peek_front() << " peek front exptecting 2" << std::endl;
  //
  // std::cout << 4 * (.75) << std::endl;
  // // mySSLL.insert(3,3);
  // // mySSLL.insert(3,1);
  // // std::cout << mySSLL.length() << " length outside #3 " << std::endl;
  // // std::cout << mySSLL.pop_front() << std::endl;
  // std::cout << mySSLL.pop_front() << std::endl;
  return 0;
}
