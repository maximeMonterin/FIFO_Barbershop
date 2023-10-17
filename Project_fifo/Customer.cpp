#include "Customer.h"

#include <iostream>


// once again, very bad way to stock all customers threads and join them in the end of the program
// but no time to do better clean version
std::vector<std::thread> threads;

/*
* CUSTOMER CLASS IMPLEMENTETION
*/

Customer::Customer(const unsigned id) {
    this->customerID = id;
    std::cout << "Hello, I'm the client n°" << this->customerID << std::endl;
}

// launch the customer thread
void Customer::doAction(void (* threadFunction)(unsigned)) const {
    threads.push_back(std::thread(threadFunction, this->customerID));
}

// join all customer threads launch since the program start
void Customer::joinThreads() {
    for (std::thread & current : threads) {
        current.join();
    }
}
