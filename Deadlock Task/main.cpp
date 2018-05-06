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

/******************************************************************************/

  /****************************************************************************/
 /*******************************Linked List Queue****************************/
/****************************************************************************/
class LinkedListQueue {
  // Linked List Queue Node
  struct QueueNode {
    int Data;         // Hold the value
    QueueNode* Next;  // Point to the Next Node
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
    QueueNode* temp = new QueueNode;
    temp->Next = NULL;
    Rear->Next = temp;
    Rear = temp;
  }

  int dequeue(void) {
    if (!isEmpty()) {
      int data = Front->Data;
      QueueNode* temp = Front;
      Front = Front->Next;
      delete temp;
      return data;
    }
    return Empty;
  }

  int getActualLength(void) {
    int ActualLength = 0;
    for (QueueNode* temp = Front; temp != Rear; temp = temp->Next) {
      ActualLength++;
    }
    return ActualLength;
  }

  void printQueue(void) {
    for (QueueNode* temp = Front; temp != Rear; temp = temp->Next) {
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
void FCFS(int** Processes, int NProcesses);
void SJF_P(int** Processes, int NProcesses);
void SJF_NP(int** Processes, int NProcesses);
void Priority_P(int** Processes, int NProcesses);
void Priority_NP(int** Processes, int NProcesses);
void RR(int** Processes, int NProcesses, int TimeQuantum);
void SortingProcessesAccordingToArrivalTime(int** Processes, int NProcesses);
void FCFS_SJF_NP_Priority_NP_CalclationsOfTimeLine(int** Processes,
                                                   int NProcesses);
void ReArrangingProcessesAccordingToBurstTime(int** Processes, int NProcesses);
void ReArrangingProcessesAccordingToPriority(int** Processes, int NProcesses);
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
  int** Processes = new int*[NProcesses];
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
void FCFS(int** Processes, int NProcesses) {
  // Sorting Processes According To Arrival Time
  SortingProcessesAccordingToArrivalTime(Processes, NProcesses);

  cout << "***********************************" << endl;
  cout << "*****First Come First Served*******" << endl;
  cout << "***********************************" << endl;

  // Calclations Of TimeLine
  FCFS_SJF_NP_Priority_NP_CalclationsOfTimeLine(Processes, NProcesses);
}
/******************Sorting Processes According To Arrival Time*****************/
void SortingProcessesAccordingToArrivalTime(int** Processes, int NProcesses) {
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
void FCFS_SJF_NP_Priority_NP_CalclationsOfTimeLine(int** Processes,
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
void SJF_NP(int** Processes, int NProcesses) {
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
void ReArrangingProcessesAccordingToBurstTime(int** Processes, int NProcesses) {
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
void Priority_NP(int** Processes, int NProcesses) {
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
void ReArrangingProcessesAccordingToPriority(int** Processes, int NProcesses) {
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
void SJF_P(int** Processes, int NProcesses) {
  // Sorting Processes According To Arrival Time
  SortingProcessesAccordingToArrivalTime(Processes, NProcesses);

  cout << "***********************************" << endl;
  cout << "***Shortest Job First Preemptive***" << endl;
  cout << "***********************************" << endl;

  int TotalWaitingTime = 0;
  int TimeLine = Processes[0][1];
  /************************************************************/
  // Array to save the Remaining Time for each process;initial 0
  int* RemainingTime = new int[NProcesses]();
  for (int i = 0; i < NProcesses; i++) {
    RemainingTime[i] = Processes[i][2];
  }
  int CounterOfCompletedProcesses = 0;
  int LastProcessNumber = -1;
  int LastTimeLine = TimeLine;

  while (CounterOfCompletedProcesses < NProcesses) {
    int j;
    for (j = 0; j < NProcesses; j++) {
      if (Processes[j][1] > TimeLine) {
        break;
      }
    }
    // Sorting Processes According To Remaining Time
    for (int z = 0; z < j; z++) {
      int MinProcessLoc = z;
      // Get Minimum Process Location
      for (int y = z + 1; y < j; y++) {
        if (RemainingTime[y] < RemainingTime[MinProcessLoc]) {
          MinProcessLoc = y;
        }
      }
      // Swaping
      int temp = RemainingTime[z];
      RemainingTime[z] = RemainingTime[MinProcessLoc];
      RemainingTime[MinProcessLoc] = temp;
      for (int k = 0; k < 7; k++) {
        temp = Processes[z][k];
        Processes[z][k] = Processes[MinProcessLoc][k];
        Processes[MinProcessLoc][k] = temp;
      }
    }
    if (j > 0) {
      for (j = 0; j < NProcesses; j++) {
        if (RemainingTime[j] != 0) {
          break;
        }
      }
      if (Processes[j][1] > TimeLine) {
        TimeLine = Processes[j][1];
      }
      Processes[j][6] = TimeLine + 1;
      RemainingTime[j]--;
      if ((Processes[j][0] != LastProcessNumber) && (LastProcessNumber != -1)) {
        cout << "* Time(" << LastTimeLine;
        cout << "->" << TimeLine;
        cout << "): Process No.(" << LastProcessNumber << ")" << endl;
        LastTimeLine = TimeLine;
      }
      LastProcessNumber = Processes[j][0];
    }
    TimeLine++;
    CounterOfCompletedProcesses = 0;
    for (j = 0; j < NProcesses; j++) {
      if (RemainingTime[j] == 0) {
        CounterOfCompletedProcesses++;
      }
    }
  }
  cout << "* Time(" << LastTimeLine;
  cout << "->" << TimeLine;
  cout << "): Process No.(" << LastProcessNumber << ")" << endl;

  for (int i = 0; i < NProcesses; i++) {
    Processes[i][4] = Processes[i][6] - (Processes[i][1] + Processes[i][2]);
    TotalWaitingTime += Processes[i][4];
  }
  /************************************************************/
  // Calclate Average Waiting Time
  float AverageWaitingTime = (float)TotalWaitingTime / NProcesses;
  cout << "***********************************" << endl;
  cout << "*\tAverage Waiting Time = " << AverageWaitingTime << endl;
  cout << "***********************************" << endl;
  cout << endl;
}
/******************************Priority Preemptive*****************************/
void Priority_P(int** Processes, int NProcesses) {
  // Sorting Processes According To Arrival Time
  SortingProcessesAccordingToArrivalTime(Processes, NProcesses);

  cout << "***********************************" << endl;
  cout << "*******Priority Preemptive*********" << endl;
  cout << "***********************************" << endl;

  int TotalWaitingTime = 0;
  int TimeLine = Processes[0][1];
  /************************************************************/
  // Array to save the Remaining Time for each process;initial 0
  int* RemainingTime = new int[NProcesses]();
  for (int i = 0; i < NProcesses; i++) {
    RemainingTime[i] = Processes[i][2];
  }
  int CounterOfCompletedProcesses = 0;
  int LastProcessNumber = -1;
  int LastTimeLine = TimeLine;

  while (CounterOfCompletedProcesses < NProcesses) {
    int j;
    for (j = 0; j < NProcesses; j++) {
      if (Processes[j][1] > TimeLine) {
        break;
      }
    }
    // Sorting Processes According To Priority
    for (int z = 0; z < j; z++) {
      int MinProcessLoc = z;
      // Get Minimum Process Location
      for (int y = z + 1; y < j; y++) {
        if (Processes[y][3] < Processes[MinProcessLoc][3]) {
          MinProcessLoc = y;
        }
      }
      // Swaping
      int temp = RemainingTime[z];
      RemainingTime[z] = RemainingTime[MinProcessLoc];
      RemainingTime[MinProcessLoc] = temp;
      for (int k = 0; k < 7; k++) {
        temp = Processes[z][k];
        Processes[z][k] = Processes[MinProcessLoc][k];
        Processes[MinProcessLoc][k] = temp;
      }
    }
    if (j > 0) {
      for (j = 0; j < NProcesses; j++) {
        if (RemainingTime[j] != 0) {
          break;
        }
      }
      if (Processes[j][1] > TimeLine) {
        TimeLine = Processes[j][1];
      }
      Processes[j][6] = TimeLine + 1;
      RemainingTime[j]--;
      if ((Processes[j][0] != LastProcessNumber) && (LastProcessNumber != -1)) {
        cout << "* Time(" << LastTimeLine;
        cout << "->" << TimeLine;
        cout << "): Process No.(" << LastProcessNumber << ")" << endl;
        LastTimeLine = TimeLine;
      }
      LastProcessNumber = Processes[j][0];
    }
    TimeLine++;
    CounterOfCompletedProcesses = 0;
    for (j = 0; j < NProcesses; j++) {
      if (RemainingTime[j] == 0) {
        CounterOfCompletedProcesses++;
      }
    }
  }
  cout << "* Time(" << LastTimeLine;
  cout << "->" << TimeLine;
  cout << "): Process No.(" << LastProcessNumber << ")" << endl;

  for (int i = 0; i < NProcesses; i++) {
    Processes[i][4] = Processes[i][6] - (Processes[i][1] + Processes[i][2]);
    TotalWaitingTime += Processes[i][4];
  }
  /************************************************************/
  // Calclate Average Waiting Time
  float AverageWaitingTime = (float)TotalWaitingTime / NProcesses;
  cout << "***********************************" << endl;
  cout << "*\tAverage Waiting Time = " << AverageWaitingTime << endl;
  cout << "***********************************" << endl;
  cout << endl;
}
/**********************************Round Robin*********************************/
void RR(int** Processes, int NProcesses, int TimeQuantum) {
  // Sorting Processes According To Arrival Time
  SortingProcessesAccordingToArrivalTime(Processes, NProcesses);

  cout << "***********************************" << endl;
  cout << "************Round Robin************" << endl;
  cout << "***********************************" << endl;

  int TotalWaitingTime = 0;
  int TimeLine = Processes[0][1];

  LinkedListQueue ReadyQueue;
  // Array to save the Remaining Time for each process;initial 0
  int* RemainingTime = new int[NProcesses]();
  // Array to indecate if the Process entered the queue before that;initial
  // false
  bool* EnteredQueueBefore = new bool[NProcesses]();
  // Array to indecate if the Process started excution before that;initial false
  bool* StartedExcutionBefore = new bool[NProcesses]();

  ReadyQueue.enqueue(Processes[0][0]);  // First Process Enter Queue
  RemainingTime[0] = Processes[0][2];   // RemainingTime = BurstTime
  EnteredQueueBefore[0] = true;

  while (ReadyQueue.isEmpty() == false) {
    int ProcessNumber = ReadyQueue.dequeue();
    int ProcessIndex = ProcessNumber - 1;
    int ProcessRemainingTime = RemainingTime[ProcessIndex];

    if (TimeQuantum >= ProcessRemainingTime && ProcessRemainingTime > 0) {
      cout << "* Time(" << TimeLine;
      TimeLine += ProcessRemainingTime;
      cout << "->" << TimeLine;
      cout << "): Process No.(" << ProcessNumber << ")" << endl;
      RemainingTime[ProcessIndex] = 0;
      Processes[ProcessIndex][6] = TimeLine;  // End Time
      // Calclate the Waiting Time = End Time - (Arrival Time + Burst Time])
      Processes[ProcessIndex][4] =
          Processes[ProcessIndex][6] -
          (Processes[ProcessIndex][1] + Processes[ProcessIndex][2]);
      TotalWaitingTime += Processes[ProcessIndex][4];

      for (int i = 0; i < NProcesses; i++) {
        if (Processes[i][1] <= TimeLine && EnteredQueueBefore[i] == false) {
          ReadyQueue.enqueue(Processes[i][0]);
          RemainingTime[i] = Processes[i][2];
          EnteredQueueBefore[i] = true;
        }
      }
    } else if (TimeQuantum < ProcessRemainingTime) {
      cout << "* Time(" << TimeLine;
      TimeLine += TimeQuantum;
      cout << "->" << TimeLine;
      cout << "): Process No.(" << ProcessNumber << ")" << endl;
      RemainingTime[ProcessIndex] = ProcessRemainingTime - TimeQuantum;

      for (int i = 0; i < NProcesses; i++) {
        if (Processes[i][1] <= TimeLine && EnteredQueueBefore[i] == false) {
          ReadyQueue.enqueue(Processes[i][0]);
          RemainingTime[i] = Processes[i][2];
          EnteredQueueBefore[i] = true;
        }
      }

      ReadyQueue.enqueue(ProcessNumber);
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
