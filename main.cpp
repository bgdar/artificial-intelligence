#include "include/fungsi.hpp"
#include "include/operasi_vector.hpp"

#include <chrono>
#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <valarray>
#include <vector>

// panggil Operator agar bisa langsung di gunakan tampa masalah 'binary'

namespace Layer {

// buat Layer (untuk merepresentasikan 1 lapisan neural network)
//  yang memiliki jumlah __neuron__ , fungsi aktivasi dan turunannya , matrix
//  bobot-nya , dan konfigurasi inisialisais dari bobotnya
class DenseLayer {
public:
  // panggil fungsi fungsi kativasi yg di terapkan di setiap layer
  double (*fungsi_aktivasi)(const double &);
  // panggil fungsi turunannya juga
  double (*derivatif_fungsi_aktivasi)(const double &);

  // inisialisais jenis aktivasi , karnel , neuron (jumlah lapisanya) yg di
  // butuhkan
  int neuron;
  // fungsi aktivasi yang mengarahkan ke yg di fungsi_aktivasi yg di tuju di
  // pointer
  std::string aktivasi;
  // matrix bobot antara input dari si neuron-nya
  std::vector<std::valarray<double>> karnel;

  /**
   * @param neuron : lapisan dengan jumlah yang bisa di atur
   * @param activasi :input , memilih fungsi aktivasi ('sigmoid','tanh','relu')
   * @param karnel_shape :
   * @param random_karnel : bobot sesuai parameter jika true maka menggunakan
   * nilai acak -1.0 sampai 1.0 , jika false maka menggunakan
   * unit_matrix_intialization  */
  DenseLayer(const int &neuron, const std::string &aktivasi,
             const std::pair<size_t, size_t> &karnel_shape,
             const bool &random_karnel) {
    // misalnya jika menggunakan fungsi sigmoid maka gunakan sigmoid ,
    // begitujuga dengan relu , tanh , jika tidak ada , masukan fungsi identitas
    if (aktivasi == "sigmoid") {
      fungsi_aktivasi =
          Fungsi::Aktivasi::sigmoid; // langsug panggil ke fungsi_aktivasi
      derivatif_fungsi_aktivasi = Fungsi::Aktivasi::sigmoid_derivatif;
    } else if (aktivasi == "tanh") {
      fungsi_aktivasi = Fungsi::Aktivasi::tanh;
      derivatif_fungsi_aktivasi = Fungsi::Aktivasi::tanh_derifatif;
    } else if (aktivasi == "relu") {
      fungsi_aktivasi = Fungsi::Aktivasi::relu;
      derivatif_fungsi_aktivasi = Fungsi::Aktivasi::relu_derivatif;
    } else if (aktivasi == "kosong" || aktivasi == "empty" ||
               aktivasi == "none" || aktivasi == "null") {
      fungsi_aktivasi = Fungsi::Helper::identitas;
      derivatif_fungsi_aktivasi = Fungsi::Helper::identitas;
    } else {
      std::cerr << "ERROR" << __func__ << " \n";
      std::cerr << "parameter tidak ada , yang ada ('relu','sigmoid','tanh' "
                   "atau 'none','kosong','empty')\n your aktivasi : "
                << aktivasi << std::endl;
      std::exit(EXIT_FAILURE);
    }

    // fungsi tambahan untuk inisialisasinya (masukan)
    this->aktivasi = aktivasi;
    this->neuron = neuron;

    // jika random_karnel true buat semaca fungsi inisialisais random karnel
    if (random_karnel) {
      Operasi_Vector::unifrom_random_initialization(karnel, karnel_shape, -1.0,
                                                    1.0);
    } else {
      Operasi_Vector::unit_matrix_intialization(karnel, karnel_shape);
    }
  }
  DenseLayer(const int &neuron, const std::string &aktivasi,
             const std::vector<std::valarray<double>> &karnel) {
    if (aktivasi == "sigmoid") {
      fungsi_aktivasi =
          Fungsi::Aktivasi::sigmoid; // langsug panggil ke fungsi_aktivasi
      derivatif_fungsi_aktivasi = Fungsi::Aktivasi::sigmoid_derivatif;
    } else if (aktivasi == "tanh") {
      fungsi_aktivasi = Fungsi::Aktivasi::tanh;
      derivatif_fungsi_aktivasi = Fungsi::Aktivasi::tanh_derifatif;
    } else if (aktivasi == "relu") {
      fungsi_aktivasi = Fungsi::Aktivasi::relu;
      derivatif_fungsi_aktivasi = Fungsi::Aktivasi::relu_derivatif;
    } else if (aktivasi == "kosong" || aktivasi == "empty" ||
               aktivasi == "none" || aktivasi == "null") {
      fungsi_aktivasi = Fungsi::Helper::identitas;
      derivatif_fungsi_aktivasi = Fungsi::Helper::identitas;
    } else {
      std::cerr << "ERROR" << __func__ << " \n";
      std::cerr << "parameter tidak ada , yang ada ('relu','sigmoid','tanh' "
                   "atau 'none','kosong','empty')\n your aktivasi : "
                << aktivasi << std::endl;
      std::exit(EXIT_FAILURE);
    }

    this->aktivasi = aktivasi;
    this->neuron = neuron;
    this->karnel = karnel;
  };
  // copy contrustor
  DenseLayer(const DenseLayer &layer) = default;

