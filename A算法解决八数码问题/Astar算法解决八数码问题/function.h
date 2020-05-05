#include <iostream>
using namespace std;

#define null 0
#define HEAD 499 //表示头结点
#define INVALID_STATE_INDEX 10 //无效的状态
#define INVALID_SET_INDEX 1000
#define WIDTH 3	//棋盘的维度

/*状态图的状态节点*/
struct Node
{
	int State[9];//该节点的状态
	int Parent;//状态图中该节点的父节点
	int h;     //节点到达目的的困难程度
	int g;     //节点的实际路径
	int f;     //节点的总路径
};

static int End[9];	//目标棋盘
static int Start[9];  //初始棋盘
static int Invalid[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //无效的状态
static Node m;
static Node n;
static Node OPEN[500];
static Node CLOSE[500];
static int O_Num;
static int C_Num;

/*寻找0所在的下标*/
int IndexOfZero(int* input)
{
	for (int i = 0; i < 9; i++)
	{
		if (input[i] == 0)
			return i;
	}
	return INVALID_STATE_INDEX;
}


/*交换数组input下标为a,b的两个位置的数*/
void Swap(int* input, int a, int b)
{
	int temp = input[a];
	input[a] = input[b];
	input[b] = temp;
}
/*设置状态信息*/
void SetState(Node& inc, int* ina)
{
	for (int i = 0; i < 9; i++)
	{
		inc.State[i] = ina[i];
	}
}
/*复制状态*/
void CopyState(Node &from, Node &to)
{
	SetState(to, from.State);
	to.f = from.f;
	to.g = from.g;
	to.h = from.h;
	to.Parent = from.Parent;
}

//按指定的方向进行状态转移
bool Move(Node& start, Node& end, int dirct)
{
	CopyState(start, end);
	int p0 = IndexOfZero(start.State);
	switch (dirct)
	{
	case 0://left
		if (p0 == INVALID_STATE_INDEX || p0 % 3 == 2)
			return false;
		else
			Swap(end.State, p0, p0 + 1);
		return true;
	case 1://right
		if (p0 == INVALID_STATE_INDEX || p0 % 3 == 0)
			return false;
		else
			Swap(end.State, p0, p0 - 1);
		return true;
	case 2://up
		if (p0 == INVALID_STATE_INDEX || p0 > 5)
			return false;
		else
			Swap(end.State, p0, p0 + 3);
		return true;
	case 3://down
		if (p0 == INVALID_STATE_INDEX || p0 < 3)
			return false;
		else
			Swap(end.State, p0, p0 - 3);
		return true;
	default:
		return false;
	}
	return false;

}

/*计算总的路径长度*/
void SethANDf(Node& input)
{
	input.h = 0;
	for (int i = 0; i < 9; i++)
	{
		if (input.State[i] != End[i])
			input.h++;
	}                                       //测试一下，目前九宫格状态与目标状态相差多少，用h衡量困难程度
	if (input.State[4] != End[4])
		input.h--;
	input.f = input.h + input.g;
}

//按代价函数从小到大的顺序排序OPEN表
void SortOPEN(Node* OPEN, int O_Num)
{
	Node temp;
	for (int i = 0; i < O_Num; i++)
	{
		for (int j = 0; j < O_Num - 1 - i; j++)
		{
			if (OPEN[j].f > OPEN[j + 1].f)
			{
				CopyState(OPEN[j], temp);
				CopyState(OPEN[j + 1], OPEN[j]);
				CopyState(temp, OPEN[j + 1]);
			}
		}
	}
}

//判断两个状态是否相等
bool EqualState(Node a, Node b)
{
	for (int i = 0; i < 9; i++)
	{
		if (a.State[i] != b.State[i])
			return false;
	}
	return true;
}
//判断输入时否等于结束状态
bool IsEnd(Node input)
{
	Node tar;
	for (int i = 0; i < 9; i++)
	{
		tar.State[i] = End[i];
	}

	return EqualState(tar, input);
}
//判断输入状态是否在状态集中
int InSet(Node input, const Node* set, int index)
{
	for (int i = 0; i < index; i++)
	{
		if (EqualState(input, set[i]))
			return i;
	}
	return INVALID_SET_INDEX;
}

//打印状态和当前代价函数
void ShowState(Node input)
{
	for (int i = 0; i < 9; i++)
	{
		cout << input.State[i] << "  ";
		if (i % 3 == 2)
			cout << endl;
	}
	cout << "代价函数为f = " << input.f << endl << endl;
}


void Solve()
{
	/*初始化信息*/
	cout << "@初始化信息：" << endl << endl;
	cout << "请输入原棋盘（用空格隔开）：" << endl;
	for (int i = 0; i < WIDTH*WIDTH; i++){
		cin >> Start[i];      //Start数组为初始矩阵，End数组为目标矩阵
	}
	cout << "请输入目标棋盘（用空格隔开）：" << endl;
	for (int i = 0; i < WIDTH*WIDTH; i++){
		cin >> End[i];
	}
	cout << "您输入的原棋盘为：" << endl;
	for (int i = 0; i < 3; i++){
		cout << Start[i * 3] << "  " << Start[i * 3 + 1] << "  " << Start[i * 3 + 2] << endl;
	}
	cout << "您输入的目标棋盘为：" << endl;
	for (int i = 0; i < 3; i++){
		cout << End[i * 3] << "  " << End[i * 3 + 1] << "  " << End[i * 3 + 2] << endl;
	}
	cout << "@搜索过程及代价函数：" << endl << endl;

	Node prob;	//新建一个变量用来保存当前
	for (int i = 0; i<9; i++)
	{
		prob.State[i] = Start[i];
	}
	prob.g = 0;
	prob.Parent = HEAD;
	SethANDf(prob);    //该函数得到目前所有的数码状态
	CopyState(prob, OPEN[O_Num++]);
	while (O_Num>0)
	{
		/*从OPEN取出f最小的状态*/
		SortOPEN(OPEN, O_Num);
		CopyState(OPEN[0], n);
		CopyState(OPEN[O_Num - 1], OPEN[0]);//用来覆盖原来最小的和保存最大的
		O_Num--;
		CopyState(n, CLOSE[C_Num++]);

		if (IsEnd(n))
		{
			cout << "存在最佳路径：" << endl;
			int index = C_Num - 1;
			while (index != HEAD)
			{
				ShowState(CLOSE[index]);
				index = CLOSE[index].Parent;
			}
			return;
			//success
		}
		else
		{
			if (Move(n, m, 0) && !EqualState(m, CLOSE[n.Parent]))
			{//move left
				m.g = n.g + 1;
				m.Parent = C_Num - 1;
				SethANDf(m);
				if (InSet(m, OPEN, O_Num) == INVALID_SET_INDEX&&InSet(m, CLOSE, C_Num) == INVALID_SET_INDEX)//neither in close nor in open
				{
					CopyState(m, OPEN[O_Num++]);
				}
				else if (InSet(m, OPEN, O_Num) == INVALID_SET_INDEX)//in close
				{
					int C_Num2 = InSet(m, CLOSE, C_Num);
					if (m.f < CLOSE[C_Num2].f)
					{
						CopyState(m, OPEN[O_Num++]);
						SetState(CLOSE[C_Num2], Invalid);
					}
				}
				else
				{       //in open
					int C_Num2 = InSet(m, OPEN, O_Num);
					if (m.f < OPEN[C_Num2].f)
					{
						OPEN[C_Num2].g = m.g;
						OPEN[C_Num2].Parent = C_Num - 1;
						SethANDf(OPEN[C_Num2]);
					}
				}
			}


			if (Move(n, m, 1) && !EqualState(m, CLOSE[n.Parent]))
			{//move right
				m.g = n.g + 1;
				m.Parent = C_Num - 1;
				SethANDf(m);
				if (InSet(m, OPEN, O_Num) == INVALID_SET_INDEX&&InSet(m, CLOSE, C_Num) == INVALID_SET_INDEX)//neither in close nor in open
				{
					CopyState(m, OPEN[O_Num++]);
				}
				else if (InSet(m, OPEN, O_Num) == INVALID_SET_INDEX)//in close
				{
					int C_Num2 = InSet(m, CLOSE, C_Num);
					if (m.f < CLOSE[C_Num2].f)
					{
						CopyState(m, OPEN[O_Num++]);
						SetState(CLOSE[C_Num2], Invalid);
					}
				}
				else
				{       //in open
					int C_Num2 = InSet(m, OPEN, O_Num);
					if (m.f < OPEN[C_Num2].f)
					{
						OPEN[C_Num2].g = m.g;
						OPEN[C_Num2].Parent = C_Num - 1;
						SethANDf(OPEN[C_Num2]);
					}
				}
			}

			if (Move(n, m, 2) && !EqualState(m, CLOSE[n.Parent]))
			{//move up
				m.g = n.g + 1;
				m.Parent = C_Num - 1;
				SethANDf(m);
				if (InSet(m, OPEN, O_Num) == INVALID_SET_INDEX&&InSet(m, CLOSE, C_Num) == INVALID_SET_INDEX)//neither in close nor in open
				{
					CopyState(m, OPEN[O_Num++]);
				}
				else if (InSet(m, OPEN, O_Num) == INVALID_SET_INDEX)//in close
				{
					int C_Num2 = InSet(m, CLOSE, C_Num);
					if (m.f < CLOSE[C_Num2].f)
					{
						CopyState(m, OPEN[O_Num++]);
						SetState(CLOSE[C_Num2], Invalid);
					}
				}
				else
				{       //in open
					int C_Num2 = InSet(m, OPEN, O_Num);
					if (m.f < OPEN[C_Num2].f)
					{
						OPEN[C_Num2].g = m.g;
						OPEN[C_Num2].Parent = C_Num - 1;
						SethANDf(OPEN[C_Num2]);
					}
				}
			}

			if (Move(n, m, 3) && !EqualState(m, CLOSE[n.Parent]))
			{//move down
				m.g = n.g + 1;
				m.Parent = C_Num - 1;
				SethANDf(m);
				if (InSet(m, OPEN, O_Num) == INVALID_SET_INDEX&&InSet(m, CLOSE, C_Num) == INVALID_SET_INDEX)//neither in close nor in open
				{
					CopyState(m, OPEN[O_Num++]);
				}
				else if (InSet(m, OPEN, O_Num) == INVALID_SET_INDEX)//in close
				{
					int C_Num2 = InSet(m, CLOSE, C_Num);
					if (m.f < CLOSE[C_Num2].f)
					{
						CopyState(m, OPEN[O_Num++]);
						SetState(CLOSE[C_Num2], Invalid);
					}
				}
				else
				{       //in open
					int C_Num2 = InSet(m, OPEN, O_Num);
					if (m.f < OPEN[C_Num2].f)
					{
						OPEN[C_Num2].g = m.g;
						OPEN[C_Num2].Parent = C_Num - 1;
						SethANDf(OPEN[C_Num2]);
					}
				}
			}
		}
	}
}
