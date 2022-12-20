#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <conio.h>
#include <io.h>
#include <iomanip>
#include <string.h>
#include <cstdlib>
#include "dateTime.h"

using namespace std;

int id;
int number;

class CLIENT;
void taoID(); //bo o dau ham main la duoc
void layID(); //bo o cuoi ham main 
void moTaiKhoan(); //Yeu cau nhap thong tin roi luu thong tin vao file
CLIENT* getListClient();//Lay du lieu trong file va tra ve mang du lieu
void saveListClient(CLIENT* client);//luu du lieu vao file
void showListClient(CLIENT* client);
bool confirmMessage (); 
int ConfirmPin(char a[]);
void inSodu(long long a);
int randomNum();
void signUp (CLIENT& p);
// void createTransation(CLIENT &a, long long cu);

// -----------------  Lich su giao dich  --------------------------------

void saveTransaction (char* x, char* path);	//Luu lich su giao dich, (char* x): lich su giao dich can luu, (char* path): duong dan file

void exportTransaction (CLIENT& a);		//In lich su giao dich, (char* path): duong dan file  

// -----------------  End Lich su giao dich  ----------------------------

class CLIENT {
public:
  int idd;
  int maSoThe;
  char hoTen[256];
  char diaChi[256];
  char soDienThoai[256];
  char cccd[256];
  long long soDuTaiKhoan;
  char taiKhoan[256];
  char matKhau[256];
  char email[256];
  char ngaySinh[256];
  char PIN[256];
public:
};

CLIENT* client;



void moTaiKhoan() {
  id++; 
  number++;
  taoID();
  
  CLIENT a;
  signUp (a);
  
  fstream f("text1.txt" , ios::binary|ios::out|ios::app);
  if(!f) cout << "error occured when open file to write!";
  f.write(reinterpret_cast<char *>(&a), sizeof(a));
  f.close();
  client = getListClient();
}
void xuatTT(CLIENT& p){
  cout<<"                 THONG TIN TAI KHOAN                  " << endl;
  cout<<"+------------------------------------------------------+" << endl; 
  cout<<"|  So tai khoan: "<< setw(36) << p.maSoThe       << "  |" << endl; 
  cout<<"|  Ten dang nhap: "<< setw(35) << p.taiKhoan     << "  |" << endl;
  cout<<"|  Ho va ten: " << setw(39) <<p.hoTen            << "  |" << endl;
  cout<<"|  So dien thoai: "<< setw(35) << p.soDienThoai  << "  |" << endl;
  cout<<"|  So can cuoc cong dan: "<< setw(28) << p.cccd  << "  |" << endl;
  cout<<"|  Dia chi: " << setw(41) << p.diaChi            << "  |" << endl;
  cout<<"|  Ngay sinh: " << setw(39) << p.ngaySinh        << "  |" << endl; 
  cout<<"|  Email: " << setw(43) << p.email               << "  |" << endl;
  cout<<"+------------------------------------------------------+" << endl; 
  
} 

void xuatSodu(CLIENT& a){
  cout << "+-----------------------------------------------------------------+" << endl;
  cout << "| SO TAI KHOAN   | TEN TAI KHOAN              | SO DU HIEN TAI    |" << endl;
  cout << "|-----------------------------------------------------------------|" << endl;
  cout << "| " << setw(14) << left <<a.maSoThe << " | " << setw(26) << left << a.hoTen <<" | "; inSodu(a.soDuTaiKhoan);
  cout << "+-----------------------------------------------------------------+" << endl;
}

