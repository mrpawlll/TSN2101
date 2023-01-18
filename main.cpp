#include "header.h"

int main(){

	cout << "\n--------------------------------------";
	cout << "\nNon-Preemptive Shortest-Job-First\t";
	cout << "\n--------------------------------------\n";
	NPSJFmain();
	
	cout << "\n--------------------------------------";
	cout << "\nPreemptive--Shortest-Job-First\t";
	cout << "\n--------------------------------------\n";
	PSJFmain();
	
	cout << "\n--------------------------------------";
	cout << "\nRound-Robin\t";
	cout << "\n--------------------------------------\n";
	RRmain();

return 0;
}