#include <iostream>
#include "SRPTree.h"
#include <ctime>

using namespace std;

int main()
{
	SRPTree srpTree;
	clock_t begin1, begin2, end1, end2 = clock();
	int readCount = 0;
	int timeCount = 0;
	double time_spent = 0.0;
	

	if (!srpTree.Initialize())
	{
		cout << "Initialization failed. Exiting...<<endl";
		return 0;
	}

	begin1 = clock();
		
	string sPerfFile = "perfFile2.txt";
	ofstream fileperfwrite;

	fileperfwrite.open(sPerfFile.c_str(), std::ofstream::out | std::ofstream::app);


	cout << "Reading DB..." << endl;
	fileperfwrite << "Reading DB..." << endl;
	int totalRarePatterns = 0;
	while (srpTree.ReadTransaction())
	{
		readCount++;
		if (readCount == srpTree.GetWindowSize())
		{
			cout << "Mining..." << endl;
			fileperfwrite << "Mining..." << endl;

			begin2 = clock();
			
			if (!timeCount)
			{
				time_spent = (double)(begin2 - begin1) / CLOCKS_PER_SEC;
			}
			else
			{
				time_spent = (double)(begin2 - end2) / CLOCKS_PER_SEC;
			}
			timeCount++;

			cout << "Time spent in reading transactions (in seconds)" << time_spent << endl;
			fileperfwrite << "Time spent in reading transactions (in seconds)" << time_spent << endl;

			totalRarePatterns +=  srpTree.Mine().size();
			end2 = clock();
			time_spent = (double)(end2 - begin2) / CLOCKS_PER_SEC;
			cout << "Time spent in mining (in seconds)" << time_spent << endl;
			cout << "Reading DB..." << endl;

			fileperfwrite << "Time spent in mining (in seconds)" << time_spent << endl;
			fileperfwrite << "Reading DB..." << endl;

			readCount = 0;
		}
	}
	end1 = clock();
	srpTree.Finalize();
	cout << "Mining Completed..." << endl;
	cout << "Total rare patterns: " << totalRarePatterns << endl;
	fileperfwrite << "Mining Completed..." << endl;
	fileperfwrite << "Total rare patterns: " << totalRarePatterns << endl;

	time_spent = (double)(end1 - begin1)/CLOCKS_PER_SEC;

	cout << "Time elapse = " << time_spent << "seconds";
	fileperfwrite << "Time elapse = " << time_spent << "seconds";

	fileperfwrite.close();
	system("PAUSE");
	return 0;
}
