//#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<ctype.h>
#include<math.h>
#include<vector>
#include<queue>
#include<stack>
#include<time.h>

using namespace ::std;

#define Height     30
#define Width      60
#define INF 0x7fffffff
#define SUCCESSED 1
#define FAILED 2
#define ERROR 3
#define DEFAULT -1

int status=DEFAULT;
int result_count = 0;
int start_time = 0, end_time = 0;
const char DIRECTION[4] = { 'U','D','L','R' };

stack<char> S;

struct Node {
	Node * parent;
	char value;
	int x, y;
	int f, h, g;
	int check; //1 open 0 close -1 unknown
};

Node map[Height][Width] = { 0 };
Node *result = NULL;
int start[2] = { 0 }, goal[2] = { 0 }, temp[2] = { 0 };

struct cmp {
	bool operator ()(Node a,Node b)	{
		return a.f > b.f; //小顶堆
	}
};

priority_queue<Node, vector<Node>, cmp>open;
//priority_queue<Node, vector<Node>, cmp>close;

void get_queue(Node pos) {
	int x = pos.x, y = pos.y;
	if ((x > 0) && (map[x - 1][y].value != '1') && map[x - 1][y].check != 0) {
		if (map[x - 1][y].check == -1) {
			map[x - 1][y].check = 1;
			map[x - 1][y].parent = &map[x][y];
			map[x - 1][y].g = map[x][y].g + 1;
			map[x - 1][y].f = map[x - 1][y].g + map[x - 1][y].h;
			open.push(map[x - 1][y]);
			if (x - 1 == goal[0] && y == goal[1]){
				status = SUCCESSED;

			}
		}
		else if (map[x - 1][y].check == 1) {
			if (map[x][y].g + 1 < map[x - 1][y].g) {
				map[x - 1][y].g = map[x][y].g + 1;
				map[x - 1][y].f = map[x - 1][y].g + map[x - 1][y].h;
				map[x - 1][y].parent = &map[x][y];
			}
			else;
		}
	}
	if ((x < Height - 1) && (map[x + 1][y].value != '1') && map[x + 1][y].check != 0) {
		if (map[x + 1][y].check == -1) {
			map[x + 1][y].check = 1;
			map[x + 1][y].parent = &map[x][y];
			map[x + 1][y].g = map[x][y].g + 1;
			map[x + 1][y].f = map[x + 1][y].g + map[x + 1][y].h;
			open.push(map[x + 1][y]);
			if (x + 1 == goal[0] && y == goal[1])
				status = SUCCESSED;
		}
		else if (map[x + 1][y].check == 1) {
			if (map[x][y].g + 1 < map[x + 1][y].g) {
				map[x + 1][y].g = map[x][y].g + 1;
				map[x + 1][y].f = map[x + 1][y].g + map[x + 1][y].h;
				map[x + 1][y].parent = &map[x][y];
			}
			else;
		}
	}
	if ((y > 0) && (map[x][y - 1].value != '1') && map[x][y - 1].check != 0) {
		if (map[x][y - 1].check == -1) {
			map[x][y - 1].check = 1;
			map[x][y - 1].parent = &map[x][y];
			map[x][y - 1].g = map[x][y].g + 1;
			map[x][y - 1].f = map[x][y - 1].g + map[x][y - 1].h;
			open.push(map[x][y - 1]);
			if (x == goal[0] && y - 1 == goal[1])
				status = SUCCESSED;
		}
		else if (map[x][y - 1].check == 1) {
			if (map[x][y].g + 1 < map[x][y - 1].g) {
				map[x][y - 1].g = map[x][y - 1].g + 1;
				map[x][y - 1].f = map[x][y - 1].g + map[x][y - 1].h;
				map[x][y - 1].parent = &map[x][y];
			}
			else;
		}
	}
	if ((y < Width - 1) && (map[x][y + 1].value != '1') && map[x][y + 1].check != 0) {
		if (map[x][y + 1].check == -1) {
			map[x][y + 1].check = 1;
			map[x][y + 1].parent = &map[x][y];
			map[x][y + 1].g = map[x][y].g + 1;
			map[x][y + 1].f = map[x][y + 1].g + map[x][y + 1].h;
			open.push(map[x][y + 1]);
			if (x == goal[0] && y + 1 == goal[1])
				status = SUCCESSED;
		}
		else if (map[x][y + 1].check == 1) {
			if (map[x][y].g + 1 < map[x][y + 1].g) {
				map[x][y + 1].g = map[x][y + 1].g + 1;
				map[x][y + 1].f = map[x][y + 1].g + map[x][y + 1].h;
				map[x][y + 1].parent = &map[x][y];
			}
			else;
		}
	}
}

int get_direction(Node * n1,Node *n2) {
	if (n2->x - n1->x == 1) {
		return 0;
	}
	if (n2->x - n1->x == -1) {
		return 1;
	}
	if (n2->y - n1->y == 1) {
		return 2;
	}
	if (n2->y - n1->y == -1) {
		return 3;
	}
}

void get_close(Node pos) {
	map[pos.x][pos.y].check = 0;
	//close.push(map[pos.x][pos.y]);
}

int get_h(Node pos,int *goal) {
	return (fabs(pos.x - goal[0]) + fabs(pos.y - goal[1]));
}

int main() {
	int i = 0, j = 0;
	FILE * fp = fopen("C:\\Users\\lifeng wang\\Desktop\\人工智能\\input.txt", "r");
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
					map[i][j].parent = NULL;
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
	map[start[0]][start[1]].f = map[start[0]][start[1]].g + map[start[0]][start[1]].h;
	if (map[start[0]][start[1]].value == '1' || map[goal[0]][goal[1]].value == '1') {
		status = ERROR;
	}
	if(status==DEFAULT)
	while (status != SUCCESSED) {
		get_close(map[temp[0]][temp[1]]);
		get_queue(map[temp[0]][temp[1]]);
		if (open.empty()) {
			status = FAILED;
			break;
		}
		else {
			temp[0] = open.top().x;
			temp[1] = open.top().y;
			open.pop();
		}
	}
	end_time = clock();
	if (status == SUCCESSED) {
		printf("%1.5f\n", (end_time - start_time) / 1000.0);
		result = &map[goal[0]][goal[1]];
		while (1) {
			S.push(DIRECTION[get_direction(result, result->parent)]);
			result_count++;
			if (result->parent->parent != NULL) {
				result = result->parent;
			}
			else break;
		}
		for (int i = 0; i < result_count; i++) {
			cout << S.top();
			S.pop();
		}
		putchar('\n');
		cout << result_count<<endl;
	}
	else if (status == ERROR)	{
		cout << "输入不合法" << endl;
	}
	else if (status == FAILED) {
		cout << "无解" << endl;
	}
	system("pause");
}
