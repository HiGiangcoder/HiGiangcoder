/*###Begin banned keyword - each of the following line if appear in code will raise error. regex supported
###End banned keyword*/
#include <bits/stdc++.h>
using namespace std;


struct DONTHUC{
	int somu;
	double heso;
	
	DONTHUC(double _heso = 0,int _somu=0){
		heso = _heso;
		somu  = _somu;
	}
	
	DONTHUC& operator = (const DONTHUC &rhs){
		if (this == &rhs) return *this;
		this->heso = rhs.heso;
		this->somu = rhs.somu;
		return *this;
	}
};


struct Node{
	DONTHUC* data;
	Node* next;
	
	Node(DONTHUC* _data = nullptr){
		this->data = _data;
		this->next = nullptr;
	}
	
};

struct DATHUC{
	Node* head;
	Node* tail;
	DATHUC(){
		this->head = nullptr;
		this->tail = nullptr;
	}
};

void Nhap(DATHUC &B, double heso, int somu){
    DONTHUC* p = new DONTHUC(heso,somu);
    Node* q = new Node(p);
    if (B.head == nullptr){
        B.head = q;
        B.tail = q;
    }
    else{
        B.tail->next = q;
        B.tail = q;
    }
}

void Xuat(DATHUC B){
    Node* p = B.head;
    bool first = true;
    while (p != nullptr){
        if (!first && p->data->heso > 0) cout << "+";
        if (p->data->heso < 0) cout << "-";
        if (p->data->heso == 0) {
            p = p->next;
            continue;
        }
        first = false;
        if (abs(p->data->heso) != 1)cout << abs(p->data->heso);

        if (p->data->somu > 1) cout << "x^" << p->data->somu;
        else if (p->data->somu == 1) cout << "x";

        p = p->next;
    }
    if (first) cout << "0";
}

double TinhDaThuc(DATHUC B, double x){
    double S = 0;
    Node* p = B.head;
    while (p != nullptr){
        S += p->data->heso * pow(x,p->data->somu);
        p = p->next;
    }
    return S;
}

int main() {
    DATHUC B;
    int N;
    
    cin >> N;
    for (int test = 0; test < N; test++){
		double heso; int somu;
		cin >> heso >> somu;
		Nhap(B,heso,somu);
    }
    
    
    cout << "Da thuc vua nhap la: "; Xuat(B);
    double x; cin >> x;
    cout << "\nVoi x=" << x << ", gia tri da thuc la: "
         << setprecision(2) << fixed << TinhDaThuc(B, x);
    return 0;
}
