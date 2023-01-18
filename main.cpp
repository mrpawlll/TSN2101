#include "header.h"

int main(){
	int choice;
	cout << "----------------------"<<endl;
	cout << "1. Non-preemptive SJF" << endl;
	cout << "2. Preemptive SJF" << endl;
	cout << "3. Round-robin" << endl;
	cout << "----------------------"<<endl;
	cout << "Enter your choice :";
	cin >> choice;
	switch(choice){
		case 1:
		system("CLS");
		NPSJFmain();
		break;
		case 2:
//		system("CLS");
//		PSJFmain();
		break;
		case 3:
		system("CLS");
		RRmain();
		break;
	}
	
	system("pause");

return 0;
}