#include <bits/stdc++.h>
#include<windows.h>
#include<stdio.h>
#include<cstdlib>
using namespace std;

#define LT 218
#define RT 191
#define CROSS 197
#define HL 196
#define VL 179
#define TT 194
#define BT 193
#define LST 195
#define RST 180
#define LB 192
#define RB 217

#define BS 8
#define SPACE 32

class Graph
{
    public:
        float x_coord, y_coord;
};

bool compareTwoPointX(Graph point1, Graph point2)
{
    return (point1.x_coord < point2.x_coord);
}

bool compareTwoPointY(Graph point1, Graph point2)
{
    return (point1.y_coord < point2.y_coord);
}

void printElements(Graph points[])
{
    for (int i = 0; i < 100; i++)
    {
        cout << points[i].x_coord << " " << points[i].y_coord << "\n";
    }
}

float min(float a, float b)
{
    float ret;
    if(a<b){
        ret=a;
    }
    ret=b;
    return ret;
}

float distance(Graph point1, Graph point2)
{
    float ans;
    ans=pow((point2.x_coord - point1.x_coord), 2) + pow((point2.y_coord - point1.y_coord), 2);
    return sqrt(ans);
}

float closestPair(Graph points[], int Totalsize)
{

    float minValue = FLT_MAX;
    if (Totalsize <= 3)
    {
        for (int i = 0; i < Totalsize; i++)
            for (int j = i + 1; j < Totalsize; j++)
                if (distance(points[i], points[j]) < minValue)
                    minValue = distance(points[i], points[j]);

        return minValue;
    }

    int mid = Totalsize / 2;
    Graph middle = points[mid];

    float left = closestPair(points, mid);
    float right = closestPair(points + mid, Totalsize - mid);

    float smallest_distance = min(left, right);

    return smallest_distance;
}

float middleClosest(Graph middlePoints[], int size, float smallest_distance)
{
    float min = smallest_distance;

    sort(middlePoints, middlePoints + size, compareTwoPointY);

    for (int i = 0; i < size; ++i)
        for (int j = i + 1; j < size && (middlePoints[j].y_coord - middlePoints[i].y_coord) < min; ++j)
            if (distance(middlePoints[i], middlePoints[j]) < min)
                min = distance(middlePoints[i], middlePoints[j]);

    return min;
}

float middlePoints(Graph points[], int size, int smallest_distance)
{
    Graph mid = points[size / 2];

    Graph middlePoints[size];
    int j = 0;
    for (int i = 0; i < size; i++)
        if (abs(points[i].x_coord - mid.x_coord) < smallest_distance)
        {
            middlePoints[j] = points[i];
            j++;
        }

    return middleClosest(middlePoints, j, smallest_distance);
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawGraph()
{
	int X=10,Y=5;
	float val=0;
	for(int i=0;i<21;i++,Y++){
		gotoxy(X,Y);
		cout << char(VL);
	}
	gotoxy(X,Y);
	cout << char(LB);
	X+=1;

	for(int i=0;i<52;i++,X++)
	{
		gotoxy(X,Y);
		cout << char(HL);
	}
	X=12;
	for(int i=0;i<6;i++,X+=10)
	{
		gotoxy(X,Y);
		cout << char(TT);
	}
	Y+=1;
	X=11;
	for(int i=0;i<6;i++,X+=10)
	{
		gotoxy(X,Y);
		printf("%0.1f",val/10);
		val+=2;
	}
	X=10;
	Y=5;
	for(int i=0;i<6;i++,Y+=4)
	{
		gotoxy(X,Y);
		cout << char(RST);
	}
	X=6;
	Y=5;
	val=10;
	for(int i=0;i<6;i++,Y+=4)
	{
		gotoxy(X,Y);
		printf("%0.1f",val/10);
		val-=2;
	}

	gotoxy(X,Y+5);
}

void plotPoints(Graph P[],int n)
{
	int X=15,Y=24;
	for(int i=0;i<n;i++)
	{
		gotoxy(X+(P[i].x_coord)*50,Y-(P[i].y_coord)*20);
		cout << ".";
	}
}

int main()
{
    srand((unsigned int)time(0));
    Graph randomPoints[100];

    for (int i = 0; i < 100; i++)
    {
        randomPoints[i].x_coord = rand() % 100;
        randomPoints[i].y_coord = rand() % 100;
    }
	//drawGraph();

	int n = sizeof(randomPoints) / sizeof(randomPoints[0]);
	//plotPoints(randomPoints,n);
	//gotoxy(0,30);

    sort(randomPoints, randomPoints + 100, compareTwoPointX);
    printElements(randomPoints);

    float smallest_number = closestPair(randomPoints, 100);
    float middle_smallest = middlePoints(randomPoints, 100, smallest_number);

    if (smallest_number < middle_smallest)
        cout <<"\n"<<smallest_number;
    else
        cout <<"\n"<<middle_smallest;

    return 0;
}
