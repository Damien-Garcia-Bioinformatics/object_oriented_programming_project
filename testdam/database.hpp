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
		std::vector<Radiography> listRadiographies ;
		std::vector<Patient> listPatients ;
		std::vector<Doctor> listDoctors ;

	public :
		// --- Constructor --- //

		DatabaseHandling() {
			set_listRadiographies() ;
			set_listPatients() ;
			set_listDoctors() ;
		}

		void load_progress() {
			upload_radiographies_database() ;
			upload_patients_database() ;
			upload_doctors_database() ;
		}

		// --- Common methods --- //
		void save_and_quit() {
			std::cout << "   ╔═════════════════════════════════════════════════════════════════════════╗\n" ;
			std::cout << "   ║  Saving database, please wait... (Save should only take a few seconds)  ║\n" ;
			std::cout << "   ║  0%                              50%                              100%  ║\n" ;
			update_radiographies_database() ;
			std::cout << "   ║  ════════════════════════════" ;
			update_patients_database() ;
			std::cout << "════════════════════" ;
			update_doctors_database() ;
			std::cout << "═════════════════════  ║\n" ;
			std::cout << "   ║  Thanks for using our database. All modifications were successfully     ║\n" ;
			std::cout << "   ║  saved.                                                                 ║\n" ;
			std::cout << "   ╚═════════════════════════════════════════════════════════════════════════╝\n\n" ;
			std::cout << "   ╔═════════════════════════════════════════════════════════════════════════╗\n" ;
			std::cout << "   ║  Created for Object Oriented Programming For Biologists Project.        ║\n" ;
			std::cout << "   ║  Authors :                                                              ║\n" ;
			std::cout << "   ║     - Damien  GARCIA   (M2BB)                                           ║\n" ;
			std::cout << "   ║     - Florian ECHELARD (M2BB)                                           ║\n" ;
			std::cout << "   ╚═════════════════════════════════════════════════════════════════════════╝\n\n" ;
		}



		// ------------------------------------------ //
		// --- Patients database handling methods --- //
		// ------------------------------------------ //

		void set_listPatients() {
			this->listPatients = upload_patients_database() ;
		}

		std::vector<Patient> get_listPatients() {
			return this->listPatients ;
		}

		Patient get_patient(int index) {
			return get_listPatients()[index] ;
		}

		int get_patient_by_ssn(std::string ssn) {
			std::vector<Patient> list {get_listPatients()} ;
			for (size_t i=0 ; i<list.size() ; i++) {
				if (list[i].get_ssn() == ssn) {
					return i ;
				}
			}
			return -1 ;
		}

		// Adds a patient to the database
		void add_patient(Patient p) {
			this->listPatients.push_back(p) ;
			update_patients_database() ;
		}

		void delete_patient(size_t index) {
			this->listPatients.erase(this->listPatients.begin() + (index)) ;
			update_patients_database() ;
		}

		// Check if patient id is in database
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
			std::vector<std::string> listRadio ;

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
				} else if (line.substr(0, line.find('=')) == "listRadio") {
					std::string section {line.substr(line.find('=') +1)} ;
					std::string temp ;
					for (int iter=0; iter<section.size() ; iter++) {
						if (section[iter] == ' ') {
							listRadio.push_back(temp) ;
							temp.clear() ;
						} else {
							temp += section[iter] ;
						}
					}
					if (!temp.empty()) {
						listRadio.push_back(temp) ;
						temp.clear() ;
					}
				} else if (line == "#End") {
					listPatients.push_back(Patient(name, surname, ssn, password, listRadio)) ;
					listRadio.clear() ;
				}
			}
			file.close() ;

			return listPatients ;
		}

		// Rewrite new version of patients database
		void update_patients_database() {
			std::vector<Patient> patients = this->listPatients ;
			std::string path {"data/patients.txt"} ;
			std::ofstream file ;
			file.open(path, std::ios::trunc) ;
			if (!file.is_open()) {
				std::cout << "Could not update patients.txt file" << std::endl ;
				exit(1) ;
			}
			for (size_t i=0 ; i<patients.size() ; i++) {
				file << "#Begin\n" ;
				file << "name=" << patients[i].get_name() << "\n" ;
				file << "surname=" << patients[i].get_surname() << "\n" ;
				file << "ssn=" << patients[i].get_ssn() << "\n" ;
				file << "password=" << patients[i].get_password() << "\n" ;
				file << "listRadio=" ;
				for (size_t j=0 ; j<patients[i].get_listRadiographies().size() ; j++) {
					file << patients[i].get_listRadiographies()[j] << " " ;
				} file << "\n" ;
				file << "#End\n\n" ;
			}
			file.close() ;
		}



		// ----------------------------------------- //
		// --- Doctors database handling methods --- //
		// ----------------------------------------- //

		void set_listDoctors() {
			this->listDoctors = upload_doctors_database() ;
		}

		std::vector<Doctor> get_listDoctors() {
			return this->listDoctors ;
		}

		Doctor get_doctor(int index) {
			return get_listDoctors()[index] ;
		}

		int get_doctor_by_cnomId(std::string cnomId) {
			std::vector<Doctor> list {get_listDoctors()} ;
			for (size_t i=0 ; i<list.size() ; i++) {
				if (list[i].get_cnomId() == cnomId) {
					return i ;
				}
			}
			return -1 ;
		}

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

		void add_patient_to_listPatients(std::string cnomId, std::string patientId) {
			size_t index {(size_t)(get_doctor_by_cnomId(cnomId))} ;
			DatabaseHandling::listDoctors[index].add_patient(patientId) ;
			DatabaseHandling::update_doctors_database() ;
			DatabaseHandling::upload_doctors_database() ;
		}

		void delete_patient_from_listPatients(std::string cnomId, std::string patientID) {
			size_t index {(size_t)(get_doctor_by_cnomId(cnomId))} ;
			DatabaseHandling::listDoctors[index].delete_patient(patientID) ;
			DatabaseHandling::update_doctors_database() ;
			DatabaseHandling::upload_doctors_database() ;
		}

		// Extracts doctors data from database
		std::vector<Doctor> upload_doctors_database() {
			std::vector<Doctor> listDoctors ;
			std::string name, surname, cnomId, password ;
			std::vector<std::string> listPatients ;

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
				}else if (line.substr(0, line.find('=')) == "listPatients") {
					std::string section {line.substr(line.find('=') +1)} ;
					std::string temp ;
					for (int i=0 ; i<section.size() ; i++) {
						if (section[i] == ' ') {
							listPatients.push_back(temp) ;
							temp.clear() ;
						} else {
							temp += section[i] ;
						}
					}
					if (!temp.empty()) {
						listPatients.push_back(temp) ;
						temp.clear() ;
					}
				} else if (line == "#End") {
					listDoctors.push_back(Doctor(name, surname, password, cnomId, listPatients)) ;
					listPatients.clear() ;
				}
			}
			file.close() ;

			return listDoctors ;
		}


		// Rewrite new version of doctors database
		void update_doctors_database() {
			std::vector<Doctor> listDoctors {this->listDoctors} ;
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
				file << "listPatients=" ;
				for (int j=0 ; j<listDoctors[i].get_listPatients().size() ; j++) {
					file << listDoctors[i].get_listPatients()[j] << " " ;
				}file << "\n" ;
				file << "#End\n\n" ;
			}
			file.close() ;
		}



		// ----------------------------------------------- //
		// --- Radiographies database handling methods --- //
		// ----------------------------------------------- //

		std::vector<Radiography> get_listRadiographies() {
			return this->listRadiographies ;
		}

		void set_listRadiographies() {
			this->listRadiographies = upload_radiographies_database() ;
		}

		void add_radiography(Radiography radio) {
			this->listRadiographies.push_back(radio) ;
			DatabaseHandling::update_radiographies_database() ;
			DatabaseHandling::upload_radiographies_database() ;
		}

		void add_radiography_to_patient(std::string patientID, std::string radioID) {
			this->listPatients[get_patient_by_ssn(patientID)].add_radiography_to_listRadiographies(radioID) ;
			DatabaseHandling::update_patients_database() ;
			DatabaseHandling::upload_patients_database() ; 
		}

		void delete_radiography(std::string radioID) {
			for (size_t i=0 ; i<this->listRadiographies.size() ; i++) {
				if (this->listRadiographies[i].get_id() == radioID) {
					this->listRadiographies.erase(this->listRadiographies.begin() + i) ;
					DatabaseHandling::update_patients_database() ;
					DatabaseHandling::upload_patients_database() ;
				}
			}
		}

		void delete_radiography_from_patient(std::string patientID, std::string radioID) {
			this->listPatients[get_patient_by_ssn(patientID)].remove_radiography_from_listRadiographies(radioID) ;
			DatabaseHandling::update_patients_database() ;
			DatabaseHandling::upload_patients_database() ;
		}

		void add_snapshot_to_radiography(std::string radioID, Snapshot snap) {
			int index {get_radiography_by_id(radioID)} ;
			this->listRadiographies[index].add_snap(snap) ;
			DatabaseHandling::update_radiographies_database() ;
			DatabaseHandling::upload_radiographies_database() ;
		}

		void delete_snapshot_from_radiography(std::string radioID, std::string snapID) {
			int radioIndex {DatabaseHandling::get_radiography_by_id(radioID)} ;
			int snapIndex {this->listRadiographies[radioIndex].get_snap_index(snapID)} ;
			this->listRadiographies[radioIndex].del_snap(snapIndex) ;
			DatabaseHandling::update_radiographies_database() ;
			DatabaseHandling::upload_radiographies_database() ;
		}

		void change_radiography_state(std::string radioID) {
			int radioIndex {DatabaseHandling::get_radiography_by_id(radioID)} ;
			if (this->listRadiographies[radioIndex].get_state() == done) {
				this->listRadiographies[radioIndex].set_state(pending) ;
			} else {
				this->listRadiographies[radioIndex].set_state(done) ;
			}
			DatabaseHandling::update_radiographies_database() ;
			DatabaseHandling::upload_radiographies_database() ;
		}


		int get_radiography_by_id(std::string id) {
			for (size_t i=0 ; i<this->listRadiographies.size() ; i++) {
				if (this->listRadiographies[i].get_id() == id) {
					return i ;
				}
			}
			return -1 ;
		}

		Radiography get_radiography(std::string id) {
			int index {get_radiography_by_id(id)} ;
			return this->listRadiographies[index] ;
		}

		// Extracts radiographies from database
		std::vector<Radiography> upload_radiographies_database() {
            std::vector<Radiography> radiographies ;
			std::string id ;
            radiographyType type ;
	        radiographyState state ;
            size_t day ;
            size_t month ;
            size_t year ;
            std::vector<std::string> snapID ;
            std::vector<std::string> snapPath ;
            std::string repContent ;
            std::ifstream file ;
			std::string  path {"data/radiographies.txt"} ;
			
			file.open(path, std::ios::in) ;
			if (!file.is_open()) {
				std::cout << "Could not upload radiographies.txt file" << std::endl ;
				exit(1) ;
			}

			std::string line ;
			while (getline(file, line)) { 
				if (line == "#Begin") {
					continue ;
				} else if (line.substr(0, line.find('=')) == "id") {
					id = line.substr(line.find('=') +1) ;
				} else if (line.substr(0, line.find('=')) == "type") {
					if (line.substr(line.find('=')+1) == "xRay") {
						type = xRay ;
					} else if (line.substr(line.find('=') +1) == "MRI") {
						type = MRI ;
					} else {
						type = ultrasound ;
					}
				} else if (line.substr(0, line.find('=')) == "state") {
					if (line.substr(line.find('=') +1) == "done") {
						state = done ;
					} else {
						state = pending ;
					}
				} else if (line.substr(0, line.find('=')) == "day") {
					day = stoi(line.substr(line.find('=') +1)) ;
                } else if (line.substr(0, line.find('=')) == "month") {
					month = stoi(line.substr(line.find('=') +1));
                } else if (line.substr(0, line.find('=')) == "year") {
					year = stoi(line.substr(line.find('=') +1)) ;
                } else if (line.substr(0, line.find('=')) == "snapID") {
					std::string section {line.substr(line.find('=') +1)} ;
					std::string temp ;
					for (size_t i=0 ; i<section.size() ; i++) {
						if (section[i] == ' ') {
							snapID.push_back(temp) ;
							temp.clear() ;
						} else {
							temp += section[i] ;
						}
					}
					if (!temp.empty()) {
						snapID.push_back(temp) ;
						temp.clear() ;
					}
                } else if (line.substr(0, line.find('=')) == "snapPath") {
					std::string section {line.substr(line.find('=') +1)} ;
					std::string temp ;
					for (size_t i=0 ; i<section.size() ; i++) {
						if (section[i] == ' ') {
							snapPath.push_back(temp) ;
							temp.clear() ;
						} else {
							temp += section[i] ;
						}
					}
					if (!temp.empty()) {
						snapPath.push_back(temp) ;
						temp.clear() ;
					}
                } else if (line.substr(0, line.find('=')) == "rep") {
					repContent = line.substr(line.find('=') +1) ;
				} else if (line == "#End") {
					std::vector<Snapshot> snaps ;
					for (size_t i=0 ; i<snapID.size() ; i++) {
						snaps.push_back(Snapshot(snapID[i], snapPath[i])) ;
					}
					snapID.clear() ;
					snapPath.clear() ;
					Report rep(repContent) ;
					radiographies.push_back(Radiography(id, type, state, day, month, year, snaps, rep)) ;
				}
			}
			file.close() ;

			return radiographies ;
		}

		// Rewrite new version of doctors database
		void update_radiographies_database() {
			std::vector<Radiography> radiographies {this->listRadiographies} ;
			std::string path {"data/radiographies.txt"} ;
			std::ofstream file ;
			file.open(path, std::ios::trunc) ;
			if (!file.is_open()) {
				std::cout << "Could not update radiographies.txt file" << std::endl ;
				exit(1) ;
			}
			for (size_t i=0 ; i<radiographies.size() ; i++) {
				Radiography radio {radiographies[i]} ;
				file << "#Begin\n" ;
				file << "id=" << radio.get_id() << "\n" ;
				file << "type=" ;
				if (radio.get_type() == xRay) {
					file << "xRay\n" ;
				} else if (radio.get_type() == MRI) {
					file << "MRI\n" ;
				} else {
					file << "ultrasound\n" ;
				}
				file << "state=" ;
				if (radio.get_state() == done) {
					file << "done\n" ;
				} else {
					file << "pending\n" ;
				}
				file << "day=" << radio.get_day() << "\n" ;
				file << "month=" << radio.get_month() << "\n" ;
				file << "year=" << radio.get_year() << "\n" ;
				file << "snapID=" ;
				for (size_t j=0 ; j<radio.get_snaps().size() ; j++) {
					file << radio.get_snap(j).get_id() << " " ;
				} file << "\n" ;
				file << "snapPath=" ;
				for (size_t j=0 ; j<radio.get_snaps().size() ; j++) {
					file << radio.get_snap(j).get_path() << " " ;
				} file << "\n" ;
				
				file << "rep=" << radiographies[i].get_report().get_content() << "\n" ;
				file << "#End\n\n" ;
			}
			file.close() ;
		}
} ;


#endif