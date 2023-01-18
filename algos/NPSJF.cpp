//1181203308 Christopher Ransil Peeris
#include "libs.h"

using namespace std;

//Created struct to store the values


static struct process{
    char pid[50];																						//declare variables 
    int arrival_time;
	int burst_time;
}NPSJFa[50];																						//declare sturct call name with array size


//Created void function for input by user
void input(int e){
    int i;																								//declare variable to be used for loop
    for(i=0;i<e;i++){																					//created for loop if i does not meet number of process, keep looping till meet requirement
    	cout<<"Process Ids: ";
        cin>>NPSJFa[i].pid;																					//store process id 
        cout<<"Process Arrival Times: ";
        cin>>NPSJFa[i].arrival_time;																			//store arrival time 
        cout<<"Process Burst Times: ";
        cin>>NPSJFa[i].burst_time;																			//store burst time
        cout<<"\n\n";
    }
}

//Created boolean function to return desired values 
bool burst_time_arrange(process NPSJFa,process b){							
    return NPSJFa.burst_time < b.burst_time; 																//compare and return desired values 
}

//Created boolean function to return desired values 
bool arrival_time_arrange(process NPSJFa,process b){
    return NPSJFa.arrival_time < b.arrival_time; 															//compare and return desired values
}
//Created void function for display 
void output(int e){
	
    sort(NPSJFa,NPSJFa+e,burst_time_arrange);																		//use sort function to arrange into ascending order
    sort(NPSJFa,NPSJFa+e,arrival_time_arrange);																	//use sort function to arrange into ascending order
    int turnaround_time=0,i;																			//declare variables 
    int tStore[e],o;
    for(i=0;i<e;i++){																					//created for loop if i does not meet number of process, keep looping till meet requirement
        o=i;
        while(NPSJFa[o].arrival_time<=turnaround_time&&o!=e){												//check whether arrival time is smaller or equals to turnaround time if yes condition is true and o does not equals to number of processes o incremented 
            o++;
        }
        sort(NPSJFa+i,NPSJFa+o,burst_time_arrange);																//use sort function to arrange into ascending order
        tStore[i]=turnaround_time;																		//turnaround time store in array
        turnaround_time+=NPSJFa[i].burst_time;																//turnaround time = turnaround time + burst time
    }
    tStore[i] = turnaround_time;																		//turnaround time store in array
    float averageWTime=0;																				//declare variables
    float averageRTime=0;
    float averageTAT=0;
    cout<<"\n";
    
    //print table
    cout<<"P.Name  ATime\tBTime\tCTime\tTATime\tWwTime\n";
    for (i=0; i<e; i++){
        cout << NPSJFa[i].pid << "\t"; 																		//Print Process ID 
        cout <<NPSJFa[i].arrival_time << "\t";																//Print AT
        cout << NPSJFa[i].burst_time << "\t";																//Print BT
        cout << tStore[i+1] << "\t"; 																	//Print CT
        cout << tStore[i]-NPSJFa[i].arrival_time+NPSJFa[i].burst_time << "\t"; 									//Print TAT
        averageTAT+=tStore[i]-NPSJFa[i].arrival_time+NPSJFa[i].burst_time;										//average turnaround time = average turnaround time + tstore - arrival time + burst time
        cout << tStore[i]-NPSJFa[i].arrival_time << "\t"; 													//Print WT
        averageWTime+=tStore[i]-NPSJFa[i].arrival_time;														//average waiting time = average waiting time + tstore - arrival time 
        cout <<"\n"; 
    }
   
    cout<<"\n\n";
    cout<<"The Average Waiting time: "<<(float)averageWTime/(float)e<<endl;								//print average waiting time
    cout<<"The Average Turnaround time: "<<(float)averageTAT/(float)e<<endl;							//print average turnaround time
    
     cout<<"\n";
    //print gantt chart
    cout<<"\n\t*****Gantt Chart*****\n";
    cout<<"===============================================\n\n";
    for (i=0; i<e; i++){
        cout <<"|   "<< NPSJFa[i].pid << "   "; 																//Print all processes in order 
    }
    cout<<"\n";
    for (i=0; i<e+1; i++){
        cout << tStore[i] << "\t"; 																		//Print Burst time of processors 
    }
    
}
//Created main body
void NPSJFmain(){
    int p;
    
    cout<<"*****Number-of-processes*****\n";
    cin>>p;
    cout<<"\n";
    input(p);
    output(p);
}
