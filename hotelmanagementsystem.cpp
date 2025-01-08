#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <locale>
#include <codecvt>

using namespace std;

// *Lop Room*
class Room {
private:
    int roomNumber;
    wstring roomType;
    wstring roomStatus;
    wstring guestName;
    wstring guestPhone;
    wstring guestEmail;
    wstring checkInDate;
    wstring checkOutDate;
    int guestCount;
    double paymentAmount;
    wstring paymentMethod;
    
    wstring guestDOB;
    wstring guestNationality;
    wstring guestGender;
    wstring guestID;

    wstring creditCardNumber;
    bool depositStatus;

    wstring loyaltyCardNumber;
    wstring loyaltyLevel;
    wstring history;
    wstring preferences;

public:
    Room(int number, const wstring& type)
        : roomNumber(number), roomType(type), roomStatus(L"Available"), guestName(L""), guestPhone(L""), guestEmail(L""), checkInDate(L""), checkOutDate(L""), guestCount(0), paymentAmount(0.0), paymentMethod(L""), guestDOB(L""), guestNationality(L""), guestGender(L""), guestID(L""), creditCardNumber(L""), depositStatus(false), loyaltyCardNumber(L""), loyaltyLevel(L""), history(L""), preferences(L"") {}

    int getRoomNumber() const { return roomNumber; }
    wstring getRoomType() const { return roomType; }
    wstring getRoomStatus() const { return roomStatus; }
    void setRoomStatus(const wstring& status) { roomStatus = status; }

    void bookRoom(const wstring& guest, const wstring& phone, const wstring& email, const wstring& dob, const wstring& nationality, const wstring& gender, const wstring& id, const wstring& checkIn, const wstring& checkOut, int guests, double payment, const wstring& method, const wstring& creditCard, bool deposit, const wstring& loyaltyCard, const wstring& loyaltyLevel, const wstring& history, const wstring& preferences) {
        if (roomStatus == L"Available") {
            roomStatus = L"Booked";
            guestName = guest;
            guestPhone = phone;
            guestEmail = email;
            guestDOB = dob;
            guestNationality = nationality;
            guestGender = gender;
            guestID = id;
            checkInDate = checkIn;
            checkOutDate = checkOut;
            guestCount = guests;
            paymentAmount = payment;
            paymentMethod = method;
            creditCardNumber = creditCard;
            depositStatus = deposit;
            loyaltyCardNumber = loyaltyCard;
            this->loyaltyLevel = loyaltyLevel;
            this->history = history;
            this->preferences = preferences;
            wcout << L"Phong " << roomNumber << L" da duoc dat boi " << guestName << L".\n";
        } else {
            wcout << L"Phong " << roomNumber << L" hien khong co san.\n";
        }
    }

    void cancelBooking() {
        if (roomStatus == L"Booked") {
            roomStatus = L"Available";
            guestName = L"";
            guestPhone = L"";
            guestEmail = L"";
            checkInDate = L"";
            checkOutDate = L"";
            guestCount = 0;
            paymentAmount = 0.0;
            paymentMethod = L"";
            creditCardNumber = L"";
            depositStatus = false;
            loyaltyCardNumber = L"";
            loyaltyLevel = L"";
            history = L"";
            preferences = L"";
            wcout << L"Phong " << roomNumber << L" da huy dat thanh cong.\n";
        } else {
            wcout << L"Phong " << roomNumber << L" chua duoc dat.\n";
        }
    }
};

class Hotel {
private:
    vector<Room> rooms;

public:
    Hotel(const vector<pair<int, wstring>>& roomList) {
        for (const auto& roomInfo : roomList) {
            rooms.emplace_back(roomInfo.first, roomInfo.second);
        }
    }

    void viewRooms() const {
        wcout << L"\n--- Danh sach phong ---\n";
        for (const auto& room : rooms) {
            wcout << L"Phong " << room.getRoomNumber() << L" - " << room.getRoomType() << L" - Trang thai: " << room.getRoomStatus() << L"\n";
        }
    }

    void bookRoom(int roomNumber, const wstring& guestName, const wstring& guestPhone, const wstring& guestEmail, const wstring& dob, const wstring& nationality, const wstring& gender, const wstring& id, const wstring& checkInDate, const wstring& checkOutDate, int guestCount, double payment, const wstring& paymentMethod, const wstring& creditCard, bool deposit, const wstring& loyaltyCard, const wstring& loyaltyLevel, const wstring& history, const wstring& preferences) {
        for (auto& room : rooms) {
            if (room.getRoomNumber() == roomNumber) {
                room.bookRoom(guestName, guestPhone, guestEmail, dob, nationality, gender, id, checkInDate, checkOutDate, guestCount, payment, paymentMethod, creditCard, deposit, loyaltyCard, loyaltyLevel, history, preferences);
                return;
            }
        }
        wcout << L"Khong tim thay phong so " << roomNumber << L".\n";
    }

