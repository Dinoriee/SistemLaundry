#include <iostream>
#include <string>

using namespace std;

#define MAX_QUEUE 10

struct QUEUE {
    int top;
    int head;
    int tail;
    string nama[MAX_QUEUE];
    char vip[MAX_QUEUE];
    int berat[MAX_QUEUE];

    QUEUE() {
        head = 0;
        tail = -1;
    }
};

int total(QUEUE &cek, int berat, char vip) {
    int hargaReg = 5000;
    int hargaVip = 8000;

    if (berat > 0) {
        if (vip == 'Y' || vip == 'y') {
            return hargaVip + total(cek, berat - 1, vip);
        } else {
            return hargaReg + total(cek, berat - 1, vip);
        }
    } else {
        return 0;
    }
}


bool enqueue(QUEUE &cek, string nama, char vip, int berat) {
    if (cek.tail == MAX_QUEUE - 1) {
        return false;
    }

    if(vip == 'Y' || vip == 'y'){
        int pos = cek.tail + 1;
        for(int i = cek.head; i <= cek.tail; i++){
            if(cek.vip[i] == 'N' || cek.vip[i] == 'n'){
                pos = i;
                break;
            }
        }

        for (int i = cek.tail; i >= pos; i--) {
            cek.nama[i + 1] = cek.nama[i];
            cek.vip[i + 1] = cek.vip[i];
            cek.berat[i + 1] = cek.berat[i];
        }
        cek.nama[pos] = nama;
        cek.vip[pos] = vip;
        cek.berat[pos] = berat;
        cek.tail++;
    }
    else {
        cek.nama[++cek.tail] = nama;
        cek.vip[cek.tail] = vip;
        cek.berat[cek.tail] = berat;
    }
    return true;
}

string dequeue(QUEUE &cek, int &biaya, int &berat) {
    if (cek.tail == -1) {
        return "";
    }
    else {
        string nama = cek.nama[cek.head];
        char vip = cek.vip[cek.head];
        berat = cek.berat[cek.head];

        biaya = total(cek, berat, vip);

        for (int i = cek.head; i < cek.tail; ++i) {
            cek.nama[i] = cek.nama[i + 1];
            cek.vip[i] = cek.vip[i + 1];
            cek.berat[i] = cek.berat[i + 1];
        }

        --cek.tail;
        return nama;
    }
}


string peek(const QUEUE &cek) {
    if (cek.tail == -1) {
        return "";
    }
    return cek.nama[cek.head];
}

bool isEmpty(const QUEUE &cek) {
     if(cek.tail == -1){
        return 1;
     }
     else{
        return 0;
     }
}

bool isFull(const QUEUE &cek) {
     if(cek.tail == MAX_QUEUE-1){
        return 1;
     }
     else{
        return 0;
     }
}

void clear(QUEUE &cek){
    cek.head = 0;
    cek.tail = -1;
}

int main() {
    QUEUE laundry;
    int pilihan, berat, biaya;
    string nama;
    char vip;

    do{
        cout << "=== Sistem Laundry ===" << endl;
        cout << "1. Tambah Pelanggan" << endl;
        cout << "2. Proses Laundry (Dequeue)" << endl;
        cout << "3. Hapus semua orderan" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilih opsi: ";
        cin >> pilihan;
        cout << endl;

        switch(pilihan){
        case 1:{
            if(isFull(laundry) == 1){
                cout << "Antrian sudah penuh" << endl;
            }
            else {
                cout << "Masukkan nama pelanggan: "; cin >> nama; cout << endl;
                cout << "Apakah pelanggan menggunakan jasa VIP: (y/n): "; cin >> vip; cout << endl;
                cout << "Berapa berat cucian " << nama << ": "; cin >> berat; cout << endl;
                if(enqueue(laundry, nama, vip, berat)){
                    cout << "Customer " << nama << " berhasil ditambahkan" << endl;
                }
                else{
                    cout << "Customer gagal ditambahakan";
                }
            }

            break;
        }
        case 2 : {
            if(isEmpty(laundry) == 1){
                cout << "Tidak terdapat antrian!" << endl << endl;
            }
            else{
                string custName = dequeue(laundry, biaya, berat);
                cout << "Customer atas nama " << custName << " dengan cucian seberat " << berat << " Kg telah diproses"<< endl;
                cout << "Biaya total laundry: " << biaya << ".Rp" << endl << endl;
                break;
            }

        }
        case 3 : {
            clear(laundry);
            cout << "Seluruh pesanan berhasil dihapus" << endl;
            break;
        }
        case 4:{
            cout << "Keluar dari program" << endl;
            break;
        }
        default :{
            cout << "Masukkan input yang valid!" << endl;
            break;
        }
    }
} while (pilihan != 4);
return 0;
}
