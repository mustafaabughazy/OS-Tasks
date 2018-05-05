/*******************************************************************************
                           OS: CPU Scheduling Task
                    3rd Computer Engineering,Helwan University
        1- ايه معوض راشد (030)
        2- ريهام محمد ابو اليزيد (043)
        3- حسن ابراهيم فتوح (038)
        4- مصطفى مجدى احمد عثمان (097)
        5- هبة اشرف فؤاد طه (105)

*******************************************************************************/

/******************************************************************************/
#include <iostream>

using namespace std;

#define Empty -100
/******************************************************************************/

  /****************************************************************************/
 /*******************************Linked List Queue****************************/
/****************************************************************************/
class LinkedListQueue {
  // Linked List Queue Node
  struct QueueNode {
    int Data;         // Hold the value
    QueueNode *Next;  // Point to the Next Node
  };

 private:
  QueueNode *Front, *Rear;

 public:
  // Consrurctor: Initialization of Queue with create Empty Node
  LinkedListQueue(void) {
    Front = new QueueNode;
    Front->Next = NULL;
    Rear = Front;
  }

  bool isEmpty(void) { return Front == Rear; }

  void enqueue(int data) {
    Rear->Data = data;
    QueueNode *temp = new QueueNode;
    temp->Next = NULL;
    Rear->Next = temp;
    Rear = temp;
  }

  int dequeue(void) {
    if (!isEmpty()) {
      int data = Front->Data;
      QueueNode *temp = Front;
      Front = Front->Next;
      delete temp;
      return data;
    }
    return Empty;
  }

  int getActualLength(void) {
    int ActualLength = 0;
    for (QueueNode *temp = Front; temp != Rear; temp = temp->Next) {
      ActualLength++;
    }
    return ActualLength;
  }

  void printQueue(void) {
    for (QueueNode *temp = Front; temp != Rear; temp = temp->Next) {
      cout << temp->Data << "\t";
    }
    cout << "\n";
  }
};
/******************************************************************************/

  /****************************************************************************/
 /****************************Functions Declarations**************************/
/****************************************************************************/
void CPU_Scheduling(void);
void FCFS(int **Processes, int NProcesses);
void SJF_P(int **Processes, int NProcesses);
void SJF_NP(int **Processes, int NProcesses);
void Priority_P(int **Processes, int NProcesses);
void Priority_NP(int **Processes, int NProcesses);
void RR(int **Processes, int NProcesses, int TimeQuantum);
void SortingProcessesAccordingToArrivalTime(int **Processes, int NProcesses);
void FCFS_SJF_NP_Priority_NP_CalclationsOfTimeLine(int **Processes,
                                                   int NProcesses);
void ReArrangingProcessesAccordingToBurstTime(int **Processes, int NProcesses);
void ReArrangingProcessesAccordingToPriority(int **Processes, int NProcesses);
/******************************************************************************/

  /****************************************************************************/
 /*********************************Main Function******************************/
/****************************************************************************/
int main(void) {
  CPU_Scheduling();
  return 0;
}
/******************************************************************************/

  /****************************************************************************/
 /**************************Functions Implementations*************************/
