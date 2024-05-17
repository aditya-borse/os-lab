/* Q. Write a C program to compute and print the average waiting time,
average turnaround time and CPU burst times for the given list of
processes. Display/print the Gantt chart for first come first serve, shortest
job first, priority scheduling and round robin scheduling algorithm. */

#include <bits/stdc++.h>
using namespace std;

#define MAX_PROCESSES 100

// struct to store info about the processes
typedef struct
{
    int pid;
    int burst_time;
    int arrival_time;
    int priority;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int remaining_time;
} Process;

void fcfs(Process processes[], int n);
void sjf(Process processes[], int n);
void priority_non_preemptive(Process processes[], int n);
void priority_preemptive(Process processes[], int n);
void round_robin(vector<Process> processes_vector, int q);

int main()
{
    Process processes[MAX_PROCESSES];
    int n, choice;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    vector<Process> processes_vector(n);

    printf("Enter the burst time, arrival time and priority of each process\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d:\n", i + 1);
        processes[i].pid = i + 1;
        processes_vector[i].pid = i + 1;
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes_vector[i].burst_time = processes[i].burst_time;
        processes_vector[i].remaining_time = processes[i].burst_time;
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        processes_vector[i].arrival_time = processes[i].arrival_time;
        printf("Priority: ");
        scanf("%d", &processes[i].priority);
    }
    printf("Select a process scheduling algorithm:\n");
    printf("1. FCFS\n");
    printf("2. SJF\n");
    printf("3. Priority Non Preemptive\n");
    printf("4. Priority Preemptive\n");
    printf("5. Round Robin\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        fcfs(processes, n);
        break;
    case 2:
        sjf(processes, n);
        break;
    case 3:
        priority_non_preemptive(processes, n);
        break;
    case 4:
        priority_preemptive(processes, n);
        break;
    case 5:
        round_robin(processes_vector, n);
        break;
    case 6:
        printf("Exiting...\n");
    default:
        printf("Invalid choice\n");
    }
    return 0;
}

void fcfs(Process processes[], int n)
{
    // sort the processes according to the arrival time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].arrival_time > processes[j + 1].arrival_time)
            {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    int total_waiting_time = 0, total_turnaround_time = 0;

    // calculate for first process
    processes[0].start_time = processes[0].arrival_time;
    processes[0].completion_time = processes[0].start_time + processes[0].burst_time;
    processes[0].turnaround_time = processes[0].completion_time - processes[0].arrival_time;
    processes[0].waiting_time = processes[0].turnaround_time - processes[0].burst_time;

    // update total waiting time and turnaround time
    total_waiting_time += processes[0].waiting_time;
    total_turnaround_time += processes[0].turnaround_time;

    // calculate for rest of the processes
    for (int i = 1; i < n; i++)
    {
        processes[i].start_time = processes[i - 1].completion_time;
        processes[i].completion_time = processes[i].start_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    // printing the gantt chart
    printf("Gantt Chart (FCFS): \n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d |", processes[i].pid);
    }
    printf("\n");

    float average_tat = (float)total_turnaround_time / n;
    float average_wt = (float)total_waiting_time / n;

    printf("\nAverage Turnaround Time: %.2f", average_tat);
    printf("\nAverage Waiting Time: %.2f\n", average_wt);
}

void sjf(Process processes[], int n)
{
    int total_waiting_time = 0, total_turnaround_time = 0;

    // first check if all the processes have same arrival time
    int same_arrival_time = 1;
    for (int i = 0; i < n - 1; i++)
    {
        if (processes[i].arrival_time != processes[i + 1].arrival_time)
        {
            same_arrival_time = 0;
            break;
        }
    }

    if (same_arrival_time == 0)
    {
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (processes[j].arrival_time > processes[j + 1].arrival_time)
                {
                    Process temp = processes[j];
                    processes[j] = processes[j + 1];
                    processes[j + 1] = temp;
                }
            }
        }
    }

    if (same_arrival_time == 1)
    {
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (processes[j].burst_time > processes[j + 1].burst_time)
                {
                    Process temp = processes[j];
                    processes[j] = processes[j + 1];
                    processes[j + 1] = temp;
                }
            }
        }
    }

    // calculate for first process
    processes[0].start_time = processes[0].arrival_time;
    processes[0].completion_time = processes[0].start_time + processes[0].burst_time;
    processes[0].turnaround_time = processes[0].completion_time - processes[0].arrival_time;
    processes[0].waiting_time = processes[0].turnaround_time - processes[0].burst_time;

    total_waiting_time += processes[0].waiting_time;
    total_turnaround_time += processes[0].turnaround_time;

    if (same_arrival_time == 0)
    {
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 1; j < n - i - 1; j++)
            {
                if (processes[j].burst_time > processes[j + 1].burst_time)
                {
                    Process temp = processes[j];
                    processes[j] = processes[j + 1];
                    processes[j + 1] = temp;
                }
            }
        }
    }

    // now do the calculation for the rest of the processes
    for (int i = 1; i < n; i++)
    {
        processes[i].start_time = processes[i - 1].completion_time;
        processes[i].completion_time = processes[i].start_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    // printing the gantt chart
    printf("Gantt Chart (SJF): \n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d |", processes[i].pid);
    }
    printf("\n");

    float average_tat = (float)total_turnaround_time / n;
    float average_wt = (float)total_waiting_time / n;

    printf("\nAverage Turnaround Time: %.2f", average_tat);
    printf("\nAverage Waiting Time: %.2f\n", average_wt);
}

