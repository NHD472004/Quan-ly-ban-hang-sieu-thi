#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>

using namespace std;


// san pham 
struct SanPham{
	string maSP;
	string tenSP;
	int soLuong;
	long long donGia;
};

struct NodeSP{
	SanPham sanpham;
	NodeSP *next;
	NodeSP *prev;
};

NodeSP* makeNodeSP(SanPham sp){
	NodeSP *newNode = new NodeSP;
    if(newNode == NULL){
        cout << endl << "Khong du bo nho!" << endl << endl;
    }
	newNode->sanpham = sp;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}


// Hoa don
struct HoaDon{
    string maHD;
    string ngayLap;
    long long tongTien = 0;
    SanPham sanpham;
};

struct NodeHD {
    HoaDon hoadon;
    NodeHD* next;
    NodeHD* prev;
};

NodeHD* makeNodeHD(HoaDon hd) {
    NodeHD* newNode = new NodeHD;
    if(newNode == NULL){
        cout << endl << "Khong du bo nho!" << endl << endl;
    }
    newNode->hoadon = hd;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

bool ktMaSP(NodeSP* head, string maSP){
    NodeSP* tmp = head;
    while(tmp != NULL){
        if(tmp->sanpham.maSP == maSP){
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

bool ktMaHD(NodeHD* head, string maHD){
    NodeHD* tmp = head;
    while(tmp != NULL){
        if(tmp->hoadon.maHD == maHD){
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

void chenCuoiSP(NodeSP*& head, SanPham sp){
    NodeSP* newNode = makeNodeSP(sp);
    if(head == NULL){
        head = newNode;
    }
    else{
        NodeSP* tmp = head;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = newNode;
        newNode->prev = tmp;
    }
}

void chenCuoiHD(NodeHD*& head, HoaDon hd){
    NodeHD* newNode = makeNodeHD(hd);
    if(head == NULL){
        head = newNode;
    }
    else{
        NodeHD* tmp = head;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = newNode;
        newNode->prev = tmp;
    }
}

// chuc nang 1: nhap danh sach san pham
void nhapDSSP(NodeSP*& head){
    int n;
    cout << "Nhap so luong san pham: ";
    cin >> n;
    cout << endl;

    for (int i = 0; i < n; ++i) {
        SanPham sp;
        cout << "NHAP THONG TIN CHO SAN PHAM THU " << i + 1 << ":" << endl;
        do{
            cout << "Nhap ma san pham: ";
            cin >> sp.maSP;
            if (ktMaSP(head, sp.maSP)) {
                cout << endl << "MA SAN PHAM NAY DA TON TAI! VUI LONG NHAP LAI!" << endl;
            }
        }
        while(ktMaSP(head, sp.maSP));
        cout << "Nhap ten san pham: ";
        cin.ignore();
        getline(cin, sp.tenSP);
        cout << "Nhap so luong: ";
        cin >> sp.soLuong;
        cout << "Nhap don gia: ";
        cin >> sp.donGia;

        chenCuoiSP(head, sp);
        cout << endl;
    }
    cout << endl << "Nhap danh sach thanh cong!" << endl;
}

// chuc nang 2: in danh sach san pham
void inDSSP(NodeSP* head){
    if(head == NULL){
        cout << endl;
        cout << "Danh sach rong!" << endl << endl;
    }
    else{
        cout << left << setw(15) << "Ma san pham" 
                     << setw(20) << "Ten san pham" 
                     << setw(15) << "So luong" 
                     << setw(15) << "Don gia" << endl;
        while (head != NULL) {
            cout << left << setw(15) << head->sanpham.maSP
                         << setw(20) << head->sanpham.tenSP 
                         << setw(15) << head->sanpham.soLuong 
                         << setw(15) << head->sanpham.donGia << endl;
            head = head->next;
        }
    }
}

// chuc nang 3: nhap danh sach hoa don
void nhapDSHD(NodeHD*& head, NodeSP* dsSanPham){
    int n;
    cout << "Nhap so luong hoa don: ";
    cin >> n;
    cout << endl;

    for(int i = 0; i < n; ++i){
        HoaDon hd;
        cout << "NHAP THONG TIN CHO HOA DON THU " << i + 1 << ":" << endl;
        do{
            cout << "Nhap ma hoa don: ";
            cin >> hd.maHD;
            if (ktMaHD(head, hd.maHD)) {
                cout << endl << "MA HOA DON NAY DA TON TAI! VUI LONG NHAP LAI!" << endl << endl;
            }
        }
        while(ktMaHD(head, hd.maHD));
        cout << "Nhap ngay lap: ";
        cin >> hd.ngayLap;
        cout << "Nhap ma san pham cho hoa don: ";
        cin >> hd.sanpham.maSP;
        while(!ktMaSP(dsSanPham, hd.sanpham.maSP)){
            cout << endl << "MA SAN PHAM NAY KHONG TON TAI TRONG DANH SACH! VUI LONG NHAP LAI!" << endl;
            cout << "Nhap ma san pham cho hoa don: ";
            cin >> hd.sanpham.maSP;
        }
        cout << "Nhap so luong san pham: ";
        cin >> hd.sanpham.soLuong;

        NodeSP* tmpSP = dsSanPham;
        while(tmpSP != NULL && tmpSP->sanpham.maSP != hd.sanpham.maSP){
            tmpSP = tmpSP->next;
        }

        if(tmpSP != NULL){
            hd.tongTien = hd.sanpham.soLuong * tmpSP->sanpham.donGia;
        }
        else{
            cout << "Khong tim thay thong tin san pham cho hoa don. Tinh tong tien khong thanh cong." << endl;
            hd.tongTien = 0;
        }

        chenCuoiHD(head, hd);
        cout << endl;
    }
}

// chuc nang 4: in danh sach hoa don
void inDSHD(NodeHD* head){
    if(head == NULL){
        cout << endl;
        cout << "Danh sach rong!" << endl << endl;
    }
    else{
        cout << left << setw(15) << "Ma hoa don"
                     << setw(15) << "Ngay lap" 
                     << setw(20) << "Ma san pham" 
                     << setw(15) << "So luong" 
                     << setw(15) << "Tong tien" << endl;
        while(head != NULL){
            cout << left << setw(15) << head->hoadon.maHD
                         << setw(15) << head->hoadon.ngayLap 
                         << setw(20) << head->hoadon.sanpham.maSP 
                         << setw(15) << head->hoadon.sanpham.soLuong 
                         << setw(15) << head->hoadon.tongTien << endl;
            head = head->next;
        }
    }
}

// chuc nang 5: doc ghi file san pham
// luu file san pham
void luuFileSanPham(NodeSP* head, const string& tenFile) {
    ofstream outFile(tenFile);
    if(!outFile.is_open()){
        cout << "Khong the mo file de ghi!" << endl;
        return;
    }

    while(head != NULL){
        outFile << head->sanpham.maSP << ",";
        outFile << head->sanpham.tenSP << ",";
        outFile << head->sanpham.soLuong << ",";
        outFile << head->sanpham.donGia << endl;
        head = head->next;
    }

    outFile.close();
    cout << endl << "Luu danh sach san pham vao file thanh cong!" << endl;
}

// doc file san pham 
void docFileSanPham(NodeSP*& head, const string& tenFile) {
    ifstream inFile(tenFile);
    if(!inFile.is_open()){
        cout << "Khong the mo file de doc!" << endl;
        return;
    }

    string line;
    while(getline(inFile, line)){
        istringstream iss(line);
        string maSP, tenSP, soLuong, donGia;

        getline(iss, maSP, ',');
        getline(iss, tenSP, ',');
        getline(iss, soLuong, ',');
        getline(iss, donGia, ',');

        SanPham sp;
        sp.maSP = maSP;
        sp.tenSP = tenSP;
        sp.soLuong = stoi(soLuong);
        sp.donGia = stoll(donGia);
        chenCuoiSP(head, sp);
    }

    inFile.close();
    cout << endl << "Doc danh sach san pham tu file thanh cong!" << endl;
}

// chuc nang 6: doc ghi file hoa don
// luu file hoa don
void luuFileHoaDon(NodeHD* head, const string& tenFile){
    ofstream outFile(tenFile);
    if(!outFile.is_open()){
        cout << "Khong the mo file de ghi!" << endl;
        return;
    }

    while(head != NULL){
        outFile << head->hoadon.maHD << ",";
        outFile << head->hoadon.ngayLap << ",";
        outFile << head->hoadon.sanpham.maSP << ",";
        outFile << head->hoadon.sanpham.soLuong << ",";
        outFile << head->hoadon.tongTien << endl;
        head = head->next;
    }

    outFile.close();
    cout << endl << "Luu danh sach hoa don vao file thanh cong!" << endl;
}

// doc file hoa don
void docFileHoaDon(NodeHD*& head, NodeSP* dsSanPham, const string& tenFile){
    ifstream inFile(tenFile);
    if(!inFile.is_open()){
        cout << "Khong the mo file de doc!" << endl;
        return;
    }

    string line;
    while(getline(inFile, line)){
        istringstream iss(line);
        string maHD, ngayLap, maSP, soLuong, tongTien;

        getline(iss, maHD, ',');
        getline(iss, ngayLap, ',');
        getline(iss, maSP, ',');
        getline(iss, soLuong, ',');
        getline(iss, tongTien, ',');

        try{
            HoaDon hd;
            hd.maHD = maHD;
            hd.ngayLap = ngayLap;
            hd.sanpham.maSP = maSP;
            hd.sanpham.soLuong = stoi(soLuong);
            hd.tongTien = stoll(tongTien);
            chenCuoiHD(head, hd);
        } 
        catch(const invalid_argument& e){
            cerr << "Loi trong qua trinh doc file: " << e.what() << endl;
        }
    }

    inFile.close();
    cout << endl << "Doc danh sach hoa don tu file thanh cong!" << endl;
}

// chuc nang 7: sap xep danh sach giam dan theo don gia san pham
void swapSP(NodeSP* a, NodeSP* b){
    SanPham tmp = a->sanpham;
    a->sanpham = b->sanpham;
    b->sanpham = tmp;
}

void sapXepGiamDanTheoDonGia(NodeSP* head){
    if(head == NULL){
        cout << "Danh sach rong!" << endl;
        return;
    } 
    else{
        NodeSP* i, * j, * minNode;
        for(i = head; i->next != NULL; i = i->next){
            minNode = i;
            for(j = i->next; j != NULL; j = j->next){
                if(j->sanpham.donGia > minNode->sanpham.donGia){
                    minNode = j;
                }
            }
            swapSP(i, minNode);
        }
    }
}

// chuc nang 8: in san pham co don gia cao nhat
void SPCoDonGiaCaoNhat(NodeSP* head){
    if(head == NULL){
        cout << "Danh sach rong!" << endl;
        return;
    }
    NodeSP* tmp = head;
    SanPham spMax = tmp->sanpham; // gia su san pham dau tien co don gia cao nhat
    while(tmp != NULL){
        if(tmp->sanpham.donGia > spMax.donGia){
            spMax = tmp->sanpham;
        }
        tmp = tmp->next;
    }
    cout << left << setw(15) << "Ma san pham" 
                 << setw(20) << "Ten san pham" 
                 << setw(15) << "So luong" 
                 << setw(15) << "Don gia" << endl;
    cout << left << setw(15) << spMax.maSP
                 << setw(20) << spMax.tenSP 
                 << setw(15) << spMax.soLuong 
                 << setw(15) << spMax.donGia << endl;
}

// chuc nang 9: tim kiem san pham theo ma
void timKiemSPTheoMa(NodeSP* head, string maSP){
    if(head == NULL){
        cout << "Danh sach rong!" << endl;
        return;
    }

    NodeSP* tmp = head;
    bool found = false;
    while(tmp != NULL){
        if(tmp->sanpham.maSP == maSP){
            cout << left << setw(15) << "Ma san pham"
                         << setw(20) << "Ten san pham" 
                         << setw(15) << "So luong" 
                         << setw(15) << "Don gia" << endl;
            cout << left << setw(15) << tmp->sanpham.maSP
                         << setw(20) << tmp->sanpham.tenSP 
                         << setw(15) << tmp->sanpham.soLuong 
                         << setw(15) << tmp->sanpham.donGia << endl;
            found = true;
            break;
        }
        tmp = tmp->next;
    }
    if(!found){
        cout << "Khong tim thay san pham nao co ma: " << maSP << endl;
    }
}

// chuc nang 10: in danh sach san pham co gia lon hon x
void SPCoGiaLonHonX(NodeSP* head, long long x){
    if(head == NULL){
        cout << "Danh sach rong!" << endl;
        return;
    }
    NodeSP* tmp = head;
    bool found = false;

    cout << left << setw(15) << "Ma san pham"
                 << setw(20) << "Ten san pham" 
                 << setw(15) << "So luong" 
                 << setw(15) << "Don gia" << endl;
    while(tmp != NULL){
        if(tmp->sanpham.donGia >= x){
            cout << left << setw(15) << tmp->sanpham.maSP
                         << setw(20) << tmp->sanpham.tenSP 
                         << setw(15) << tmp->sanpham.soLuong 
                         << setw(15) << tmp->sanpham.donGia << endl;
            found = true;
        }
        tmp = tmp->next;
    }

    if(!found){
        cout << "Khong co san pham co don gia lon hon " << x << " trong danh sach." << endl;
    }
}

// chuc nang 11: chen san pham vao vi tri x
void chenSauMaSP(NodeSP*& head, string maSP){
    string maSPChen;
    string tenSPChen;
    int soLuongChen;
    long long donGiaChen;

    do{
        cout << "Nhap ma san pham can chen: ";
        cin >> maSPChen;
        if(ktMaSP(head, maSPChen)){
            cout << endl << "MA SAN PHAM DA CO TRONG DANH SACH! VUI LONG NHAP LAI!" << endl;
        }
    }
    while(ktMaSP(head, maSPChen));
    cout << "Nhap ten san pham can chen: ";
    cin.ignore();
    getline(cin, tenSPChen);
    cout << "Nhap so luong san pham can chen: ";
    cin >> soLuongChen;
    cout << "Nhap don gia san pham can chen: ";
    cin >> donGiaChen;
    cout << endl;

    SanPham sp;
    sp.maSP = maSPChen;
    sp.tenSP = tenSPChen;
    sp.soLuong = soLuongChen;
    sp.donGia = donGiaChen;

    if(head == NULL){
        cout << "Danh sach rong!" << endl;
        return;
    }
    NodeSP* tmp = head;
    while(tmp != NULL){
        if(tmp->sanpham.maSP == maSP){
            NodeSP* newNode = makeNodeSP(sp);
            newNode->next = tmp->next;
            newNode->prev = tmp;

            if(tmp->next != NULL){
                tmp->next->prev = newNode;
            }
            tmp->next = newNode;

            cout << endl << "Danh sach sau khi chen" << endl;
            inDSSP(head);
            return;
        }
        tmp = tmp->next;
    }
    cout << "Khong tim thay san pham co ma: " << maSP << " trong danh sach!" << endl;
}

// chuc nang 12: xoa san pham co ma la x (x duoc nhap tu ban phim)
void xoaSPTheoMa(NodeSP*& head, string maSP){
    if(head == NULL){
        cout << "Danh sach rong!" << endl;
        return;
    }

    NodeSP* truoc = head;
    NodeSP* sau = NULL;
    while(truoc != NULL){
        if(truoc->sanpham.maSP == maSP){
            if(sau == NULL){
                head = truoc->next;
            }
            else{
                sau->next = truoc->next;
                if(truoc->next != NULL){
                    truoc->next->prev = sau;
                }
            }
            delete truoc;

            cout << "Danh sach sau khi xoa san pham co ma: " << maSP << endl;
            inDSSP(head);
            return;
        }
        sau = truoc;
        truoc = truoc->next;
    }
    cout << "Khong tim thay san pham trong danh sach!" << endl;
}

// chuc nang 13: sua thong tin san pham co ma la x (x duoc nhap tu ban phim)
void suaTTSP(NodeSP*& head, string maSP){
    if(head == NULL){
        cout << "Danh sach rong!" << endl;
        return;
    }

    NodeSP* tmp = head;
    while(tmp != NULL){
        if(tmp->sanpham.maSP == maSP){
            cout << "Sua thong tin cho san pham co ma: " << maSP << endl;
            cout << "Nhap ten san pham moi: ";
            cin.ignore();
            getline(cin, tmp->sanpham.tenSP);
            cout << "Nhap so luong san pham moi: ";
            cin >> tmp->sanpham.soLuong;
            cout << "Nhap don gia san pham moi: ";
            cin >> tmp->sanpham.donGia;

            cout << endl << "Danh sach san pham sau khi sua thong tin san pham co ma: " << maSP << endl;
            inDSSP(head);
            return;
        }
        tmp = tmp->next;
    }
    cout << "Khong tim thay san pham co ma: " << maSP << endl;
}

// chuc nang 14: in hoa don co nhieu san pham nhat
void inHDCoNhieuSPNhat(NodeHD* head){
     if(head == NULL){
        cout << "Danh sach rong!" << endl;
        return;
    }

    NodeHD* tmp = head;
    NodeHD* hoaDonNhieuSPNhat = NULL;
    int maxSoLuongSP = 0;

    while(tmp != NULL){
        int tongSoLuongSP = tmp->hoadon.sanpham.soLuong;

        NodeHD* tmpSP = tmp->next;
        while(tmpSP != NULL && tmpSP->hoadon.maHD == tmp->hoadon.maHD){
            tongSoLuongSP += tmpSP->hoadon.sanpham.soLuong;
            tmpSP = tmpSP->next;
        }

        if(tongSoLuongSP > maxSoLuongSP){
            maxSoLuongSP = tongSoLuongSP;
            hoaDonNhieuSPNhat = tmp;
        }
        tmp = tmpSP;
    }

    if(hoaDonNhieuSPNhat != NULL){
        cout << left << setw(15) << "Ma hoa don"
                     << setw(15) << "Ngay lap"
                     << setw(20) << "Ma san pham"
                     << setw(15) << "So luong" 
                     << setw(15) << "Tong tien" << endl;
        cout << left << setw(15) << hoaDonNhieuSPNhat->hoadon.maHD 
                     << setw(15) << hoaDonNhieuSPNhat->hoadon.ngayLap 
                     << setw(20) << hoaDonNhieuSPNhat->hoadon.sanpham.maSP 
                     << setw(15) << maxSoLuongSP 
                     << setw(15) << hoaDonNhieuSPNhat->hoadon.tongTien << endl;
    }
    else{
        cout << "Khong tim thay hoa don nao trong danh sach." << endl;
    }
}

// chuc nang 15: tim kiem theo ma hoa don
void timKiemMaHD(NodeHD* head, string maHD){
    if(head == NULL){
        cout << "Danh sach rong!" << endl;
        return;
    }

    NodeHD* tmp = head;
    bool found = false;
    while(tmp != NULL){
        if(tmp->hoadon.maHD == maHD){
            cout << left << setw(15) << "Ma hoa don"
                         << setw(15) << "Ngay lap" 
                         << setw(20) << "Ma san pham" 
                         << setw(15) << "So luong" 
                         << setw(15) << "Tong tien" << endl;
            cout << left << setw(15) << tmp->hoadon.maHD
                         << setw(15) << tmp->hoadon.ngayLap 
                         << setw(20) << tmp->hoadon.sanpham.maSP 
                         << setw(15) << tmp->hoadon.sanpham.soLuong 
                         << setw(15) << tmp->hoadon.tongTien << endl;
            found = true;
            break;
        }
        tmp = tmp->next;
    }
    if(!found){
        cout << "Khong tim thay hoa don nao co ma: " << maHD << endl;
    }
}

// chuc nang 16: chen hoa don vao sau ma hoa don duoc nhap tu ban phim
void chenSauMaHD(NodeHD*& head, NodeSP* dsSanPham, string maHD){
    string maHDChen;
    string ngayLapChen;
    long long tongTienChen = 0;
    SanPham sp;

    if(head == NULL){
        cout << "Danh sach rong!" << endl;
        return;
    }

    do{
        cout << "Nhap ma hoa don: ";
        cin >> maHDChen;
        if(ktMaHD(head, maHDChen)){
            cout << endl << "MA HOA DON NAY DA TON TAI! VUI LONG NHAP LAI!" << endl << endl;
        }
    }
    while(ktMaHD(head, maHDChen));
    cout << "Nhap ngay lap: ";
    cin >> ngayLapChen;
    cout << "Nhap ma san pham cho hoa don: ";
    cin >> sp.maSP;
    while(!ktMaSP(dsSanPham, sp.maSP)){
        cout << endl << "MA SAN PHAM NAY KHONG TON TAI TRONG DANH SACH! VUI LONG NHAP LAI!" << endl << endl;
        cout << "Nhap ma san pham cho hoa don: ";
        cin >> sp.maSP;
    }
    cout << "Nhap so luong san pham: ";
    cin >> sp.soLuong;

    NodeSP* tmpSP = dsSanPham;
    while(tmpSP != NULL && tmpSP->sanpham.maSP != sp.maSP){
        tmpSP = tmpSP->next;
    }

    if(tmpSP != NULL){
        tongTienChen = sp.soLuong * tmpSP->sanpham.donGia;
    }
    else{
        cout << "Khong tim thay thong tin san pham cho hoa don. Tinh tong tien khong thanh cong." << endl;
        tongTienChen = 0;
    }

    HoaDon hd;
    hd.maHD = maHDChen;
    hd.ngayLap = ngayLapChen;
    hd.sanpham.maSP = sp.maSP;
    hd.sanpham.soLuong = sp.soLuong;
    hd.tongTien = tongTienChen;

    NodeHD* tmp = head;
    while(tmp != NULL){
        if(tmp->hoadon.maHD == maHD){
            NodeHD* newNode = makeNodeHD(hd);
            newNode->next = tmp->next;
            newNode->prev = tmp;

            if(tmp->next != NULL){
                tmp->next->prev = newNode;
            }
            tmp->next = newNode;

            cout << endl << "Danh sach hoa don sau khi chen vao sau hoa don co ma: " << maHD << endl;
            inDSHD(head);
            return;
        }
        tmp = tmp->next;
    }
    cout << "Khong tim thay hoa don co ma: " << maHD << " trong danh sach!" << endl;
}

// chuc nang 17: xoa hoa don co ma la x (x duoc nhap tu ban phim)
void xoaHDTheoMa(NodeHD*& head, string maHD){
    if(head == NULL){
        cout << "Danh sach rong!" << endl;
        return;
    }

    NodeHD* truoc = head;
    NodeHD* sau = NULL;
    while(truoc != NULL){
        if(truoc->hoadon.maHD == maHD){
            if(sau == NULL){
                head = truoc->next;
            }
            else{
                sau->next = truoc->next;
                if(truoc->next != NULL){
                    truoc->next->prev = sau;
                }
            }
            delete truoc;

            cout << endl << "Danh sach hoa don sau khi xoa hoa don co ma: " << maHD << endl;
            inDSHD(head);
            return;
        }
        sau = truoc;
        truoc = truoc->next;
    }
    cout << "Khong tim thay hoa don trong danh sach!" << endl;
}

// chuc nang 18: sua thong tin theo ma hoa don
void suaTTHD(NodeHD*& head, NodeSP* dsSanPham, string maHD){
    if(head == NULL){
        cout << "Danh sach rong!" << endl;
        return;
    }

    NodeHD* tmp = head;
    while(tmp != NULL){
        if(tmp->hoadon.maHD == maHD){
            cout << "Sua thong tin cho hoa don co ma: " << maHD << endl;
            cout << "Nhap ngay lap moi: ";
            cin >> tmp->hoadon.ngayLap;
            cout << "Nhap ma san pham moi cho hoa don: ";
            cin >> tmp->hoadon.sanpham.maSP;
            while(!ktMaSP(dsSanPham, tmp->hoadon.sanpham.maSP)){
                cout << endl << "MA SAN PHAM NAY KHONG TON TAI TRONG DANH SACH! Vui long nhap lai." << endl << endl;
                cout << "Nhap ma san pham moi cho hoa don: ";
                cin >> tmp->hoadon.sanpham.maSP;
            }
            cout << "Nhap so luong moi: ";
            cin >> tmp->hoadon.sanpham.soLuong;

            NodeSP* tmpSP = dsSanPham;
            while(tmpSP != NULL && tmpSP->sanpham.maSP != tmp->hoadon.sanpham.maSP){
                tmpSP = tmpSP->next;
            }

            if(tmpSP != NULL){
                tmp->hoadon.tongTien = tmp->hoadon.sanpham.soLuong * tmpSP->sanpham.donGia;
            }
            else{
                cout << "Khong tim thay thong tin san pham cho hoa don. Tinh tong tien khong thanh cong." << endl;
                tmp->hoadon.tongTien = 0;
            }

            cout << endl << "Danh sach hoa don sau khi sua hoa don co ma: " << maHD << endl;
            inDSHD(head);
            return;
        }
        tmp = tmp->next;
    }
    cout << "Khong tim thay hoa don nao co ma: " << maHD << endl;
}

// chuc nang 19: thong ke tong doanh thu tu tat ca hoa don
long long tinhTongDoanhThu(NodeHD* head){
    long long tongDoanhThu = 0;
    NodeHD* tmp = head;
    while (tmp != NULL) {
        tongDoanhThu += tmp->hoadon.tongTien;
        tmp = tmp->next;
    }
    return tongDoanhThu;
}

void thongKeTongDoanhThu(NodeHD* head){
    long long tongDoanhThu = tinhTongDoanhThu(head);
    cout << "Tong doanh thu tu tat ca cac hoa don: " << tongDoanhThu << " VND" << endl;
}

// chuc nang 20: thong ke tong luong san pham ton kho
int tinhTongTonKho(NodeSP* head) {
    int tongTonKho = 0;
    NodeSP* tmp = head;
    while(tmp != NULL){
        tongTonKho += tmp->sanpham.soLuong;
        tmp = tmp->next;
    }
    return tongTonKho;
}

void thongKeTonKho(NodeSP* head){
    int tongTonKho = tinhTongTonKho(head);
    cout << "Tong so luong san pham ton kho: " << tongTonKho << endl;
}


// tao menu chinh
void mainMenuTable(){
    cout << "============================================MENU============================================" << endl;
    cout << "|| 1. Nhap danh sach san pham                                                             ||" << endl;
    cout << "|| 2. Hien danh sach san pham                                                             ||" << endl;
    cout << "|| 3. Nhap danh sach hoa don                                                              ||" << endl;
    cout << "|| 4. Hien danh sach hoa don                                                              ||" << endl;
    cout << "|| 5. Doc luu file san pham                                                               ||" << endl;
    cout << "|| 6. Doc luu file hoa don                                                                ||" << endl;
    cout << "|| 7. Sap xep danh sach giam dan theo don gia                                             ||" << endl;
    cout << "|| 8. In ra thong tin san pham co don gia cao nhat                                        ||" << endl;
    cout << "|| 9. Tim kiem san pham theo ma san pham                                                  ||" << endl;
    cout << "|| 10. In danh sach san pham co don gia lon hon hoac bang don gia duoc nhap tu ban phim   ||" << endl;
    cout << "|| 11. Chen san pham vao sau ma san pham duoc nhap tu ban phim                            ||" << endl;
    cout << "|| 12. Xoa san pham co ma duoc nhap tu ban phim                                           ||" << endl;
    cout << "|| 13. Sua thong tin san pham co ma duoc nhap tu ban phim                                 ||" << endl;
    cout << "|| 14. In hoa don co nhieu san pham nhat                                                  ||" << endl;
    cout << "|| 15. Tim kiem hoa don theo ma hoa don                                                   ||" << endl;
    cout << "|| 16. Chen hoa don vao sau ma hoa don duoc nhap tu ban phim                              ||" << endl;
    cout << "|| 17. Xoa hoa don co ma duoc nhap tu ban phim                                            ||" << endl;
    cout << "|| 18. Sua thong tin hoa don co ma hoa don duoc nhap tu ban phim                          ||" << endl;
    cout << "|| 19. Thong ke tong doanh thu tu tat ca cac hoa don                                      ||" << endl;
    cout << "|| 20. Thong ke tong so luong san pham ton kho                                            ||" << endl;
    cout << "|| 0. Thoat chuong trinh                                                                  ||" << endl;
    cout << "============================================================================================" << endl;
}

// tao menu doc luu file san pham
void subMenuSP(){
    cout << "======================MENU======================" << endl;
    cout << "|| 1. Luu file san pham                       ||" << endl;
    cout << "|| 2. Doc file san pham                       ||" << endl;
    cout << "|| 0. Tro ve menu chinh                       ||" << endl;
    cout << "================================================" << endl;
}

// tao menu doc luu file hoa don
void subMenuHD(){
    cout << "======================MENU======================" << endl;
    cout << "|| 1. Luu file hoa don                        ||" << endl;
    cout << "|| 2. Doc file hoa don                        ||" << endl;
    cout << "|| 0. Tro ve menu chinh                       ||" << endl;
    cout << "================================================" << endl;
}

// xoa bo nho dem sau khi su dung chuong trinh
void xoaBoNho(NodeSP*& dsSanPham, NodeHD*& dsHoaDon){
    while(dsSanPham != NULL){
        NodeSP* tmp = dsSanPham;
        dsSanPham = dsSanPham->next;
        delete tmp;
    }

    while(dsHoaDon != NULL){
        NodeHD* tmp = dsHoaDon;
        dsHoaDon = dsHoaDon->next;
        delete tmp;
    }
}


int main(){
    NodeSP* dsSanPham = NULL;
    NodeHD* dsHoaDon = NULL;
    int luaChon;
    
    while(true){
        mainMenuTable();
        cout << endl;
        cout << "Nhap lua chon: ";
        cin >> luaChon;

        switch(luaChon){
            case 1:
                nhapDSSP(dsSanPham);
                cout << "Nhap danh sach thanh cong!" << endl;
                break;
            case 2:
                inDSSP(dsSanPham);
                cout << endl;
                break;
            case 3:
                nhapDSHD(dsHoaDon, dsSanPham);
                cout << "Nhap danh sach thanh cong!" << endl;
                break;
            case 4:
                inDSHD(dsHoaDon);
                cout << endl;
                break;
            case 5: {
                cout << endl;
                int subSP;
                subMenuSP();
                cout << endl;
                cout << "Nhap lua chon: ";
                cin >> subSP;
                switch(subSP){
                    case 1:
                        luuFileSanPham(dsSanPham, "SanPham.txt");
                        break;
                    case 2:
                        docFileSanPham(dsSanPham, "SanPham.txt");
                        break;
                    case 0:
                        break;
                }
                cout << endl;
                break;
            }
            case 6: {
                cout << endl;
                int subHD;
                subMenuHD();
                cout << endl;
                cout << "Nhap lua chon: ";
                cin >> subHD;
                switch(subHD){
                    case 1:
                        luuFileHoaDon(dsHoaDon, "HoaDon.txt");
                        break;
                    case 2:
                        docFileHoaDon(dsHoaDon, dsSanPham, "HoaDon.txt");
                        break;
                    case 0:
                        break;
                }
                cout << endl;
                break;
            }
            case 7:
                sapXepGiamDanTheoDonGia(dsSanPham);
                inDSSP(dsSanPham);
                cout << endl;
                break;
            case 8:
                SPCoDonGiaCaoNhat(dsSanPham);
                cout << endl;
                break;
            case 9:{
                string maSP;
                cout << "Nhap ma san pham: ";
                cin >> maSP;
                cout << endl;

                timKiemSPTheoMa(dsSanPham, maSP);
                cout << endl;
                break;
            }
            case 10:{
                long long donGia;
                cout << "Nhap don gia: ";
                cin >> donGia;
                cout << endl;

                SPCoGiaLonHonX(dsSanPham, donGia);
                cout << endl;
                break;
            }
            case 11:{
                string maSP;
                cout << "Nhap ma san pham: ";
                cin >> maSP;
                cout << endl;

                chenSauMaSP(dsSanPham, maSP);
                cout << endl;
                break;
            }
            case 12:{
                string maSP;
                cout << "Nhap ma san pham: ";
                cin >> maSP;
                cout << endl;

                xoaSPTheoMa(dsSanPham, maSP);
                cout << endl;
                break;
            }
            case 13:{
                string maSP;
                cout << "Nhap ma san pham: ";
                cin >> maSP;
                cout << endl;

                suaTTSP(dsSanPham, maSP);
                cout << endl;
                break;
            }
            case 14:
                inHDCoNhieuSPNhat(dsHoaDon);
                cout << endl;
                break;
            case 15:{
                string maHD;
                cout << "Nhap ma hoa don: ";
                cin >> maHD;
                cout << endl;

                timKiemMaHD(dsHoaDon, maHD);
                cout << endl;
                break;
            }
            case 16:{
                string maHD;
                cout << "Nhap ma hoa don: ";
                cin >> maHD;
                cout << endl;

                chenSauMaHD(dsHoaDon, dsSanPham, maHD);
                break;
            }
            case 17:{
                string maHD;
                cout << "Nhap ma hoa don: ";
                cin >> maHD;
                cout << endl;

                xoaHDTheoMa(dsHoaDon, maHD);
                cout << endl;
                break;
            }
            case 18:{
                string maHD;
                cout << "Nhap ma hoa don: ";
                cin >> maHD;
                cout << endl;

                suaTTHD(dsHoaDon, dsSanPham, maHD);
                cout << endl;
                break;
            }
            case 19:
                cout << endl;
                thongKeTongDoanhThu(dsHoaDon);
                cout << endl;
                break;
            case 20:
                cout << endl;
                thongKeTonKho(dsSanPham);
                cout << endl;
                break;
            case 0:
                return 0;
            default:
                cout << endl << "LUA CHON KHONG HOP LE! VUI LONG NHAP LAI!" << endl;
        }
    }
    
    xoaBoNho(dsSanPham, dsHoaDon);
    return 0;
}

