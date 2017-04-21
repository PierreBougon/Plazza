//
// Created by peau_c on 4/21/17.
//

#include "Mutex.hpp"

plazza::Mutex::Mutex() {
}

plazza::Mutex::~Mutex() {
	mutex.unlock();
}

void plazza::Mutex::lock() {
	mutex.lock();
}

void plazza::Mutex::unlock() {
	mutex.unlock();
}
