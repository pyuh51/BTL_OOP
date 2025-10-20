#include <iostream>
#include <vector>
#include <string>
#include <iomanip> 
#include <cstdlib> 
#include <fstream>
#include <sstream>
using namespace std;
const int IGNORE_BUFFER_SIZE = 1000;

class QuanAo;
class Ao;
class Quan;
class Bo;
void docDuLieu(vector<QuanAo*>& danhSachSanPham);
void ghiDuLieu(const vector<QuanAo*>& danhSachSanPham);

// LỚP CHA: QUANAO

class QuanAo {
protected:
    int makeLoai;
    string brand;
    string size;
    string color;
    string material;
    string style;
    string origin;
    long long int number;
    double price;

public:
    QuanAo() {
        this->makeLoai = 0;
        this->number = 0;
        this->price = 0.0;
    }

    // Hàm nhập thông tin
    virtual void nhap() {
        cout << "\n--- NHAP THONG TIN SAN PHAM ---" << endl;
        
        cout << "Nhap brand (thuong hieu): ";
        getline(cin, brand);
        cout << "Nhap size (S, M, L, XL...): ";
        getline(cin, size);
        cout << "Nhap color (mau sac): ";
        getline(cin, color);
        cout << "Nhap material (chat lieu): ";
        getline(cin, material);
        cout << "Nhap style (kieu dang): ";
        getline(cin, style);
        cout << "Nhap origin (xuat xu): ";
        getline(cin, origin);
        
        cout << "Nhap number (so luong): ";
        while (!(cin >> number)) {
            cout << "Loi: Vui long nhap mot so. Thu lai: ";
            cin.clear();
            cin.ignore(IGNORE_BUFFER_SIZE, '\n'); 
        }
        cout << "Nhap price (gia tien): ";
        while (!(cin >> price)) {
            cout << "Loi: Vui long nhap mot so. Thu lai: ";
            cin.clear();
            cin.ignore(IGNORE_BUFFER_SIZE, '\n');
        }
        cin.ignore(IGNORE_BUFFER_SIZE, '\n'); // Xóa bộ đệm sau nhập số
    }

    virtual void inDayDu() const {
       ios::fmtflags f = cout.flags();
       streamsize prec = cout.precision();

       cout << left << setw(10) << getLoai()
           << left << setw(15) << brand
           << left << setw(8) << size
           << left << setw(15) << color
           << left << setw(20) << material
           << left << setw(15) << style
           << left << setw(15) << origin
           << left << setw(12) << number;

       cout << left << setw(15) << fixed << setprecision(0) << price << endl;

       // Restore stream state
       cout.flags(f);
       cout.precision(prec);
    }

    virtual void inToiGian() const {
       // Save stream state so fixed/precision do not leak
       ios::fmtflags f = cout.flags();
       streamsize prec = cout.precision();

       cout << left << setw(15) << brand
           << left << setw(8) << size
           << left << setw(15) << color
           << left << setw(20) << material
           << left << setw(15) << style
           << left << setw(15) << origin
           << left << setw(12) << number;

       cout << left << setw(15) << fixed << setprecision(0) << price << endl;

       // Restore stream state
       cout.flags(f);
       cout.precision(prec);
    }

    // Hàm ảo thuần túy quan trọng để phân loại
    virtual string getLoai() const = 0;
    string getBrand() const { return brand; }
    string getMaterial() const { return material; }
    string getSize() const { return size; }
    string getOrigin() const { return origin; }

    void banHang(int soLuongBan) {
        if (soLuongBan > 0 && soLuongBan <= this->number) {
            this->number -= soLuongBan;
            cout << "\n==> Ban thanh cong " << soLuongBan << " san pham. So luong con lai: " << this->number << endl;
        } else {
            cout << "\n==> So luong ban khong hop le hoac khong du hang! (Con lai: " << this->number << ")" << endl;
        }
    }

    friend void docDuLieu(vector<QuanAo*>& danhSachSanPham);
    friend void ghiDuLieu(const vector<QuanAo*>& danhSachSanPham);
    
    virtual ~QuanAo() {}
};

//
// HÀM TIỆN ÍCH IN TIÊU ĐỀ
// 
void inTieuDeDayDu() {
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << left << setw(10) << "LOAI"
          << left << setw(15) << "BRAND"
          << left << setw(8) << "SIZE"
          << left << setw(15) << "COLOR"
          << left << setw(20) << "MATERIAL"
          << left << setw(15) << "STYLE"
          << left << setw(15) << "ORIGIN"
          << left << setw(12) << "NUMBER"
          << left << setw(15) << "PRICE (VND)" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
}

