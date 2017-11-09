#include "psll.h"
#include <iostream>
#include <stdexcept>
#include <stddef.h>

int main(){
  cop3530::PSLL<int> myPSLL = cop3530::PSLL<int>();
  std::cout << myPSLL.length() << " length, expecting 0" << std::endl;



  std::cout << "push front test" << std::endl;
  myPSLL.push_front(1);
  myPSLL.push_front(2);
  myPSLL.push_front(3);
  myPSLL.push_front(4);
  myPSLL.print(std::cout);
  std::cout << std::endl;
  std::cout << myPSLL.length() << " length, expecting 4" << std::endl;
  std::cout << myPSLL.peek_front() << " front peek" << std::endl;
  std::cout << myPSLL.peek_back() << " back peek" << std::endl;
  std::cout << "End push front test" << std::endl;

  std::cout << "Pop front test" << std::endl;
  for(size_t i = myPSLL.length(); i>0; i--){
    std::cout << myPSLL.pop_front() << std::endl;
  }

  std::cout << myPSLL.length() << " length, expecting 0" << std::endl;
  std::cout << "End pop back test" << std::endl;

  std::cout <<  "===============================" << std::endl;
  std::cout <<  "===============================" << std::endl;
  std::cout << "push back test" << std::endl;
  myPSLL.push_back(1);
  myPSLL.push_back(2);
  myPSLL.push_back(3);
  myPSLL.push_back(4);
  myPSLL.print(std::cout);
  std::cout << std::endl;
  std::cout << myPSLL.length() << " length, expecting 4" << std::endl;
  std::cout << myPSLL.peek_front() << " front peek" << std::endl;
  std::cout << myPSLL.peek_back() << " back peek" << std::endl;
  std::cout << "End Push back test" << std::endl;

  std::cout << "Replace test" << std::endl;
  std::cout << myPSLL.replace(5,0) << " value replace expecting 1" << std::endl;
  myPSLL.replace(6,3);
  myPSLL.replace(7,1);
  myPSLL.print(std::cout);
  std::cout << std::endl;
  std::cout << "End Replace test" << std::endl;


  std::cout << "Start remove test" << std::endl;
  std::cout << myPSLL.remove(3) << " remove expecting 6" << std::endl;
  myPSLL.print(std::cout);
  std::cout << std::endl;
  std::cout << myPSLL.remove(0) << " remove expecting 5" << std::endl;
  myPSLL.print(std::cout);
  std::cout << std::endl;
  std::cout << myPSLL.remove(1) << " remove expecting 3" << std::endl;
  myPSLL.print(std::cout);
  std::cout << std::endl;
  myPSLL.remove(0);
  myPSLL.print(std::cout);
  std::cout << std::endl;

  // std::cout << "Pop back test" << std::endl;
  // for(size_t i = myPSLL.length(); i>0; i--){
  //   std::cout << myPSLL.pop_back() << std::endl;
  // }
  // std::cout << myPSLL.length() << " length, expecting 0" << std::endl;
  // std::cout << "End pop back test" << std::endl;


  // std::cout << "Pop front test" << std::endl;
  // for(size_t i = myPSLL.length(); i>0; i--){
  //   std::cout << myPSLL.pop_front() << std::endl;
  // }

//
// test push back and pop back
  return 0;
}
