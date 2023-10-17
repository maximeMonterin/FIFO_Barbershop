#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <vector>
#include <thread>


class Customer {
    private:
        // FIELDS
        unsigned customerID;

    public:
        // CONSTRUCTOR
        Customer(const unsigned id);


        // METHODS
        void doAction(void (* threadFunction)(unsigned)) const;
        static void joinThreads();
};

#endif // CUSTOMER_H
