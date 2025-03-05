
#include <ctime> // for time(0)
#include <iostream> // for cin and cout
#include <cmath> // for M_PI and others
#include <vector> // for vectors (duh)
#include <cstdlib> // for random
#include <cassert> // for assert in the tests() function
#include "TimeCode.h" // for timecode's (duh)

using namespace std;

struct DryingSnapShot {
	// This is a struct, it's like an object
	// that doesn't have any methods.
	// You can read more about them in the ZyBook
	// just search for "struct"
	string name;
	time_t startTime;
	TimeCode *timeToDry;
};

//get_time_remaining funtion to return the time remaining 
long long int get_time_remaining(DryingSnapShot dss){ 

	time_t currentTime = time(0); // get current time
    time_t elapsedTime = currentTime - dss.startTime; // get elapsed time by subtracting the start time from the current time

    long long int totalDryTime = dss.timeToDry->GetTimeCodeAsSeconds(); // get the total dry time
    long long int remainingTime = totalDryTime - elapsedTime; // get the remaining time by subtracting the elapsed time from total time
	long long int zero = 0;  // make a long long int that holds 0, so it can be used in max funtion

    return max(remainingTime,zero); //ensures that a negative value is never returned 
		// return the remaing time
}

string drying_snap_shot_to_string(DryingSnapShot dss){

	long long int remainingTime = get_time_remaining(dss); // get the time remaining for dss

    TimeCode remaining(0,0,remainingTime);// create TimeCode of remaining time
      if (remainingTime == 0) { // if the remaining time is 0, then that batch is done drying
        return "Batch-" + dss.name + " (takes " + dss.timeToDry->ToString() + " to dry) DONE!";

    } else { // if remaining time is not 0, then the batch is still drying
        return "Batch-" + dss.name + " (takes " + dss.timeToDry->ToString() + " to dry) time remaining: " + remaining.ToString();
    }

	
}

//calculate surface area of a sphere from given radius
double get_sphere_sa(double rad){
	return 4 * M_PI * pow(rad,2);
	
}


TimeCode *compute_time_code(double surfaceArea){ // create time for given surface area
	long long int dryingSeconds = static_cast<long long int>(surfaceArea);
    return new TimeCode(0, 0, dryingSeconds); // return time code
}

//testing 
void tests(){
	// test get_time_remaining
	DryingSnapShot dss;
	dss.startTime = time(0);
	TimeCode tc = TimeCode(0, 0, 7);
	dss.timeToDry = &tc;
	long long int ans = get_time_remaining(dss);
	assert(ans > 6 && ans < 8);

	
	dss.startTime = time(0);
	tc = TimeCode(0, 1, 5);
	dss.timeToDry = &tc;
	ans = get_time_remaining(dss);
	assert(ans > 64 && ans < 66);

	dss.startTime = time(0);
	tc = TimeCode(1, 1, 3);
	dss.timeToDry = &tc;
	ans = get_time_remaining(dss);
	assert(ans > 3662 && ans < 3664);
	


	// test get_sphere_sa
	double sa = get_sphere_sa(2.0);
	assert (50.2654 < sa && sa < 50.2655);
	
	sa = get_sphere_sa(7.0);
	assert (615.7520 < sa && sa < 615.7522);

	sa = get_sphere_sa(14.52);
	assert (2649.36 < sa && sa < 2649.38);


	// test compute_time_code
	TimeCode *tc2 = compute_time_code(1.0);
	assert(tc2->GetTimeCodeAsSeconds() == 1);
	
	tc2 = compute_time_code(64.0);
	assert(tc2->GetTimeCodeAsSeconds() == 64);

	tc2 = compute_time_code(1244.0);
	assert(tc2->GetTimeCodeAsSeconds() == 1244);

	delete tc2; // delete pointer tc2

	cout << "ALL TESTS PASSED!" << endl;

}


int main(){
	vector<DryingSnapShot> batches;
	char choice;
	// run tests
	tests();

	//prompt user to chose an option
	cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
	while (cin >> choice) { // assign option to char choice
		// source for learning tolower: https://www.geeksforgeeks.org/tolower-function-in-cpp/ 
		choice = (char)tolower(choice); // convert input to lowercase so case does not matter
		
		// check if choice entered is one of the options
		if (choice == 'a' || choice == 'v' || choice == 'q') {
			if (choice == 'a') { // if a or add, ask for a radius
				double r;
				cout << "Radius: ";
				cin >> r;

				// calculate surface area based on given radius
				double surfaceArea = get_sphere_sa(r);
				TimeCode *dryingTime = compute_time_code(surfaceArea);

				//create new DryingSnapShot called newBatch
				DryingSnapShot newBatch; 
				newBatch.name = to_string(rand()); // Generate random batch ID
				newBatch.startTime = time(0); // set start time to current time
				newBatch.timeToDry = dryingTime; // set time to dry for new batch to drying time

				batches.push_back(newBatch); // add new DryingSnapShot to vector batches
				cout << drying_snap_shot_to_string(newBatch) << endl;

			} 
			else if (choice == 'v') { // if choice is v or view, print each of the DryingSnapShots in batches
				for (size_t i = 0; i < batches.size(); ) {
					cout << drying_snap_shot_to_string(batches.at(i)) << endl;
					if (get_time_remaining(batches.at(i)) == 0) { // if time remaining is 0 delethe the batch after printing
					delete batches.at(i).timeToDry; 

					// source for learing erase funciton for vectors: https://www.geeksforgeeks.org/vector-erase-in-cpp-stl/
					batches.erase(batches.begin() + i); // Remove finished batch
				} else {
					i++; // Only increment if no deletion occurred
					}
		}
				cout << batches.size() << " batches being tracked." << endl; // print number of batches being tracked
	}
			else if (choice == 'q') { // if choice is q or quit, break the loop
				break;
			}
		}
		//if choice is not one of options, let the user know and ask to pick a vaild option
		else{ cout << "Invalid choice. Please enter (A)dd, (V)iew, or (Q)uit." << endl; }

        cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
    }

	// delete each DryingSnapShot batch in batches, so storage is freed up after program runs
	for (DryingSnapShot batch : batches) {
        delete batch.timeToDry;
   		}

	return 0;
}