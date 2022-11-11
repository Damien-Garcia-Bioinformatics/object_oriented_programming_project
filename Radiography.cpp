#include <string>
#include <vector>
#include "class.hpp"

// --- Set --- //

void Radiography::set_type(radiographyType type) {
	this->type = type ;
}
void Radiography::set_state(radiographyState state) {
	this->state = state ;
}
void Radiography::set_day(int day) {
	this->day = day ;
}
void Radiography::set_month(int month) {
	this->month = month ;
}
void Radiography::set_year(int year) {
	this->year = year ;
}
void Radiography::set_listSnapshot(std::vector<Snapshot> listSnapshot) {
	this->listSnapshot = listSnapshot ;
}

// --- Get --- //
radiographyType Radiography::get_type() {
	return this->type ;
}
radiographyState Radiography::get_state(){
	return this->state ;
}
int Radiography::get_day() {
	return this-> day ;
}
int Radiography::get_month() {
	return this->month ;
}
int Radiography::get_year() {
	return this->year ;
}
std::vector<Snapshot> Radiography::get_listSnapshot() {
	return this->listSnapshot ;
}

// --- Constructor --- //
Radiography::Radiography(radiographyType type, radiographyState State, int day, int month, int year, std::vector<Snapshot> listSnapshot) {
	set_type(type) ;
	set_state(state) ;
	set_day(day) ;
	set_month(month) ;
	set_year(year) ;
	set_listSnapshot(listSnapshot) ;
}

// --- Other functions --- //
void Radiography::add_snapshot(Snapshot snap) {
	this->listSnapshot.push_back(snap) ;
}