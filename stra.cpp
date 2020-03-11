#include <stdio.h>
#include <stdlib.h>

//代表无限大
#define inf 	100000
//点的个数
#define V_SIZE	6

//数组填充
void array_fill(int* array, int len, int val) {
	int i;
	for (i = 0; i < len; i++) {
		array[i] = val;
	}
}
/*函数功能：
 * 	stra核心算法找距离
 *	输入参数：
 *	graph	以矩阵的方式转化图形
 *	n		矩阵大小,即点的个数
 *	start	起点
 *	dist	距离
 * */
void stra(int graph[][V_SIZE], int n, int start, int dist[]) {
	int* path = (int*)malloc(sizeof(int) * n);/*定义一个指针，为该指针分配一个一块n个int空间的内存*/
	int* shortest = (int*)malloc(sizeof(int) * n);
	int* mark = (int*)malloc(sizeof(int) * n);
	int min, v, i, j;
	array_fill(mark, n, 0);
	array_fill(dist, n, inf);

	for (i = 0; i < n; i++) {
		dist[i] = graph[start][i];/*记录从起点到各个点的距离distance*/
		if (i != start && dist[i] < inf)path[i] = start;
		else path[i] = -1;/*-1对应的位置是之后没法考虑的*/
	}
	mark[start] = 1;/*记录算过的这个点为True，标记为1*/
	while (1) /*一直到。。。。。*/
	{
		min = inf; v = -1;
		//找到最小的距离
		for (i = 0; i < n; i++) {
			if (!mark[i]) /*不算自己找剩下的最短距离，然后标记成下一个mark点*/
			{
				if (dist[i] < min) { min = dist[i]; v = i; }
			}
		}
		if (v == -1)break; //找不到更短的路径了，没有符合要求的点了（上面的循环失效）
		//更新最短路径，v变成了从起点距离最近的那个点。
		mark[v] = 1;
		for (i = 0; i < n; i++) //在接下来的循环中在以v为起点的范围内找下一个点（满足的条件是从初始点到v再到它的距离小于直接从初始点到它的距离）。并将其更新为初始点到它的距离
		{
			if (!mark[i] &&
				graph[v][i] != inf &&
				dist[v] + graph[v][i] < dist[i]) {
				dist[i] = dist[v] + graph[v][i];
				path[i] = v;//path[i]表示再这一步做选择的时候是基于v这个点做的选择。比如path[3]=5,表示在5这个点能找到到达3最近的路
			}
		}
	}
	//输出路径
	printf("起点\t终点\t最短距离\t对应路径 \n");
	for (i = 0; i < n; i++) //这个循环比较nice（原作真强）
	{
		if (i == start) continue;
		array_fill(shortest, n, 0);
		printf("%d\t", start);
		printf("%d\t", i);
		printf("%d\t", dist[i]);
		int k = 0;
		shortest[k] = i;
		while (path[shortest[k]] != start) //到起点就挂掉，不在起点时每一个shortest的值都是path（shortset值-1）
										   //s[0]存的终点, s[1]存的就是path（s[0]）是到终点有最近的路的“上一个点”.
										   //s[2]=path(s[1]) 表示s[2]代表有到“上一个点”最近距离的点，依次类推到起点为止。
		{
			k++; shortest[k] = path[shortest[k - 1]];
		}
		k++; shortest[k] = start;
		for (j = k; j > 0; j--) {
			printf("%d->", shortest[j]);
		}
		printf("%d\n", shortest[0]);
	}
	free(path);
	free(shortest);
	free(mark);
	return;
}

int main()
{
	int dist[V_SIZE];
	int W[V_SIZE][V_SIZE] = {
				{  0,   1,   4,  inf,  inf,  inf },
				{  1,   0,   2,   7,    5,  inf },
				{  4,   2,   0,  inf,    1,  inf },
				{ inf,  7,  inf,   0,    3,    2 },
				{ inf,  5,    1,   3,   0,    6 },
				{ inf, inf,  inf,   2,   6,    0 }
	};

	stra(W, V_SIZE, 2, dist);
	return 0;
}
