#include <stdio.h>
#include <iostrem>
#include <queue>
#include <fstream>
#include <string.h>

using namespace std;

const char direction[4]={'E','W','S','N'};

typedef struct {
    int x;
    int y;
    int value;
    Node *parent;
    int f;
    int g;
    int h;
}Node;

Node MapNode[18][25];
queue <Node> open_list;
queue <Node> closed_list;

void readFileSet();
void initNode(Node node);
void checkSE(Node start, Node end);
void Astar(Node start, Node end);

int main(void){
    for(int i=0; i<18; i++){
        for(int j=0; j<25; j++){
            initNode(MapNode[i][j]);
        }
    }// init the map
    readFileSet();//read input.txt and set the map
    Node S,E;//start and end 
    initNode(S);
    initNode(E);
    cin >> S.x >> S.y;
    cin >> E.x >> E.y;
    checkSE(S,E);//check start and end 
    Astar(S, E);

    system("pause");
}

void readFileSet(){
    ifstream in("C:\\Users\\lifeng wang\\Desktop\\人工智能\\input.txt");
    if(in) {
         for(int i=0; i<18; i++) {
            for(int j=0; j<25; j++){
                in >> MapNode[i][j].value;
                MapNode[i][j].x=i;
                MapNode[i][j].y=j;
            }
         }
    }
    else {
        cout << "no such file..." <<endl;
    }
}

void initNode(Node node){
    node.x=0;
    node.y=0;
    node.value=0;
    node.f=0;
    node.g=0;
    node.h=0;
    node.parent=NULL;
}

void checkSE(Node start, Node end){
    if(start.value==0 && end.value==0)
        cout << "start and end are OK" << endl;
    else
        cout << "UNACCESSABLE POINT" << endl;
}

void Astar(Node start, Node end){
    open_list.push
}