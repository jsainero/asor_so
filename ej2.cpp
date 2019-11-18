#include <iostream>
#include <sched.h>

using namespace std;

int main(){
    int pid;
    cout << "Introduzca el pid: ";
    cin >> pid;
    int plan = sched_getscheduler(pid);
    switch (plan){
        case SCHED_OTHER : 
            cout << "RR standard\n";
            break;
        case SCHED_BATCH :
            cout << "Batch style\n";
            break;
        case SCHED_IDLE :
            cout << "Very low priority ... \n";
            break;
        case SCHED_FIFO :
            cout << "FIFO \n";
            break;
        case SCHED_RR :
            cout << "RR policy\n";
            break;
        default:
            cout << "eroro\n";
    }
    
    struct sched_param param;
    sched_getparam(pid,&param);
    cout << "La prioridad del planificador es " << param.sched_priority<<"\n";
    cout << "max: "<< sched_get_priority_max(plan)<< '\n';
    cout << "min: "<< sched_get_priority_min(plan)<< '\n';
    return 0;
}