void chuyenkhoan(CLIENT& a){
  xuatSodu(a);
  char bank[256],nd[256];
  int stk=0,s;
  long long tien;
  cout << "  Vui long chon hinh thuc chuyen tien:"<<endl;
  cout << "  [1].Chuyen noi bo."<<endl;
  cout << "  [2].Chuyen lien ngan hang."<<endl;
  cout << "  [0].Thoat giao dich."<<endl;
  cout << "  Nhap lua chon: ";
  cin >> s;
  switch (s)
  {
  case 1:
  {
    system("cls");
    int kh=0;
    do
    {
      CK:
      cout<<"  Nhap so tai khoan ma ban muon chuyen toi: "; 
      cin >> stk;
      int i=1;
      for (i = 1; i<= number; i++)
        if (stk == client[i].maSoThe){
          if(stk!=a.maSoThe){
          kh = i;
          cout<<"  Ten nguoi thu huong: "<<client[i].hoTen<<endl;
          do
        {
          cout<<"  Nhap so tien muon chuyen: "; cin >>tien;
          if(tien>a.soDuTaiKhoan) {
          	cout<<"  So du khong du de chuyen, vui long nhap so du nho hon "; inSodu(a.soDuTaiKhoan); 
		    } 
        } while (tien>a.soDuTaiKhoan);

		    fflush (stdin);
        cout<<"  Nhap noi dung chuyen khoan: "; cin.getline(nd,256);
        if(strcmp(nd,"")==0)sprintf(nd," %s chuyen tien",a.hoTen );
        int q=3;
        do{
          int check=ConfirmPin(a.PIN);
          if(!check){
            q--;
            cout<<"  Ma pin sai! Vui long nhap lai! Con "<<q<<" lan nhap!"<<endl;
            if(q==0){
              cout<<"Da nhap sai qua 3 lan! Vui long thuc hien lai giao dich moi!"<<endl;
               return;
            }
          }
          else break;
         }while(1);

        if (confirmMessage()) {
        if(a.soDuTaiKhoan-tien<=50000){
          cout<<"  Yeu cau so du duy tri tai khoan toi thieu 50.000 VND, quy khach vui long nap them tien vao tai khoan de thuc hien giao dich!"<<endl;
        }
        else{
        long long cu= a.soDuTaiKhoan;
        a.soDuTaiKhoan-=tien;
        client[kh].soDuTaiKhoan += tien;
        
        cout<<"  Giao dich thanh cong! So du hien tai cua quy khach la: "; inSodu(a.soDuTaiKhoan);
        char x[256],y[256];
        dateTime d;
        sprintf(x," TK: %d \n GD: -%d %d/%d/%d %d:%d \n Hinh thuc: Chuyen Khoan \n ND: %s \n Ma GD: %d\n_",a.maSoThe,tien,d.getDay(),d.getMon(),d.getYear(),d.getHour(),d.getMin(),nd,randomNum());
        char path1[256],path2[256];
        sprintf(path1,"./LSGD/%d-%s.txt",a.idd,a.hoTen);
        saveTransaction(x,path1);
        sprintf(y," TK: %d \n GD: +%d %d/%d/%d %d:%d \n Hinh thuc: Chuyen Khoan \n ND: %s \n Ma GD: %d\n_",client[kh].maSoThe,tien,d.getDay(),d.getMon(),d.getYear(),d.getHour(),d.getMin(),nd,randomNum());
        sprintf(path2,"./LSGD/%d-%s.txt",client[kh].idd,client[kh].hoTen);
        saveTransaction(y,path2);
        saveListClient(client);
        client = getListClient();
        cout<<"------------------------------------\nThong bao bien dong so du: ";
        cout<<x;
        }
        }

    }
    else{ 
      cout<<"Khong the chuyen cho chinh ban! Vui long nhap STK khac!"<<endl;
      goto CK;
    }
    }
    else 
      if(i == number+1){
      	cout<<"  Khong tim thay khach hang co so tai khoan: "<<stk<< "\n" <<"  Vui long nhap lai!"<<endl;
      	stk = 0;
	  } 

    }while (stk == 0);
  }
break;
  
  case 2:
  {
    fflush(stdin);
     system("cls");
    cout<<"Chon ngan hang ban muon chuyen den:"<<endl;
    int choose=0;
    struct bank
    {
      char name[256];
    };
    bank listbank[8]={"","Agribank","Mb Bank","Tien Phong","VP Bank","ACB","Nam A Bank","Sacombank"};
      cout<<"1. Ngan hang AgriBank"<<endl;
      cout<<"2. Ngan hang Mb bank"<<endl;
      cout<<"3. Ngan hang Tien Phong"<<endl;
      cout<<"4. Ngan hang VP Bank"<<endl;
      cout<<"5. Ngan hang ACB"<<endl;
      cout<<"6. Ngan hang Nam A Bank"<<endl;
      cout<<"7. Ngan hang SacomBank"<<endl;
      cout<<"0. Khong co ngan hang ban ban tim"<<endl;
      cout<<"Nhap lua chon cua ban: ";
      cin>>choose;
    
    if(choose==0){
      cout<<"Nhap ngan hang chuyen den: "<<endl;
      cin.getline(listbank[0].name,256);
    } 
    fflush(stdin);
    cout<<"  Nhap so tai khoan ma ban muon chuyen toi: "; 
    cin >> stk;
    do
    {
      cout<<"  Nhap so tien muon chuyen: "; cin >>tien;
      if(tien>a.soDuTaiKhoan) cout<<"  So du khong du de chuyen, vui long nhap so du nho hon "<<a.soDuTaiKhoan<<endl;
    } while (tien>a.soDuTaiKhoan);
    fflush(stdin);
    cout<<"  Nhap noi dung chuyen khoan: "; cin.getline(nd,256);
    if(strcmp(nd,"")==0)sprintf(nd," %s chuyen tien",a.hoTen );
    int q=3;
        do{
          int check=ConfirmPin(a.PIN);
          if(!check){
            q--;
            cout<<"  Ma pin sai! Vui long nhap lai! Con "<<q<<" lan nhap!"<<endl;
            if(q==0){
              cout<<"Da nhap sai qua 3 lan! Vui long thuc hien lai giao dich moi!"<<endl;
               return;
            }
          }
          else break;
         }while(1);
    if (confirmMessage()) {
      if(a.soDuTaiKhoan<=50000){
        cout<<"  So du quy khach nho hon 50K, vui long nap them tien vao tai khoan de thuc hien giao dich!"<<endl;
      }
      else{
      a.soDuTaiKhoan=a.soDuTaiKhoan-tien-0.02*tien;
      system("cls");
      cout<<"  Giao dich thanh cong! So du hien tai cua quy khach la: "; inSodu(a.soDuTaiKhoan);
      cout<<" (Da tru 2% phi giao dich)"<<endl;
      char x[256];
      dateTime d;
      sprintf(x," TK: %d \n GD: -%d %d/%d/%d %d:%d \n Hinh thuc: Chuyen khoan den STK: %d thuoc ngan hang %s \n ND: %s \n Ma GD: %d\n_",a.maSoThe,tien,d.getDay(),d.getMon(),d.getYear(),d.getHour(),d.getMin(),stk,listbank[choose].name,nd,randomNum());
      char path[256];
      sprintf(path,"./LSGD/%d-%s.txt",a.idd,a.hoTen);
      saveTransaction(x,path);
      saveListClient(client);
      client = getListClient();
      cout<<"------------------------------------\nThong bao bien dong so du: "<<endl;
      cout<<x;
      }
    } 
    break;
  }
    case 0: return;
  }
  
}

