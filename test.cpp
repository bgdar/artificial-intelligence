#include "include/operasi_vector.hpp"

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <utility>
#include <valarray>
#include <vector>

int main() {

  // contoh sudah di custom cout<<
  // buat standar cout
  // auto p = std::make_pair(3.142323232,2.7123243);
  // std::cout << p <<std::endl;
  // std::valarray<double> arraynya = {2.3,45.2,4.2,23.5};
  // std::cout << arraynya;

  // CONTOH utnuk insert_element
  // std::valarray<int> arrayinsert = { 1,3,4};
  // auto resulArrayInsert = insert_element(arrayinsert,2);
  // std::cout << resulArrayInsert <<std::endl;

  // CONTOH untuk pop_front dan pop_and
  // std::valarray<int> arrayPop = {2, 3, 4, 5};
  // auto ambilValue = pop_front(arrayPop);
  // std::cout << "sisa Array : " << ambilValue << std::endl;
  // auto ambillastvalue = pop_back(arrayPop);
  // std::cout << "sisa array " << ambillastvalue;

  // CONTOH shuffling
  // std::vector<std::vector<std::valarray<double>>> A = {
  //     {{1.1, 2.2}},
  //     {{3.3, 4.4}},
  //     {{5.5, 6.6}},
  // };
  // std::vector<std::vector<std::valarray<double>>> B = {
  //     {{10.0}},
  //     {{20.0}},
  //     {{30.0}},
  // };
  // std::cout << " sebelum shuffling \n";
  // for (size_t i = 0; i < A.size(); ++i) {
  //   std::cout << "A[" << i << "] = { " << A[i][0][0] << "," << A[i][0][1]
  //             << "} -> ";
  //   std::cout << "B[" << i << "] = {" << B[i][0][0] << "} \n";
  // }
  // equal_shuffle(A, B);
  // std::cout << std::endl;
  // std::cout << " setelah shuffling \n";
  // for (size_t i = 0; i < A.size(); ++i) {
  //   std::cout << "A[" << i << "] = { " << A[i][0][0] << "," << A[i][0][1]
  //             << "} -> ";
  //   std::cout << "B[" << i << "] = {" << B[i][0][0] << "} \n";
  // }

  // CONTOH random data dummy
  std::vector<std::valarray<double>> matriks;
  std::pair<size_t, size_t> shape = {3, 4}; // 3 x 4 (3 baris 4column)
  double low = 0.0, high = 1.0;

  unifrom_random_initialization(matriks, shape, low, high);

  std::cout.precision(4); // ambil 4 baris aja
  std::cout << "matrix inisialisais yg di acak " << std::endl;
  for (const auto &row : matriks) {
    std::cout << row << std::endl;
  }

  // CONTOH inisialisasi matrix
  // std::vector<std::valarray<double>> matrix;
  // std::pair<size_t, size_t> shape = {10, 10}; // 4 x5 (4 baris 5 kolom)
  //
  // unit_matrix_intialization(matrix, shape);
  //
  // std::cout << "inisialisais hasil matrix identitas \n";
  // for (const auto &row : matrix) {
  //   std::cout << row << "\n";
  // }

  // CONTOH zero inisialisasi
  // std::vector<std::valarray<double>> matrixs;
  // std::pair<size_t, size_t> shape = {5, 5}; // 5x5
  //
  // zero_initialization(matrixs, shape);
  //
  // std::cout << "inisialisasi matrix awal \n";
  // for (const auto &row : matrixs) {
  //   for (double value : row) {
  //     std::cout << value << " ";
  //   }
  //   std::cout << "\n";
  // }

  // CONTOH sum
  // std::vector<std::valarray<int>> matriks = {
  //     {1, 2, 3},
  //     {4, 5, 6},
  // };
  // // result = sum(matriks);
  // std::cout << "ouput :" << sum(matriks) << "\n";

  // CONTOH get shape
  // std::vector<std::valarray<int>> matriks = {
  //     {1, 2, 3, 3},
  //     {5, 6, 7, 8},
  //     {9, 10, 11, 12},
  // };
  // auto shape = get_shape(matriks);
  // std::cout << "ukuran dari matrix : " << shape.first << "x" << shape.second
  //           << "\n";

  // CONTOH minman scalling
  std::vector<std::vector<std::valarray<double>>> dataset = {
      {{1.0, 2.0}},
      {{3.0, 4.0}},
      {{5.0, 6.0}},
  };
  auto normalisasi = minmax_scaling(dataset, 0.0, 1.0); // rentang 0.0 - 1.0
  for (const auto &sampel : normalisasi) {
    for (const auto &layer : sampel) {
      for (double value : layer) {
        std::cout << value << " ";
      }
      std::cout << std::endl;
    }
  }

  return 0;
}
