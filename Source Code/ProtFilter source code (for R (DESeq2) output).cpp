#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;


int bsearch(const vector<string>& list, const string& key){
// pre: list.size() == # elements in list
// post: returns index of key in list, -1 if key not found
    int low = 0;                   // leftmost possible entry
    int high = list.size()-1;      // rightmost possible entry
    int mid;                       // middle of current range

    while (low <= high){   
mid = (low + high)/2;
        if (list[mid] == key)       // found key, exit search
           return mid;
        else if (list[mid] < key)   // key in upper half
           low = mid + 1;
        else                        // key in lower half
           high = mid - 1;
    }
    return -1;                      // not in list
} 

void insert(vector<string> & a, string newword){          // NOT const vector
// pre: a[0] <= … <= a[a.size()-1], a is sorted
// post: newnum inserted into a, a still sorted
    int count = a.size();  // size before insertion
    a.push_back(newword);   // increase size –newnum is inserted at the
                       // end but inserted value is not important
    int loc = count;      // start searching insertion loc from end
   
    while (loc > 0 && a[loc-1] > newword){    
a[loc] = a[loc-1]; 
loc--;        // shift right until the proper insertion cell
    }
    a[loc] = newword;  //actual insertion 
}


int main(){
	string filename, line, word, genename; 
	vector <string> refListVec;
	ifstream refList, filterTarget;
	ofstream output;
	output.open("filteredRes.csv");

	cout << "Please enter the reference list file: ";
	cin >> filename; refList.open(filename.c_str());

	if(refList.fail()){
		cout << "Cannot find reference list, exiting..." << endl;
	}

	else{
		cout << "Constructing reference list..." << endl;
		while(getline(refList, line)){
			if(bsearch(refListVec, line) == -1){
				insert(refListVec, line);
			}
		}
		cout << "Construction finished. Please enter results to filter: ";
		cin >> filename;filterTarget.open(filename.c_str());
		if(filterTarget.fail()){
			cout << "Cannot find target, exiting..." << endl;
		}
		else{
			cout << "Writing filtered file..." << endl;
			getline(filterTarget, line); output << line << endl; // for metadata line, optional
			while(getline(filterTarget, line)){
				genename =  line.substr(0, line.find(",")); // change this line to adapt to filter to different formats
				if(bsearch(refListVec, genename) != -1){
					output << line << endl;
				}
			}
			cout << "Exiting..." << endl;
		}

	}
	




	return 0;
}