    void cancelBooking(int roomNumber) {
        for (auto& room : rooms) {
            if (room.getRoomNumber() == roomNumber) {
                room.cancelBooking();
                return;
            }
        }
        wcout << L"Khong tim thay phong so " << roomNumber << L".\n";
    }
};

int main() {
    vector<pair<int, wstring>> roomList = {
        {101, L"Single"}, {102, L"Double"}, {201, L"Suite"}, {202, L"Double"}, {301, L"Single"}
    };

    Hotel myHotel(roomList);

    int choice;
    do {
        wcout << L"\n--- Quan ly khach san ---\n";
        wcout << L"1. Xem danh sach phong\n";
        wcout << L"2. Dat phong\n";
        wcout << L"3. Huy dat phong\n";
        wcout << L"4. Thoat\n";
        wcout << L"Nhap lua chon: ";
        wcin >> choice;

        switch (choice) {
            case 1:
                myHotel.viewRooms();
                break;
            case 2: {
                int roomNumber, guestCount;
                wstring guestName, guestPhone, guestEmail, checkInDate, checkOutDate, paymentMethod, dob, nationality, gender, id, creditCard, loyaltyCard, loyaltyLevel, history, preferences;
                bool deposit;
                double payment;

                wcout << L"Nhap so phong muon dat: ";
                wcin >> roomNumber;
                wcin.ignore();
                wcout << L"Nhap ten khach hang: ";
                getline(wcin, guestName);
                wcout << L"Nhap so dien thoai khach hang: ";
                getline(wcin, guestPhone);
                wcout << L"Nhap email khach hang: ";
                getline(wcin, guestEmail);
                wcout << L"Nhap ngay sinh (yyyy-mm-dd): ";
                getline(wcin, dob);
                wcout << L"Nhap quoc tich: ";
                getline(wcin, nationality);
                wcout << L"Nhap gioi tinh: ";
                getline(wcin, gender);
                wcout << L"Nhap so can cuoc/ho chieu: ";
                getline(wcin, id);
                wcout << L"Nhap ngay nhan phong (yyyy-mm-dd): ";
                getline(wcin, checkInDate);
                wcout << L"Nhap ngay tra phong (yyyy-mm-dd): ";
                getline(wcin, checkOutDate);
                wcout << L"Nhap so luong khach: ";
                wcin >> guestCount;
                wcout << L"Nhap so tien thanh toan: ";
                wcin >> payment;
                wcin.ignore();
                wcout << L"Nhap phuong thuc thanh toan: ";
                getline(wcin, paymentMethod);
                wcout << L"Nhap so the tin dung: ";
                getline(wcin, creditCard);

                wstring depositInput;
                wcout << L"Nhap trang thai dat coc (1: Dat coc, 0: Khong): ";
                getline(wcin, depositInput);

                if (depositInput == L"1") {
                    deposit = true;
                } else if (depositInput == L"0") {
                    deposit = false;
                } else {
                    wcout << L"Gia tri khong hop le! Mac dinh la 'Khong dat coc'.\n";
                    deposit = false;
                }

                wcout << L"Nhap so the khach hang than thiet: ";
                getline(wcin, loyaltyCard);
                wcout << L"Nhap hang khach hang (Silver, Gold, Platinum): ";
                getline(wcin, loyaltyLevel);
                wcout << L"Nhap lich su luu tru: ";
                getline(wcin, history);
                wcout << L"Nhap so thich: ";
                getline(wcin, preferences);

                myHotel.bookRoom(roomNumber, guestName, guestPhone, guestEmail, dob, nationality, gender, id, checkInDate, checkOutDate, guestCount, payment, paymentMethod, creditCard, deposit, loyaltyCard, loyaltyLevel, history, preferences);
                break;
            }
            case 3: {
                int roomNumber;
                wcout << L"Nhap so phong muon huy: ";
                wcin >> roomNumber;
                myHotel.cancelBooking(roomNumber);
                break;
            }
            case 4:
                wcout << L"Chuong trinh ket thuc. Cam on ban da su dung he thong!\n";
                break;
            default:
                wcout << L"Lua chon khong hop le. Vui long thu lai!\n";
        }
    } while (choice != 4);

    return 0;
}
