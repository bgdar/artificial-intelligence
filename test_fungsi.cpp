#include "include/fungsi.hpp"
#include <iostream>

int main() {

  // CONTOH funsi sigmoid
  // double X = 0;
  // double hasil_sigmoid = Fungsi_Aktivasi::sigmoid(X);
  // std::cout << "hasil sigmoid :" << hasil_sigmoid << "\n";
  // CONTOH sigmoid derivatif
  // double hasil_sigmoid_derifatif =
  //     Fungsi_Aktivasi::sigmoid_derivatif(hasil_sigmoid);
  // std::cout << "hasil sigmoid derivatif :" << hasil_sigmoid_derifatif <<
  // "\n";

  // CONTOH relu
  // double X = -2;
  // double relu = Fungsi_Aktivasi::relu(X);
  // std::cout << "hasil relu " << relu << "\n";
  // // CONTOH relu_derivatif
  // double turunan_relu = Fungsi_Aktivasi::relu_derivatif(relu);
  // std::cout << "hasil relu derivatif :" << turunan_relu << "\n";

  // CONTOH tangh
  double X = 2.0;
  double hasil_tanh = Fungsi_Aktivasi::tanh(X);
  std::cout << "tangh : " << hasil_tanh << "\n";
  // COntoh tanh derifatif
  std::cout << " turunan tanh " << Fungsi_Aktivasi::tanh_derifatif(hasil_tanh);

  return 0;
}
