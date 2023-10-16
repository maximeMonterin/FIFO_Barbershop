#include <iostream>
#include <queue>
#include <mutex>
#include <semaphore>

#include "Customer.h"

using namespace std;

counting_semaphore semaphore{5};
mutex doctorMut;


void fct(unsigned j){
    cout << "the doctor takes care of me, n°" << j << endl;

    this_thread::sleep_for(40000ms); // do its action

    cout << "finish n°" << j << endl;
    doctorMut.unlock();
}

int main() {
    unsigned j = 0;
    queue<Customer> queue;

    while(j < 100) {
        ++j;

        if(semaphore.try_acquire()){
            queue.push(Customer(j));
            cout << "new customer in the queue !" << endl;

        } else {
            cout << "block n°" << j << endl;
        }

        if (doctorMut.try_lock()) {
            const Customer nextCustomer = queue.front();
            queue.pop();
            nextCustomer.doAction(&fct);

            semaphore.release();
        }

        this_thread::sleep_for(5000ms);
    }

    Customer::joinThreads();

    return 0;
}
