#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#define N 5
struct PCB
{
    char name[8];
    int arrive_time;
    int run_time;
    int finish_time;
    int zhouzhuan_time;
};
int total = 0;
struct PCB pcb[N], temp;
void output()
{
    float sum0 = 0, sum1 = 0;
    printf("----------------------------------------------------------------------------------------------\n");
    printf("进程名 到达时间 运行时间 完成时间 周转时间 带权周转时间\n");
    printf("----------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < N; i++)
    {
        float daiquanzhouzhuan = (float)(pcb[i].finish_time - pcb[i].arrive_time) / pcb[i].run_time;
        printf(" %s %d %d %d %d %.2f\n", pcb[i].name, pcb[i].arrive_time, pcb[i].run_time, pcb[i].finish_time, pcb[i].zhouzhuan_time,
                daiquanzhouzhuan);
        sum0 += pcb[i].zhouzhuan_time;
        sum1 += daiquanzhouzhuan; 
    }
    printf("平均周转时间：%.2f\n", sum0 / N);
    printf("平均带权周转时间：%.2f\n", sum1 / N);
    printf("----------------------------------------------------------------------------------------------\n");
}
bool cmp(PCB a, PCB b){
    return a.arrive_time < b.arrive_time;
}
int main()
{
    int i, j, tmp;
    bool isDebug = false;
    printf("是否自动输入? 1是/0否\n");
    scanf("%d", &tmp);
    if (tmp == 1)
        isDebug = true;

    for (i = 0; i < N; i++)
    {
        if (isDebug){
            pcb[i].name[0] = 'a' + i;
            pcb[i].name[1] = '\0';
            pcb[i].arrive_time = i;
            pcb[i].run_time = 2 * i + 1;
            continue;
        }
        printf("请输入进程名\n");
        scanf("%s", pcb[i].name);
        printf("请输入到达时间:");
        scanf("%d", &pcb[i].arrive_time);
        printf("请输入要运行时间");
        scanf("%d", &pcb[i].run_time);
    }

    std::sort(pcb, pcb + N, cmp);

    for (i = 0; i < N; i++)
    {
        printf("%s ", pcb[i].name);
        printf("%d ", pcb[i].arrive_time);
        printf("%d \n", pcb[i].run_time);
    }

    pcb[0].finish_time = pcb[0].arrive_time + pcb[0].run_time;
    pcb[0].zhouzhuan_time = pcb[0].finish_time - pcb[0].arrive_time;
    for (i = 1; i < N; i++)
    {
        if (pcb[i - 1].finish_time >= pcb[i].arrive_time)
            pcb[i].finish_time = pcb[i - 1].finish_time + pcb[i].run_time;
        else
            pcb[i].finish_time = pcb[i].arrive_time + pcb[i].run_time;
        pcb[i].zhouzhuan_time = pcb[i].finish_time - pcb[i].arrive_time;
    }
    output();

    return 0;
}