void napTien(CLIENT& a){
  xuatSodu( a);
  long long tien;
  cout<<"  Nhap so tien muon nap: "; cin>>tien;
  if (confirmMessage() ) {
  	a.soDuTaiKhoan+=tien;
  	cout<<"\n  Ban da nap thanh cong! So du hien tai la: "; inSodu(a.soDuTaiKhoan);
  	cout << "\n  ";
    char x[256];
    dateTime d;
    sprintf(x," TK: %d \n GD: +%d %d/%d/%d %d:%d \n Hinh thuc: Nap Tien \n ND: Nap tien vao tai khoan \n Ma GD: %d\n_",a.maSoThe,tien,d.getDay(),d.getMon(),d.getYear(),d.getHour(),d.getMin(),randomNum());
    char path[256];
    sprintf(path,"./LSGD/%d-%s.txt",a.idd,a.hoTen);
    saveTransaction(x,path);
  	saveListClient(client);
  	client = getListClient();
    cout<<"------------------------------------\nThong bao bien dong so du: ";
    cout<<x;
  }	else {
  	return;
  }
  
}

void rutTien(CLIENT& a){
  xuatSodu( a);
  int sl=3;
  long long tien;
  do
  {
    cout<<"  Nhap so tien muon rut: "; cin >>tien;
    if(tien>a.soDuTaiKhoan){
       cout<<"  So du khong du de rut, vui long nhap so du nho hon "; inSodu(a.soDuTaiKhoan);
    }
  } while (tien>a.soDuTaiKhoan);
NhapPin:  
  if(ConfirmPin(a.PIN)==1){
  if (confirmMessage() ) {
  	a.soDuTaiKhoan-=tien;
  	cout<<"\n  Ban da rut thanh cong! So du hien tai la: "; inSodu(a.soDuTaiKhoan);
  	cout << "\n  ";
    char x[256];
    dateTime d;
    sprintf(x," TK: %d \n GD: -%d %d/%d/%d %d:%d \n Hinh thuc: Rut Tien \n ND: Rut tien tu tai khoan %d \n Ma GD: %d\n_",a.maSoThe,tien,d.getDay(),d.getMon(),d.getYear(),d.getHour(),d.getMin(),a.maSoThe,randomNum());
    char path[256];
    sprintf(path,"./LSGD/%d-%s.txt",a.idd,a.hoTen);
    saveTransaction(x,path);
  	saveListClient(client);
  	client = getListClient();
    cout<<"------------------------------------\nThong bao bien dong so du: ";
        cout<<x;
  } else {
  	return;
  }
  }else{
    cout<<"Ma pin sai! Con "<<sl<<" lan nhap ma!"<<endl;
    sl--;
    if(sl>=0) goto NhapPin;
    else{
      cout<<"Da nhap sai qua 3 lan! Vui long thuc hien lai giao dich!"<<endl;
    }
  }
}

