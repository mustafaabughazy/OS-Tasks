/******************************************************************************

                               OS: Deadlock Task/Detection Algorithm
                    3rd Computer Engineering,Helwan University
        1- ايه معوض راشد (030)
        2- ريهام محمد ابو اليزيد (043)
        3- حسن ابراهيم فتوح (038)
        4- مصطفى مجدى احمد عثمان (097)
        5- هبة اشرف فؤاد طه (105)
      
*******************************************************************************/

#include <iostream>

using namespace std;

int main() {
	//Enter NO. of processes
	int NProcesses;
	cout << "***********************************" << endl;
	cout << "* Enter Number of Processes:\t";
	cin >> NProcesses;
	cout << "***********************************" << endl;
	cout << endl;

	// create : 2D Array
	// Each Process Has (Number & Allocation(ABC) & MAX(ABC) & Available (ABC)
	//                          & Need(ABC) )//13 coulmn

	//Safe_Sequance Array
	int *Safe_Sequance = new int[NProcesses];

	//Array to hold the remaining Processes
	int *hold = new int[NProcesses];

	int **Processes = new int *[NProcesses];
	for (int i = 0; i < NProcesses; i++) {
		Processes[i] = new int[13];
	}
	// Enter Processes
	cout << "***********************************" << endl;
	cout << "**********Enter Processes**********" << endl;
	cout << "***********************************" << endl;

	//Enter the Allocation & MAX
	for (int i = 0; i < NProcesses; i++) {
		cout << "* Process No.(" << i + 1 << "):" << endl;
		Processes[i][0] = i + 1;
		cout << "*\t Allocation(ABC) = ";
		cin >> Processes[i][1];
		cin >> Processes[i][2];
		cin >> Processes[i][3];
		cout << "*\t Need(ABC) = ";
		cin >> Processes[i][4];
		cin >> Processes[i][5];
		cin >> Processes[i][6];
		cout << "***********************************" << endl;
	}

	//Available resource
	cout << "*\t Enter Available(ABC) = ";
	cin >> Processes[0][7];
	cin >> Processes[0][8];
	cin >> Processes[0][9];
	cout << "***********************************" << endl;

	//Print Processes Array
	cout << "***********************************" << endl;
	cout << "************Processes Array**********" << endl;
	cout << "***********************************" << endl;
	cout << "Process | Allocation | MAX | Available | Need |" << endl;
	cout << "------  |----ABC---  | ABC | ---ABC--- | -ABC |" << endl;
	cout << "-----------------------------------------------" << endl;
	for (int i = 0; i < NProcesses; i++) {
		for (int j = 0; j < 13; j++) {
			cout << Processes[i][j] << " " << " ";
		}
		cout << endl;
	}

	//pointer to fill the Safe_Sequance Array and hold Array
	int spointer = 0;
	int hpointer = 0;

	for (int i = 0; i < NProcesses; i++) {
		//if Process needs < Available put it on Safe_Sequance Array and change the Available resources
		if (Processes[i][10] < Processes[0][7]
				&& Processes[i][11] < Processes[0][8]
				&& Processes[i][12] < Processes[0][9]) {
			Safe_Sequance[spointer] = Processes[i][0];
			spointer++;
			Processes[0][7] = Processes[0][7] + Processes[i][1];
			Processes[0][8] = Processes[0][8] + Processes[i][2];
			Processes[0][9] = Processes[0][9] + Processes[i][3];
		} else {
			hold[hpointer] = Processes[i][0];
			hpointer++;
		}

	}

	//the Processes in hold Array
	while (hpointer != 0) {
		for (int i = 0; i < hpointer; i++) {
			for (int j = 0; j < NProcesses; j++) {
				if (hold[i] == Processes[j][0]
						&& Processes[j][10] < Processes[0][7]
						&& Processes[j][11] < Processes[0][8]
						&& Processes[j][12] < Processes[0][9]) {
					Safe_Sequance[spointer] = hold[i];
					spointer++;
					Processes[0][7] += Processes[j][1];
					Processes[0][8] += Processes[j][2];
					Processes[0][9] += Processes[j][3];
					hpointer--;
				}
				else{
					cout <<" There is a Deadlock "<<endl ; 
					return 0; 
				}
			}
		}
	}

	//print Safe_Sequance Array
	cout << "***********************************" << endl;
	cout << "************Safe_Sequance**********" << endl;
	cout << "***********************************" << endl;
	for (int i = 0; i < spointer; i++) {
		cout << Safe_Sequance[i] << "\t";
	}

	return 0;
}
