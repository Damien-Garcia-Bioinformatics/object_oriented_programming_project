#ifndef __RADIOGRAPHY__
#define __RADIOGRAPHY__


#include <iostream>
#include <string>
#include <vector>
#include "snapshot.hpp"
#include "report.hpp"


//typedef enum std::string {xRay, ultrasound, MRI} std::string ;
//typedef enum std::string {done, pending} std::string ;

class Radiography {
    private :
        // Attributes :
    	std::string type ;
	    std::string state ;
        size_t day ;
        size_t month ;
        size_t year ;
        Snapshot snaps ;
        Report rep ;

    public :
        // Set functions :
        void set_type(std::string type) {
            this->type = type ;
        }
        void set_state(std::string state) {
            this->state = state ;
        }
        void set_day(size_t day) {
            this->day = day ;
        }
        void set_month(size_t month) {
            this->month = month ;
        }
        void set_year(size_t year) {
            this->year = year ;
        }
        void set_report(Report rep) {
            this->rep = rep ;
        }
        void set_snapshots(Snapshot snaps) {
            this->snaps = snaps ;
        }

        // Get functions :
        std::string get_type() {
            return this->type ;
        }
        std::string get_state() {
            return this->state ;
        }
        size_t get_day() {
            return this->day ;
        }
        size_t get_month() {
            return this->month ;
        }
        size_t get_year() {
            return this->year ;
        }
        Report get_report() {
            return this->rep ;
        }
        Snapshot get_snaps() {
            return this->snaps ;
        }
      

        // Constructor :
        Radiography(std::string type, std::string state, size_t day, size_t month, size_t year) {
            set_type(type) ;
            set_state(state) ;
            set_day(day) ;
            set_month(month) ;
            set_year(year) ;
        }

        // Destructor
        ~Radiography() { }

        // Other functions :
        void add_snap(std::string id, std::string path) {
            this->snaps = Snapshot(id, path) ;
        };
        
        void add_report(std::string content, std::string password) {
            this->rep = (Report(content,password)) ;
        }
} ;


class List_Radiography{
	std::vector<Radiography> listRadio;
	
	public :
        void get_test(){for(Radiography radio : listRadio) std::cout << radio.get_snaps().get_path() << std::endl;}

		List_Radiography(std::string filepath){
			this->listRadio = download_radiolist(filepath);
		}
		
		~List_Radiography(){
			std::cout << "Database purged" << std::endl;
		}
		
		std::vector<Radiography> download_radiolist(std::string path){
            std::vector<Radiography> radiographies;
            std::string type ;
	        std::string state ;
            size_t day ;
            size_t month ;
            size_t year ;
            std::string snapID ;
            std::string snapPath ;
            std::string repCnt ;
			std::string repPwd;
            std::ifstream file ;
			file.open(path, std::ios::in) ;
			if (!file.is_open()) {
				std::cout << "Could not download" << std::endl ;
				exit(1) ;
			}

			std::string line ;
			while (getline(file, line)) { 
				if (line == "#Begin") {
					continue ;
				} else if (line.substr(0, line.find('=')) == "type") {
					type = line.substr(line.find('=') +1) ;
				} else if (line.substr(0, line.find('=')) == "state") {
					state = line.substr(line.find('=') +1) ;
				} else if (line.substr(0, line.find('=')) == "day") {
					day = stoi(line.substr(line.find('=') +1)) ;
                } else if (line.substr(0, line.find('=')) == "month") {
					month = stoi(line.substr(line.find('=') +1));
                } else if (line.substr(0, line.find('=')) == "year") {
					year = stoi(line.substr(line.find('=') +1)) ;
                } else if (line.substr(0, line.find('=')) == "snapID") {
					snapID = line.substr(line.find('=') +1) ;
                } else if (line.substr(0, line.find('=')) == "snapPath") {
					snapPath = line.substr(line.find('=') +1) ;
                } else if (line.substr(0, line.find('=')) == "repCnt") {
					repCnt = line.substr(line.find('=') +1) ;
                } else if (line.substr(0, line.find('=')) == "repPwd") {
					repPwd = line.substr(line.find('=') +1) ;
				} else if (line == "#End") {
                    Radiography radio(type,state,day,month,year);
                    radio.add_snap(snapID, snapPath);
                    radio.add_report(repCnt, repPwd);
					radiographies.push_back(radio) ;
				}
			}
			file.close() ;

			return radiographies ;
		}
};

#endif
