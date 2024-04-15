#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <fstream>


using namespace std;

float uniformRand();
double expDist(float t);
float const MAX_TIME = 175200;//20 years in hours

int main() {
    vector<double> server1;
    vector<double> server2;
    double totTime = 0;//total time server has been running based on failure events
    double failTime = 0;//time server will fail
    double restoreTime = 0;//time server operation will be restored
    double distance = 0;//distance between server 1 down time and server 2 downtime. If number is <= 0 then times overlap
    double bothFail = 0;//stores the sum of all double failure times to divide from total number of trials to find the average fail time
    bool overlap = false;//if fail times of both servers overlap then true

    ofstream File("Question2PartA_Output.txt");//Part A will output results in a file as well as console

//////////////////////Start Part A/////////////////////////////////////////////////////////

    cout << "************Begin Part A***************" << endl;
    srand(time(0));
    while (totTime <= MAX_TIME ) {
		//first server trial to 20 years
        failTime = (expDist(500) + totTime);//getting fail time + previous restore time
        restoreTime = failTime + 10;//add 10 hours for restore time
        server1.push_back(failTime);
        server1.push_back(restoreTime);
        totTime = restoreTime;
    }
    totTime = 0;//reset counters
    failTime = 0;
    restoreTime = 0;
	
	//second server trial to 20 years
    srand(time(0) + 100);//change srand manually because it's too quick to get a new srand value from clock
    while (totTime <= MAX_TIME ) {

        failTime = (expDist(500) + totTime);
        restoreTime = failTime + 10;
        server2.push_back(failTime);
        server2.push_back(restoreTime);
        totTime = restoreTime;
    }
	
	//prints server 1 and server 2 results to console and a file 
    for (auto i = server1.begin(); i != server1.end(); i += 2) {
        File << fixed << setprecision(1) << "Server 1 Fail Time: " << *i << "  Restore Time: " << *(i + 1) << endl;
        cout << fixed << setprecision(1) << "Server 1 Fail Time: " << *i << "  Restore Time: " << *(i + 1) << endl;
    }

    for (auto i = server2.begin(); i != server2.end(); i += 2) {
        File << fixed << setprecision(1) << "Server 2 Fail Time: " << *i << "  Restore Time: " << *(i + 1) << endl;
        cout << fixed << setprecision(1) << "Server 2 Fail Time: " << *i << "  Restore Time: " << *(i + 1) << endl;
    }
    File.close();
//////////////////////////End Part A. Begin Part B///////////////////////////////////////

    cout <<"\n\n**************Begin Part B****************\n" << endl;
    for (int k = 0; k < 1000; k++) {//1000 trials
        totTime = 0;//clearing all variables from previous calculations
        failTime = 0;
        restoreTime = 0;
        server1.clear();//clearing vectors
        server2.clear();
        overlap = false;//reset flag

        srand(time(0)*(k+1));//change seed every loop with k
        while (totTime <= MAX_TIME) {

            failTime = (expDist(500) + totTime);
            restoreTime = failTime + 10;
            server1.push_back(failTime);
            server1.push_back(restoreTime);
            totTime = restoreTime;
        }
        totTime = 0;
        failTime = 0;
        restoreTime = 0;

        srand(time(0)*(k*100));
        while (totTime <= MAX_TIME) {

            failTime = (expDist(500) + totTime);
            restoreTime = failTime + 10;
            server2.push_back(failTime);
            server2.push_back(restoreTime);
            totTime = restoreTime;
        }

        for (auto i = server1.begin(); i != server1.end() && !overlap; i += 2) {
            for (auto j = server2.begin(); j != server2.end() && !overlap; j += 2) {
                distance = max(*i, *j) - min(*(i + 1), *(j + 1));//subtracts the higher value of the start of both server failures
                //from the lowest value of the restoration time of both servers to give the distance between the two vectors.
                //If the distance is non-zero positive integer then the two times do not overlap. If the distance is
                //zero or negative then the times overlap.
                if (distance <= 0) {
                    cout << "Both servers failed at " << *i << endl;
                    bothFail += *i;//sum the failure time
                    overlap = true;//end loop when failure occurs to avoid further calculations
                }
            }
        }
    }
    cout << "The average failure time is: " << (bothFail/1000) << endl;





    return 0;
}

//returns random float from 0 to 1
float uniformRand() {
    return ((float) rand()/RAND_MAX);//
}

//returns fail time based on exponential distribution with MTBF of 500
double expDist(float t) {
    float x, z;

    z = uniformRand();
    x = (-t)*log(z);
    return (x);
}
