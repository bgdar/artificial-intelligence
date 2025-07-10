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
  // std::vector<std::valarray<double>> matriks;
  // std::pair<size_t, size_t> shape = {3, 4}; // 3 x 4 (3 baris 4column)
  // double low = 0.0, high = 1.0;
  //
  // unifrom_random_initialization(matriks, shape, low, high);
  //
  // std::cout.precision(4); // ambil 4 baris aja
  // std::cout << "matrix inisialisais yg di acak " << std::endl;
  // for (const auto &row : matriks) {
  //   std::cout << row << std::endl;
  // }

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
  // std::vector<std::vector<std::valarray<double>>> dataset = {
  //     {{1.0, 2.0}},
  //     {{3.0, 4.0}},
  //     {{5.0, 6.0}},
  // };
  // auto normalisasi = minmax_scaling(dataset, 0.0, 1.0); // rentang 0.0 - 1.0
  // for (const auto &sampel : normalisasi) {
  //   for (const auto &layer : sampel) {
  //     for (double value : layer) {
  //       std::cout << value << " ";
  //     }
  //     std::cout << std::endl;
  //   }
  // }

  // CONTOH argmax
  // std::vector<std::valarray<double>> nilainya = {{2.0, 3.4, 5.0, 3.2, 1.2}};
  // size_t index_tertinggi = argmax(nilainya);
  // std::cout << "nilai index maximum terdapa pad index " << index_tertinggi
  //           << "\n";

  // CONTOH perkalian matrix
  // std::vector<std::valarray<int>> matrixs = {{1, 2}, {3, 4}};
  //
  // std::vector<std::valarray<int>> resultkali = matrixs * 3;
  // for (const auto &row : resultkali) {
  //   for (int value : row) {
  //     std::cout << value << " ";
  //   }
  //   std::cout << "\n";
  // }
  // std::cout << "\n";
  // std::vector<std::valarray<int>> resulttambah = matrixs + 3;
  // for (const auto &row : resulttambah) {
  //   for (int value : row) {
  //     std::cout << value << " ";
  //   }
  //   std::cout << "\n";
  // }
  // std::cout << "\n";
  // std::vector<std::valarray<int>> resultkurang = matrixs - 3;
  // for (const auto &row : resultkurang) {
  //   for (int value : row) {
  //     std::cout << value << " ";
  //   }
  //   std::cout << "\n";
  // }
  // std::cout << "\n";

  // // CONTOH traspose
  // std::vector<std::valarray<int>> matriks = {{1, 2, 3}, {4, 5, 6}};
  // std::vector<std::valarray<int>> matriks_baru = transpose(matriks);
  // for (const auto A : matriks_baru) {
  //   for (int value : A) {
  //     std::cout << value << " ";
  //   }
  //   std::cout << " \n";
  // }

  // CONTOH penambhana Array
  // std::vector<std::valarray<int>> matrix_A = {{1, 2, 3}, {4, 5, 6}};
  // std::vector<std::valarray<int>> matrix_B = {{7, 8, 9}, {10, 11, 12}};
  // std::vector<std::valarray<int>> matrix_result = matrix_A + matrix_B;
  // for (const auto &row : matrix_result) {
  //   for (int value : row) {
  //     std::cout << value << " ";
  //   }
  //   std::cout << "\n";
  // }

  // CONTOH perkalian matriks
  // std::vector<std::valarray<int>> matrix_a = {{1, 2, 3}, {4, 5, 6}};
  // std::vector<std::valarray<int>> matrix_b = {{7, 8}, {9, 10}, {11, 12}};
  //
  // std::vector<std::valarray<int>> hasil_kali =
  //     Operasi_Vector::perkalianMatrix(matrix_a, matrix_b);
  //
  // for (const auto &row : hasil_kali) {
  //   for (const int value : row) {
  //     std::cout << value << " ";
  //   }
  //   std::cout << "\n";
  // }

  // CONTOH hadamard product
  std::vector<std::valarray<int>> matrix_a = {{1, 2}, {3, 4}};
  std::vector<std::valarray<int>> matrix_b = {{5, 6}, {7, 8}};
  auto hasil_hadamard = Operasi_Vector::hadamard_product(matrix_a, matrix_b);
  for (const auto &row : hasil_hadamard) {
    for (int value : row) {
      std::cout << value << " ";
    }
    std::cout << "\n";
  }

  return 0;
}
