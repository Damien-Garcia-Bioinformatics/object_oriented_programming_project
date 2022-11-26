// Object Oriented Programming - TP Project
// GARCIA Damien
// ECHELARD Florian
// M2BB

// Object Oriented Programming - TP Project
// GARCIA Damien
// ECHELARD Florian
// M2BB

#ifndef __RADIOGRAPHY__
#define __RADIOGRAPHY__


#include <string>
#include <vector>

#include "snapshot.hpp"
#include "report.hpp"


// Type definition :
typedef enum radiographyType {xRay, ultrasound, MRI} radiographyType ;
typedef enum radiographyState {done, pending} radiographyState ;


class Radiography {
    private :
        // Attributes :
        std::string id ;
    	radiographyType type ;
		radiographyState state ;
        size_t day ;
        size_t month ;
        size_t year ;
        std::vector<Snapshot> snaps ;
        Report rep ;

    public :
        // Set functions :
        void set_id(std::string id) {
            this->id = id ;
        }
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
        std::string get_id() {
            return this->id ;
        }
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
        Radiography(std::string id) {
            set_id(id) ;
        }

        Radiography(std::string id, radiographyType type, radiographyState state, size_t day, size_t month, size_t year) {
            set_id(id) ;
            set_type(type) ;
            set_state(state) ;
            set_day(day) ;
            set_month(month) ;
            set_year(year) ;
        }

        Radiography(std::string id, radiographyType type, radiographyState state, size_t day, size_t month, size_t year, std::vector<Snapshot> snaps, Report rep) {
            set_id(id) ;
            set_type(type) ;
            set_state(state) ;
            set_day(day) ;
            set_month(month) ;
            set_year(year) ;
            set_snapshots(snaps) ;
            set_report(rep) ;
        }

        Radiography(std::string id, std::string type, std::string state, size_t day, size_t month, size_t year) {
            set_id(id) ;
            if (type == "xRay") {
                set_type(xRay) ;
            } else if (type == "MRI") {
                set_type(MRI) ;
            } else {
                set_type(ultrasound) ;
            }
            if (state == "done") {
                set_state(done) ;
            } else {
                set_state(pending) ;
            }
            set_day(day) ;
            set_month(month) ;
            set_year(year) ;
            std::vector<Snapshot> snaps ;
            set_snapshots(snaps) ;
            Report rep ;
            set_report(rep) ;
        }

        // Destructor
        ~Radiography() { }

        // Other functions :

        // Returns the index of a specific snapshot in the list of spnapshots.
        int get_snap_index(std::string id) {
            for (int i=0 ; i<(int)(this->get_snaps().size()) ; i++) {
                if (this->get_snaps()[i].get_id() == id) {
                    return i ;
                }
            }
            return -1 ;
        }

        // Adds a snap in list.
        void add_snap(Snapshot snap) {
            this->snaps.push_back(snap) ;
        }

        // Removes a snap by its position in list of snapshots.
        void del_snap(size_t index) {
            this->snaps.erase(snaps.begin() + index) ;
        }

        // Adds or replaces the report attribute.
        void add_report(Report rep) {
            this->rep = rep ;
        }

        // Deletes the report attribute value.
        void del_report() {
            this->rep = Report("") ;
        }
} ;


#endif