void doiMapin(CLIENT& a){
  char mk[256];
  char pin[256];
  do
  {
    cout<<"  Vui long nhap mat khau: ";
    fflush(stdin);
    cin.getline(mk,256);
    if(strcmp(mk, a.matKhau) == 0) break;
    else{
      cout<<"Mat khau khong chinh xac! Vui long nhap lai! "<<endl;
    }
  } while (1);

  do
  {
    cout<<"  Vui long nhap ma pin cu: ";
    cin.getline(pin,256);
    if(strcmp(pin,a.PIN)==0) break;
    else{
      cout<<"Ma pin khong chinh xac! Vui long nhap lai!"<<endl;
    }
  } while (1);
  cout<<"  Nhap ma pin moi: ";
  cin.getline(a.PIN,256);
  if(confirmMessage()){ 
    cout<<"  Thay doi ma pin thanh cong!"<<endl;
    system("pause");
    saveListClient(client);
    client = getListClient();
  }
  else{ 
    cout<<"  Thay doi ma pin khong thanh cong!"<<endl;
    system("pause");
  }
}



int check(char* tendn, char* mk){
  for (int i = 1; i <= number; i++)
  {
    if(strcmp(client[i].taiKhoan,tendn)==0 && strcmp(client[i].matKhau, mk)==0){
    	
    	return i;	
	}	
	
  }
  return 0;
}

int log_in(){
  char tendn[256];
  char mk[256];
  fflush(stdin);
  system("cls");
  cout << "\n  Ten Dang Nhap: "; cin.getline(tendn,256);
  
  	int i = 0;
    char ch;
    cout << "  Mat khau: ";
    ch = _getch();
    while(ch != 13){//character 13 is enter
      mk[i] = ch;
      i ++;
      cout << '*';
      ch = _getch();
    }
  
  return check(tendn,mk);
  
  
  
}

CLIENT* getListClient() {
  CLIENT* client = new CLIENT [number+1];
  int i = 1;
  fstream f("text1.txt" , ios::binary|ios::in);
  if(!f) cout << "error occured when open file to read!";
  while(f.good()) {
    f.read(reinterpret_cast<char *>(&client[i]), sizeof(client[i]));
    i++;
    if(f.eof()) break;
  }
  f.close();
  return client;
}

void saveListClient(CLIENT* client) {
	fstream f("text1.txt" , ios::binary|ios::out|ios::trunc);
  	if(!f) cout << "error occured when open file to write!";
	for(int i = 1; i<=number; i++) {
		f.write(reinterpret_cast<char *>(&client[i]), sizeof(client[i]));
	}
	f.close();
}

void saveListClient(CLIENT* client, int ii) {
  fstream f("text1.txt" , ios::binary|ios::out|ios::trunc);
  	if(!f) cout << "error occured when open file to write!";
	for(int i = 1; i<=number; i++) {
    if (i == ii) continue;
		f.write(reinterpret_cast<char *>(&client[i]), sizeof(client[i]));
	}
	f.close();
}