void inTieuDeToiGian() {
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
    cout << left << setw(15) << "BRAND"
          << left << setw(8) << "SIZE"
          << left << setw(15) << "COLOR"
          << left << setw(20) << "MATERIAL"
          << left << setw(15) << "STYLE"
          << left << setw(15) << "ORIGIN"
          << left << setw(12) << "NUMBER"
          << left << setw(15) << "PRICE (VND)" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------" << endl;
}

// CÁC LỚP CON //

class Ao : public QuanAo {
public:
    Ao(){
        this->makeLoai = 1;
    }
    string getLoai() const override { return "Ao"; }
};

class Quan : public QuanAo {
public:
    Quan(){
        this->makeLoai = 2;
    }
    string getLoai() const override { return "Quan"; }
};

class Bo : public QuanAo {
public:
    Bo(){
        this->makeLoai = 3;
    }
    string getLoai() const override { return "Bo"; }
};

void hienThiTheoLoai(const vector<QuanAo*>& ds, const string& loaiCanHienThi) {
    cout << "\n*** DANH SACH SAN PHAM LOAI " << loaiCanHienThi << " ***" << endl;
    inTieuDeToiGian();
    bool found = false;
    for (const auto& sp : ds) {
        // So sánh bằng hàm ảo getLoai() để đảm bảo tính Polymorphism
        if (sp->getLoai() == loaiCanHienThi) {
            sp->inToiGian();
            found = true;
        }
    }
    if (!found) {
        cout << "==> Khong co san pham loai " << loaiCanHienThi << " trong kho." << endl;
    }
}

void nhapThongTinSanPham(vector<QuanAo*>& ds) {
    int choice;
    do {
        cout << "\n--- MENU NHAP THONG TIN ---" << endl;
        cout << "1.1. Nhap thong tin Ao" << endl;
        cout << "1.2. Nhap thong tin Quan" << endl;
        cout << "1.3. Nhap thong tin Bo" << endl;
        cout << "0. Quay lai menu chinh" << endl;
        cout << "Lua chon cua ban: ";
        
        while (!(cin >> choice)) {
            cout << "Loi: Vui long nhap mot so. Thu lai: ";
            cin.clear();
            cin.ignore(IGNORE_BUFFER_SIZE, '\n');
        }
        cin.ignore(IGNORE_BUFFER_SIZE, '\n');

        QuanAo* spMoi = nullptr;

        switch (choice) {
            case 1: spMoi = new Ao(); break;
            case 2: spMoi = new Quan(); break;
            case 3: spMoi = new Bo(); break; 
            case 0: cout << "Quay lai menu chinh..." << endl; return;
            default: cout << "Lua chon khong hop le." << endl; continue;
        }

        spMoi->nhap();
        ds.push_back(spMoi);
        cout << "\n==> Da them san pham moi thanh cong!" << endl;

    } while (true);
}

void hienThiThongTin(const vector<QuanAo*>& ds) {
    if (ds.empty()) {
        cout << "\nChua co san pham nao trong kho!" << endl;
        return;
    }

    int choice;
    do {
        cout << "\n--- MENU HIEN THI THONG TIN ---" << endl;
        cout << "2.1. Hien thi chi tiet (3 bang rieng, KHONG cot LOAI)" << endl;
        cout << "2.2. Hien thi theo brand (Toi gian)" << endl;
        cout << "2.3. Hien thi theo chat lieu (Toi gian)" << endl;
        cout << "0. Quay lai menu chinh" << endl;
        cout << "Lua chon cua ban: ";
        
        while (!(cin >> choice)) {
            cout << "Loi: Vui long nhap mot so. Thu lai: ";
            cin.clear();
            cin.ignore(IGNORE_BUFFER_SIZE, '\n');
        }
        cin.ignore(IGNORE_BUFFER_SIZE, '\n');

        switch (choice) {
            case 1: { 
                hienThiTheoLoai(ds, "Ao");
                hienThiTheoLoai(ds, "Quan");
                hienThiTheoLoai(ds, "Bo");
                break;
            }
            case 2: { 
                string brandCanTim;
                cout << "Nhap brand can hien thi: ";
                getline(cin, brandCanTim);
                cout << "\n*** DANH SACH SAN PHAM THEO BRAND: " << brandCanTim << " (TOI GIAN) ***" << endl;
                
                inTieuDeToiGian();
                bool found = false;
                for (const auto& sp : ds) {
                    if (sp->getBrand() == brandCanTim) {
                        sp->inToiGian();
                        found = true;
                    }
                }
                if (!found) {
                    cout << "Khong tim thay san pham nao voi brand nay." << endl;
                }
                break;
            }
            case 3: { 
                string materialCanTim;
                cout << "Nhap chat lieu can hien thi: ";
                getline(cin, materialCanTim);
                cout << "\n*** DANH SACH SAN PHAM THEO CHAT LIEU: " << materialCanTim << " (TOI GIAN) ***" << endl;
                
                inTieuDeToiGian();
                bool found = false;
                for (const auto& sp : ds) {
                    if (sp->getMaterial() == materialCanTim) {
                        sp->inToiGian();
                        found = true;
                    }
                }
                if (!found) {
                    cout << "Khong tim thay san pham nao voi chat lieu nay." << endl;
                }
                break;
            }
            case 0:
                cout << "Quay lai menu chinh..." << endl;
                break;
            default:
                cout << "Lua chon khong hop le. Vui long chon lai." << endl;
                break;
        }
    } while (choice != 0);
}