  ~DenseLayer() = default;
  // copy assigmet operator
  DenseLayer &operator=(const DenseLayer &layer) = default;
  // assigment
  DenseLayer &operator=(DenseLayer &&) = default;
};

}; // namespace Layer

/** bungkus layer dalam 1 kesatuan ( NEURAL NETWORK )*/
class NeuralNetwork {
private:
  // fungsi layer untuk menerima data dari layer
  std::vector<Layer::DenseLayer> layers;

  // buat lagi untuk info kalau layer sudah berhasil di buat
  NeuralNetwork(
      const std::vector<std::pair<int, std::string>> &config,
      const std::vector<std::vector<std::valarray<double>>> &karnels) {
    // informasikan fungsi di layer pertama tidak ada jika confignya == 'none'
    if (config.begin()->second == "none") {
      std::cerr << "ERROR fungsi :" << __func__ << " \n";
      std::cerr << "layer pertama tidak memiliki fungsi aktivasi tapi ";
      std::cerr << config.begin()->second;
      std::exit(EXIT_FAILURE);
    }
    // jika tidak ada 1 atau kurang dari 1 layer
    if (config.size() <= 1) {
      std::cerr << "ERROR fungsi :" << __func__ << "\n";
      std::cerr << "neural network setidaknya harus memiliki 2layer \n";
      std::exit(EXIT_FAILURE);
    }
    // konstruksikan untuk mengisil hasilnya ke dalam  1 kesatuan
    //  untuk bekerja dengan banyak layer
    for (size_t i = 0; i < config.size(); i++) {
      // masukin ke dalam DanseLayer
      layers.emplace_back(
          Layer::DenseLayer(config[i].first, config[i].second, karnels[i]));
    }
    std::cout << "network aready \n";
  }

