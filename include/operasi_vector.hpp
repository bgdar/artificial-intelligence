#ifndef OPERASI_VECTOR_HPP_
#define OPERASI_VECTOR_HPP_

#include <ostream>
#include <iostream>
#include <valarray>


/**
 * @brief custum ouput dengan 2 nilai
 * @tparam T custum type yg di gunakan
 * @param ouput adalah ouput yang sudah di format
 * @param A adalah pasangan ouput yg di beriakan
 * @return std::ostream& reference ke output
 * */
template <typename T> // dengan tujuan untuk menghindari operasi beantai
std::ostream &operator<<(std::ostream &output , const std::pair<T,T> &A ){
  //batasin 4 angka doang
  output.precision(4);
  // cektak ke ouput karena ia stream
  //std::cout  << "(" <<A.first << "," << A.second << ")"; ala bg arfy
  output << "(" <<A.first << "," << A.second << ")";
  return output;
}
/**
 * @brief (overide) jika nilainya di kasi majemuk atau array t
 * memungkinkan mencetak std::cout << valarray
 *
 * @param T tipe yang terdapat di element valarray
 * @param output adalah stream untuk std::cout
 * @param A adalah valarray yg akan di tampilkan
 * @return std::ostream& reference ke ouput cout-nya
 **/
template <typename T>
std::ostream &operator <<(std::ostream &output , std::valarray<T> &A){
  //batasi precision 4 digit
  output.precision(4);
  //loop semua element di valarray
  for (const auto &a : A){
    output << a << " ";
  }
  output<<std::endl;
  return output;
}
/**
 * @brief menambahkan elemet baru ke akhir valarray
 *
 * karena constan yg tidak bisa di risize  maka buat valarray 
 * degan ukuran di tambah 1
 *
 * @tparam T type data element yg di berikan
 * @param A adalah valarray aslinya 
 * @param elemet adalah elemet baru yg akan di tambahkan
 * @return std::valarray<T> yaitu valarray baru 
 */
template <typename T> // tujuannya membuat array baru 
std::valarray<T> insert_element(const std::valarray<T> &A,const T &element){
  // buat val array baru dari valarray lama dengan ukuran + 1
  std::valarray<T>B;
  // fungsi untuk menambahkan 1 element
  B.resize(A.size() + 1);
  for(size_t i = 0; i < A.size();i++){
    //isi nilai dari element A 1 per 1
    B[i]  =  A[i]; 
  }
  // baru masukin nilai element baru (di ahirnya)
  B[B.size() - 1 ] = element;
  return B;
}

#endif // OPERASI_VECTOR_HPP_
