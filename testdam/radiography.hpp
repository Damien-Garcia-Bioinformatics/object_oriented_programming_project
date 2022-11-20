#ifndef __RADIOGRAPHY__
#define __RADIOGRAPHY__


#include <iostream>
#include <string>
#include <vector>
#include "snapshot.hpp"
#include "report.hpp"


typedef enum radiographyType {xRay, ultrasound, MRI} radiographyType ;
typedef enum radiographyState {done, pending} radiographyState ;

class Radiography {
    private :
        // Attributes :
    	radiographyType type ;
		radiographyState state ;
        size_t day ;
        size_t month ;
        size_t year ;
        std::vector<Snapshot> snaps ;
        Report rep ;

    public :
        // Set functions :
        void set_type(radiographyType type) {
            this->type = type ;
        }
        void set_state(radiographyState state) {
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
        void set_snapshots(std::vector<Snapshot> snaps) {
            this->snaps = snaps ;
        }

        // Get functions :
        radiographyType get_type() {
            return this->type ;
        }
        radiographyState get_state() {
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
        std::vector<Snapshot> get_snaps() {
            return this->snaps ;
        }
        Snapshot get_snap(size_t index) {
            return this->snaps.at(index) ;
        }

        // Constructor :
        Radiography(radiographyType type, radiographyState state, size_t day, size_t month, size_t year) {
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
            this->snaps.push_back(Snapshot(id, path)) ;
        }
        void del_snap(std::vector<Snapshot> &snaps, size_t index) {
            this->snaps.erase(snaps.begin() + index) ;
        }
        void add_report(std::string content, std::string password) {
            this->rep = (Report(content,password)) ;
        }
} ;


#endif