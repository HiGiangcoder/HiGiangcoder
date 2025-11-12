#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// lop co so
class NhanVien {
protected:
    string maNV, hoTen, soDienThoai, email;
    int tuoi;
    double luongCoBan;

public:
    NhanVien(string ma = "", string ten = "", int t = 0, string sdt = "", string mail = "", double lcb = 0)
        : maNV(ma), hoTen(ten), tuoi(t), soDienThoai(sdt), email(mail), luongCoBan(lcb) {}

    // khi del con trỏ lớp cơ sở, phương thức ảo này sẽ gọi xuống class con    
    virtual ~NhanVien() {} 

    virtual void Nhap() {
        cout << "Ma NV: "; cin >> maNV;
        cin.ignore();
        cout << "Ho ten: "; getline(cin, hoTen);
        cout << "Tuoi: "; cin >> tuoi;
        cout << "So dien thoai: "; cin >> soDienThoai;
        cout << "Email: "; cin >> email;
        cout << "Luong co ban: "; cin >> luongCoBan;
    }

    virtual void Xuat() const {
        cout << left << setw(10) << maNV
             << setw(20) << hoTen
             << setw(8) << tuoi
             << setw(15) << soDienThoai
             << setw(25) << email
             << setw(15) << fixed << setprecision(0) << luongCoBan;
    }

    // hàm thuần ảo: tức là hàm trống, mục đích chủ yếu để gọi phương thức ở class con
    virtual double TinhLuong() const = 0; 
};

// Lớp con
class LapTrinhVien : public NhanVien {
private:
    int soGioOT;

public:
    LapTrinhVien() : NhanVien(), soGioOT(0) {}

    void Nhap() override {
        NhanVien::Nhap();
        cout << "So gio OT: ";
        cin >> soGioOT;
    }

    void Xuat() const override {
        NhanVien::Xuat();
        cout << setw(10) << soGioOT
             << setw(15) << TinhLuong()
             << " (Lap trinh vien)" << endl;
    }

    double TinhLuong() const override {
        return luongCoBan + soGioOT * 200000;
    }
};

// lớp con
class KiemChungVien : public NhanVien {
private:
    int soLoiPhatHien;

public:
    KiemChungVien() : NhanVien(), soLoiPhatHien(0) {}

    void Nhap() override {
        NhanVien::Nhap();
        cout << "So loi phat hien: ";
        cin >> soLoiPhatHien;
    }

    void Xuat() const override {
        NhanVien::Xuat();
        cout << setw(10) << soLoiPhatHien
             << setw(15) << TinhLuong()
             << " (Kiem chung vien)" << endl;
    }

    double TinhLuong() const override {
        return luongCoBan + soLoiPhatHien * 50000;
    }
};

int main() {
    int n;
    cout << "Nhap so luong nhan vien: ";
    cin >> n;

    NhanVien** ds = new NhanVien*[n]; // mảng con trỏ gốc

    for (int i = 0; i < n; ++i) {
        cout << "\nNhan vien thu " << i + 1 << ":\n";
        cout << "1. Lap trinh vien\n2. Kiem chung vien\nChon loai: ";
        int loai;
        cin >> loai;

        if (loai == 1)
            ds[i] = new LapTrinhVien();
        else
            ds[i] = new KiemChungVien();

        ds[i]->Nhap();
    }

    cout << "\n\n=== DANH SACH NHAN VIEN ===\n";
    cout << left << setw(10) << "MaNV"
         << setw(20) << "Ho ten"
         << setw(8) << "Tuoi"
         << setw(15) << "SDT"
         << setw(25) << "Email"
         << setw(15) << "LuongCB"
         << setw(10) << "Phu thu"
         << setw(15) << "Tong luong"
         << "Loai\n";
    cout << string(120, '-') << endl;

    double tongLuong = 0;
    for (int i = 0; i < n; ++i) {
        ds[i]->Xuat();
        tongLuong += ds[i]->TinhLuong();
    }

    double luongTB = tongLuong / n;
    cout << "\nLuong trung binh: " << fixed << setprecision(0) << luongTB << endl;

    cout << "\n=== NHAN VIEN CO LUONG THAP HON TB ===\n";
    for (int i = 0; i < n; ++i) {
        if (ds[i]->TinhLuong() < luongTB)
            ds[i]->Xuat();
    }

    // Giải phóng bộ nhớ
    for (int i = 0; i < n; ++i) {
        delete ds[i];
    }
    delete[] ds; // phải del từng dữ liệu được n pointer trỏ tới rồi mới xóa mảng pointer

    return 0;
}
