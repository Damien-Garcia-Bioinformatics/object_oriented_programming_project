// Project Oriented Programming Project
// Damien GARCIA, Florian Echelard
// M2BB


#ifndef __CLASS__
#define __CLASS__


#include <string>
#include <vector>


// --- Type declaration --- //

typedef enum usertype {patient, doctor} usertype ;
typedef enum radiographyState {done, pending} radiographyState ;
typedef enum radiographyType {xRay, ultrasound, MRI} radiographyType ;


// --- Class declaration --- //

class User {
	private :
		std::string name ;
		std::string surname ;
		// usertype type ;

	public :
		void set_name(std::string) ;
		void set_surname(std::string) ;
		// void set_usertype(usertype) ;

		std::string get_name() ;
		std::string get_surname() ;
		// usertype get_usertype() ;

		User(std::string, std::string) ;
} ;


class Patient:private User {
	private :
		std::string socialSecurity ;

	public :
		void set_socials(std::string) ;
		
		std::string get_socials() ;

		Patient(std::string name, std::string surname, std::string socials) : User(name, surname) ;
} ;


class Doctor:private User {
	private :
		std::string id ;
	
	public :
		void set_id(std::string) ;
		
		std::string get_id() ;
		
		Doctor(std::string) ;
} ;


class MedicalReport {
	private :
		std::string content ;
		std::string password ;

	public :
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

	public :
		//Set
		void set_id(size_t) ;
		void set_path(std::string) ;

		//Get
		size_t get_id() ;
		std::string get_path() ;
} ;


class Radiography {
	private :
		radiographyType type ;
		radiographyState state ;
		int day ;
		int month ;
		int year ;
		MedicalReport medicalReport ;
		std::vector<Snapshot> listSnapshot ;

	public :
		//Set
		void set_type(radiographyType) ;
		void set_state(radiographyState) ;
		void set_day(int) ;
		void set_month(int) ;
		void set_year(int) ;
		void set_medicalReport(MedicalReport) ;
		void set_listSnapshot(std::vector<Snapshot>) ;

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