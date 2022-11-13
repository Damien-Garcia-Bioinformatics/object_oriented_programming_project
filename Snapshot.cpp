#include <iostream>
#include "class.hpp"

// --- Set functions --- //
void Snapshot::set_id(size_t id) {
	this->id = id ;
}
void Snapshot::set_path(std::string path) {
	this->path = path ;
}

// --- Get functions --- //
size_t Snapshot::get_id() {
	return this->id ;
}
std::string Snapshot::get_path() {
	return this->path ;
}