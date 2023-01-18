//PAUL
#include "libs.h"

using namespace std;

//declare 3 nodes, b and c nodes for sorting arrays soon
static struct PSJFnode{
    char pname;
    int btime;
    int atime;
    int ctime=0;
	int wtime;
}PSJFa[1000],PSJFb[1000],PSJFc[1000];

//insert values for each process
void insertPSJF(int n){
    int i;
    for(i=0;i<n;i++){
        cin>>PSJFa[i].pname; //process number
        cin>>PSJFa[i].btime; //process burst time
        cin>>PSJFa[i].atime; // process arrival time
        PSJFa[i].wtime=-PSJFa[i].atime+1;
    }
}

//function to compare burst time
bool PSJFbtimesort(PSJFnode PSJFa,PSJFnode PSJFb){
    return PSJFa.btime < PSJFb.btime; 
}

bool PSJFatimeSort(PSJFnode PSJFa,PSJFnode PSJFb){
    return PSJFa.atime < PSJFb.atime; 
}
void PSJFdisplay(int nop,int qt){
	int k=0,f=0,r=0,q=0;
    int n=nop;
    sort(PSJFa,PSJFa+n,PSJFatimeSort);
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
             sort(PSJFb+f,PSJFb+r,PSJFbtimesort);    

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
    	cout << "PNAME :"<< PSJFc[i].pname << endl;
        if(PSJFc[i].pname==PSJFc[i+1].pname){

			PSJFc[i+1].btime;
            PSJFc[i].btime+=PSJFc[i+1].btime;

            for(j=i+1;j<k-1;j++)
                PSJFc[j]=PSJFc[j+1];
            k--;
            i--;
        }
    }
    

    
    // k == number of times process switches
    cout<<"---------------";
    cout<<"\n|Gantt Chart |\n";
    cout<<"---------------\n";
    int rtime=0;
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
}
void PSJFmain(){
    int nop,choice,i,qt;
    cout<<"Enter number of processes\n";
    cin>>nop;
    cout<<"Enter process, burst time and arrival time in that order\n";
    insertPSJF(nop);
    PSJFdisplay(nop,1);
}