#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <vector>
#include <thread>

class Customer {
    private:
        unsigned j;

    public:
        Customer(const unsigned j);
        void doAction(void (* fct)(unsigned)) const;

        static void joinThreads();
};

#endif // CUSTOMER_H
