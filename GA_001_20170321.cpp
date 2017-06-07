#include<iostream>
#include<iomanip>
#include<time.h>
#include<stdlib.h>

using namespace std;

//funtion
void twoPointSwap(int*, int*);
void init();
void printMaternal();
float twoPointDistance(int ,int);
void operationPathLong(int);
int getRand(int, int);
void rank();
int getRankN(int);
void mating();
void mutation(float);
void reproduce();

int Maternal[5][9],Offspring[2][9];
float pathLong[7][3];
//路徑表
float Distance_table[8][8]={
    {000.0, 091.8, 105.2, 089.9, 189.9, 076.2, 278.3, 054.4},
    {000.0, 000.0, 187.2, 038.9, 271.3, 162.9, 363.3, 088.4},
    {000.0, 000.0, 000.0, 194.1, 182.3, 031.4, 176.1, 153.8},
    {000.0, 000.0, 000.0, 000.0, 294.1, 166.1, 368.3, 063.6},
    {000.0, 000.0, 000.0, 000.0, 000.0, 168.0, 243.0, 185.9},
    {000.0, 000.0, 000.0, 000.0, 000.0, 000.0, 202.2, 122.8},
    {000.0, 000.0, 000.0, 000.0, 000.0, 000.0, 000.0, 320.0},
    {000.0, 000.0, 000.0, 000.0, 000.0, 000.0, 000.0, 000.0}
};

int main(){
    init();
    printMaternal();
    int N;
    float p;
    cin >> N >> p;
    for(int x = 0; x < N; x++){
        mating();
        mutation(p);
        reproduce();
    }
    printMaternal();
    return 0;
}

void init(){
    srand(time(NULL));
    //設定初始母體
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 8; j++){
            Maternal[i][j] = j + 1;
        }
        //亂數處理
        for(int j = 0; j < 50; j++){
            twoPointSwap(&Maternal[i][getRand(7, 1)], &Maternal[i][getRand(7, 1)]);
        }
        Maternal[i][8] = 1;
    }
    operationPathLong(-1);
}

//交配
void mating(){
    int Parents[2] = {getRankN(1), getRankN(2)}, point = getRand(6, 2);
    Offspring[0][0] = 1;
    for(int i = 1; i < point; i++){
        Offspring[0][i] = Maternal[Parents[0] - 1][i];
    }
    for(int i = 1; i < 8; i++){
        for(int j = 1; j < 8; j ++){
            if(Maternal[Parents[1]][i] == Offspring[0][j])break;
            else if(Offspring[0][j] == 0){
                Offspring[0][j] = Maternal[Parents[1]][i];
                break;
            }
        }
    }
    operationPathLong(-1);
}

//突變
void mutation(float probability){
    if(getRand(100, 0) * 0.01 >= probability)return;
    int p1 = getRand(7, 1), p2 = getRand(7, 1);
    while (p1 == p2)p2 = getRand(7, 1);
    twoPointSwap(&Offspring[0][p1], &Offspring[0][p2]);
}

//複製 
void reproduce(){
    int loser = getRankN(5);
    for(int i = 1; i < 8; i++)Maternal[loser][i] = Offspring[0][i];
}

//印出母體
void printMaternal(){
    for(int i = 0; i < 5; i++){
        cout << i + 1 << ":";
        for(int j = 0; j < 9; j++){
            cout << Maternal[i][j] << " ";
        }
        cout << fixed << setprecision(1) << pathLong[i][0] << " " << pathLong[i][1] << " " << pathLong[i][2] << endl;
    }
}

//母體路徑長
void operationPathLong(int row){
    if(row == -1){
        for(int i = 0; i < 5; i++){
            pathLong[i][0] = 0;
            for(int j = 0; j < 8; j++){
                cout << endl << j+1 << endl;
                pathLong[i][0] += twoPointDistance(Maternal[i][j], Maternal[i][j+1]);
            }
        }
        rank();
    }
    else if(row > 5){
        pathLong[row][0] = 0;
        for(int i = 0; i < 8; i++){
            pathLong[row][0] += twoPointDistance(Offspring[row-5][i], Offspring[row-5][i+1]);
        }
    }
    else{
        pathLong[row][0] = 0;
        for(int i = 0; i < 8; i++){
            pathLong[row][0] += twoPointDistance(Maternal[row][i], Maternal[row][i+1]);
        }
    }
}

//排名
void rank(){
    float max = 0,tmp[6];
    for(int i = 0; i < 5; i++){
        if(max < pathLong[i][0])max = pathLong[i][0];
        tmp[i] = pathLong[i][0];
    }
    for(int i = 0; i < 5; i++){
        pathLong[i][1] =max -pathLong[i][0];
        for(int j = i; j < 5; j++){
            if(tmp[i] > tmp[j]){
                tmp[5] = tmp[i];
                tmp[i] = tmp[j];
                tmp[j] = tmp[5];
            }
        }
        pathLong[i][2] = 0;
    }
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(tmp[i] == pathLong[j][0] && pathLong[j][2] == 0){
                pathLong[j][2] = i + 1; 
                break;
            }
        }
    }
}

//取得第N個排名
int getRankN(int n){
    for(int i = 0; i < 5; i++){
        if(pathLong[i][2] == n){
            return i;
        }
    } 
}
//兩點距離
float twoPointDistance(int x, int y){
    if(x < y)return Distance_table[x-1][y-1];
    return Distance_table[y-1][x-1];
}
//兩點位置交換
void twoPointSwap(int* a1, int* a2){
    int t;
    t = *a1;
    *a1 = *a2;
    *a2 = t;
}

//取得亂數
int getRand(int range, int displacement){
    return rand() % range + displacement;
}
