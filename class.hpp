#include <string>
#include <vector>

class Patient {
	private :
		std::string name ;
		std::string surname ;
		std::string socialSecurity ;

		std::string get_name() ;
		std::string get_surname() ;
		std::string get_socials() ;

		void set_name(std::string) ;
		void set_surname(std::string) ;
		void set_socials(std::string) ;

	public :
		Patient(std::string, std::string, std::string) ; //Constructor
		~Patient() //Destructor
}

class MedicalExamination {
	
}

class MedicalReport {
	private :
		std::string content ;
		std::string password ;

		//Get
		std::string get_content() ;
		std::string get_password() ;
		
		//Set
		void set_content(std::string) ;
		void set_password(std::string) ;

		//Other methods
		bool isValidPassword(std::string) ;
}

class Snapshot {
	int identifier ;
	
}

class Radiography {
	std::string type ;
	std::string state ;
	int day ;
	int month ;
	int year ;
	std::vector<Snapshot> listSnapshot ;
}

