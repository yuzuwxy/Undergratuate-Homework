#ifndef STRUCTURE_H
#define STRUCTURE_H

#endif // STRUCTURE_H

#pragma once
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<iomanip>
#include<ctime>
#include<vector>
#include<algorithm>

using namespace std;

struct Progress {
    int time;
    int arrive;
    int PID;
    int memory;
    int endtime;
    int state = 0;			// 0为尚未到达或当前时刻到达，1为已分配内存且正在运行，2为进程已回收，3为进程挂起
};


typedef struct{
    int JobID;
    int start;
    int endd;
}Unused, Used;

