#include <iostream>
#include <string>
using namespace std;

// lớp cơ sở
class NhanVien {
protected:
    string hoTen;
    string ngaySinh;
    double luongCoBan;

public:
    virtual void Nhap() {
        cout << "Nhap ho ten: ";
        getline(cin, hoTen);
        cout << "Nhap ngay sinh: ";
        getline(cin, ngaySinh);
        cout << "Nhap luong co ban: ";
        cin >> luongCoBan;
        cin.ignore();
    }

    virtual void Xuat() const {
        cout << "Ho ten: " << hoTen << "\n";
        cout << "Ngay sinh: " << ngaySinh << "\n";
        cout << "Luong co ban: " << luongCoBan << "\n";
    }

    virtual double TinhLuong() const = 0; 
    string GetHoTen() const { return hoTen; }

    virtual ~NhanVien() {}
};

// lớp con
class NhanVienVanPhong : public NhanVien {
private:
    int soNgayLamViec;
    double troCap;

public:
    void Nhap() override {
        NhanVien::Nhap();
        cout << "Nhap so ngay lam viec: ";
        cin >> soNgayLamViec;
        cout << "Nhap tro cap: ";
        cin >> troCap;
        cin.ignore();
    }

    void Xuat() const override {
        cout << "\n== Nhan vien van phong ==\n";
        NhanVien::Xuat();
        cout << "So ngay lam viec: " << soNgayLamViec << "\n";
        cout << "Tro cap: " << troCap << "\n";
        cout << "Luong: " << TinhLuong() << "\n";
    }

    double TinhLuong() const override {
        return luongCoBan + soNgayLamViec * 200000 + troCap;
    }
};

// lớp con
class NhanVienSanXuat : public NhanVien {
private:
    int soSanPham;

public:
    void Nhap() override {
        NhanVien::Nhap();
        cout << "Nhap so san pham: ";
        cin >> soSanPham;
        cin.ignore();
    }

    void Xuat() const override {
        cout << "\n== Nhan vien san xuat ==\n";
        NhanVien::Xuat();
        cout << "So san pham: " << soSanPham << "\n";
        cout << "Luong: " << TinhLuong() << "\n";
    }

    double TinhLuong() const override {
        return luongCoBan + soSanPham * 2000;
    }
};

// lớp cơ sở
class NhanVienQuanLy : public NhanVien {
private:
    double heSoChucVu;
    double thuong;

public:
    void Nhap() override {
        NhanVien::Nhap();
        cout << "Nhap he so chuc vu: ";
        cin >> heSoChucVu;
        cout << "Nhap thuong: ";
        cin >> thuong;
        cin.ignore();
    }

    void Xuat() const override {
        cout << "\n== Nhan vien quan ly ==\n";
        NhanVien::Xuat();
        cout << "He so chuc vu: " << heSoChucVu << "\n";
        cout << "Thuong: " << thuong << "\n";
        cout << "Luong: " << TinhLuong() << "\n";
    }

    double TinhLuong() const override {
        return luongCoBan * heSoChucVu + thuong;
    }
};

// lớp công ty
class CongTy {
private:
    NhanVien* ds[100];
    int soLuong;

public:
    CongTy() : soLuong(0) {}

    void Nhap() {
        cout << "Nhap so luong nhan vien: ";
        cin >> soLuong;
        cin.ignore();

        for (int i = 0; i < soLuong; i++) {
            cout << "\nChon loai nhan vien (1: VP, 2: SX, 3: QL): ";
            int loai; cin >> loai;
            cin.ignore();

            if (loai == 1) ds[i] = new NhanVienVanPhong();
            else if (loai == 2) ds[i] = new NhanVienSanXuat();
            else ds[i] = new NhanVienQuanLy();

            cout << "\nNhap thong tin nhan vien thu " << i+1 << ":\n";
            ds[i]->Nhap();
        }
    }

    void Xuat() const {
        cout << "\n===== DANH SACH NHAN VIEN =====\n";
        for (int i = 0; i < soLuong; i++) {
            ds[i]->Xuat();
        }
    }

    double TongLuong() const {
        double tong = 0;
        for (int i = 0; i < soLuong; i++) tong += ds[i]->TinhLuong();
        return tong;
    }

    void TimKiemTheoTen(const string& ten) const {
        cout << "\nKet qua tim kiem cho '" << ten << "':\n";
        bool found = false;
        for (int i = 0; i < soLuong; i++) {
            if (ds[i]->GetHoTen() == ten) {
                ds[i]->Xuat();
                found = true;
            }
        }
        if (!found) cout << "Khong tim thay nhan vien!\n";
    }

    ~CongTy() {
        for (int i = 0; i < soLuong; i++) delete ds[i];
    }
};

int main() {
    CongTy cty;
    cty.Nhap();
    cty.Xuat();

    cout << "\nTong luong cong ty: " << cty.TongLuong() << "\n";

    string ten;
    cout << "\nNhap ten nhan vien can tim: ";
    getline(cin, ten);
    cty.TimKiemTheoTen(ten);

    return 0;
}
