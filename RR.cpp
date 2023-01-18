#include "libs.h"
using namespace std;
struct RRnode{
    char process;
    int burst;
    int arrival;
    int restime=0;
    int ctime=0;
    int wait=-1;
}RRa[100],RRb[100],RRc[100];

static void insertRR(int n){
    int i;
    for(i=0;i<n;i++){
    	cout<<"==================\n";
    	cout<<"Process Name\n";
        cin>>RRa[i].process;
        cout<<"Arrival Time\n";
        cin>>RRa[i].arrival;
        cout<<"Burst Time\n";
        cin>>RRa[i].burst;
        RRa[i].wait=-RRa[i].arrival;
    }
}
bool btimeSort(RRnode RRa,RRnode RRb){
    return RRa.burst < RRb.burst; 
}
bool atimeSort(RRnode RRa,RRnode RRb){
    return RRa.arrival < RRb.arrival; 
}

void RRdisplay(int nop,int qt){
	int k=0,f=0,r=0;
    int n=nop,q;
    sort(RRa,RRa+n,atimeSort);
    int ttime=0,i;
    int j,tArray[n];
    int alltime=0;
    bool moveLast=false;
    for(i=0;i<n;i++){
        alltime+=RRa[i].burst;
    }
    alltime+=RRa[0].arrival;
    for(i=0;ttime<=alltime;){
        j=i;
        while(RRa[j].arrival<=ttime&&j!=n){
            RRb[r]=RRa[j];
            j++;
            r++;
        }
        if(r==f){
            RRc[k].process='i';
            RRc[k].burst=RRa[j].arrival-ttime;
            RRc[k].arrival=ttime;
            ttime+=RRc[k].burst;
            k++;
            continue;
        }
        i=j;
        if(moveLast==true){
            RRb[r]=RRb[f];
            f++;
            r++;
        }
        j=f;
        if(RRb[j].burst>qt){
            RRc[k]=RRb[j];
            RRc[k].burst=qt;
            k++;
            RRb[j].burst=RRb[j].burst-qt;
            ttime+=qt;  
            moveLast=true;
            for(q=0;q<n;q++){
                if(RRb[j].process!=RRa[q].process){
                    RRa[q].wait+=qt;
                }
            }
        }
        else{
            RRc[k]=RRb[j];
            k++;
            f++;
            ttime+=RRb[j].burst;  
            moveLast=false;
            for(q=0;q<n;q++){
                if(RRb[j].process!=RRa[q].process){
                    RRa[q].wait+=RRb[j].burst;
                }
            }
        }
        if(f==r&&i>=n)
        break;
    }
    tArray[i]=ttime;
    ttime+=RRa[i].burst;
    int rtime=0;
    for(j=0;j<n&&j<6;j++){
        rtime=0;
        for(i=0;i<k;i++){
            if(RRc[i].process==RRa[j].process){
                RRa[j].restime=rtime;
                break;
            }
            rtime+=RRc[i].burst;
        }
    }
    float averageWaitingTime=0;
    float averageResponseTime=0;
    float averageTAT=0;
        cout<<"\nGantt Chart\n";
    rtime=0;
    for (i=0; i<k+1&&i<20; i++){
        if(i!=k)
            cout<<"|   "<< RRc[i].process << "   "; 
        rtime+=RRc[i].burst;
        for(j=0;j<6;j++){
            if(RRa[j].process==RRc[i].process)
                RRa[j].ctime=rtime;
        } 
    }
    
    cout<<"\n";
    rtime=0;
    for (i=0; i<k+1&&i<20; i++){
        cout << rtime << "\t";
        if (i == k){
	    break;
		}else{
        tArray[i]=rtime;
        rtime+=RRc[i].burst; 
		}
    }
    cout<<"\n";
    cout<<"\n";
    cout<<"P.Name  AT\tBT\tCT\tTAT\tWT\tRT\n";
    for (i=0; i<6&&i<nop&&RRa[i].process!='i'; i++){
        if(RRa[i].process=='\0')
            break;
        cout << RRa[i].process << "\t"; 
        cout << RRa[i].arrival << "\t";
        cout << RRa[i].burst << "\t";
        cout << RRa[i].ctime << "\t"; 
        cout << RRa[i].wait+RRa[i].ctime-rtime+RRa[i].burst << "\t"; 
        averageTAT+=RRa[i].wait+RRa[i].ctime-rtime+RRa[i].burst;
        cout << RRa[i].wait+RRa[i].ctime-rtime << "\t"; 
        averageWaitingTime+=RRa[i].wait+RRa[i].ctime-rtime;
        cout << RRa[i].restime-RRa[i].arrival << "\t";  
        averageResponseTime+=RRa[i].restime-RRa[i].arrival;
        cout <<"\n"; 
    }
    cout<<"Average Response time: "<<(float)averageResponseTime/(float)n<<endl;
    cout<<"Average Waiting time: "<<(float)averageWaitingTime/(float)n<<endl;
    cout<<"Average TA time: "<<(float)averageTAT/(float)n<<endl;
}
void RRmain(){
    int nop,choice,i,qt;
    cout<<"Enter number of processes\n";
    cin>>nop;
    cout<<"Enter time quantum\n";
    cin>>qt;
    insertRR(nop);
    RRdisplay(nop,qt);

}
