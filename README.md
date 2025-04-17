# Plagialisme_code-NLP
Sistem pendeteksi plagialisme code degan algoritma NLP dan mechin learning 


### example alur 
   +-------------+
   |  Kode Baru  |. <- inputan code baru 
   +------+------+  
          |
          v
  +---------------+
  | Preprocessing |
  | (normalisasi) |
  +---------------+
          |
          v
  +----------------------+
  | Representasi Kode    | <-- TF-IDF / AST / Embedding
  +----------------------+
          |
          v
  +----------------------------+
  | Bandingkan dengan Database |
  +----------------------------+
          |
          v
  +------------------------+
  | Hasil & Referensi Mirip |.  
  +------------------------+
  
