#ifndef FUNGSI_HPP__
#define FUNGSI_HPP__

#include <algorithm>
#include <cmath>
namespace Fungsi_Aktivasi {

/**
 * @brif funsgi sigmoid , akan mengambil 1 nilai numerik (x) yang di ubah ke 0
 * | 1.0 untuk probabilitas atau keluaran biner.
 * @Rumus : sigmoid(x) = 1/1+e^-x ,
 *      e(euler number bernilai)=2.71828...
 *
 * @param X : nilai logit yang diberikan
 * @return double nilai hasil sigmoid
 */
double sigmoid(const double &X) {
  return 1.0 / (1.0 + std::exp(-X));
  // return 1.0/(1.0/2.178*X)  jika tampa exp (manual)
}
/**
 * @brif fungsi sigmoid derifatif (turunan sigmoid)
 * di gunakan untuk menghitung gradident error | meng-update model selama fase
 * training
 * @param Y       : hasil ouput dari  sigmoid
 * @return double : hasil turunan dari sigmoid
 */
double sigmoid_derivatif(const double &Y) { return Y * (1.0 - Y); }

/**
 * @brif fungsi relu (rectrified linear unit )
 * jika input nya besar atau == 0 maka output = input
 * jika inputnya negatif maka ouputnya = 0
 * membantu mengatasi masalah terjadinya venishing gradien banyak di gunakan di
 * header layer
 * @example :  3 -> 3,
 *            0 -> 0,
 *           -1 -> 0,
 *
 * @param X       : input nilai tipe double
 * @return double : hasil nilai relu, 0 atau nilai asli
 */
double relu(const double &X) { return std::max(0.0, X); }

/**
 * @brif fungsi relu derifatif (turunan dari relu )
 * untuk mengupdate bobot dari neural network dan menghitung ada berapa gradient
 * error,
 * @example Y >  0 -> turunanya = 1,
 *          Y <  0 -> turunnanya = 0 ,
 *          Y == 0 -> turunanya = 0 atau 1 ,
 *
 * @param Y : nilai yang di berikan ( ouput dari Relu)
 * @return double : hasil 0.0 jika 1.0 dan jika kurang dari 0.0 maka hasilnay
 * 0.0
 */
double relu_derivatif(const double &Y) { return Y >= 0.0 ? 1.0 : 0.0; }

/**
 * @brif hyperbolic tangen (tanh )
 * fungsi untuk memetakan nilai input apapun  dari minus tak terhingga sampai
 * plus tak terhinga ke rentang antara -1 sampai 1
 * @example X >  1 = +1 ,
 *          X <  1 = -1 ,
 *          X == 0 = 0 ,
 * @param X : nilai yang di berikan
 * @return double : hasil kalkulasi tanh
 */
double tanh(const double &X) { return 2.0 / (1.0 + std::exp(-2.0 * X)) - 1.0; }

/**
 * @brif fungsi tanh derifatif (turunan tanh)
 * @param Y : nilai tanh atau ouput dari tanh yang di hitung
 * @return double : nilai turunan dari tanh
 */
double tanh_derifatif(const double &Y) { return 1.0 - Y * Y; }
} // namespace Fungsi_Aktivasi

#endif // !FUNGSI_HPP__
#define FUNGSI_HPP__
