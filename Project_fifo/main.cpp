#include <iostream>
#include <vector>
#include <mutex>
#include <semaphore>
#include <thread>

using namespace std;

counting_semaphore semaphore{5};

void fct(unsigned j){
    cout << "test n°" << j << endl;
    cout << "test id : " << this_thread::get_id() << endl;

    this_thread::sleep_for(100000ms); // do its action

    cout << "finish n°" << j << endl;
    semaphore.release();
}

int main()
{
    unsigned j = 0;
    vector<thread> threads;

    while(j < 100) {
        ++j;

        if(semaphore.try_acquire()){
            threads.push_back(thread(fct, j));
        }
        else{
            cout << "block n°" << j << endl;
        }

        this_thread::sleep_for(5000ms);
    }

    for (thread & customer : threads) {
        customer.join();
    }

    return 0;
}
