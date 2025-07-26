#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

#define RESET   "\033[0m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define RED     "\033[1;31m"
#define CYAN    "\033[1;36m"

// Fungsi keanggotaan
float fuzzy_rendah(float x, float a, float b) {
    if (x <= a) return 1;
    else if (x >= b) return 0;
    else return (b - x) / (b - a);
}

float fuzzy_tinggi(float x, float a, float b) {
    if (x <= a) return 0;
    else if (x >= b) return 1;
    else return (x - a) / (b - a);
}

float fuzzy_normal(float x, float a, float b, float c, float d) {
    if (x <= a || x >= d) return 0;
    else if (x > a && x <= b) return (x - a) / (b - a);
    else if (x > b && x <= c) return 1;
    else return (d - x) / (d - c);
}

void garis() {
    cout << CYAN << "===============================================" << RESET << endl;
}

void run_program() {
    garis();
    cout << CYAN << "  FERNANDA RIFKY SYAHRIAL (23533738)  " << RESET << endl;
    cout << CYAN << "  SISTEM PENILAIAN RISIKO KESEHATAN (FUZZY)  " << RESET << endl;
    garis();

    float tekanan_darah, detak_jantung, usia;
    cout << "Masukkan Tekanan Darah (mmHg)  : ";
    cin >> tekanan_darah;
    cout << "Masukkan Detak Jantung (BPM)   : ";
    cin >> detak_jantung;
    cout << "Masukkan Usia (tahun)          : ";
    cin >> usia;

    float td_rendah = fuzzy_rendah(tekanan_darah, 90, 110);
    float td_normal = fuzzy_normal(tekanan_darah, 100, 120, 120, 140);
    float td_tinggi = fuzzy_tinggi(tekanan_darah, 130, 160);

    float dj_lambat = fuzzy_rendah(detak_jantung, 50, 70);
    float dj_normal = fuzzy_normal(detak_jantung, 60, 80, 80, 100);
    float dj_cepat  = fuzzy_tinggi(detak_jantung, 90, 120);

    float usia_muda   = fuzzy_rendah(usia, 20, 35);
    float usia_dewasa = fuzzy_normal(usia, 30, 45, 45, 60);
    float usia_tua    = fuzzy_tinggi(usia, 55, 70);

    // Aturan fuzzy
    float r1 = min({td_normal, dj_normal, usia_muda});     // Risiko rendah
    float r2 = min({td_tinggi, dj_cepat, usia_tua});       // Risiko tinggi
    float r3 = min({td_normal, dj_normal, usia_dewasa});   // Risiko sedang
    float r4 = min({td_tinggi, dj_normal, usia_dewasa});   // Risiko tinggi
    float r5 = min(td_rendah, dj_lambat);                  // Risiko sedang
    float r6 = min(td_rendah, usia_muda);                  // Risiko rendah

    float hasil = 0;
    float total = 0;

    hasil += r1 * 25; total += r1;
    hasil += r2 * 85; total += r2;
    hasil += r3 * 50; total += r3;
    hasil += r4 * 85; total += r4;
    hasil += r5 * 50; total += r5;
    hasil += r6 * 25; total += r6;

    float risiko = (total != 0) ? hasil / total : 0;

    garis();
    cout << fixed << setprecision(2);
    cout << ">> Nilai Risiko Fuzzy: " << risiko << endl;

    if (risiko < 40)
        cout << GREEN << ">> Kategori Risiko   : RENDAH" << RESET << endl;
    else if (risiko < 70)
        cout << YELLOW << ">> Kategori Risiko   : SEDANG" << RESET << endl;
    else
        cout << RED << ">> Kategori Risiko   : TINGGI" << RESET << endl;
    garis();
}

int main() {
    char ulang;
    do {
        run_program();
        cout << "Apakah ingin menginputkan lagi? (y/n): ";
        cin >> ulang;
        cout << endl;
    } while (ulang == 'y' || ulang == 'Y');

    cout << CYAN << "Terima kasih! Tetap jaga kesehatan Anda." << RESET << endl;
    return 0;
}
