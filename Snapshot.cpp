#include <iostream>
#include "class.hpp"

// --- Set functions --- //
void Snapshot::set_id(int id) {
	this->id = id ;
}
void Snapshot::set_path(std::string path) {
	this->path = path ;
}

// --- Get functions --- //
int Snapshot::get_id() {
	return this->id ;
}
std::string Snapshot::get_path() {
	return this->path ;
}