#include <iostream>
#include <queue>
#include <mutex>
#include <semaphore>

#include "Customer.h"

/*
* CONSTANTS & GLOBAL VARIABLES
*/

#define TIME_BETWEEN_EACH_CLIENTS 5000ms
#define TIME_DOCTOR_ACTIVITY 10000ms

std::counting_semaphore semaphore{5};
std::mutex doctorMut;

/*
* FUNCTIONS
*/

void doctorActivity(const unsigned id){
    std::cout << "the doctor takes care of me, n°" << id << std::endl;

    // doctor doing its action
    std::this_thread::sleep_for(TIME_DOCTOR_ACTIVITY);

    std::cout << "doctor finish client n°" << id << std::endl;
    doctorMut.unlock();
}

void doctorAvailable(queue<Customer> & queue) {
    // wait for the first client (process in the main thread)
    // very bad way to do this but no time to fix this in a better clean version
    std::this_thread::sleep_for(700ms);

    while (true) {
        if (doctorMut.try_lock()) {
            // get the next client in the queue and launch its action
            const Customer nextCustomer = queue.front();
            nextCustomer.doAction(&doctorActivity);

            // release the queue and the semaphore counter
            queue.pop();
            semaphore.release();
        }

        std::this_thread::sleep_for(100ms);
    }
}

/*
* MAIN PROGRAM (ENTRY POINT)
*/

int main() {
    unsigned clientCounter = 0;
    std::queue<Customer> queue;

    // launch the thread that manage the doctor process
    std::thread processUpdate(doctorAvailable, ref(queue));

    // main program manage the customer flow in the shop
    while(true) {
        ++clientCounter;

        if(semaphore.try_acquire()){
            queue.push(Customer(clientCounter));
            std::cout << "new customer in the queue !" << std::endl;

        } else {
            std::cout << "client n°" << clientCounter << " leaves the shop !" << std::endl;
        }

        std::this_thread::sleep_for(TIME_BETWEEN_EACH_CLIENTS);
    }

    Customer::joinThreads();
    processUpdate.join();

    return 0;
}
