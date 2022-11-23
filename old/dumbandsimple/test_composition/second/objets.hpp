#include <iostream>
#include <vector>
#include <string>
using namespace std;

class PetitObjet{
	int spe;
	int access1;
	int access2;
	bool status;
	string photo_filepath; //faudra changer vers une struct avec liste de numero de photo
	string cr_filepath;
	string passwd;

	public :
		int get_access1();
	       	int get_access2();
	       	int get_spe(); 
		//void get_photo();
		//bool is_access1(int);
		//bool is_access2(int); facultatif si je parcours déjà et que je get le result anyway? 
		void get_cr(string);
		void set_spe(int); 
		void set_acc1(int);
		void set_acc2(int);
		void set_stat(bool);
		void set_photo(string);
		void set_cr(string);

};

class GrosObjet{
	vector<PetitObjet> liste;
	vector<passwd_user> log_matrix;
	public :
		void get_access1(int); // parcours liste et affiche la spé des objets si access1 correspond
		void get_access2(int); // parcours liste et affiche la spé des objets si access2 correspond
		PetitObjet get_object(int); // pour l'instant l'accès réel se fait sur spe
		// ca peut ne pas retourner l'objet(donc void) mais le push back direct, ce qui ne nécessitera pas une autre méthode
		void init_object(); // vector.push_back(info), soit une suite de cin soit file un struct
		void set(PetitObjet); // faire un commutateur (switch/case) pour un petit menu sur ce qui est rempli
		void affiche_liste();
		PetitObjet ajouter_objet(); // appelle set() après avoir init new et puis push back
};

struct passwd_user{
	string user_id;
	string passwd;
}

//void PetitObjet::get_info(int access){(access == 1) ? return access1 : return access2;}

int PetitObjet::get_access1(){return access1;}
int PetitObjet::get_access2(){return access2;}
int PetitObjet::get_spe(){return spe;}
void PetitObjet::get_cr(string password){} // confronte le password donné et celui stocké dans l'objet
void PetitObjet::set_spe(int special_id){spe = special_id}
void PetitObjet::set_acc1(int access1_id){spe = access1_id}
void PetitObjet::set_acc2(int access2_id){spe = access2_id}
void PetitObjet::set_stat(bool status){spe = status}
void PetitObjet::set_photo(string photo_path){spe = photo_path}
void PetitObjet::set_cr(string cr_path){spe = cr_path}


void get_access1(int access1_id){}; // boucle sur les objets du vecteur et compare
void get_access2(int access2_id){}; //same appelle PetitObjet.get_spe() si match
void init_object(){}; // là j'avoue c'est pas clair ce qu'on fait


void set(PetitObjet){
	bool boule;
	int inte;
	string toimemetusais;
	cin >> inte;
	PetitObjet.set_spe(inte);
	cin >> inte;
	PetitObjet.set_acc1(inte);
	cin >> inte;
	PetitObjet.set_acc2(inte);
	cin >> boule;
	PetitObjet.set_stat(boule);
	cin >> toimemetusais;
	PetitObjet.set_photo(toimemetusais);
	cin >> toimemetusais;
	PetitObjet.set_cr(toimemetusais);
};