/****************************************************************************/
void CPU_Scheduling(void) {
  // Enter Number of Processes and Time Quantum
  int NProcesses, TimeQuantum;
  cout << "***********************************" << endl;
  cout << "* Enter Number of Processes:\t";
  cin >> NProcesses;
  cout << "***********************************" << endl;
  cout << "* Enter The Time Quantum:\t";
  cin >> TimeQuantum;
  cout << "***********************************" << endl;
  cout << endl;

    // create Processes Array: 2D
   // Each Process Has (Number & Arrival Time & Burst Time & Priority
  //                          & Waiting Time & Start Time & End Time)
  int **Processes = new int *[NProcesses];
  for (int i = 0; i < NProcesses; i++) {
    Processes[i] = new int[7];
  }

  // Enter Processes
  cout << "***********************************" << endl;
  cout << "**********Enter Processes**********" << endl;
  cout << "***********************************" << endl;
  int TotalBurstTime = 0;
  for (int i = 0; i < NProcesses; i++) {
    cout << "* Process No.(" << i + 1 << "):" << endl;
    Processes[i][0] = i + 1;
    cout << "*\t Arrival Time = ";
    cin >> Processes[i][1];
    cout << "*\t Burst Time = ";
    cin >> Processes[i][2];
    TotalBurstTime += Processes[i][2];
    cout << "*\t Priority = ";
    cin >> Processes[i][3];
    cout << "***********************************" << endl;
    // Waiting Time -> Processes[i][4]
    // Start Time -> Processes[i][5]
    // End Time -> Processes[i][6]
  }
  cout << "*\tTotal Burst Time = " << TotalBurstTime << endl;
  cout << "***********************************" << endl;
  cout << endl;

  FCFS(Processes, NProcesses);
  SJF_P(Processes, NProcesses);
  SJF_NP(Processes, NProcesses);
  Priority_P(Processes, NProcesses);
  Priority_NP(Processes, NProcesses);
  RR(Processes, NProcesses, TimeQuantum);
}
/****************************First Come First Served***************************/
void FCFS(int **Processes, int NProcesses) {
  // Sorting Processes According To Arrival Time
  SortingProcessesAccordingToArrivalTime(Processes, NProcesses);

  cout << "***********************************" << endl;
  cout << "*****First Come First Served*******" << endl;
  cout << "***********************************" << endl;

  // Calclations Of TimeLine
  FCFS_SJF_NP_Priority_NP_CalclationsOfTimeLine(Processes, NProcesses);
}
/******************Sorting Processes According To Arrival Time*****************/
void SortingProcessesAccordingToArrivalTime(int **Processes, int NProcesses) {
  // Sorting Processes According To Arrival Time
  for (int i = 0; i < NProcesses; i++) {
    int MinProcessLoc = i;
    // Get Minimum Process Location
    for (int j = i + 1; j < NProcesses; j++) {
      if (Processes[j][1] < Processes[MinProcessLoc][1]) {
        MinProcessLoc = j;
      }
    }
    // Swaping
    for (int k = 0; k < 7; k++) {
      int temp = Processes[i][k];
      Processes[i][k] = Processes[MinProcessLoc][k];
      Processes[MinProcessLoc][k] = temp;
    }
  }
}
/************(FCFS + SJF_NP + Priority_NP) Calclations Of Time Line************/
void FCFS_SJF_NP_Priority_NP_CalclationsOfTimeLine(int **Processes,
                                                   int NProcesses) {
  int TotalWaitingTime = 0;
  int TimeLine = Processes[0][1];

  for (int i = 0; i < NProcesses; i++) {
    Processes[i][5] = TimeLine;                           // Start Time
    Processes[i][6] = Processes[i][5] + Processes[i][2];  // End Time
    // Calclate the Waiting Time = Start Time - Arrival Time
    Processes[i][4] = Processes[i][5] - Processes[i][1];
    TotalWaitingTime += Processes[i][4];
    cout << "* Time(" << Processes[i][5] << "->" << Processes[i][6];
    cout << "): Process No.(" << Processes[i][0] << ")" << endl;
    TimeLine += Processes[i][2];
  }
  // Calclate Average Waiting Time
  float AverageWaitingTime = (float)TotalWaitingTime / NProcesses;
  cout << "***********************************" << endl;
  cout << "*\tAverage Waiting Time = " << AverageWaitingTime << endl;
  cout << "***********************************" << endl;
  cout << endl;
}
/***********************Shortest Job First Non-Preemptive**********************/
void SJF_NP(int **Processes, int NProcesses) {
  // Sorting Processes According To Arrival Time
  SortingProcessesAccordingToArrivalTime(Processes, NProcesses);

  // ReArranging Processes According To Burst Time
  ReArrangingProcessesAccordingToBurstTime(Processes, NProcesses);

  cout << "***********************************" << endl;
  cout << "*Shortest Job First Non-Preemptive*" << endl;
  cout << "***********************************" << endl;

  // Calclations Of TimeLine
  FCFS_SJF_NP_Priority_NP_CalclationsOfTimeLine(Processes, NProcesses);
}
/*****************ReArranging Processes According To Burst Time****************/
void ReArrangingProcessesAccordingToBurstTime(int **Processes, int NProcesses) {
  // ReArranging Processes According To Burst Time
  int TimeLineFlage = 0;
  for (int i = 0; i < NProcesses - 1; i++) {
    TimeLineFlage = TimeLineFlage + Processes[i][2];
    int MinProcessLoc = i + 1;
    for (int j = i + 1; j < NProcesses; j++) {
      if (TimeLineFlage >= Processes[j][1] &&
          Processes[j][2] < Processes[MinProcessLoc][2]) {
        MinProcessLoc = j;
      }
    }
    // Swaping
    for (int k = 0; k < 7; k++) {
      int temp = Processes[i + 1][k];
      Processes[i + 1][k] = Processes[MinProcessLoc][k];
      Processes[MinProcessLoc][k] = temp;
    }
  }
}
/****************************Priority Non-Preemptive***************************/
void Priority_NP(int **Processes, int NProcesses) {
  // Sorting Processes According To Arrival Time
  SortingProcessesAccordingToArrivalTime(Processes, NProcesses);

  // ReArranging Processes According To Priority
  ReArrangingProcessesAccordingToPriority(Processes, NProcesses);

  cout << "***********************************" << endl;
  cout << "*****Priority Non-Preemptive*******" << endl;
  cout << "***********************************" << endl;

  // Calclations Of TimeLine
  FCFS_SJF_NP_Priority_NP_CalclationsOfTimeLine(Processes, NProcesses);
}
/******************ReArranging Processes According To Priority*****************/
void ReArrangingProcessesAccordingToPriority(int **Processes, int NProcesses) {
  // ReArranging Processes According To Priority
  int TimeLineFlage = 0;
  for (int i = 0; i < NProcesses - 1; i++) {
    TimeLineFlage = TimeLineFlage + Processes[i][2];
    int MinProcessLoc = i + 1;
    for (int j = i + 1; j < NProcesses; j++) {
      if (TimeLineFlage >= Processes[j][1] &&
          Processes[j][3] < Processes[MinProcessLoc][3]) {
        MinProcessLoc = j;
      }
    }
    // Swaping
    for (int k = 0; k < 7; k++) {
      int temp = Processes[i + 1][k];
      Processes[i + 1][k] = Processes[MinProcessLoc][k];
      Processes[MinProcessLoc][k] = temp;
    }
  }
}
/*************************Shortest Job First Preemptive************************/
void SJF_P(int **Processes, int NProcesses) {
  int TotalWaitingTime = 0;
  cout << "***********************************" << endl;
  cout << "***Shortest Job First Preemptive***" << endl;
  cout << "***********************************" << endl;
  int TimeLine = 0;

  // Calclate Average Waiting Time
  float AverageWaitingTime = (float)TotalWaitingTime / NProcesses;
  cout << "***********************************" << endl;
  cout << "*\tAverage Waiting Time = " << AverageWaitingTime << endl;
  cout << "***********************************" << endl;
  cout << endl;
}
/******************************Priority Preemptive*****************************/
void Priority_P(int **Processes, int NProcesses) {
  int TotalWaitingTime = 0;
  cout << "***********************************" << endl;
  cout << "*******Priority Preemptive*********" << endl;
  cout << "***********************************" << endl;
  int TimeLine = 0;

  // Calclate Average Waiting Time
  float AverageWaitingTime = (float)TotalWaitingTime / NProcesses;
  cout << "***********************************" << endl;
  cout << "*\tAverage Waiting Time = " << AverageWaitingTime << endl;
  cout << "***********************************" << endl;
  cout << endl;
}
/**********************************Round Robin*********************************/
void RR(int **Processes, int NProcesses, int TimeQuantum) {
  int TotalWaitingTime = 0;
  cout << "***********************************" << endl;
  cout << "************Round Robin************" << endl;
  cout << "***********************************" << endl;
  int TimeLine = 0;
  LinkedListQueue Rqueue ;
  int *reminderTime;
  //array to calculate reminder time for each process
  reminderTime = new int[NProcesses];
  int process;
  for (int i =0; i<NProcesses; i++){

    // put all processes in ready queue
    Rqueue.enqueue(Processes[i][0]);
    // at the beginning reminder = burst time
    reminderTime[i] = Processes[i][2];
 }
  while (Rqueue.isEmpty() == false){
    process = Rqueue.dequeue()-1;
    if (TimeQuantum >reminderTime[process] && reminderTime[process] >0 )

    {
        cout << "* time of p"<< process+1 << " from "<< TimeLine;
        TimeLine += reminderTime[process];
        cout << " to "<< TimeLine << endl;
        reminderTime[process] = 0;

    }
    else if (TimeQuantum <reminderTime[process]){
        cout << "* time of p"<< process+1 << " from "<< TimeLine;
        TimeLine += TimeQuantum;
        cout << " to "<< TimeLine << endl ;

        reminderTime[process] =reminderTime[process] - TimeQuantum;
        Rqueue.enqueue(process+1);
    }
  }
  // Calclate Average Waiting Time
  float AverageWaitingTime = (float)TotalWaitingTime / NProcesses;
  cout << "***********************************" << endl;
  cout << "*\tAverage Waiting Time = " << AverageWaitingTime << endl;
  cout << "***********************************" << endl;
  cout << endl;
}
  /****************************************************************************/
 /**********************************<The End>*********************************/
/****************************************************************************/

