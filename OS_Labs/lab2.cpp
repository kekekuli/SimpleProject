#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 5
struct PCB
{
    char name[8];       // 进程名称
    int arrive_time;    // 到达时间
    int run_time;       // 运行时间
    int finish_time;    // 完成时间
    int zhouzhuan_time; // 周转时间
    float daiquan_time; // 带权周转时间
    bool finished;      // 是否运行完成
};
// 进程初始化
struct PCB pcb[N] =
    {{"AAA", 0, 4}, {"BBB", 1, 3}, {"CCC", 2, 5}, {"DDD", 20, 2}, {"EEE", 4, 4}};
// 进程输出函数
void output()
{
    float sum0 = 0, sum1 = 0;
    printf("----------------------------------------------------------------------------------------------\n");
    printf("进程名 到达时间 运行时间 完成时间 周转时间 带权周转时间\n");
    printf("----------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < N; i++)
    {
        printf(" %s %d %d %d %d %f\n ", pcb[i].name, pcb[i].arrive_time, pcb[i].run_time,
               pcb[i].finish_time, pcb[i].zhouzhuan_time, pcb[i].daiquan_time);
        sum0 += pcb[i].zhouzhuan_time;
        sum1 += pcb[i].daiquan_time;
    }
    printf("平均周转时间：%.2f\n", sum0 / N);
    printf("平均带权周转时间：%.2f\n", sum1 / N);
    printf("----------------------------------------------------------------------------------------------\n");
}
int main()
{
    int i, j, k, min_time, index;
    int last_finishedPCB_index; // 记录上一次已经运行的进程的数组下标
    output();
    // 运行第一个到达的进程 得到它的完成时间、周转时间等,并设置为已访问
    pcb[0].finish_time = pcb[0].arrive_time + pcb[0].run_time;
    pcb[0].zhouzhuan_time = pcb[0].finish_time - pcb[0].arrive_time;
    pcb[0].finished = true;
    pcb[0].daiquan_time = (float)pcb[0].zhouzhuan_time / pcb[0].finish_time;
    last_finishedPCB_index = 0;
    // 下面在剩下的进程中循环找出运行时间最小的进程，
    // 计算它的完成时间、周转时间等，并设置为已访问。
    for (i = 0; i < N; i++)
    {
        // 先找出没有访问过的运行时间最小的进程的下标
        index = -1;
        min_time = 100;
        for (j = 0; j < N; j++)
        {
            if (min_time > pcb[j].run_time && pcb[j].finished == false && pcb[j].arrive_time <= pcb[last_finishedPCB_index].finish_time)
            {
                min_time = pcb[j].run_time;
                index = j;
            }
        }
        if (index == -1)
        {
            int arrive_time = pcb[last_finishedPCB_index].finish_time;
            for (k = 0; k < N; k++){
                if (pcb[k].finished == false && (pcb[k].arrive_time > arrive_time && 
                    (index == -1 || pcb[k].arrive_time < pcb[index].arrive_time))){
                        index = k;
                }
            }
        }
        // 运行找到的最短进程 得到它的完成时间、周转时间等,并设置为已访问
        if (pcb[index].arrive_time <= pcb[last_finishedPCB_index].finish_time)
            pcb[index].finish_time = pcb[last_finishedPCB_index].finish_time + pcb[index].run_time;
        else
            pcb[index].finish_time = pcb[index].arrive_time + pcb[index].run_time;
        pcb[index].zhouzhuan_time = pcb[index].finish_time - pcb[index].arrive_time;
        pcb[index].daiquan_time = (float)pcb[index].zhouzhuan_time / pcb[index].run_time;
        pcb[index].finished = true;
        last_finishedPCB_index = index;
    }
    output();
    return 0;
}