  /**
   * Fungsi forwat pass ( single prediksi)
   * fungsi untuk kalkulasi dari hasil ouput setelah layer terakhir
   */
  std::vector<std::vector<std::valarray<double>>>
  __detail_single_prediksi(const std::vector<std::valarray<double>> &X) {
    std::vector<std::vector<std::valarray<double>>> details;
    std::vector<std::valarray<double>> pass_sementara = X;

    details.emplace_back(X);

    for (const auto &l : layers) {
      // kalikan
      pass_sementara =
          Operasi_Vector::perkalianMatrix(pass_sementara, l.karnel);
      // fungsi aktivasi tiap nilai logist (nilai matrix yang di berikan )
      pass_sementara =
          Operasi_Vector::apply_function(pass_sementara, l.fungsi_aktivasi);
      details.emplace_back(pass_sementara);
    };
    return details;
  }

public:
  NeuralNetwork() = default;
  // explisit dari neural network nantik buat contrustor yg menerima konfigurasi
  // layer sebagai inputnya nantik
  explicit NeuralNetwork(
      const std::vector<std::pair<int, std::string>> &config) {
    // informasikan fungsi di layer pertama tidak ada jika confignya == 'none'
    if (config.begin()->second == "none") {
      std::cerr << "ERROR fungsi :" << __func__ << " \n";
      std::cerr << "layer pertama tidak memiliki fungsi aktivasi tapi ";
      std::cerr << config.begin()->second;
      std::exit(EXIT_FAILURE);
    }
    // jika tidak ada 1 atau kurang dari 1 layer
    if (config.size() <= 1) {
      std::cerr << "ERROR fungsi :" << __func__ << "\n";
      std::cerr << "neural network setidaknya harus memiliki 2layer \n";
      std::exit(EXIT_FAILURE);
    }
    // PROSES Layer
    // ini adalah alur jalannya dari setiap nilai layer (0:layer = 0 -> 0 -> 0)
    layers.push_back(Layer::DenseLayer(config[0].first, config[0].second,
                                       {config[0].first, config[0].first},
                                       false));
    // buat layer dimana ia memprosesnya
    for (size_t i = 1; i < config.size(); i++) {
      layers.push_back(Layer::DenseLayer(config[i].first, config[i].second,
                                         {config[i - 1].first, config[i].first},
                                         true));
    }
  }
  NeuralNetwork(const NeuralNetwork &model) = default;
  ~NeuralNetwork() = default;
  NeuralNetwork &operator=(const NeuralNetwork &model) = default;
  NeuralNetwork(NeuralNetwork &&) = default;
  // operator assigmint
  NeuralNetwork &operator=(NeuralNetwork &&) = default;

