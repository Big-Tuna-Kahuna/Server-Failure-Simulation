# Server-Failure-Simulation
Simulates the failure and restoration of two servers over a 20-year period, using exponential distribution to determine the mean time between failures (MTBF) It simulates these failures in two parts: Part A details individual server failures and restorations while Part B runs multiple trials to calculate the average time at which both servers fail simultaneously.

Features
Part A: Simulates and logs each server's failures and restoration times over 20 years.
Part B: Conducts 1000 trials to determine the average time both servers fail simultaneously, considering the overlap of their downtime.
Outputs results to both the console and a text file for record-keeping and analysis.

Requirements
C++11 compatible compiler
C++ Standard Library (cmath for mathematical functions and vector for dynamic data handling)
Usage
The program does not require any command line arguments and can be executed directly after compilation.

Compilation Command
g++ -o server_failure_simulation simulation.cpp -std=c++11

Running the Program
After compilation, run the program using:
./server_failure_simulation

Output
Part A: Outputs the fail time and restore time for each server to the console and to a file named Question2PartA_Output.txt.
Part B: Outputs the average time of simultaneous failure to the console.

Explanation of Functions
float uniformRand(): Generates a uniform random number between 0 and 1.
double expDist(float t): Generates a fail time based on an exponential distribution; t is the mean time between failures, used here to simulate server failures.

Internal Workings
The simulation uses vectors to track each server's fail and restore times.
Exponential distribution is used to simulate the time between failures with a mean time of 500 hours.
The program calculates overlaps in downtime to find instances where both servers fail at the same time.

Important Considerations
The program's calculations are based on an assumed MTBF of 500 hours.
Random seeds are manually adjusted to ensure variability between trials in Part B.
The constant MAX_TIME defines the total simulation time as 175200 hours (20 years).
This simulation can be particularly useful for system administrators, network engineers, and reliability engineers to estimate risks and prepare for potential downtimes in server operations. It provides a statistical basis for understanding how often critical overlaps in server failures might occur.
