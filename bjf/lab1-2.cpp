#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<ctype.h>
#include<math.h>
#include<vector>
#include<queue>
#include<stack>
#include<time.h>
#include<string.h>

using namespace ::std;

#define Height     30
#define Width      60
#define INF 0x7fffffff
#define SUCCESSED 1
#define FAILED 2
#define ERROR 3
#define DEFAULT -1

int status = DEFAULT;
int result_count = 0;
int start_time = 0, end_time = 0;

const char DIRECTION[4] = { 'U','D','L','R' };

char resultA[1000] = { 0 }, resultB[1000] = { 0 };
int SIZE = 1000;

struct Node {
	Node * parent;
	char value;
	int x, y;
	int h;
	int check; //1 open 0 close -1 unknown
};

Node map[Height][Width] = { 0 };
Node *result = NULL;
int start[2] = { 0 }, goal[2] = { 0 }, temp[2] = { 0 };

int get_h(Node pos, int *goal) {
	return (fabs(pos.x - goal[0]) + fabs(pos.y - goal[1]));
}

void IDA_star(int level, char direction, int x, int y, int max) {
	if (0 == level) {
		map[x][y].check = 1;
		IDA_star(level + 1, DIRECTION[0], x - 1, y, max);
		IDA_star(level + 1, DIRECTION[1], x + 1, y, max);
		IDA_star(level + 1, DIRECTION[2], x, y - 1, max);
		IDA_star(level + 1, DIRECTION[3], x, y + 1, max);
	    if (status != SUCCESSED)
			IDA_star(0, 0, x, y, max + (Width+Height)/2);
		if (max > Width*Height) {
			status = FAILED;
			return;
		}
	}
	else {
		if (level + map[x][y].h > max || level + map[x][y].h >= SIZE)
			return;
		if ((x >= 0) && (x < Height) && (y >= 0) && (y < Width) && map[x][y].value == '0'&&map[x][y].check == -1) {
			resultA[level - 1] = direction;
			map[x][y].check = 1;
			if (x == goal[0] && y == goal[1]) {
				if (strlen(resultA) < SIZE) {
					strcpy(resultB, resultA);
					SIZE = strlen(resultA);
				}
				resultA[level - 1] = '\0';
				map[x][y].check = -1;
				status = SUCCESSED;
				return;
			}
			IDA_star(level + 1, DIRECTION[0], x - 1, y, max);
			IDA_star(level + 1, DIRECTION[1], x + 1, y, max);
			IDA_star(level + 1, DIRECTION[2], x, y - 1, max);
			IDA_star(level + 1, DIRECTION[3], x, y + 1, max);
			resultA[level - 1] = '\0';
			map[x][y].check = -1;
		}
	}
}

int main() {
	int i = 0, j = 0;
	FILE * fp = fopen("E:\\input2.txt", "r");
	char ch = fgetc(fp);
	cin >> start[0] >> start[1] >> goal[0] >> goal[1];
	for (i = 0; i < Height; i++) {
		for (j = 0; j < Width; j++) {
			while (1) {
				if (isdigit(ch)) {
					map[i][j].value = ch;
					map[i][j].check = -1;
					map[i][j].x = i;
					map[i][j].y = j;
					map[i][j].h = get_h(map[i][j], goal);
					ch = fgetc(fp);
					break;
				}
				else
					ch = fgetc(fp);
			}
		}
	}
	//for (i = 0; i < Height; i++) {
	//	for (j = 0; j < Width; j++) {
	//		printf("%c ", map[i][j].value);
	//	}
	//	putchar('\n');
	//}
	start_time = clock();
	temp[0] = start[0]; temp[1] = start[1];
	if (map[start[0]][start[1]].value == '1' || map[goal[0]][goal[1]].value == '1') {
		status = ERROR;
	}
	if (status != ERROR) {
		IDA_star(0, 0, start[0], start[1], (Width + Height) / 2);
			end_time = clock();
		if (status == SUCCESSED) {
			printf("%1.8lf\n", (end_time - start_time) / 1000.0);
			for (int i = 0; i < strlen(resultB); i++) {
				cout << resultB[i];
			}
			cout << endl << strlen(resultB) << endl;
		}
		else {
			cout << "无结果" << endl;
		}
	}
	else
		cout << "输入错误" << endl;
	system("pause");
}