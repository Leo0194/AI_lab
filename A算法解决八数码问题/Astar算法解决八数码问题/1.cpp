#include <iostream>
#include <vector>
#include <string>
#define col 3
#define row 3
#define maxnum 10000
#define maxdistance 10000
using namespace std;
 
 /*定义节点*/ 
class node{
public:
    int number[row][col];//将九宫格定义为3*3矩阵 
    string str;           // 
    int distances;        //定义距离 
    int depth;            //定义搜索深度 
    int findex;           //定义搜索广度 
    node(){             
    }
    int dis();
    void voluation(int index);           //定义搜索函数 
    bool isend();                        //判断搜索是否结束 
    bool isequal(node q);				 //判断节点是否相等 
};
vector <node> v;
node father,intent;        
void node::voluation(int index){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            number[i][j]=v[index].number[i][j];
        }
    }
} 
/*计算节点的距离*/ 
int node::dis(){
    int s=0;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(number[i][j]!=intent.number[i][j]){
                s=s+1;
            }
        }
    }
    distances=s;
    return s;
}
/*判断节点是否结束*/ 
bool node::isend(){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(number[i][j]!=intent.number[i][j]){
                return false;
            }
        }
    }
    return true;
}
/*判断节点是否相等*/ 
bool node::isequal(node q){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(number[i][j]!=q.number[i][j]){
                return false;
            }
        }
    }
    return true;
}
/*判断是否昂贵*/ 
bool isexpansive(node &n){
    for(int i=0;i<v.size();i++){
        if(v[i].isequal(n)){
            return false;
        }
    }
    return true;
}
/*判断是否为空*/ 
bool isempty(){
    for(int i=0;i<v.size();i++){
        if(v[i].distances!=maxnum){
            return false;
        }
    }
    return true;
}
/*找到最小值*/ 
int find_min(){
    int min_x=maxnum;
    int index_min;
    for(int i=0;i<v.size();i++){
        if(v[i].distances+v[i].depth<min_x){
            index_min=i;
            min_x=v[i].distances+v[i].depth;
        }
    }
    return index_min;
}
void swap_t(int &a,int &b){
    int t;
    t=a;
    a=b;
    b=t;
}

void breath(int index){
    int index_x,index_y;
    int flag=0;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(v[index].number[i][j]==0){
                index_x=i;
                index_y=j;
                flag=1;
                break;
            }
            if(flag==1){
                break;
            }
        }
    }
    node upnode,downnode,leftnode,rightnode;
    upnode.voluation(index);
    downnode.voluation(index);
    leftnode.voluation(index);
    rightnode.voluation(index);
    int up_dis=maxdistance;
    int down_dis=maxdistance;
    int left_dis=maxdistance;
    int right_dis=maxdistance;
    if(index_x>0){
        swap_t(upnode.number[index_x][index_y],upnode.number[index_x-1][index_y]);
        if(isexpansive(upnode)){
                up_dis=upnode.dis();
                upnode.findex=index;
                upnode.depth=v[index].depth+1;
                upnode.str="down";
                v.push_back(upnode);
        }
    }
    if(index_x<2){
        swap_t(downnode.number[index_x][index_y],downnode.number[index_x+1][index_y]);
        if(isexpansive(downnode)){
                down_dis=downnode.dis();
                downnode.findex=index;
                downnode.depth=v[index].depth+1;
                downnode.str="up";
                v.push_back(downnode);
        }
    }
    if(index_y>0){
        swap_t(leftnode.number[index_x][index_y],leftnode.number[index_x][index_y-1]);
        if(isexpansive(leftnode)){
                left_dis=leftnode.dis();
                leftnode.findex=index;
                leftnode.depth=v[index].depth+1;
                leftnode.str="right";
                v.push_back(leftnode);
        }
    }
    if(index_y<2){
        swap_t(rightnode.number[index_x][index_y],rightnode.number[index_x][index_y+1]);
        if(isexpansive(rightnode)){
                right_dis=rightnode.dis();
                rightnode.findex=index;
                rightnode.depth=v[index].depth+1;
                rightnode.str="left";
                v.push_back(rightnode);
        }
    }
    v[index].distances=maxnum;
}
/*操作函数*/ 
ostream& operator<<(ostream& os, node& no)
{
 for (int i = 0; i < row; i++) {
  for (int j = 0; j < col; j++)
   os << no.number[i][j] << ' ';
  os << endl;
 }
 return os;}
 /*打印函数*/ 
void print(int index, vector<node>& rstep_v)
{
 
 rstep_v.push_back(v[index]);
 index = v[index].findex;
 while (index != 0) 
 {
  rstep_v.push_back(v[index]);
  index = v[index].findex;
 }
 
 
 for (int i = rstep_v.size() - 1; i >= 0; i--){
  cout << "Step " << rstep_v.size() - i<< endl;
  node p=rstep_v[i];
  cout<<p.str<<endl;
  cout<< p << endl;
}	
}
void process(){
	while(1){
	int t=0;
    	if(isempty()){
    		cout << "error" << endl;
   			exit(-1);
		}
		
		else{
			int best=find_min();
			node temp=v[best];
			if(temp.isend()){
				t=1;
				 vector<node> rstep_v;
				 print(best,rstep_v);
				 
			}
			else{
				breath(best);
			}
		}
		if(t)
		break;
	}
}
 /*主函数*/ 
int main()
{
    cout << "Input source:" << endl;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            cin>>father.number[i][j];
        }
    }
    father.findex=0;
    father.depth=0;
    cout << "Input end:" << endl;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            cin>>intent.number[i][j];
        }
    }
    v.push_back(father);
    process();
    return 0;
}
