#include <iostream>
#include <string>

using namespace std;

int main(){
	string nom_fichier;
	int choix;


	cout << "Quelle base de données voulez-vous consulter? " << endl;
	cin >> nom_fichier ; // le nom du fichier/le path pour le fichier sauvegardé
       	cout << "Que souhaitez-vous faire? \n \t 1. Ajouter une radiographie à la liste \n \t 2. Supprimer une radiographie \n \t 3. Afficher le contenu d'un dossier médical" << endl;
	cin >> choix;

	switch(choix){
		case 1 :
			cout << "Ajout...";
			break;
		case 2 :
			cout << "Suppression...";
			break;
		case 3 :
			cout << "Affichage...";
			break;
	}
		
	
}
