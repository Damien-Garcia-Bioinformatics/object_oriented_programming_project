#include <iostream>
#include <vector>
#include <string>
using namespace std;

class PetitObjet{
	int spe;
	int access1;
	int access2;
	bool status;
	string photo_filepath;
	string cr_filepath;
	
	public :
		void get(int);
		void set(int);
};

class GrosObjet{
	vector<PetitObjet> liste;
	public :
		void get_access();
		void set(int);
};

void PetitObjet::get(int access){cout << un << endl;}

void PetitObjet::set(int blipoop){un = blipoop;}

void GrosObjet::get(){uno.get(); dos.get(); tres.get();}

void GrosObjet::set(int blipaduloop){
	uno.set(blipaduloop);
	dos.set(blipaduloop + 1);
	tres.set(blipaduloop + 2);
}
