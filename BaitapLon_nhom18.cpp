#include <iostream>
#include <string>
using namespace std;

// Dinh nghia lop SinhVien
class SinhVien {
public:
    string maSoSinhVien;
    string hoTen;
    string lop;
    float diemTrungBinh;
    string gioiTinh; 
    SinhVien* next;

    SinhVien() : next(NULL) {
        maSoSinhVien = "";
        hoTen = "";
        lop = "";
        diemTrungBinh = 0.0;
        gioiTinh = "";  
    }

    // Phuong thuc nhap thong tin sinh vien
    void nhapThongTin() {
        cout << "Nhap ma so sinh vien: ";
        getline(cin, maSoSinhVien);
        cout << "Nhap ho va ten: ";
        getline(cin, hoTen);
        cout << "Nhap lop: ";
        getline(cin, lop);
        
        do {
            cout << "Nhap gioi tinh (Nam/Nu): ";
            getline(cin, gioiTinh);
            if (gioiTinh != "Nam" && gioiTinh != "Nu") {
                cout << "Gioi tinh khong hop le. Vui long nhap lai.\n";
            }
        } while (gioiTinh != "Nam" && gioiTinh != "Nu");
        
       do {
            cout << "Nhap diem trung binh (0 - 10): ";
            cin >> diemTrungBinh;
            if (diemTrungBinh < 0 || diemTrungBinh > 10) {
                cout << "Diem khong hop le. Vui long nhap lai.\n";
            }
        } while (diemTrungBinh < 0 || diemTrungBinh > 10);
        cin.ignore(); // Bo qua ky tu '\n' con sot lai trong bo dem
    }

    // Phuong thuc xuat thong tin sinh vien
    void xuatThongTin() const {
        cout << "Ma so sinh vien: " << maSoSinhVien << " | "
             << "Ho va ten: " << hoTen << " | "
             << "Lop: " << lop << " | "
             << "Diem trung binh: " << diemTrungBinh << " | "
             << "Gioi tinh: " << gioiTinh << " | "
             << "Hoc luc: " << phanLoaiHocLuc() << endl;
    }

    // Phuong thuc phan loai hoc luc theo diem trung binh
    string phanLoaiHocLuc() const {
        if (diemTrungBinh >= 8.0) {
            return "Gioi";
        } else if (diemTrungBinh >= 6.5) {
            return "Kha";
        } else if (diemTrungBinh >= 3.5) {
            return "Trung binh";
        } else {
            return "Yeu";
        }
    }
};

// Dinh nghia lop DanhSachSinhVien de quan ly danh sach sinh vien
class DanhSachSinhVien {
private:
    SinhVien* head; // Con tro toi dau danh sach

public:
    // Ham khoi tao
    DanhSachSinhVien() : head(NULL) {}

    // Ham them sinh vien vao dau danh sach
    void themDau() {
        SinhVien* sv = new SinhVien();
        sv->nhapThongTin();
        sv->next = head;
        head = sv;
    }

    // Ham them sinh vien vao cuoi danh sach
    void themCuoi() {
        SinhVien* sv = new SinhVien();
        sv->nhapThongTin();
        if (head == NULL) {
            head = sv;
        } else {
            SinhVien* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = sv;
        }
    }

    // Ham xoa sinh vien o dau danh sach
    void xoaDau() {
        if (head == NULL) {
            cout << "Danh sach trong, khong the xoa." << endl;
            return;
        }
        SinhVien* temp = head;
        head = head->next;
        delete temp;
        cout << "Da xoa sinh vien o dau danh sach." << endl;
    }

    // Ham xoa sinh vien o cuoi danh sach
    void xoaCuoi() {
        if (head == NULL) {
            cout << "Danh sach trong, khong the xoa." << endl;
            return;
        }
        if (head->next == NULL) {
            delete head;
            head = NULL;
            cout << "Da xoa sinh vien o cuoi danh sach." << endl;
            return;
        }
        SinhVien* temp = head;
        while (temp->next->next != NULL) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = NULL;
        cout << "Da xoa sinh vien o cuoi danh sach." << endl;
    }

