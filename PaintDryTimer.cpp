
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


long long int get_time_remaining(DryingSnapShot dss){
	time_t currentTime = time(0);
    time_t elapsedTime = currentTime - dss.startTime;
    long long int totalDryTime = dss.timeToDry->GetTimeCodeAsSeconds();
    long long int remainingTime = totalDryTime - elapsedTime;
	long long int zero = 0;  // make a long long int that holds 0, so it can be used in max funtion
    return max(remainingTime,zero); //ensures that a negative value is never returned 
}


string drying_snap_shot_to_string(DryingSnapShot dss){

	long long int remainingTime = get_time_remaining(dss);
    TimeCode remaining(0,0,remainingTime);
      if (remainingTime == 0) {
        return "Batch-" + dss.name + " (takes " + dss.timeToDry->ToString() + " to dry) DONE!";
    } else {
        return "Batch-" + dss.name + " (takes " + dss.timeToDry->ToString() +
               " to dry) time remaining: " + remaining.ToString();
    }

	
}

//calculate surface area of a sphere
double get_sphere_sa(double rad){
	return 4 * M_PI * pow(rad,2);
	
}


TimeCode *compute_time_code(double surfaceArea){
	long long int dryingSeconds = static_cast<long long int>(surfaceArea);
    return new TimeCode(0, 0, dryingSeconds);
	return nullptr;
}


void tests(){
	// get_time_remaining
	DryingSnapShot dss;
	dss.startTime = time(0);
	TimeCode tc = TimeCode(0, 0, 7);
	dss.timeToDry = &tc;
	long long int ans = get_time_remaining(dss);
	assert(ans > 6 && ans < 8);
	// add more tests here


	// get_sphere_sa
	double sa = get_sphere_sa(2.0);
	assert (50.2654 < sa && sa < 50.2655);
	// add more tests here


	// compute_time_code
	TimeCode *tc2 = compute_time_code(1.0);
	//cout << "tc: " << tc.GetTimeCodeAsSeconds() << endl;
	assert(tc2->GetTimeCodeAsSeconds() == 1);
	delete tc2;


	// add more tests here


	cout << "ALL TESTS PASSED!" << endl;

}


int main(){
	vector<DryingSnapShot> batches;
	char choice;

	cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
	while (cin >> choice) {
		// source for learning tolower: https://www.geeksforgeeks.org/tolower-function-in-cpp/ 
		choice = (char)tolower(choice); // convert input to lowercase so case does not matter

		if (choice == 'a' || choice == 'v' || choice == 'q') {

			if (choice == 'a') {
				double r;
				cout << "Radius: ";
				cin >> r;

				double surfaceArea = get_sphere_sa(r);
				TimeCode *dryingTime = compute_time_code(surfaceArea);

				DryingSnapShot newBatch;
				newBatch.name = to_string(rand()); // Generate random batch ID
				newBatch.startTime = time(0);
				newBatch.timeToDry = dryingTime;

				batches.push_back(newBatch);
				cout << drying_snap_shot_to_string(newBatch) << endl;

			} 
			else if (choice == 'v') {
				for (size_t i = 0; i < batches.size(); ) {
					cout << drying_snap_shot_to_string(batches.at(i)) << endl;
					if (get_time_remaining(batches.at(i)) == 0) {
					delete batches.at(i).timeToDry;

					// source for learing erase funciton for vectors: https://www.geeksforgeeks.org/vector-erase-in-cpp-stl/
					batches.erase(batches.begin() + i); // Remove finished batch
				} else {
					i++; // Only increment if no deletion occurred
					}
		}
				cout << batches.size() << " batches being tracked." << endl;
	}
			else if (choice == 'q') {
				break;
			}
		}
		else{ cout << "Invalid choice. Please enter (A)dd, (V)iew, or (Q)uit." << endl; }

        cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
    }

	for (DryingSnapShot batch : batches) {
        delete batch.timeToDry;
   		}
	//tests());
	return 0;
}