  // fungsi untuk mengambil X waize (load dataset)
  std::pair<std::vector<std::vector<std::valarray<double>>>,
            std::vector<std::vector<std::valarray<double>>>>
  get_xy_from_csv(const std::string &file_name, const bool &last_label,
                  const bool &normalize, const int &slip_lines = 1) {
    // panggil ifstream , unuk read file
    std::ifstream in_file;
    //
    in_file.open(file_name.c_str() /*panggil dalam bentuk string*/,
                 std::ios::in /*input*/);
    // validasi permasalah saat membuka file
    if (!in_file.is_open()) {
      std::cerr << "ERROR fungsi" << __func__ << "\n";
      std::cerr << "Tidak bisa di buka file \n";
      std::exit(EXIT_FAILURE);
    }
    // ambil nilai X , Y , dan Z di dataset dengan membuat vector baru
    std::vector<std::vector<std::valarray<double>>> X, Y;
    std::string line;
    // hilangkah fungsi fungsi yang berhubungan dengan new line
    for (int i = 0; i < slip_lines; i++) {
      // hapus fungsi 'enter' dan gabung jadi kesatuan matrix
      std::getline(in_file, line, '\n');
    }
    // ambil info dari file dan simpan ke X,Y
    while (!in_file.eof() && std::getline(in_file, line, '\n')) {
      std::valarray<double> x_data, y_data;
      // ambil string frame dari setiap line dari dataset
      std::stringstream ss(line);
      std::string token;
      // setiap dari baris dataset nya (',')
      while (std::getline(ss, token, ',')) {
        x_data = Operasi_Vector::insert_element(x_data, std::stod(token));
      }
      // jika label terdapat di column terakhir juga
      if (last_label) {
        y_data.resize(this->layers.back().neuron);
        if (y_data.size() > 1) {
          y_data[x_data[x_data.size() - 1]] = 1;
        } else {
          y_data[0] = x_data[x_data.size() - 1];
        }
        x_data = Operasi_Vector::pop_back(x_data);
      } else {
        y_data.resize(this->layers.back().neuron);
        if (y_data.size() > 1) {
          y_data[x_data[x_data.size() - 1]] = 1;
        } else {
          y_data[0] = x_data[x_data.size() - 1];
        }
        x_data = Operasi_Vector::pop_back(x_data);
      }
      // hasil nilai colecting dari csv data push ke colect X dan Y
      X.push_back({x_data});
      Y.push_back({y_data});
    }
    // jika ada fungsi normalisasi pada fase training
    if (normalize) {
      X = Operasi_Vector::minmax_scaling(X, 0.01, 1.0);
    }
    in_file.close();
    return std::make_pair(X, Y);
  }
  /** fungsi untuk membprediksi setiap semple yang di berikan dari nilai X nya
   * jadi ini akan mengembalikan aktivasi dari layer paling terakhir (nilai
   * aktual)*/
  std::vector<std::valarray<double>>
  single_prediksi(const std::vector<std::valarray<double>> &X) {
    auto aktivasi = this->__detail_single_prediksi(X);
    return aktivasi.back();
  }
  /** besch predistion
   * @return vector prediksi */
  std::vector<std::vector<std::valarray<double>>>
  batch_prediksi(const std::vector<std::vector<std::valarray<double>>> &X) {
    std::vector<std::vector<std::valarray<double>>> prediksi_batch(X.size());
    for (size_t i = 0; i < X.size(); i++) {
      prediksi_batch[i] = this->single_prediksi(X[i]);
    }
    return prediksi_batch;
  };
  /**fungsi fiting data
   * menerapkan fungsi back prepagation*/
  void fiting_model(const std::vector<std::vector<std::valarray<double>>> &X_,
                    std::vector<std::vector<std::valarray<double>>> Y_,
                    const int &epochs = 100, const double &learning_rate = 0.01,
                    const size_t batch_size = 32, const bool &shuffel = true) {
    // ambil nilai X dan Y
    std::vector<std::vector<std::valarray<double>>> X = X_, Y = Y_;
    // validasi label dan input datanya harus sama
    if (X.size() != Y.size()) {
      std::cerr << "ERROR di fungsi " << __func__ << "\n";
      std::cerr << "X dan Y berbeda ukuranya \n";
    }
    // buat fase trainin
    std::cout << "INFO : Training running ..." << std::endl;
    for (int epoch_data = 1; epoch_data <= epochs; epoch_data++) {
      if (shuffel) {
        Operasi_Vector::equal_shuffle(X, Y);
      }
      // start clock dari 'sekarang'
      auto start = std::chrono::high_resolution_clock::now();
      // inisialiasasi performance matrix-nya
      double loss = 0, akurasi = 0;
      for (size_t bach_start = 0; bach_start < X.size();
           bach_start += batch_size) {
        for (size_t i = bach_start;
             i < std::min(X.size(), bach_start + batch_size); i++) {
          std::vector<std::valarray<double>> grad, cur_error, predicted;
          auto aktivasi = this->__detail_single_prediksi(X[i]);
          // hitung gradient vector untuk meng-store gradien dari semua layer
          //  yang menghasilkan nilai rata rata untuk di masukan ke karnel-nya
          //  jadi nantik akan  buat gradien baru berdasarkan ukuran dari per
          //  layernya
          std::vector<std::vector<std::valarray<double>>> gradient;
          gradient.resize(this->layers.size());

          // inisialisasi zero-nya
          for (size_t i = 0; i < gradient.size(); i++) {
            Operasi_Vector::zero_initialization(
                gradient[i], Operasi_Vector::get_shape(this->layers[i].karnel));
          }
          predicted = aktivasi.back();
          cur_error = predicted - Y[i];

          // fungsi back propagation berjalan
          loss += Operasi_Vector::sum(Operasi_Vector::apply_function(
              cur_error, Fungsi::Helper::pangkat));
          // jika operasi nya sama maka ddi tambhakan 1
          if (Operasi_Vector::argmax(predicted) ==
              Operasi_Vector::argmax(Y[i])) {
            akurasi += 1;
          };
          // layer untuk back propagation
          for (size_t j = this->layers.size() - 1; j >= 1; j--) {
            cur_error = Operasi_Vector::hadamard_product(
                cur_error, Operasi_Vector::apply_function(
                               aktivasi[j + 1],
                               this->layers[j].derivatif_fungsi_aktivasi));
            // hitung
            grad = Operasi_Vector::perkalianMatrix(
                Operasi_Vector::transpose(aktivasi[j]), cur_error);
            cur_error = Operasi_Vector::perkalianMatrix(
                cur_error, Operasi_Vector::transpose(this->layers[j].karnel));
            gradient[j] = gradient[j] + grad / double(batch_size);
          }
          // menghitung learning rete
          for (size_t j = this->layers.size() - 1; j >= 1; j--) {
            this->layers[j].karnel =
                this->layers[j].karnel - gradient[j] * learning_rate;
          }
        }
      }
      auto stop = std::chrono::high_resolution_clock::now();
      auto duration =
          std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

      loss /= X.size();
      akurasi /= X.size();
      std::cout.precision(0);
      std::cout << "taining epoch" << epochs << "/" << epoch_data;
      std::cout << "lost " << loss;
      std::cout << " akurasi " << akurasi;
      std::cout << "time " << duration.count() / 1e6 << "detik \n";
    }
    return;
  }
  /**
   * fungsi untuk meng fiting dari file dataset (csv)
   */
  void fifting_from_csv(const std::string &file_name, const bool &last_label,
                        const int &epochs, const double &learning_rate,
                        const bool &normalize, const int &slip_lines = 1,
                        const size_t &batch_size = 32,
                        const bool &shuffel = true) {
    auto data =
        this->get_xy_from_csv(file_name, last_label, normalize, slip_lines);
    // fifting model
    this->fiting_model(data.first, data.second, epochs, learning_rate,
                       batch_size, shuffel);
  }
  /** fungsi untuk evaluasi model */
  void evaluation(const std::vector<std::vector<std::valarray<double>>> &X,
                  std::vector<std::vector<std::valarray<double>>> &Y) {
    std::cout << "INFO :evaluasi model started \n";
    double akurasi = 0, loss = 0;
    // ambil setiap semple dalam input yang di berikan
    for (size_t i = 0; i < X.size(); i++) {
      auto prediksi = this->single_prediksi(X[i]);
      // validasi apakah prediksi benar
      if (Operasi_Vector::argmax(prediksi) == Operasi_Vector::argmax(Y[i])) {
        akurasi += 1;
      }
      loss +=
          Operasi_Vector::sum(Operasi_Vector::apply_function(
                                  Y[i] - prediksi, Fungsi::Helper::pangkat) *
                              0.5);
    }
    akurasi /= X.size();
    loss /= X.size();
    std::cout << "evaluasi akurasi :" << akurasi << std::endl;
    std::cout << "evaluasi loss :" << loss << std::endl;
  }
  /**fungsi evaluasi model , yang tersimpan ke dalam csv (save model)*/
  void evaluation_csv(const std::string &file_name, const bool &last_label,
                      const bool &normalize, const int &slip_lines = 1) {
    // ambil tarining data dari csv  ( dataset )
    auto data =
        this->get_xy_from_csv(file_name, last_label, normalize, slip_lines);
    this->evaluation(data.first, data.second);
    return;
  }
  /** fungsi untuk menyimpan model baru dari hasil training */
  void save_model(const std::string &last_file_name) {
    std::string file_name = last_file_name;
    // jika file name ketemu dengan tanda ujungnya model
    if (file_name.find("model") == file_name.npos) {
      file_name += ".model";
    }
    // simpan
    std::ofstream out_file;
    out_file.open(file_name.c_str(), std::ofstream::out | std::ofstream::trunc);

    if (!out_file.is_open()) {
      std::cerr << "ERROR :" << __func__ << "\n";
      std::cerr << "file tidak bisa di buka" << file_name << std::endl;
      std::exit(EXIT_FAILURE);
    }
    // set model
    out_file << layers.size();
    out_file << std::endl;
    for (const auto &layer : this->layers) {
      out_file << layer.neuron << ' ' << layer.aktivasi << std::endl;
      const auto shape = Operasi_Vector::get_shape(layer.karnel);
      out_file << shape.first << ' ' << shape.second << std::endl;
      for (const auto &row : layer.karnel) {
        for (const auto &value : row) {
          out_file << value << ' ';
        }
        out_file << std::endl;
      }
    }
    std::cout << "INFO : model di simpan \n";
    std::cout << "name :" << file_name << std::endl;
    out_file.close();
    return;
  }

