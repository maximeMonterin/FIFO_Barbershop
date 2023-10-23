# FIFO_Barbershop 💈🧑‍🦰

This C++ school project delves into the realms of threads and mutex to solve the classic barbershop problem. Originally proposed by Dijkstra and later discussed in Silberschatz and Galvin's Operating Systems Concepts, this project brings the theoretical problem into practical coding.

## Introduction

Let's tailor this issue to a system that closely mirrors it.

### The Barbershop Problem 💇‍♂️💺

Picture a barbershop with a waiting room equipped with n chairs and the sacred barber room housing the all-important barber chair. Here's the scenario: If no customers await their turn, the barber gracefully dozes off. But, the moment a customer strolls in and all the chairs are occupied, the customer decides to gracefully exit the shop. If the barber is busy attending to someone else but there are vacant chairs, the customer happily takes a seat. However, if the barber is in a deep slumber, it's the customer's responsibility to wake them up.

To make the problem a little more concrete, the following information has been added:

- Customer threads will be calling a function named `getHairCut`.
- Should a customer arrive when the shop is bursting with activity, they can invoke `balk`, a function that doesn't bother to return.
- The barber thread, on the other hand, gracefully invokes `cutHair`.
- When the barber executes `cutHair`, precisely one thread should concurrently invoke `getHairCut`.

### The Doctor's Office Problem 🚑👩‍⚕️

Imagine a bustling doctor's office with a waiting room equipped with n chairs and the doctor's consultation room containing the prestigious doctor's chair. Here's the scenario: If the doctor has no patients waiting, they might take a quick break. However, the moment a patient enters the office and all chairs are occupied, the patient decides to patiently wait. If the doctor is busy examining another patient but there are empty chairs, the new patient takes a seat. But if the doctor is currently unavailable, it's the patient's responsibility to gently request their attention.
  
## Source Links

Dig deeper into the intricacies of synchronization and semaphores with the guidance of the "Little Book Of Semaphores" [PDF link](https://greenteapress.com/semaphores/LittleBookOfSemaphores.pdf). Let the semaphore journey begin! 📚🤿✨