    // Ham sap xep danh sach sinh vien theo ma so sinh vien tang dan
    void sapXepTangDan() {
        if (head == NULL || head->next == NULL) return;  

        SinhVien* i = head;
        while (i != NULL) {  
            SinhVien* j = i->next;
            while (j != NULL) {  
              if (i->maSoSinhVien > j->maSoSinhVien) {  
                swap(i->maSoSinhVien, j->maSoSinhVien);
                swap(i->hoTen, j->hoTen);
                swap(i->lop, j->lop);
                swap(i->diemTrungBinh, j->diemTrungBinh);
                swap(i->gioiTinh, j->gioiTinh);
            }
            j = j->next;  
        }
        i = i->next;  
    }
}


    // Ham sap xep danh sach sinh vien theo diem trung binh giam dan
    void sapXepGiamDanTheoDiemTB() {
        if (head == NULL || head->next == NULL) return;

        SinhVien* i = head;
        while (i != NULL) {
            SinhVien* j = i->next;
            while (j != NULL) {
                if (i->diemTrungBinh < j->diemTrungBinh) {
                    // Hoan doi du lieu giua hai sinh vien
                    swap(i->maSoSinhVien, j->maSoSinhVien);
                    swap(i->hoTen, j->hoTen);
                    swap(i->lop, j->lop);
                    swap(i->diemTrungBinh, j->diemTrungBinh);
                }
                j = j->next;
            }
            i = i->next;
        }
    }

    // Ham hien thi danh sach sinh vien theo hoc luc
    void hienThiDanhSachTheoHocLuc() const {
    SinhVien* temp = head;
    bool found = false;
    cout << "\nDanh sach sinh vien theo hoc luc:\n";

    cout << "Hoc luc Gioi: \n";
    while (temp != NULL) {
        if (temp->phanLoaiHocLuc() == "Gioi") {
            temp->xuatThongTin();
            found = true;
        }
        temp = temp->next;
    }
    if (!found) cout << "Khong co sinh vien hoc luc Gioi.\n";

    temp = head;
    found = false;
    cout << "Hoc luc Kha: \n";
    while (temp != NULL) {
        if (temp->phanLoaiHocLuc() == "Kha") {
            temp->xuatThongTin();
            found = true;
        }
        temp = temp->next;
    }
    if (!found) cout << "Khong co sinh vien hoc luc Kha.\n";

    temp = head;
    found = false;
    cout << "Hoc luc Trung binh: \n";
    while (temp != NULL) {
        if (temp->phanLoaiHocLuc() == "Trung binh") {
            temp->xuatThongTin();
            found = true;
        }
        temp = temp->next;
    }
    if (!found) cout << "Khong co sinh vien hoc luc Trung binh.\n";

    temp = head;
    found = false;
    cout << "Hoc luc Yeu: \n";
    while (temp != NULL) {
        if (temp->phanLoaiHocLuc() == "Yeu") {
            temp->xuatThongTin();
            found = true;
        }
        temp = temp->next;
    }
    if (!found) cout << "Khong co sinh vien hoc luc Yeu.\n";
}


    // Ham hien thi danh sach sinh vien
    void hienThiDanhSach() const {
    SinhVien* temp = head;
    if (temp == NULL) {
        cout << "Danh sach sinh vien trong.\n";
        return;
    }
    while (temp != NULL) {
        temp->xuatThongTin();  
        temp = temp->next;
    }
}


    // Ham tim kiem sinh vien theo ma so
    void timKiemTheoMaSo(const string& maSo) const {
        SinhVien* temp = head;
        while (temp != NULL) {
            if (temp->maSoSinhVien == maSo) {
                temp->xuatThongTin();
                return;
            }
            temp = temp->next;
        }
        cout << "Khong tim thay sinh vien voi ma so: " << maSo << endl;
    }

