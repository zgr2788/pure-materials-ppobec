#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>


using namespace std;



struct GeneCount
{	GeneCount(){
	NAME = "NA";
	count = 0;
}

	GeneCount(string Hname){
		NAME = Hname;
		count = 1;
	}

	string NAME;
	int count;
};


void SelectSort(vector<GeneCount> & a){
    int j, k, minIndex, numElts = a.size();
	GeneCount temp;
    for(k=0; k < numElts - 1; k++){
        minIndex = k;            
        for(j=k+1; j < numElts; j++)
            if (a[j].count > a[minIndex].count)
               minIndex = j;     
        temp = a[k];         
        a[k] = a[minIndex];
        a[minIndex] = temp;
    }
}




int main(){
	ifstream inputF; // accepted input: a space separated value file with every row containing gene names.
	ofstream outputF; outputF.open("readLog");
	string fileName, line, word;
	vector <GeneCount> mainList;
	bool listCheck = false;

	cout << "Please enter filename to open: ";
	cin >> fileName; inputF.open(fileName.c_str());

	if(!inputF.fail()){
		cout << "Processing..." << endl;
		while(getline(inputF, line)){
			istringstream reader(line);
			while(reader >> word){
				listCheck = false;
				for (long unsigned int i = 0; i < mainList.size(); i++){
					if (word == mainList[i].NAME){
						listCheck = true;
						mainList[i].count++;
					}
				}
				if (!listCheck)
						mainList.push_back(GeneCount(word));
			}

		}
		cout << "Sorting..." << endl;
		SelectSort(mainList);
		cout << "Printing..." << endl;
		for (long unsigned int i = 0; i < mainList.size(); i++)
			outputF << mainList[i].NAME << ": " << mainList[i].count << endl;

		cout << "Exiting..." << endl;
	
	}

	else
	cout << "Failed to open file, exiting..." << endl;
	




	return 0;
}
