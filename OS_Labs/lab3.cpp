#include <stdio.h>
#include <stdlib.h>
int const total = 200;       // 内存总数
int const beginaddress = 20; // 初次分配起始地址
struct Block
{
    int addr; // 块的起始地址
    int size; // 块的大小
    int flag; // 块的分配状态 1：代表已分配 0：代表未分配；
} block[100];
int count = 0; // 块的个数，初值为 0，分配一个则加 1，减少一个则减 1
// 显示函数模块
void display() // 显示所有块的模块
{
    int i;
    printf(" 目前内存情况\n");
    printf("-------------------------------------------------------------------------------- \n");
    printf(" 块号 起始地址 大小 分配状态\n");
    for (i = 1; i <= count; i++)
    {
        printf(" %d %d %d ", i, block[i].addr, block[i].size);
        if (block[i].flag == 0)
            printf("未分配\n");
        else
            printf("已分配\n");
    }
    printf("-------------------------------------------------------------------------------- \n");
}
// 进程进入函数，采用首次适应算法
void shoucishiyin()
{
    /*采用首次适应算法
    首先输入要调入内存的进程的大小。然后在 block 数组中找未分配且比该进程大的块，
    如找到的块和进程一样大，直接将该块设为已分配，如比进程大，该块要分为两块，
    一块已分配，一块空闲，并且后面的块依次后移一位。
    */
    int size;
    printf("请输入要调入内存的进程大小:");
    scanf("%d", &size);
    for (int i = 1; i <= count; i++)
        if (block[i].flag == 0 && block[i].size >= size)
        {
            if (block[i].size == size)
                block[i].flag = 1;
            else
            {
                count++;
                for (int j = count; j > i + 1; j--)
                {
                    block[j] = block[j - 1];
                }
                // 新的第 i+1 块
                block[i + 1].flag = 0;
                block[i + 1].addr = block[i].addr + size;
                block[i + 1].size = block[i].size - size;
                // 新的第 i 块
                block[i].flag = 1;
                block[i].size = size;
            }
            break;
        }
    display();
}
// 进程退出函数
void jinchengExit() // 作业调出内存模块
{
    int kuaihao;
    printf("请输入要调出内存的块号:");
    scanf("%d", &kuaihao);
    if (block[kuaihao].flag == 0)
        printf("该块内存是空闲的,无需调出\n");
    else
    { // 将该块设为空闲，就是将该块的 flag 设为 0，
        // 还考虑了该块的下一块如果是空闲的，则将这两块合并为一块，总块数减 1
        // 如果要考虑该块的前一块是空闲，则将这两块合并为一块，总块数减 1，如何改
        block[kuaihao].flag = 0;
        if (block[kuaihao + 1].flag == 0)
        {
            block[kuaihao].size = block[kuaihao].size + block[kuaihao + 1].size;
            for (int i = kuaihao + 2; i <= count; i++)
                block[i - 1] = block[i];
            count--;
        }
        if (block[kuaihao - 1].flag == 0)
        {
            block[kuaihao - 1].size = block[kuaihao].size + block[kuaihao - 1].size;
            for (int i = kuaihao + 1; i <= count; i++)
                block[i - 1] = block[i];
            count--;
        }
    }
    display();
}
int main()
{
    int exit_flag = 0, select;
    // 第一块初始化
    block[1].addr = beginaddress;
    block[1].flag = 0;
    block[1].size = total - beginaddress;
    count = 1;
    display();
    while (exit_flag == 0)
    {
        printf(" 请输入相应操作\n");
        printf(" 1. 进程进入内存 \n");
        printf(" 2. 进程退出内存\n");
        printf(" 3. 显示当前状态\n");
        printf(" 4. 退出");
        printf("\n \n 请选择:");
        scanf("%d", &select);
        switch (select)
        {
        case 1:
            shoucishiyin();
            break;
        case 2:
            jinchengExit();
            break;
        case 3:
            display();
            break;
        case 4:
            exit_flag = 1;
            break;
        default:
            printf("选择错误，请重新选择");
        }
    }
    return 0;
}