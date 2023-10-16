#include <iostream>
#include <queue>
#include <mutex>
#include <semaphore>

#include "Customer.h"

using namespace std;

counting_semaphore semaphore{5};
mutex doctorMut;


void fct(const unsigned j){
    cout << "the doctor takes care of me, n°" << j << endl;

    this_thread::sleep_for(10000ms); // doctor doing its action

    cout << "finish n°" << j << endl;
    doctorMut.unlock();
}

void doctorAvailable(queue<Customer> & queue) {
    this_thread::sleep_for(500ms); // wait for the first client

    while (true) {
        if (doctorMut.try_lock()) {
            const Customer nextCustomer = queue.front();
            queue.pop();
            nextCustomer.doAction(&fct);

            semaphore.release();
        }

        this_thread::sleep_for(100ms);
    }
}

int main() {
    unsigned j = 0;
    queue<Customer> queue;

    thread processUpdate(doctorAvailable, ref(queue));

    while(true) {
        ++j;

        if(semaphore.try_acquire()){
            queue.push(Customer(j));
            cout << "new customer in the queue !" << endl;

        } else {
            cout << "block n°" << j << endl;
        }

        this_thread::sleep_for(5000ms);
    }

    Customer::joinThreads();
    processUpdate.join();

    return 0;
}