void layID() {
  fstream f("id.txt" , ios::in);
  if(!f) cout << "error occured when open file to read!";
  f >> id;
  f >> number;
  f.close();
}
void taoID() {
  fstream f("id.txt" , ios::out|ios::trunc);
  if(!f) cout << "error occured when open file to write!";
  f << id << ' ';
  f << number;
  f.close();
}



void deleteCLient(int i) {
      saveListClient(client, i);
      client = getListClient();
      number--;
	taoID();
    
	
}

void inSodu(long long a ){
  long long n=a;
  int d=0;
  if(a!=0){
  while (n>0)
  {
    n/=10;
    d++;
  }
  int arr[d+1];
  n=a;
  for (int i = 1; i <= d; i++) {
    arr[i]=n%10;
    n/=10;
  }
  if(d%3==0){
    for (int i = 1; i <= d; i++)
   {
     cout<<arr[d-i+1];
     if(i%3==0 && i<d) cout<<".";
   }
  }
  else{
    for (int i = d; i > d-d%3; i--){
      cout<<arr[i];
    }
    cout<<".";
    int t=d-d%3;
     for (int i = 1; i <= t; i++)
   {
     cout<<arr[t-i+1];
     if(i%3==0 && i< t) cout<<".";
   }
  }
  }else cout<<a;
  cout<<" VND";
  cout<<endl;
}

bool confirmMessage () {
//	system("cls");
	cout << endl;
	cout << "  +------------------------------+" << endl;
	cout << "  | !!!  Xac nhan giao dich  !!! |" << endl;
	cout << "  +------------------------------+" << endl;
	cout << "\n";
	cout << "  1: Xac nhan" << endl;
	cout << "  0: Tu choi" << endl;
	
	bool select;
	cout << "  Nhap lua chon: ";
	cin >> select;
	
//	system("cls");
	
	if (select == 1)	return 1;
	else 				return 0;
}
int ConfirmPin(char a[]){
    char pin[256];
    cout<<"  Vui long nhap ma pin de xac nhan giao dich: ";
    cin.getline(pin,256);
    if(strcmp(pin,a)==0) return 1;
    else return 0;
}
int randomNum(){
  srand(time(NULL));
	int res = rand()*10000;
  return res;
}

// ------------------------------------------------------------------------------------

void saveTransaction (char* x, char* path) {
	fstream f;
	f.open(path, ios::out | ios::app);
	f << x;
	f.close();
} 

void exportTransaction (CLIENT& a) {
	
	fstream f;
	char path[256];
	sprintf(path,"./LSGD/%d-%s.txt",a.idd,a.hoTen);
	f.open(path, ios::in);
  if(!(f.peek()==std::ifstream::traits_type::eof())){
	string temp;
	system ("cls");
	cout << "\n\t\t LICH SU GIAO DICH" << endl;
	while (!f.eof()) {
		cout << "\n";
		cout << "--------------------------------------------" << endl;
		getline(f, temp, '_');
		cout << temp << endl;
		
	}
  }
  else{
    cout<<"Chua co lich su giao dich!"<<endl;
  }
	f.close();

}