void priority_non_preemptive(Process processes[], int n)
{
    int total_waiting_time = 0, total_turnaround_time = 0;

    // make a copy of processes array
    Process temp_pro[MAX_PROCESSES];
    for (int i = 0; i < n; i++)
    {
        temp_pro[i] = processes[i];
    }

    // sort the processes based on arrival time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (temp_pro[j].arrival_time > temp_pro[j + 1].arrival_time)
            {
                Process temp = temp_pro[j];
                temp_pro[j] = temp_pro[j + 1];
                temp_pro[j + 1] = temp;
            }
        }
    }

    // sort the processes having same arrival time based on priority
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (temp_pro[i].arrival_time == temp_pro[j].arrival_time && temp_pro[i].priority > temp_pro[j].priority)
            {
                Process temp = temp_pro[i];
                temp_pro[i] = temp_pro[j];
                temp_pro[j] = temp;
            }
        }
    }

    temp_pro[0].start_time = temp_pro[0].arrival_time;
    temp_pro[0].completion_time = temp_pro[0].start_time + temp_pro[0].burst_time;
    temp_pro[0].turnaround_time = temp_pro[0].completion_time - temp_pro[0].arrival_time;
    temp_pro[0].waiting_time = temp_pro[0].turnaround_time - temp_pro[0].burst_time;

    total_waiting_time += temp_pro[0].waiting_time;
    total_turnaround_time += temp_pro[0].turnaround_time;

    // now sort rest of the processes based on priority
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 1; j < n - i - 1; j++)
        {
            if (temp_pro[j].priority > temp_pro[j + 1].priority)
            {
                Process temp = temp_pro[j];
                temp_pro[j] = temp_pro[j + 1];
                temp_pro[j + 1] = temp;
            }
        }
    }

    // now do the calculation for rest of the processes
    for (int i = 1; i < n; i++)
    {
        temp_pro[i].start_time = temp_pro[i - 1].completion_time;
        temp_pro[i].completion_time = temp_pro[i].start_time + temp_pro[i].burst_time;
        temp_pro[i].turnaround_time = temp_pro[i].completion_time - temp_pro[i].arrival_time;
        temp_pro[i].waiting_time = temp_pro[i].turnaround_time - temp_pro[i].burst_time;

        total_waiting_time += temp_pro[i].waiting_time;
        total_turnaround_time += temp_pro[i].turnaround_time;
    }

    // gantt chart
    printf("\nGantt chart: Non Preemptive\n\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d |", temp_pro[i].pid);
    }

    float avg_tat = (float)total_turnaround_time / n;
    float avg_wt = (float)total_waiting_time / n;

    printf("\n\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);
}

// function to find highest priority process based on current time and arrival time of process
int findHighestPriority(Process processes[], int n, int current_time)
{
    int index = -1;
    int highestPriority = 999;
    for (int i = 0; i < n; i++)
    {
        if (processes[i].arrival_time <= current_time && processes[i].burst_time > 0 && processes[i].priority < highestPriority)
        {
            index = i;
            highestPriority = processes[i].priority;
        }
    }
    return index;
}

void priority_preemptive(Process processes[], int n)
{
    int current_time = 0;
    int completed = 0;
    int total_waiting_time = 0, total_turnaround_time = 0;

    printf("\nGantt Chart: Priority Scheduling (Preemptive)\n");
    while (completed != n)
    {
        int highestPriority = findHighestPriority(processes, n, current_time);

        if (highestPriority == -1)
        {
            current_time++;
            continue;
        }

        printf("P%d |", processes[highestPriority].pid);
        processes[highestPriority].burst_time--;
        current_time++;

        if (processes[highestPriority].burst_time == 0)
        {
            completed++;
            processes[highestPriority].completion_time = current_time;
            processes[highestPriority].turnaround_time = processes[highestPriority].completion_time - processes[highestPriority].arrival_time;
            processes[highestPriority].waiting_time = processes[highestPriority].turnaround_time - processes[highestPriority].remaining_time;
            total_waiting_time += processes[highestPriority].waiting_time;
            total_turnaround_time += processes[highestPriority].turnaround_time;
        }
    }

    float avg_wt = (float)total_waiting_time / n;
    float avg_tat = (float)total_turnaround_time / n;

    printf("\n\nAverage waiting time: %.2f\n", avg_wt);
    printf("\nAverage turnaround time: %.2f\n", avg_tat);
}

void round_robin(vector<Process> processes, int q)
{
    queue<Process> readyQueue;
    int n = processes.size();
    int current_time = 0;
    int total_waiting_time = 0, total_turnaround_time = 0;

    cout << "Gantt Chart Round Robin: " << endl;
    while (!readyQueue.empty() || !processes.empty())
    {
        if (!processes.empty() && processes.front().arrival_time <= current_time)
        {
            readyQueue.push(processes.front());
            cout << "P" << processes.front().pid << " |";
            processes.erase(processes.begin());
        }

        if (readyQueue.empty())
        {
            current_time++;
            continue;
        }

        Process current_process = readyQueue.front();
        readyQueue.pop();

        int execution_time = min(q, current_process.burst_time);
        current_process.burst_time -= execution_time;
        current_time += execution_time;

        if (current_process.burst_time > 0)
        {
            readyQueue.push(current_process);
            cout << "P" << processes.front().pid << " |";
        }
        else 
        {
            current_process.completion_time = current_time;
            current_process.turnaround_time = current_process.completion_time - current_process.arrival_time;
            current_process.waiting_time = current_process.turnaround_time - current_process.remaining_time;
            total_waiting_time += current_process.waiting_time;
            total_turnaround_time += current_process.turnaround_time;
            cout << "P" << processes.front().pid << " (completed) |";
        }
    }

    float avg_wt = (float)total_waiting_time / n;
    float avg_tat = (float)total_turnaround_time / n;
    cout << endl;
    cout << "Average waiting time: " << avg_wt << endl;
    cout << "Average turnaround time: " << avg_tat << endl;
}
