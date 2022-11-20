#ifndef __DATABASE__
#define __DATABASE__


#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "patient.hpp"
#include "doctor.hpp"


class DatabaseHandling {
	private :
		// Attributes :
		std::vector<Patient> listPatients ;
		std::vector<Doctor> listDoctors ;

	public :
		// Constructor :
		DatabaseHandling() {
			set_listPatients() ;
			set_listDoctors() ;
		}

		// --- Basic methods --- //

		// Set functions :
		void set_listPatients() {
			this->listPatients = upload_patients_database() ;
		}
		void set_listDoctors() {
			this->listDoctors = upload_doctors_database() ;
		}

		// Get functions :
		std::vector<Patient> get_listPatients() {
			return this->listPatients ;
		}
		std::vector<Doctor> get_listDoctors() {
			return this->listDoctors ;
		}
		Patient get_patient(int index) {
			return get_listPatients()[index] ;
		}
		Doctor get_doctor(int index) {
			return get_listDoctors()[index] ;
		}


		// --- Patients database handling methods --- //

		// Adds a patient to the database
		void add_patient(Patient p) {
			this->listPatients.push_back(p) ;
			update_patients_database(listPatients) ;
		}

		int is_patient(std::string ssn) {
			for (size_t i=0 ; i<get_listPatients().size() ; i++) {
				if (this->get_listPatients()[i].get_ssn() == ssn) {
					return i ;
				}
			}
			return -1 ;
		}

		// Extracts patients data from database
		std::vector<Patient> upload_patients_database() {
			std::vector<Patient> listPatients ;
			std::string name, surname, ssn, password ;

			std::string path {"data/patients.txt"} ;
			std::ifstream file ;
			file.open(path, std::ios::in) ;
			if (!file.is_open()) {
				std::cout << "Could not upload patients.txt file" << std::endl ;
				exit(1) ;
			}

			std::string line ;
			while (getline(file, line)) { 
				if (line == "#Begin") {
					continue ;
				} else if (line.substr(0, line.find('=')) == "name") {
					name = line.substr(line.find('=') +1) ;
				} else if (line.substr(0, line.find('=')) == "surname") {
					surname = line.substr(line.find('=') +1) ;
				} else if (line.substr(0, line.find('=')) == "ssn") {
					ssn = line.substr(line.find('=') +1) ;
				} else if (line.substr(0, line.find('=')) == "password") {
					password = line.substr(line.find('=') +1) ;
				} else if (line == "#End") {
					listPatients.push_back(Patient(name, surname, password, ssn)) ;
				}
			}
			file.close() ;

			return listPatients ;
		}

		// Rewrite new version of patients database
		void update_patients_database(std::vector<Patient> listPatients) {
			std::string path {"data/patients.txt"} ;
			std::ofstream file ;
			file.open(path, std::ios::trunc) ;
			if (!file.is_open()) {
				std::cout << "Could not update patients.txt file" << std::endl ;
				exit(1) ;
			}

			for (size_t i=0 ; i<listPatients.size() ; i++) {
				file << "#Begin\n" ;
				file << "name=" << listPatients[i].get_name() << "\n" ;
				file << "surname=" << listPatients[i].get_surname() << "\n" ;
				file << "ssn=" << listPatients[i].get_ssn() << "\n" ;
				file << "password=" << listPatients[i].get_password() << "\n" ;
				file << "#End\n\n" ;
			}
			file.close() ;
		}


		// --- Doctors database handling methods --- //

		// Adds a doctor to the database
		void add_doctor(Doctor d) {
			this->listDoctors.push_back(d) ;
		}

		int is_doctor(std::string cnomId) {
			for (size_t i=0 ; i<get_listDoctors().size() ; i++) {
				if (this->get_listDoctors()[i].get_cnomId() == cnomId) {
					return i ;
				}
			}
			return -1 ;
		}

		// Extracts doctors data from database
		std::vector<Doctor> upload_doctors_database() {
			std::vector<Doctor> listDoctors ;
			std::string name, surname, cnomId, password ;

			std::string path {"data/doctors.txt"} ;
			std::ifstream file ;
			file.open(path, std::ios::in) ;
			if (!file.is_open()) {
				std::cout << "Could not upload doctors.txt file" << std::endl ;
				exit(1) ;
			}

			std::string line ;
			while (getline(file, line)) { 
				if (line == "#Begin") {
					continue ;
				} else if (line.substr(0, line.find('=')) == "name") {
					name = line.substr(line.find('=') +1) ;
				} else if (line.substr(0, line.find('=')) == "surname") {
					surname = line.substr(line.find('=') +1) ;
				} else if (line.substr(0, line.find('=')) == "cnomId") {
					cnomId = line.substr(line.find('=') +1) ;
				} else if (line.substr(0, line.find('=')) == "password") {
					password = line.substr(line.find('=') +1) ;
				} else if (line == "#End") {
					listDoctors.push_back(Doctor(name, surname, password, cnomId)) ;
				}
			}
			file.close() ;

			return listDoctors ;
		}


		// Rewrite new version of doctors database
		void update_doctors_database(std::vector<Doctor> listDoctors) {
			std::string path {"data/doctors.txt"} ;
			std::ofstream file ;
			file.open(path, std::ios::trunc) ;
			if (!file.is_open()) {
				std::cout << "Could not update doctors.txt file" << std::endl ;
				exit(1) ;
			}

			for (size_t i=0 ; i<listDoctors.size() ; i++) {
				file << "#Begin\n" ;
				file << "name=" << listDoctors[i].get_name() << "\n" ;
				file << "surname=" << listDoctors[i].get_surname() << "\n" ;
				file << "cnomId=" << listDoctors[i].get_cnomId() << "\n" ;
				file << "password=" << listDoctors[i].get_password() << "\n" ;
				file << "#End\n\n" ;
			}
			file.close() ;
		}
} ;


#endif