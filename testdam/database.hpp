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
		std::vector<Patient*> listPatients ;
		std::vector<Doctor*> listDoctors ;

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
		std::vector<Patient*> get_listPatients() {
			return this->listPatients ;
		}
		std::vector<Doctor*> get_listDoctors() {
			return this->listDoctors ;
		}


		// --- Patients database handling methods --- //

		// Adds a patient to the database
		void add_patient(Patient p) {
			Patient *ptr {&p} ;
			this->listPatients.push_back(ptr) ;
		}

		// Extracts patients data from database
		std::vector<Patient*> upload_patients_database() {
			std::vector<Patient*> listPatients ;
			Patient *ptr {nullptr} ;
			std::string name, surname, socials ;

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
					ptr = new Patient(name, surname, socials) ;
				} else if (line.substr(0, line.find('=')) == "name") {
					ptr->set_name(line.substr(line.find('=') +1)) ;
				} else if (line.substr(0, line.find('=')) == "surname") {
					ptr->set_surname(line.substr(line.find('=') +1)) ;
				} else if (line.substr(0, line.find('=')) == "socials") {
					ptr->set_socials(line.substr(line.find('=') +1)) ;
				} else if (line == "#End") {
					listPatients.push_back(ptr) ;
				}
			}
			file.close() ;

			return listPatients ;
		}

		// Rewrite new version of patients database
		void update_patients_database() {
			std::vector<Patient*> listPatients {get_listPatients()} ;
			std::string path {"data/patients.txt"} ;
			std::ofstream file ;
			file.open(path, std::ios::trunc) ;
			if (!file.is_open()) {
				std::cout << "Could not update patients.txt file" << std::endl ;
				exit(1) ;
			}

			for (size_t i=0 ; i<listPatients.size() ; i++) {
				file << "#Begin\n" ;
				file << "name=" << listPatients[i]->get_name() << "\n" ;
				file << "surname=" << listPatients[i]->get_surname() << "\n" ;
				file << "socials=" << listPatients[i]->get_socials() << "\n" ;
				file << "#End\n" ;
			}
			file.close() ;
		}


		// --- Doctors database handling methods --- //

		// Adds a doctor to the database
		void add_doctor(Doctor d) {
			Doctor *ptr {&d} ;
			this->listDoctors.push_back(ptr) ;
		}

		// Extracts doctors data from database
		std::vector<Doctor*> upload_doctors_database() {
			std::vector<Doctor*> listDoctors ;
			Doctor *ptr {nullptr} ;
			std::string name, surname, cnomID ;

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
					ptr = new Doctor(name, surname, cnomID) ;
				} else if (line.substr(0, line.find('=')) == "name") {
					ptr->set_name(line.substr(line.find('=') +1)) ;
				} else if (line.substr(0, line.find('=')) == "surname") {
					ptr->set_surname(line.substr(line.find('=') +1)) ;
				} else if (line.substr(0, line.find('=')) == "cnomId") {
					ptr->set_cnomId(line.substr(line.find('=') +1)) ;
				} else if (line == "#End") {
					listDoctors.push_back(ptr) ;
				}
			}
			file.close() ;

			return listDoctors ;
		}


		// Rewrite new version of doctors database
		void update_doctors_database() {
			std::vector<Doctor*> listDoctors {get_listDoctors()} ;
			std::string path {"data/doctors.txt"} ;
			std::ofstream file ;
			file.open(path, std::ios::trunc) ;
			if (!file.is_open()) {
				std::cout << "Could not update doctors.txt file" << std::endl ;
				exit(1) ;
			}

			for (size_t i=0 ; i<listDoctors.size() ; i++) {
				file << "#Begin\n" ;
				file << "name=" << listDoctors[i]->get_name() << "\n" ;
				file << "surname=" << listDoctors[i]->get_surname() << "\n" ;
				file << "cnomID=" << listDoctors[i]->get_cnomId() << "\n" ;
				file << "#End\n" ;
			}
			file.close() ;
		}
} ;


#endif