// Project Oriented Programming Project
// Damien GARCIA
// M2BB


#ifndef __CLASS__
#define __CLASS__


#include <string>
#include <vector>


typedef enum usertype {patient, doctor} usertype ;


// --- Class declaration --- //

class User {
	private :
		std::string name ;
		std::string surname ;
		usertype type ;

		void set_name(std::string) ;
		void set_surname(std::string) ;
		void set_usertype(usertype) ;

	public :
		std::string get_name() ;
		std::string get_surname() ;
		usertype get_usertype() ;

		User(std::string, std::string, usertype) ;
} ;


class Patient:private User {
	private :
		std::string socialSecurity ;

		void set_socials(std::string) ;

	public :
		std::string get_socials() ;

		Patient(std::string) ;
} ;


class Doctor:private User {
	private :
		std::string id ;

		void set_id(std::string) ;
	
	public :
		std::string get_id() ;
		
		Doctor(std::string) ;
} ;


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

		//Other methods
		bool isValidPassword(std::string) ;
} ;


class Snapshot {
	private :
		size_t id ;
		std::string path ;

		//Set
		void set_id(size_t) ;
		void set_path(std::string) ;

	public :
		//Get
		size_t get_id() ;
		std::string get_path() ;
} ;


class Radiography {
	protected :
		enum class radiographyState {done, pending} ;
		enum class radiographyType {xRay, ultrasound, MRI} ;

	private :
		radiographyType type ;
		radiographyState state ;
		int day ;
		int month ;
		int year ;
		MedicalReport medicalReport ;
		std::vector<Snapshot> listSnapshot ;

		//Set
		void set_type(radiographyType) ;
		void set_state(radiographyState) ;
		void set_day(int) ;
		void set_month(int) ;
		void set_year(int) ;
		void set_medicalReport(MedicalReport) ;
		void set_listSnapshot(std::vector<Snapshot>) ;

	public :
		//Get
		radiographyType get_type() ;
		radiographyState get_state() ;
		int get_day() ;
		int get_month() ;
		int get_year() ;
		MedicalReport get_medicalReport() ;
		std::vector<Snapshot> get_listSnapshot() ;

		//Constructor
		Radiography() ;

		//Other functions
		void add_snapshot(Snapshot snap) ;
		void remove_snapshot(Snapshot snap) ;
} ;


class MedicalExamination {
	private :
		MedicalReport report ;
		Radiography radio ;
} ;


#endif