    // Ham tim kiem sinh vien theo ten
    void timKiemTheoTen(const string& ten) const {
        SinhVien* temp = head;
        while (temp != NULL) {
            if (temp->hoTen == ten) {
                temp->xuatThongTin();
                return;
            }
            temp = temp->next;
        }
        cout << "Khong tim thay sinh vien voi ten: " << ten << endl;
    }

    // Ham xoa toan bo danh sach sinh vien
    void xoaDanhSach() {
        SinhVien* temp;
        while (head != NULL) {
            temp = head;
            head = head->next;
            delete temp;
        }
        cout << "Da xoa toan bo danh sach sinh vien." << endl;
    }

    // Ham hieu chinh sinh vien theo ma so
    void suaSinhVien(const string& maSo) {
        SinhVien* temp = head;
        while (temp != NULL) {
            if (temp->maSoSinhVien == maSo) {
                cout << "Nhap lai thong tin cho sinh vien " << maSo << ":\n";
                temp->nhapThongTin();
                return;
            }
            temp = temp->next;
        }
        cout << "Khong tim thay sinh vien voi ma so: " << maSo << endl;
    }
};

// Menu cho nguoi dùng
int main() {
    DanhSachSinhVien danhSach;
    int luaChon;
    do {
        cout << "\n----- MENU -----\n";
        cout << "1. Them sinh vien vao dau danh sach\n";
        cout << "2. Them sinh vien vao cuoi danh sach\n";
        cout << "3. Xoa sinh vien o dau danh sach\n";
        cout << "4. Xoa sinh vien o cuoi danh sach\n";
        cout << "5. Sap xep danh sach theo ma so sinh vien\n";
        cout << "6. Sap xep danh sach theo diem trung binh\n";
        cout << "7. Hien thi danh sach sinh vien theo hoc luc\n";
        cout << "8. Hien thi danh sach sinh vien\n";
        cout << "9. Tim kiem sinh vien theo ma so\n";
        cout << "10. Tim kiem sinh vien theo ten\n";
        cout << "11. Xoa toan bo danh sach\n";
        cout << "12. Sua thong tin sinh vien\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> luaChon;
        cin.ignore(); // Bo qua ky tu '\n' con sot lai trong bo dem

        switch (luaChon) {
            case 1:
                danhSach.themDau();
                break;
            case 2:
                danhSach.themCuoi();
                break;
            case 3:
                danhSach.xoaDau();
                break;
            case 4:
                danhSach.xoaCuoi();
                break;
            case 5:
                danhSach.sapXepTangDan();
                break;
            case 6:
                danhSach.sapXepGiamDanTheoDiemTB();
                break;
            case 7:
                danhSach.hienThiDanhSachTheoHocLuc();
                break;
            case 8:
            	cout <<"Danh sach sinh vien:\n";
                danhSach.hienThiDanhSach();
                break;
            case 9: {
                string maSo;
                cout << "Nhap ma so sinh vien can tim: ";
                getline(cin, maSo);
                danhSach.timKiemTheoMaSo(maSo);
                break;
            }
            case 10: {
                string ten;
                cout << "Nhap ten sinh vien can tim: ";
                getline(cin, ten);
                danhSach.timKiemTheoTen(ten);
                break;
            }
            case 11:
                danhSach.xoaDanhSach();
                break;
            case 12: {
                string maSo;
                cout << "Nhap ma so sinh vien can sua: ";
                getline(cin, maSo);
                danhSach.suaSinhVien(maSo);
                break;
            }
            case 0:
                cout << "Thoat chuong trinh." << endl;
                break;
            default:
                cout << "Lua chon khong hop le. Vui long chon lai.\n";
        }
    } while (luaChon != 0);

    return 0;
}