// 3. Bán hàng và cập nhật
void banVaCapNhat(vector<QuanAo*>& ds) {
    if (ds.empty()) {
        cout << "\nChua co san pham nao trong kho!" << endl;
        return;
    }

    cout << "\n--- DANH SACH SAN PHAM DE BAN ---" << endl;
    cout << left << setw(4) << "STT" << "| ";
    cout << left << setw(15) << "BRAND"
         << left << setw(8) << "SIZE"
         << left << setw(15) << "COLOR"
         << left << setw(20) << "MATERIAL"
         << left << setw(15) << "STYLE"
         << left << setw(15) << "ORIGIN"
         << left << setw(12) << "NUMBER"
         << left << setw(15) << "PRICE (VND)" << endl;

    for (size_t i = 0; i < ds.size(); ++i) {
        cout << left << setw(4) << (i + 1) << "| ";
        ds[i]->inToiGian();
    }
    
    int stt;
    cout << "\nChon STT san pham can ban (nhap 0 de huy): ";
    while (!(cin >> stt)) {
        cout << "Loi: Vui long nhap mot so. Thu lai: ";
        cin.clear();
        cin.ignore(IGNORE_BUFFER_SIZE, '\n');
    }
    
    if (stt <= 0 || stt > ds.size()) {
        cout << "Huy thao tac." << endl;
        return;
    }

    int soLuongBan;
    cout << "Nhap so luong can ban: ";
    while (!(cin >> soLuongBan)) {
        cout << "Loi: Vui long nhap mot so. Thu lai: ";
        cin.clear();
        cin.ignore(IGNORE_BUFFER_SIZE, '\n');
    }
    cin.ignore(IGNORE_BUFFER_SIZE, '\n');

    ds[stt-1]->banHang(soLuongBan);
}

// 4. Tìm kiếm (Giữ nguyên)
void timKiem(const vector<QuanAo*>& ds) {
    if (ds.empty()) {
        cout << "\nChua co san pham nao trong kho!" << endl;
        return;
    }

    int choice;
    do {
        cout << "\n--- MENU TIM KIEM ---" << endl;
        cout << "4.1. Tim kiem theo co (size)" << endl;
        cout << "4.2. Tim kiem theo chat lieu" << endl;
        cout << "4.3. Tim kiem theo hang (brand)" << endl;
        cout << "4.4. Tim kiem theo xuat xu" << endl;
        cout << "0. Quay lai menu chinh" << endl;
        cout << "Lua chon cua ban: ";
        
        while (!(cin >> choice)) {
            cout << "Loi: Vui long nhap mot so. Thu lai: ";
            cin.clear();
            cin.ignore(IGNORE_BUFFER_SIZE, '\n');
        }
        cin.ignore(IGNORE_BUFFER_SIZE, '\n');
        
        string keyword;
        bool found = false;

        switch (choice) {
            case 1: {
                cout << "Nhap size can tim: ";
                getline(cin, keyword);
                cout << "\n--- KET QUA TIM KIEM THEO SIZE: " << keyword << " ---" << endl;
                inTieuDeToiGian(); 
                for (const auto& sp : ds) {
                    if (sp->getSize() == keyword) {
                        sp->inToiGian();
                        found = true;
                    }
                }
                break;
            }
            case 2: {
                cout << "Nhap chat lieu can tim: ";
                getline(cin, keyword);
                cout << "\n--- KET QUA TIM KIEM THEO CHAT LIEU: " << keyword << " ---" << endl;
                inTieuDeToiGian();
                for (const auto& sp : ds) {
                    if (sp->getMaterial() == keyword) {
                        sp->inToiGian();
                        found = true;
                    }
                }
                break;
            }
            case 3: {
                cout << "Nhap brand can tim: ";
                getline(cin, keyword);
                cout << "\n--- KET QUA TIM KIEM THEO BRAND: " << keyword << " ---" << endl;
                inTieuDeToiGian();
                for (const auto& sp : ds) {
                    if (sp->getBrand() == keyword) {
                        sp->inToiGian();
                        found = true;
                    }
                }
                break;
            }
            case 4: {
                cout << "Nhap xuat xu can tim: ";
                getline(cin, keyword);
                cout << "\n--- KET QUA TIM KIEM THEO XUAT XU: " << keyword << " ---" << endl;
                inTieuDeToiGian();
                for (const auto& sp : ds) {
                    if (sp->getOrigin() == keyword) {
                        sp->inToiGian();
                        found = true;
                    }
                }
                break;
            }
            case 0:
                cout << "Quay lai menu chinh..." << endl;
                return;
            default:
                cout << "Lua chon khong hop le." << endl;
                continue;
        }

        if (!found) {
            cout << "Khong tim thay san pham nao phu hop." << endl;
        }

    } while (true);
}

