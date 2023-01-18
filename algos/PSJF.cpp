//PAUL
#include "libs.h"

using namespace std;

//declare 3 nodes, b and c nodes for sorting arrays soon
static struct PSJFnode{
    char pname;
    int btime;
    int atime=0;
    int ctime=0;
	int wtime;
}PSJFa[1000],PSJFb[1000],PSJFc[1000];

//insert values for each process
void insertPSJF(int n){
    int i;
    for(i=0;i<n;i++){
    	cout << "Enter process name:";
        cin>>PSJFa[i].pname; //process number
    	cout << "Enter burst time:";
        cin>>PSJFa[i].btime; //process burst time
    	cout << "Enter arrival time:";
        cin>>PSJFa[i].atime; // process arrival time
        PSJFa[i].wtime=-PSJFa[i].atime+1;
        cout << "\n\n";
    }
}

//function to compare burst time
bool PSJFbtimeSort(PSJFnode PSJFa,PSJFnode PSJFb){
    return PSJFa.btime < PSJFb.btime; 
}

bool PSJFatimeSort(PSJFnode PSJFa,PSJFnode PSJFb){
    return PSJFa.atime < PSJFb.atime; 
}

bool ATZeroMany(int nop){
	int temp = 0;
	for(int i=0;i<nop;i++){
		if(PSJFa[i].atime==0);
		temp ++;
	}	
	return (temp>1);
}

void PSJFdisplay(int nop,int qt){
	int k=0,f=0,r=0,q=0;
    int n=nop;
    sort(PSJFa,PSJFa+n,PSJFatimeSort);
    
    //sort for arriv. time = 0. possible multiple arriv.time=0 with diff burst times
    if(ATZeroMany(nop)){
    	PSJFnode* ptr = new PSJFnode();
        PSJFnode* hold = new PSJFnode();
    	PSJFnode* swap = new PSJFnode();
    	ptr = &PSJFa[0]; // point to index 0 as PSJFa already sorted according to arrival time
    	//ptr hold lowest burst time amount for earliest process in ptr
    	for (int i = 0; i<nop;i++){	
    		if((PSJFa[i].atime == 0)&&(PSJFa[i].btime< ptr->btime)){
			ptr = &PSJFa[i];
			}
		}
		hold =  &PSJFa[0];
		
		//swap index 0 with ptr(which holds lowest burst time && lowest arriv time)
		*swap = *hold;
		*hold = *ptr;
		*ptr = *swap;
	}

	
    int ttime=0,i;
    int j;
    int alltime=0;
    bool moveLast=false;
    //get total of burst time
    for(i=0;i<n;i++){
        alltime+=PSJFa[i].btime;
    }
    alltime+=PSJFa[0].atime;
    
    //sort processes
    for(i=0;ttime<=alltime;){
        j=i;
    
        //assign values of 'a' node to 'b' node
        while(PSJFa[j].atime<=ttime&&j!=n){
            PSJFb[r]=PSJFa[j];
            j++;
            r++;
        }
        
        if(r==f){
            PSJFc[k].pname='i';
            PSJFc[k].btime=PSJFa[j].atime-ttime;
            PSJFc[k].atime=ttime;
            ttime+=PSJFc[k].btime;
            k++;
            continue;
        }
        i=j;
        if(moveLast==true){
        sort(PSJFb+f,PSJFb+r,PSJFbtimeSort);    
        }
        j=f;
        
        if(PSJFb[j].btime>qt){
            PSJFc[k]=PSJFb[j];
            PSJFc[k].btime=qt;
            k++;
            PSJFb[j].btime=PSJFb[j].btime-qt;
            ttime+=qt;  
            moveLast=true;
            for(q=0;q<n;q++){
                if(PSJFb[j].pname!=PSJFa[q].pname){
                    PSJFa[q].wtime+=qt;
                }
            }
        }
        else{
            PSJFc[k]=PSJFb[j];
            k++;
            f++;
            ttime+=PSJFb[j].btime;  
            moveLast=false;
            for(q=0;q<n;q++){
                if(PSJFb[j].pname!=PSJFa[q].pname){
                    PSJFa[q].wtime+=PSJFb[j].btime;
                }
            }
        }
        if(f==r&&i>=n)
        break;
    }
    //end sort
    
    //total up burst time for each context switch
    for(i=0;i<k-1;i++){
        if(PSJFc[i].pname==PSJFc[i+1].pname){

			PSJFc[i+1].btime;
            PSJFc[i].btime+=PSJFc[i+1].btime;

            for(j=i+1;j<k-1;j++)
                PSJFc[j]=PSJFc[j+1];
            k--;
            i--;
        }
    }
    

    int rtime=0;
   
    float averageWaitingTime=0;
    float averageTAT=0;
    cout<<"\n";
    cout<<"\n";
    cout<<"+---------------+---------------+---------------+---------------+---------------+---------------+\n";
    cout<<"|\tP.Name\t|\tArriv.T\t|\tBurst.T\t|\tExit.T\t|Turnaround.T\t|Waiting.T\t|\n";
    cout<<"+---------------+---------------+---------------+---------------+---------------+---------------+\n";
    for (i=0; i<nop&&PSJFa[i].pname!='i'; i++){
        if(PSJFa[i].pname=='\0')
            break;
        cout<<"|\t" <<'P'<< PSJFa[i].pname << "\t"; 
        cout<<"|\t"<< PSJFa[i].atime << "\t";
        cout<<"|\t" << PSJFa[i].btime << "\t";
        cout<<"|\t" << PSJFa[i].ctime << "\t"; 
        
        cout<<"|\t"<< PSJFa[i].wtime+PSJFa[i].ctime-rtime+PSJFa[i].btime << "\t"; 
        averageTAT+=PSJFa[i].wtime+PSJFa[i].ctime-rtime+PSJFa[i].btime;
        
        cout<<"|\t"<< PSJFa[i].wtime+PSJFa[i].ctime-rtime << "\t|"; 
        averageWaitingTime+=PSJFa[i].wtime+PSJFa[i].ctime-rtime;
        cout <<"\n"; 
    }
    cout<<"+---------------+---------------+---------------+---------------+---------------+---------------+\n";
    cout<<"Average waiting time: "<<(float)averageWaitingTime/(float)n<<endl;
    cout<<"Average turnaround time: "<<(float)averageTAT/(float)n<<endl;
    
     // k == number of times process switches
    cout<<"---------------";
    cout<<"\n|Gantt Chart |\n";
    cout<<"---------------\n";
    //print the boxes first
    for (i=0; i<k; i++){
        if(i!=k)
            cout<<"|  "<<'P'<< PSJFc[i].pname << "   "; 
        rtime+=PSJFc[i].btime;
        for(j=0;j<n;j++){
            if(PSJFa[j].pname==PSJFc[i].pname)
                PSJFa[j].ctime=rtime;
        } 
    }
    cout<<"|\n";
    
    //then print the numbers for the context switches
    //initialize for first process array
    rtime=0;
    for (i=0; i<k+1; i++){
    	//first iteration prints 0 for initial process
        cout << rtime << "\t";
        //next context switch time is taken by adding into rtime + C's burst time
        rtime+=PSJFc[i].btime; 
    }
    
    
}
void PSJFmain(){
    int nop,choice,i,qt;
    cout<<"Number of processes : ";
    cin>>nop;
    insertPSJF(nop);
    PSJFdisplay(nop,1);
}