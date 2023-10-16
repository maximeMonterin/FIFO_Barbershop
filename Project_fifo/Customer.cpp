#include "Customer.h"

#include <iostream>

using namespace std;

std::vector<std::thread> threads;


Customer::Customer(const unsigned j) {
    this->j = j;
    cout << "Hello, I'm the client n°" << j << endl;
}

void Customer::doAction(void (* fct)(unsigned)) const {
    threads.push_back(thread(fct, this->j));
}

void Customer::joinThreads() {
    for (thread & current : threads) {
        current.join();
    }
}
