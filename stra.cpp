#include <stdio.h>
#include <stdlib.h>

//�������޴�
#define inf 	100000
//��ĸ���
#define V_SIZE	6

//�������
void array_fill(int* array, int len, int val) {
	int i;
	for (i = 0; i < len; i++) {
		array[i] = val;
	}
}
/*�������ܣ�
 * 	stra�����㷨�Ҿ���
 *	���������
 *	graph	�Ծ���ķ�ʽת��ͼ��
 *	n		�����С,����ĸ���
 *	start	���
 *	dist	����
 * */
void stra(int graph[][V_SIZE], int n, int start, int dist[]) {
	int* path = (int*)malloc(sizeof(int) * n);/*����һ��ָ�룬Ϊ��ָ�����һ��һ��n��int�ռ���ڴ�*/
	int* shortest = (int*)malloc(sizeof(int) * n);
	int* mark = (int*)malloc(sizeof(int) * n);
	int min, v, i, j;
	array_fill(mark, n, 0);
	array_fill(dist, n, inf);

	for (i = 0; i < n; i++) {
		dist[i] = graph[start][i];/*��¼����㵽������ľ���distance*/
		if (i != start && dist[i] < inf)path[i] = start;
		else path[i] = -1;/*-1��Ӧ��λ����֮��û�����ǵ�*/
	}
	mark[start] = 1;/*��¼����������ΪTrue�����Ϊ1*/
	while (1) /*һֱ������������*/
	{
		min = inf; v = -1;
		//�ҵ���С�ľ���
		for (i = 0; i < n; i++) {
			if (!mark[i]) /*�����Լ���ʣ�µ���̾��룬Ȼ���ǳ���һ��mark��*/
			{
				if (dist[i] < min) { min = dist[i]; v = i; }
			}
		}
		if (v == -1)break; //�Ҳ������̵�·���ˣ�û�з���Ҫ��ĵ��ˣ������ѭ��ʧЧ��
		//�������·����v����˴�������������Ǹ��㡣
		mark[v] = 1;
		for (i = 0; i < n; i++) //�ڽ�������ѭ��������vΪ���ķ�Χ������һ���㣨����������Ǵӳ�ʼ�㵽v�ٵ����ľ���С��ֱ�Ӵӳ�ʼ�㵽���ľ��룩�����������Ϊ��ʼ�㵽���ľ���
		{
			if (!mark[i] &&
				graph[v][i] != inf &&
				dist[v] + graph[v][i] < dist[i]) {
				dist[i] = dist[v] + graph[v][i];
				path[i] = v;//path[i]��ʾ����һ����ѡ���ʱ���ǻ���v���������ѡ�񡣱���path[3]=5,��ʾ��5��������ҵ�����3�����·
			}
		}
	}
	//���·��
	printf("���\t�յ�\t��̾���\t��Ӧ·�� \n");
	for (i = 0; i < n; i++) //���ѭ���Ƚ�nice��ԭ����ǿ��
	{
		if (i == start) continue;
		array_fill(shortest, n, 0);
		printf("%d\t", start);
		printf("%d\t", i);
		printf("%d\t", dist[i]);
		int k = 0;
		shortest[k] = i;
		while (path[shortest[k]] != start) //�����͹ҵ����������ʱÿһ��shortest��ֵ����path��shortsetֵ-1��
										   //s[0]����յ�, s[1]��ľ���path��s[0]���ǵ��յ��������·�ġ���һ���㡱.
										   //s[2]=path(s[1]) ��ʾs[2]�����е�����һ���㡱�������ĵ㣬�������Ƶ����Ϊֹ��
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