void docDuLieu(vector<QuanAo*>& danhSachSanPham)
{
    fstream file("dssanpham.txt", ios::in);
    if(!file)
    {
        cerr << "Khong tim thay file dssanpham.txt de doc du lieu!" << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string Loai;
        string number;
        string price;
        QuanAo* sp = nullptr;
        getline(ss, Loai, ',');
        if(Loai == "1") sp = new Ao();
        else if(Loai == "2") sp = new Quan();
        else if(Loai == "3") sp = new Bo();
        getline(ss, sp->brand, ',');
        getline(ss, sp->size, ',');
        getline(ss, sp->color, ',');
        getline(ss, sp->material, ',');
        getline(ss, sp->style, ',');
        getline(ss, sp->origin, ',');
        getline(ss, number, ',');
        sp->number = stoll(number);
        getline(ss, price);
        sp->price = stod(price);
        danhSachSanPham.push_back(sp);
    }

    file.close();
}

void ghiDuLieu(const vector<QuanAo*>& danhSachSanPham)
{
    fstream file("dssanpham.txt", ios::out | ios::trunc);

    for (const auto& sp : danhSachSanPham) {
        file << sp->makeLoai << ","
             << sp->brand << ","
             << sp->size << ","
             << sp->color << ","
             << sp->material << ","
             << sp->style << ","
             << sp->origin << ","
             << sp->number << ","
             << sp->price << endl;
    }

    file.close();
}

void giaiPhongBoNho(vector<QuanAo*>& ds) {
    for (auto& sp : ds) {
        delete sp;
    }
    ds.clear();
}


int main() {
    //system("chcp 65001"); 
    cout << "\n\n";       
    
    vector<QuanAo*> danhSachSanPham;
    docDuLieu(danhSachSanPham);
    int luaChon;

    do {
        cout << "\n\n**************************************************" << endl;
        cout << "* CHUONG TRINH QUAN LY SHOP QUAN AO              *" << endl;
        cout << "**************************************************" << endl;
        cout << "* 1. Nhap thong tin san pham                     *" << endl;
        cout << "* 2. Hien thi thong tin san pham                 *" << endl;
        cout << "* 3. Ban hang va cap nhat so luong               *" << endl;
        cout << "* 4. Tim kiem san pham                           *" << endl;
        cout << "* 5. Thoat chuong trinh                          *" << endl;
        cout << "**************************************************" << endl;
        cout << "Nhap lua chon cua ban: ";
        
        while (!(cin >> luaChon)) {
            cout << "Loi: Vui long nhap mot so. Thu lai: ";
            cin.clear(); 
            cin.ignore(IGNORE_BUFFER_SIZE, '\n'); 
        }
        cin.ignore(IGNORE_BUFFER_SIZE, '\n'); 

        switch (luaChon) {
            case 1: nhapThongTinSanPham(danhSachSanPham); break;
            case 2: hienThiThongTin(danhSachSanPham); break;
            case 3: banVaCapNhat(danhSachSanPham); break;
            case 4: timKiem(danhSachSanPham); break;
            case 5: cout << "\nDang thoat chuong trinh..." << endl; break;
            default: cout << "\nLua chon khong hop le. Vui long chon lai." << endl; break;
        }
        
        if (luaChon != 5) {
            cout << "\nNhan Enter de tiep tuc...";
            cin.get();
        }

    } while (luaChon != 5);
    
    ghiDuLieu(danhSachSanPham);
    giaiPhongBoNho(danhSachSanPham);

    cout << "Da giai phong bo nho. Cam on da su dung chuong trinh!" << endl;

    return 0;
}