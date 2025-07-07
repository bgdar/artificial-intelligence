#include "include/operasi_vector.hpp"

#include <iostream>
#include <ostream>
#include <utility>
#include <valarray>

int main () {

  // sudah di custom cout<<
  // buat standar cout
  // auto p = std::make_pair(3.142323232,2.7123243);
  // std::cout << p <<std::endl;

  // std::valarray<double> arraynya = {2.3,45.2,4.2,23.5};
  // std::cout << arraynya;
  
  // contoh utnuk insert_element
  std::valarray<int> arrayinsert = { 1,3,4};
  auto resulArrayInsert = insert_element(arrayinsert,2);
  std::cout << resulArrayInsert <<std::endl;
  
  return 0;
}