  /** fungsi untuk load model yang telah di simpan */
  NeuralNetwork load_mode(const std::string &file_name) {
    std::ifstream in_file;
    in_file.open(file_name.c_str());

    if (!in_file.is_open()) {
      std::cout << "ERROR : di fungsi" << __func__ << "\n";
      std::cerr << "file :" << file_name << "tidak bisa di buka \n";
      std::exit(EXIT_FAILURE);
    }
    // panggil untuk storing konfigurasi dari si model
    std::vector<std::pair<int, std::string>> config;
    std::vector<std::vector<std::valarray<double>>> karnel;

    size_t total_layer = 0;
    in_file >> total_layer;
    // loop untuk setiap configurasi model-nya
    for (size_t i = 0; i < total_layer; i++) {
      int neuron = 0;
      std::string aktivasi;
      size_t shape_a = 0, shape_b = 0;
      std::vector<std::valarray<double>> karnel;
      // tambahkan
      in_file >> neuron >> aktivasi >> shape_a >> shape_b;

      // emplace_back untuk confignya
      for (size_t f = 0; f < shape_a; f++) {
        std::valarray<double> row(shape_a);
        for (size_t g = 0; g < shape_b; g++) {
          in_file >> row[g];
        }
        karnel.push_back(row);
      }
      config.emplace_back(std::make_pair(neuron, aktivasi));
      karnel.emplace_back(karnel[i]);
    }
    std::cout << "INFO : model aready loaded \n";
    in_file.close();
    return NeuralNetwork(config, karnel);
  }
  /** fungsi untuk mem-print hasil dari dataset yang di berikan */
  void result() {
    std::cout << "============= Neural Network ============ \n\n";

    // tampilkan perlayer
    for (size_t i = 1; i <= layers.size(); i++) {
      std::cout << i << ")";
      std::cout << "Neuron :" << layers[i - 1].neuron;
      std::cout << "aktivasi" << layers[i - 1].aktivasi;
      std::cout << " karnel shape :"
                << Operasi_Vector::get_shape(layers[i - 1].karnel);
      std::cout << std::endl;
      std::cout << "@reference : Warga Slowy \n";
    }
  }
};

static void tetsting() {
  NeuralNetwork tetsNN = NeuralNetwork({
      {4, "none"},    // layer 1 dengan 4 neuron tampa aktivasi
      {6, "relu"},    // layer 2 dengan 6 neuron degan aktivasi relu
      {3, "sigmoid"}, // layer 3 degan 3 neuron degan aktivasi sigmoid
  });

  tetsNN.result();
  tetsNN.fifting_from_csv("dataset/Iris.csv", true, 100, 0.3, false, 2, 32,
                          true);
  return;
  ;
}

int main() {
  tetsting();
  return 0;
}
