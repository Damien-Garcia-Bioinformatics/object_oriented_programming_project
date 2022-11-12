#include <iostream>
using namespace std;

class PetitObjet1{
	int un;
	public :
		void get();
		void set(int);
};

class PetitObjet2{
	int deux;
	public :
		void get();
		void set(int);
};
class PetitObjet3{
	int trois;
	public :
		void get();
		void set(int);
};

class GrosObjet{
	PetitObjet1 uno;
	PetitObjet2 dos;
	PetitObjet3 tres;

	public :
		void get();
		void set(int);
};

void PetitObjet1::get(){cout << un << endl;}
void PetitObjet2::get(){cout << deux << endl;}
void PetitObjet3::get(){cout << trois << endl;}

void PetitObjet1::set(int blipoop){un = blipoop;}
void PetitObjet2::set(int blipoop){deux = blipoop;}
void PetitObjet3::set(int blipoop){trois = blipoop;}

void GrosObjet::get(){uno.get(); dos.get(); tres.get();}
void GrosObjet::set(int blipaduloop){
	uno.set(blipaduloop);
	dos.set(blipaduloop + 1);
	tres.set(blipaduloop + 2);
}
