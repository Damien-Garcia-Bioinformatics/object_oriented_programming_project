// Project Oriented Programming Project
// Damien GARCIA
// M2BB


#ifndef __CLASS__
#define __CLASS__


#include <string>
#include <vector>


// --- Data types --- //

// typedef enum radiographyState {done, pending} radiographyState ;
// typedef enum radiographyType {xRay, ultrasound, MRI} radiographyType ;

enum class radiographyState {done, pending} ;
enum class radiographyType {xRay, ultrasound, MRI} ; 


//----------------------------------------------------------------------------//

// --- Class declaration --- //

class Patient {
	private :
		std::string name ;
		std::string surname ;
		std::string socialSecurity ;

		void set_name(std::string) ;
		void set_surname(std::string) ;
		void set_socials(std::string) ;

	public :
		std::string get_name() ;
		std::string get_surname() ;
		std::string get_socials() ;
	
		Patient(std::string, std::string, std::string) ; //Constructor
		~Patient() ; //Destructor
} ;


//----------------------------------------------------------------------------//


class MedicalExamination {
	

} ;


//----------------------------------------------------------------------------//


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

		//Constructor
		MedicalReport(std::string, std::string) ;
		~MedicalReport() ;

		//Other methods
		bool isValidPassword(std::string) ;
} ;


//----------------------------------------------------------------------------//


class Snapshot {
	private :
		int id ;
		std::string path ;

		//Set
		void set_id(int) ;
		void set_path(std::string) ;

	public :
		//Get
		int get_id() ;
		std::string get_path() ;
} ;


//----------------------------------------------------------------------------//


class Radiography {
	private :
		// radiographyType type ;
		// radiographyState state ;
		int day ;
		int month ;
		int year ;
		MedicalReport medicalReport ;
		std::vector<Snapshot> listSnapshot ;

		//Set
		// void set_type(radiographType) ;
		// void set_state(radiographyState) ;
		void set_day(int) ;
		void set_month(int) ;
		void set_year(int) ;
		void set_listSnapshot(std::vector<Snapshot>) ;

	public :
		//Get
		// radiographyType get_type() ;
		// radiographyState get_state() ;
		int get_day() ;
		int get_month() ;
		int get_year() ;
		std::vector<Snapshot> get_listSnapshot() ;

		//Constructor
		Radiography() ;

		//Other functions
		void add_snapshot(Snapshot snap) ;
} ;


#endif