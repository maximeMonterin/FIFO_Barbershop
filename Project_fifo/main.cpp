#include <iostream>
#include <queue>
#include <mutex>
#include <semaphore>

#include "Customer.h"

/*
* CONSTANTS & GLOBAL VARIABLES
*/

using namespace std::chrono_literals;

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

void doctorAvailable(std::queue<Customer> & queue) {
    while (true) {
        // if the doctor doesn't take care of a client and there are no customers in the queue,
        // the doctor sleeping as the problem subject
        if (queue.size() == 0 && doctorMut.try_lock()) {
            doctorMut.unlock();

            std::cout << "The doctor sleeping" << std::endl;
            std::this_thread::sleep_for(700ms);

        } else if (doctorMut.try_lock()) {
            // get the next client in the queue and launch its action
            const Customer nextCustomer = queue.front();
            nextCustomer.doAction(&doctorActivity);

            // release the queue and the semaphore counter
            queue.pop();
            semaphore.release();
        }

        // limit "FPS" of the thread no needs to refresh fast
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
