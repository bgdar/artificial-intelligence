#ifndef OPERASI_VECTOR_HPP_
#define OPERASI_VECTOR_HPP_

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <ostream>
#include <random>
#include <utility>
#include <valarray>
#include <vector>

// membungkus dengan namespace (modular)
namespace Operasi_Vector {
/**
 * @brief custum ouput dengan 2 nilai
 * @tparam T custum type yg di gunakan
 * @param ouput adalah ouput yang sudah di format
 * @param A adalah pasangan ouput yg di beriakan
 * @return std::ostream& reference ke output
 * */
template <typename T> // dengan tujuan untuk menghindari operasi beantai
std::ostream &operator<<(std::ostream &output, const std::pair<T, T> &A) {
  // batasin 4 angka doang
  output.precision(4);
  // cektak ke ouput karena ia stream
  // std::cout  << "(" <<A.first << "," << A.second << ")"; ala bg arfy
  output << "(" << A.first << "," << A.second << ")";
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
std::ostream &operator<<(std::ostream &output, const std::valarray<T> &A) {
  // batasi precision 4 digit
  output.precision(4);
  // loop semua element di valarray
  for (const auto &a : A) {
    output << a << " ";
  }
  output << std::endl;
  return output;
}
// versi lain untuk menangani overflow unuk vector
// template <typename T>
// std::ostream &operator<<(std::ostream &os, const std::valarray<T> &A) {
//   os.precision(4);
//   for (size_t i = 0; i < A.size(); ++i) {
//
//     os << "["<< A[i];
//     if (i < A.size() - 1)
//       os << "] "; // spasi antar elemen
//   }
//   return os;
// }

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
std::valarray<T> insert_element(const std::valarray<T> &A, const T &element) {
  // buat valarray baru dari valarray lama dengan ukuran + 1
  std::valarray<T> B;
  // fungsi untuk menambahkan 1 element
  B.resize(A.size() + 1);
  for (size_t i = 0; i < A.size(); i++) {
    // isi nilai dari element A 1 per 1
    B[i] = A[i];
  }
  // baru masukin nilai element baru (di ahirnya)
  B[B.size() - 1] = element;
  return B;
}
/**
 * @brief  rencananya copy value dari A ke B dengan menghapus element pertama
 * pada Bcon contoh : [1,2,3,4] -> [2,3,4]
 * @tparam T adalah tipe data element yg di berikan
 * @param A adalah valarray asli
 * @return std::valarray<T> yaitu valarray baru yang sudah di pop value awalnya
 */
template <typename T> std::valarray<T> pop_front(const std::valarray<T> &A) {
  // buat valarray baru
  std::valarray<T> B;
  // kurangkan element nya dulu
  B.resize(A.size() - 1);
  // copy semua element A ke B , di mulai dari element 1
  for (size_t i = 1; i < A.size(); ++i) {
    B[i - 1] = A[i];
  }
  return B;
}

/**
 * @brief  rencananya copy value dari A ke B dengan menghapus element terakhir
 * pada Bcon contoh : [1,2,3,4] -> [1,2,3]
 * @tparam T adalah tipe data element yg di berikan
 * @param A adalah valarray asli
 * @return std::valarray<T> yaitu valarray baru yang sudah di pop value awalnya
 */
template <typename T> std::valarray<T> pop_back(const std::valarray<T> &A) {
  // siapkan valarray baru
  std::valarray<T> B;
  // hapus element terakhir
  B.resize(A.size() - 1);
  // copy elemen ke B , tapi nilai ke 4 atau terakhir tidak akan di hitung ( di
  // hapus)
  for (size_t i = 0; i < A.size() - 1; i++) {
    B[i] = A[i];
  }
  return B;
}

/*
 * @brief fungsi equal_shuffle
 * tujuanya untuk mengacak data array beserta labelnya dengan teknik _equal
 * shuffle_ contoh : A[0] = {5,6} b[0] = 30 , misalnya di kalikan 5*6
 *
 * @tparam T : Template parameter yg di masukan nilai
 * @param A  : input data (misalnya untuk fitur atau citra)
 * @param B  : input data untuk label (hasil prediksi)
 */
template <typename T>
// 2 parameter A dan B ibaratkan berbentuk
// {
//  { {1,2},{misal...}}
// }
void equal_shuffle(std::vector<std::vector<std::valarray<T>>> &A,
                   std::vector<std::vector<std::valarray<T>>> &B) {
  // bila ukuran dari A dan B tidak sama maka trow error
  if (A.size() != B.size()) {
    // __func__ : akan me return nama string dari nama fungsi yg di berikn
    std::cerr << "ERRRO di fungsi" << __func__ << " : ";
    std::cerr << " shufffeling tidak bisa karena 2 vector berbeda size ";
    std::cerr << "A :" << A.size() << "|" << "B :" << B.size() << std::endl;
    // keluarkan program dengan info di atas
    std::exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i < A.size(); i++) {
    // buat nilai shuffle , random kan nilainya berdasarkan waktu exce pertama
    // (waktu system) kali ( waktu yg sekarang ada)
    std::srand(std::chrono::system_clock::now().time_since_epoch().count());
    // menghasilakn angka acak antar 0 sampai size dari A - 1
    size_t random_index = std::rand() % A.size();
    // swap elemet ke i dengan acak di vector A dan B secara sama
    // untuk memastika bahwa pair data tetap cocok setelah di random
    std::swap(A[i], A[random_index]);
    std::swap(B[i], B[random_index]);
  }
  return;
}
/**
 * @brief fungsu untuk dataset dummy dalam hal ini Matrix (2D)
 * ini digunakan untuk inisialisasi bobot neural network
 * degan rentan 0 - 1 misalnya :[0.232,0.456,0.789]
 * nilai random yg tersebar secara seragam dalam suatu rentang tertentu
 *
 * @tparam T    : type data yg di berikan
 * @param  A    : vector yang di berikan
 * @param shape : ukuran dari vector
 * @param low   : nilai terkecil
 * @param high  : nilai tertinggi
 */
template <typename T>
void unifrom_random_initialization(std::vector<std::valarray<T>> &A,
                                   const std::pair<size_t, size_t> &shape,
                                   const T &low, const T &high) {
  // bersihkan element A
  A.clear();
  // buar random degan generator dari nilai-nilai nya ( random_engine ini lebih
  // akurat dan flexibel dari rand())
  std::default_random_engine generator(
      // angka acak berdasarkan waktu system , yg berbeda setiap program di
      // jalanakan
      std::chrono::system_clock::now().time_since_epoch().count());
  // distribusikan sebuah nilai berdasarkan type yg di beriakan untuk di masukan
  std::uniform_real_distribution<T> nilai_distribusi(low, high);
  // loop untuk memasukan sesuai ukuran nilai yg di berikan
  for (size_t i = 0; i < shape.first; /*row*/ i++) {
    std::valarray<T> row;
    row.resize(shape.second);
    for (auto &r : row /*column */) {
      r = nilai_distribusi(generator);
    }
    A.push_back(row);
  }
  return;
}

/**
 * @brief fungsi inisialisasi matrix identitas (matrix persegi yg jumlah baris
 * == jumlah kolom)
 *
 * yg di mana semau element bernilai 0 kecuali pada diagonal utama bernilai 1
 * [1,0,0,0] ini menghasilkan  garis yg diagonal
 * [0,1,0,0]  berfungsi untuk menginialisasi sebuah layer di neural network
 * [0,0,1,0] juga bisa untuk simulasi numerik
 * [0,0,0,1]
 */
template <typename T>
void unit_matrix_intialization(std::vector<std::valarray<T>> &A,
                               std::pair<size_t, size_t> &shape) {
  A.clear();
  for (size_t i = 0; i < shape.first; i++) {
    // buat array baris
    std::valarray<T> row;
    //
    row.resize(shape.second);
    // isi baris pada elemet pertama = 1 selanjutnya di isi 0,0,0..
    row[i] = T(1);
    A.push_back(row);
  }
  return;
}

/**
 * @brief matrix zero inisialition
 * bertujuan pada mechin learning sederhana untuk menginisialisasi nilai awal
 * pada matric identitas di atas untuk di gunakan (data dummy | matrix 0)
 *
 * @tparam T : tipe yang di berikan
 * @param A  : Vector yang akan di buat matrix nol
 * @param shape : ukuran dari sebuah matrix misalnya 2 x3 (baris x colum)
 */
template <typename T>
void zero_initialization(std::vector<std::valarray<T>> &A,
                         const std::pair<size_t, size_t> &shape) {
  // bersihkan array A jika ada data
  A.clear();
  // shape.first : jumlah baris
  // shape.second : jumlah column
  // loop setiao baris
  for (size_t i = 0; i < shape.first; i++) {
    std::valarray<T> row;
    row.resize(shape.second);
    // isi ke matrix param A yg di berikan (adalah : 0)
    A.push_back(row);
    // jika mau menghindari alokasi memori berkali klai (performance) :
    // A.reserve(shape.first);
  }
  return;
}

/**
 * @brief fungsi menjumlah nilai matrix (baris dan column)
 * [1,2,3] jumlahkan semua matrix ini
 * [4,5,6] 1+2+3+4+5+6 = 21
 *
 * @tparam T : tipe data yg di berikan
 * @param A  : matrix yang kan di hitung ( baris dan column )
 * @return T : akan mengemabalikasi type data yg di berikan(valuenya)
 * */
template <typename T> T sum(const std::vector<std::valarray<T>> &A) {
  // buat nilai hasilnya dulu yg di mulai dar 0 ( menampung kumlah total-nya)
  T result = 0;
  for (const auto &matrixs : A) {
    // sum : fn bawaan dari valarray untuk menjumlahkan semua element
    // (baris-nya)
    result += matrixs.sum();
  }
  return result;
}

/**
 *@brief  get_shape fn yg mengemablikan jumlah ukuran matrix (baris dan column)
 *
 * @tparam  : type data yang akan di berikan
 * @param A : vector yg akan di hitung baris dan column
 * @return std::pair<size_t,size_t> : jumlah ukuran baris dan colum
 */
template <typename T>
std::pair<size_t, size_t> get_shape(const std::vector<std::valarray<T>> &A) {
  // buat subsize
  // (*A.begin()) : untuk iterator ke baris pertama si A
  // .size()      : untuk mengambil jumlah dari si column
  const size_t sub_size = (*A.begin()).size();
  // validasi
  for (const auto &a : A) {
    if (a.size() != sub_size) {
      std::cerr << "ERROR di fungsi" << __func__ << ":";
      std::cerr << "panjang dari matrix tidak sama  \n";
      std::exit(EXIT_FAILURE);
    }
  }
  // pairing dari sub ukuranya (jumlah baris dan column)
  return std::make_pair(A.size(), sub_size);
}

/**
 * @brief minmax scalling ( normalisasi data)
 * fungsi untuk normalisassi data , agar semua fitur punya bobot yg sama untuk
 * di gunakan neural network misalnya jika ada nilai yg 1.000.000.000-an ini
 * bisa jadi dominasi, yg padahal nilainya cuman 1
 * @tparam T   : tipe template dari suatu type data
 * @param A    : vector yang akan di normalisasikan
 * @param low  : nilai rendah
 * @param high : nilai tinggi
 */
template <typename T>
std::vector<std::vector<std::valarray<T>>>
minmax_scaling(const std::vector<std::vector<std::valarray<T>>> &A,
               const T &low, const T &high) {
  // nilai baru dari A copy ke B
  std::vector<std::vector<std::valarray<T>>> B = A;
  // ambil  baris dan kolom dari B element 0
  const auto shape = get_shape(B[0]);
  // jika ukuran column != 1 ( representasi 1 layer dari fitur yg harus
  // setidaknya ada (biargak 'ringkih'))
  if (shape.first != 1) {
    std::cerr << "ERROR di fungsi " << __func__ << ":";
    std::cerr << "vector yg di berikan tidak support untuk normalisasi data ";
    std::cerr << shape << std::endl;
    std::exit(EXIT_FAILURE);
  }
  // cari nilai min dan max
  //  ini jumlah fitur (column) , untuk nantik di lakukan normalisasi per fitur
  for (size_t i = 0; i < shape.second; /* jumlah column*/ i++) {
    T min = B[0][0][i], max = B[0][0][i];
    for (size_t j = 0; j < B.size(); j++) {
      // cari nilai terkecil dan terbesar dari seluruh semple(column) yg di
      // berikan
      min = std::min(min, B[j][0][i]);
      max = std::max(max, B[j][0][i]);
    }
    // fungsi dari min max scalling
    for (size_t k = 0; k < B.size(); k++) {
      // RUMUS : scalling = ((x - min) / (max - min)) x (high - low) + low
      // akan menghasilkan akan menjadikan semua nilai fitur dari nilai i akan
      // berada dalam rentang low dan high
      B[k][0][i] = ((B[k][0][i] - min) / (max - min)) * (high - low) + low;
    }
  }

  return B;
}

/**
 * @brief fungsi untuk mencari suatu index dari nilai maximum dalam 1 vector
 * tunggal [2.0,5.0,3.0,1.2,3.3,4.5] = nilai tertinggi 5.0 dan Outputnya 1 (5.0
 * di index 1)
 *
 *  @tparam T      : type data vector yang di berikan
 *  @param A       : vector yang di hitung argmax nya
 *  @return size_t : posisi index nilai tertinggi nya
 */
template <typename T> size_t argmax(const std::vector<std::valarray<T>> &A) {
  // ambil jumlah baris dan kolom
  const auto shape = get_shape(A);
  // validasi apakah vetor dengan baris tunggal
  if (shape.first != 1) {
    std::cerr << "ERROR di fungsi :" << __func__ << ":";
    std::cerr << "vectornya tidak support degan fungsi argmax \n";
    std::exit(EXIT_FAILURE);
  }
  // cari index di salah 1 element maxsimum-nya
  // std::distance   : menghitung silisis antara iterator2 lain(banding nilai yg
  // paling tinggi di vector) std:: begin     : sebagai iterasi awal dari suatu
  // vector std::max_element: mencari iterator ke element yg maxsimum std::end
  // : sebagai iterator di akhrinya
  return std::distance(std::begin(A[0]),
                       std::max_element(std::begin(A[0]), std::end(A[0])));
}

/*@brief perkalian matrix (overide) dengan scallar tertentu , misalnya
 * matrix : [[1,2],[3,4]]
 * value  : 2
 * Ouput  : [[2,4],[6,8]]
 * overload nantik x perkalian di c++
 *
 * @tparam T    : type data yang di berikan
 * @param A     : vector yang akan di kalikan dengan nilai scalar
 * @param value : nilai scalar
 * @return std::vector<<std::vallaray<T>> hasil perkalian-nya */
template <typename T>
std::vector<std::valarray<T>> operator*(const std::vector<std::valarray<T>> &A,
                                        const T &value) {
  // buat vector baru dengan copy dari value A ke vector B
  std::vector<std::valarray<T>> B = A;
  // loop setiap baris dan kalikan dengan nilai scallar (value)
  for (auto &row : B) {
    row *= value;
  }
  return B;
}

/*@brief penambahan matrix (overide) dengan scallar tertentu , misalnya
 * matrix : [[1,2],[3,4]]
 * value  : 2
 * Ouput  : [[3,4],[5,6]]
 * overload nantik x perkalian di c++
 *
 * @tparam T    : type data yang di berikan
 * @param A     : vector yang akan di tambahkan dengan nilai scalar
 * @param value : nilai scalar
 * @return std::vector<<std::vallaray<T>> hasil penambahan-nya */
template <typename T>
std::vector<std::valarray<T>> operator+(const std::vector<std::valarray<T>> &A,
                                        const T &value) {
  // buat vector baru dengan copy dari value A ke vector B
  std::vector<std::valarray<T>> B = A;
  // loop setiap baris dan tambahkan dengan nilai scallar (value)
  for (auto &row : B) {
    row += value;
  }
  return B;
}

/*@brief pembagian matrix (overide) dengan scallar tertentu , misalnya
 * matrix : [[1,2],[3,4]]
 * value  : 2
 * Ouput  : [[2,1],[1,2]]
 * overload nantik x perkalian di c++
 *
 * @tparam T    : type data yang di berikan
 * @param A     : vector yang akan di kalikan dengan nilai scalar
 * @param value : nilai scalar
 * @return std::vector<<std::vallaray<T>> hasil pembagian-nya */
template <typename T>
std::vector<std::valarray<T>> operator/(const std::vector<std::valarray<T>> &A,
                                        const T &value) {
  // buat vector baru dengan copy dari value A ke vector B
  std::vector<std::valarray<T>> B = A;
  // loop setiap baris dan bagikan dengan nilai scallar (value)
  for (auto &row : B) {
    row /= value;
  }
  return B;
}

/*@brief pengurangan matrix (overide) dengan scallar tertentu , misalnya
 * matrix : [[1,2],[3,4]]
 * value  : 2
 * Ouput  : [[-1,0],[1,2]]
 * overload nantik x perkalian di c++
 *
 * @tparam T    : type data yang di berikan
 * @param A     : vector yang akan di kurangkan dengan nilai scalar
 * @param value : nilai scalar
 * @return std::vector<<std::vallaray<T>> hasil pengurangan-nya */
template <typename T>
std::vector<std::valarray<T>> operator-(const std::vector<std::valarray<T>> &A,
                                        const T &value) {
  // buat vector baru dengan copy dari value A ke vector B
  std::vector<std::valarray<T>> B = A;
  // loop setiap baris dan kurangkan dengan nilai scallar (value)
  for (auto &row : B) {
    row -= value;
  }
  return B;
}

/**
 * @brif fungsi untuk mentrasfor ukuran dari matrix , misalnya
 * [1,2,3] => [1,4] baris jadi kolom
 * [4,5,6]    [2,5] baris menjadi kolom
 *            [3,6]
 *
 * @tparam T : type data yg di berikan
 * @param A  : vector atau matrix yang akan di traspose
 * @return std::vector<std::valarray<T>> : hasil traspose dari matrix
 */
template <typename T>
std::vector<std::valarray<T>>
transpose(const std::vector<std::valarray<T>> &A) {
  // ambil ukuran | shape untuk di traspose ( jumlah Baris & column)
  const auto shape = get_shape(A);
  // fungsi untuk membuat salinan baru A -> B (copy) agar nilai asli A tidak
  // kegangu
  std::vector<std::valarray<T>> B;
  // loop unutk merubahnya
  for (size_t j = 0; j < shape.second /*column*/; j++) {
    // buat 1 baris untuk memisah transpose ( panjangnya sama karena berasal
    // dari baris lama)
    std::valarray<T> row;
    row.resize(shape.first /*baris*/);
    // loop untuk mengisis baris baru dari column ,ambil element ke-i dari kolom
    // j
    for (size_t i = 0; i < shape.first; i++) {
      // ubah dari kolom ke baris | baris ke kolom
      row[i] = A[i][j];
    }
    B.push_back(row);
  }
  return B;
}

/**
 * @brif fungsi menambahkan 2 vector | matrix sekaligus , misalnya :
 * A : [1,2]  B : [5,6] = [6,8]
 *     [3,4]      [7,8]   [10,12]
 * Overiding operator tandan '+'
 *
 * @tparam T : tipe daya yang akan di berikan
 * @param A  : matrix A
 * @param B  : matrix B
 * @return  std::vector<std::valarray<T>> : hasil penjumlahan matrix A + B
 */
template <typename T>
std::vector<std::valarray<T>>
operator+(const std::vector<std::valarray<T>> &A,
          const std::vector<std::valarray<T>> &B) {
  // ambil panjang kolom dan baris
  const auto shape_a = get_shape(A);
  const auto shape_b = get_shape(B);
  // validasi apakah baris dan kolom sama
  if (shape_a.second != shape_b.second) {
    std::cerr << "ERROR di fungsi :" << __func__ << ":";
    std::cerr << "matrix nya memiliki ukuran kolom yang berbeda ";
    std::cerr << "kolom A :" << shape_a.second << "kolom B :" << shape_b.second;
    std::exit(EXIT_FAILURE);
  }
  if (shape_a.first != shape_b.first) {
    std::cerr << "ERROR di fungsi :" << __func__ << ":";
    std::cerr << "matrix nya memiliki ukuran baris yang berbeda ";
    std::cerr << "baris A :" << shape_a.first << "baris B :" << shape_b.first;
    std::exit(EXIT_FAILURE);
  }
  // tambahkan setiap vector
  // copyan ke c
  std::vector<std::valarray<T>> C;
  for (size_t i = 0; i < A.size(); i++) {
    C.push_back(A[i] + B[i]);
  }
  return C;
}

/**
 * @brif fungsi mengurangkan 2 vector | matrix sekaligus , misalnya :
 * A : [1,2]  B : [5,6] = [6,8]
 *     [3,4]      [7,8]   [10,12]
 * Overiding operator tandan '-'
 *
 * @tparam T : tipe daya yang akan di berikan
 * @param A  : matrix A
 * @param B  : matrix B
 * @return  std::vector<std::valarray<T>> : hasil pengurangan matrix A + B
 */
template <typename T>
std::vector<std::valarray<T>>
operator-(const std::vector<std::valarray<T>> &A,
          const std::vector<std::valarray<T>> &B) {
  // ambil panjang kolom dan baris
  const auto shape_a = get_shape(A);
  const auto shape_b = get_shape(B);
  // validasi apakah baris dan kolom sama
  if (shape_a.second != shape_b.second) {
    std::cerr << "ERROR di fungsi :" << __func__ << ":";
    std::cerr << "matrix nya memiliki ukuran kolom yang berbeda ";
    std::cerr << "kolom A :" << shape_a.second << "kolom B :" << shape_b.second;
    std::exit(EXIT_FAILURE);
  }
  if (shape_a.first != shape_b.first) {
    std::cerr << "ERROR di fungsi :" << __func__ << ":";
    std::cerr << "matrix nya memiliki ukuran baris yang berbeda ";
    std::cerr << "baris A :" << shape_a.first << "baris B :" << shape_b.first;
    std::exit(EXIT_FAILURE);
  }
  // tambahkan setiap vector
  // copyan ke c
  std::vector<std::valarray<T>> C;
  for (size_t i = 0; i < A.size(); i++) {
    C.push_back(A[i] - B[i]);
  }
  return C;
}

/**
 * @brif perkalian antara 2 matrix
 *
 * @tparam T : type data yang di berikan
 * @param  A : vector yg memiliki kolom yg sama dengan kolom B
 * 2param B  :  vector yang memiliki baris yang sama dengan matrix A
 * @return B : st:vector<std::valarray<T>> hasil perkalian 2 vector
 */
template <typename T>
std::vector<std::valarray<T>>
perkalianMatrix(const std::vector<std::valarray<T>> &A,
                const std::vector<std::valarray<T>> &B) {
  // ambil ukuran baris dan kolom
  const auto shape_a = get_shape(A);
  const auto shape_b = get_shape(B);

  // validasi 2 vector (kolom A != baris B)
  if (shape_a.second != shape_b.first) {
    std::cerr << "ERROR :" << __func__ << ":";
    std::cerr << " tidak bisa di kalikan karena kolom dan baris antara matrix "
                 "A dan B berbeda";
    std::exit(EXIT_FAILURE);
  }
  // vector untuk menyimpan hasil
  std::vector<std::valarray<T>> result;
  // loop melalui vector A
  for (size_t i = 0; i < shape_a.first; i++) {
    // buat baris baru untuk matrix result
    std::valarray<T> row;
    row.resize(shape_b.second);
    for (size_t j = 0; j < shape_b.second; j++) {
      for (size_t k = 0; k < shape_a.second; k++) {
        // hitung nilai element matriks
        //  ambil element K dari baris i di matrix A
        //  dan kalikan dengan element j di kolom K di matrix B
        //  dan tambahkan element result dari baris[j]
        row[j] += A[i][k] * B[k][j];
      }
    }
    result.push_back(row);
  }
  return result;
}

/**
 * @brif operasi hadamard product (mengalikan matriksx dengan matriks
 * lainya tapi per elementnya ) dan menghasilkan matrix baru misalnya :
 * [1,2] X [5,6] = [5,12]   (column dan baris hasus sama )
 * [3,4]   [7,8]   [21,32]
 *
 * @tparam T :tipe data yang di berikan
 * @param A  : matrix A
 * @param B  : matrix B
 * @return std::vector<<std::valarray<T>> : hasil dari perkalian matrix  A dan B
 */
template <typename T>
std::vector<std::valarray<T>>
hadamard_product(std::vector<std::valarray<T>> &A,
                 std::vector<std::valarray<T>> &B) {
  const auto shape_a = get_shape(A);
  const auto shape_b = get_shape(B);
  // validasi , pengecekan nilai misalnya 2x2 harus 2x2 , begitu juga 2x3 harus
  // dengan 2x3 yakni kolom dan barisnya
  if (shape_a.first != shape_a.first || shape_b.second != shape_b.second) {
    std::cerr << "ERROR :" << __func__ << ":";
    std::cerr << "matrix yang di berikan berbeda dimensi";
    std::exit(EXIT_FAILURE);
  }
  // lakukan kalkulasi (perkalian)
  std::vector<std::valarray<T>> result;
  for (size_t i = 0; i < A.size(); i++) {
    result.push_back(A[i] * B[i]);
  }
  return result;
}
} // namespace Operasi_Vector

#endif // OPERASI_VECTOR_HPP_
