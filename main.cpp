#include "header.h"

int main(){
	int choice;
	do{
	cout << "----------------------"<<endl;
	cout << "1. Non-preemptive SJF" << endl;
	cout << "2. Preemptive SJF" << endl;
	cout << "3. Round-robin" << endl;
	cout << "----------------------"<<endl;
	cout << "Enter your choice or exit by typing '0':";
	cin >> choice;
	switch(choice){
		case 1:
		system("CLS");
		NPSJFmain();
		cout<<"\n";
		break;
		
		case 2:
		system("CLS");
		PSJFmain();
		cout<<"\n";
		break;
		
		case 3:
		system("CLS");
		RRmain();
		cout<<"\n";
		break;
	}	
	system("pause");
	system("CLS");
		
	}while(choice!=0);
	
	
return 0;
}