void signUp (CLIENT& p) {
	fflush(stdin);
    
    cout << "  Nhap ten: ";
    cin.getline(p.hoTen, 256);
    cout << "\n";
    cout << "  Nhap dia chi email: ";
    cin.getline(p.email, 256);
    cout << "\n";
    cout << "  Nhap so dien thoai: ";
    cin.getline(p.soDienThoai, 256);
    cout << "\n";
    cout << "  Nhap can cuoc cong dan: ";
    cin.getline(p.cccd, 256);
    cout << "\n";
    cout << "  Nhap dia chi: ";
    cin.getline(p.diaChi, 256);
    cout << "\n";
    cout << "  Nhap ngay sinh (dd-mm-yy): ";
    cin.getline(p.ngaySinh, 256);
    cout << "\n";
    int temp=0;
  	do {
  		
  		cout << "  Nhap ten dang nhap: ";
  		cin.getline(p.taiKhoan, 256);
  		temp = 0;
  		for (int i = 1; i <= number; i++) {
  			if (strcmp(p.taiKhoan, client[i].taiKhoan) == 0) {
  				temp = 1;
  				cout << "\n  Ten dang nhap da ton tai. Vui long su dung ten dang nhap khac \n" << endl;
			}
		}
	} while (temp);
	cout << "\n";
	
	
  	do {
  		cout << "  Nhap mat khau: ";
  		cin.getline(p.matKhau, 256);
  		temp = 0;
  		if (strlen(p.matKhau) < 6) {
  			temp = 1;
			cout << "\n  Mat khau phai toi thieu 6 ki tu. Vui long nhap lai mat khau khac\n" << endl;	
		}
  		
	} while (temp);
  	
  	do {
  		cout << "\n";
        cout << "  Xac nhan mat khau: ";
        char temp[256];
        fflush(stdin);
        cin.getline(temp, 256);
        if (strcmp(temp, p.matKhau) == 0) {
            break;
        } else {
            cout << "\n\n!!!Mat khau xac nhan khong chinh xac!!!" << endl;
            cout << "!!!Vui long xac nhan lai mat khau!!!\n" << endl;
        }
    } while(1);
    
    cout << "\n";
    cout<<"  Nhap ma pin moi: "; cin.getline(p.PIN,256);
    do {
    	cout << "\n";
        cout << "  Xac nhan ma pin: ";
        char t[256];
        cin>>t;
        if (strcmp(t,p.PIN)==0) {
            cout<<"  Tai khoan quy khach da duoc tao thanh cong! Vui long dang nhap de su dung dich vu!"<<endl;
            cout<<p.PIN;
            system("pause");
            break;
        } else {
            cout << "\n\n!!!Ma pin xac nhan khong chinh xac!!!" << endl;
            cout << "!!!Vui long xac nhan lai ma pin!!!\n" << endl;
        }
    } while (1);
    
    p.maSoThe = 10000000 + id;
    p.soDuTaiKhoan = 0;
    p.idd = id;
}

void quenMatKhau () {
	fflush (stdin);
	cout << "  Nhap ten dang nhap: ";
	char _tenDangNhap[256];
	cin.getline(_tenDangNhap, 256);
	int check = 0;
	int i;
	for (i=1; i<=number; i++) {
		if (strcmp (_tenDangNhap, client[i].taiKhoan) == 0) {
			check = 1;
			break;
    }
	}
	if (check) {
		cout << "  Quy khach vui long xac nhan mot so thong tin can thiet" << endl;
		cout << "  Nhap so dien thoai dang ky: ";
		char _sdt[256];
		cin.getline(_sdt, 256);
		cout << "  Nhap ho ten: ";
		char _hoTen[256];
		cin.getline(_hoTen, 256);
		cout << "  Nhap so can cuoc cong dan da dang ky: ";
		char _cccd[256];
		cin.getline(_cccd, 256);
		
    if (strcmp (_sdt, client[i].soDienThoai) == 0 && strcmp (_hoTen, client[i].hoTen) == 0 && strcmp (_cccd, client[i].cccd)==0)
    {
		do 
    {
			char _matKhau[256];
			cout << "\n  Nhap mat khau moi: ";
			cin.getline(_matKhau, 256);
			cout << "  Xac nhan lai mat khau: ";
			char _matkhau1[256];
      cin.getline(_matkhau1,256);
			if (strcmp (_matKhau, _matkhau1) == 0) 
      {
				cout << "  Thay doi mat khau thanh cong!!!" << endl;
        strcpy(client[i].matKhau,_matkhau1);
        saveListClient(client);
        client = getListClient();
        system("pause");
				break;
			} 
      else 
      {
				cout << "  Mat khau xac nhan khong trung khop!!!" << endl;
        system("pause");
      }
		}while (1);
    }
    else{
      cout<<"Thong tin quy khach vua nhap khong khop voi thong tin da dang ky tren TV Bank! Vui long thuc hien lai!"<<endl;
      system("pause");
    }
	} else {
		cout << "  Tai khoan vua nhap khong ton tai! Vui long quy khach thuc hien lai!" << endl;
    system("pause");
	}
}

// -------------------------------------------------------------------------------------

#endif
