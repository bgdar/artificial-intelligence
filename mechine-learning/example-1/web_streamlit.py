# ini file web untuk menampilkan model ( hasil training ) dengan streamlit

# RUN
# streamlit run <nama_file>.py

# file: app_klasifikasi_jeruk.py
# RUN: streamlit run app_klasifikasi_jeruk.py

import streamlit as st
import pandas as pd
import joblib
import numpy as np


model = joblib.load("model-klasifikasi-jeruk.joblib")


st.title("Klasifikasi Jeruk 🍊")
st.write("Masukkan data jeruk untuk memprediksi kualitasnya.")

# --------------------------------------
# Form input user
# --------------------------------------
with st.form(key="input_form"):
    diameter = st.number_input("Diameter (cm)", min_value=0.0, step=0.01, value=3.0)
    berat = st.number_input("Berat (gram)", min_value=0.0, step=0.1, value=50.0)
    tebal_kulit = st.number_input("Tebal Kulit (cm)", min_value=0.0, step=0.01, value=0.5)
    kadar_gula = st.number_input("Kadar Gula (%)", min_value=0.0, step=0.1, value=10.0)
    asal_daerah = st.selectbox("Asal Daerah", ["Kalimantan", "Jawa", "Sumatra", "Jawa Barat"])
    warna = st.selectbox("Warna", ["hijau", "kuning", "oranye"])
    musim_panen = st.selectbox("Musim Panen", ["hujan", "kemarau"])
    
    submit_button = st.form_submit_button(label="Prediksi")

# --------------------------------------
# Proses prediksi
# --------------------------------------
if submit_button:
    # Buat dataframe dari input user
    new_data = pd.DataFrame([[diameter, berat, tebal_kulit, kadar_gula,
                              asal_daerah, warna, musim_panen]],
                            columns=["diameter","berat","tebal_kulit","kadar_gula",
                                     "asal_daerah","warna","musim_panen"])
    
    # Prediksi kelas
    predik = model.predict(new_data)[0]
    
    # Probabilitas semua kelas
    presentase = model.predict_proba(new_data)[0]
    
    # Probabilitas kelas prediksi
    index_pred = list(model.classes_).index(predik)
    confidence = presentase[index_pred] * 100
    
    # --------------------------------------
    # Tampilkan hasil
    # --------------------------------------
    st.success(f"Model memprediksi: **{predik}** dengan tingkat keyakinan {confidence:.2f}%")
    
    st.subheader("Probabilitas untuk semua kelas:")
    prob_df = pd.DataFrame({
        "Kelas": model.classes_,
        "Probabilitas (%)": np.round(presentase*100, 2)
    })
    st.table(prob_df)
