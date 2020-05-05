#include <iostream>
using namespace std;

#define null 0
#define HEAD 499 //��ʾͷ���
#define INVALID_STATE_INDEX 10 //��Ч��״̬
#define INVALID_SET_INDEX 1000
#define WIDTH 3	//���̵�ά��

/*״̬ͼ��״̬�ڵ�*/
struct Node
{
	int State[9];//�ýڵ��״̬
	int Parent;//״̬ͼ�иýڵ�ĸ��ڵ�
	int h;     //�ڵ㵽��Ŀ�ĵ����ѳ̶�
	int g;     //�ڵ��ʵ��·��
	int f;     //�ڵ����·��
};

static int End[9];	//Ŀ������
static int Start[9];  //��ʼ����
static int Invalid[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //��Ч��״̬
static Node m;
static Node n;
static Node OPEN[500];
static Node CLOSE[500];
static int O_Num;
static int C_Num;

/*Ѱ��0���ڵ��±�*/
int IndexOfZero(int* input)
{
	for (int i = 0; i < 9; i++)
	{
		if (input[i] == 0)
			return i;
	}
	return INVALID_STATE_INDEX;
}


/*��������input�±�Ϊa,b������λ�õ���*/
void Swap(int* input, int a, int b)
{
	int temp = input[a];
	input[a] = input[b];
	input[b] = temp;
}
/*����״̬��Ϣ*/
void SetState(Node& inc, int* ina)
{
	for (int i = 0; i < 9; i++)
	{
		inc.State[i] = ina[i];
	}
}
/*����״̬*/
void CopyState(Node &from, Node &to)
{
	SetState(to, from.State);
	to.f = from.f;
	to.g = from.g;
	to.h = from.h;
	to.Parent = from.Parent;
}

//��ָ���ķ������״̬ת��
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

/*�����ܵ�·������*/
void SethANDf(Node& input)
{
	input.h = 0;
	for (int i = 0; i < 9; i++)
	{
		if (input.State[i] != End[i])
			input.h++;
	}                                       //����һ�£�Ŀǰ�Ź���״̬��Ŀ��״̬�����٣���h�������ѳ̶�
	if (input.State[4] != End[4])
		input.h--;
	input.f = input.h + input.g;
}

//�����ۺ�����С�����˳������OPEN��
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

//�ж�����״̬�Ƿ����
bool EqualState(Node a, Node b)
{
	for (int i = 0; i < 9; i++)
	{
		if (a.State[i] != b.State[i])
			return false;
	}
	return true;
}
//�ж�����ʱ����ڽ���״̬
bool IsEnd(Node input)
{
	Node tar;
	for (int i = 0; i < 9; i++)
	{
		tar.State[i] = End[i];
	}

	return EqualState(tar, input);
}
//�ж�����״̬�Ƿ���״̬����
int InSet(Node input, const Node* set, int index)
{
	for (int i = 0; i < index; i++)
	{
		if (EqualState(input, set[i]))
			return i;
	}
	return INVALID_SET_INDEX;
}

//��ӡ״̬�͵�ǰ���ۺ���
void ShowState(Node input)
{
	for (int i = 0; i < 9; i++)
	{
		cout << input.State[i] << "  ";
		if (i % 3 == 2)
			cout << endl;
	}
	cout << "���ۺ���Ϊf = " << input.f << endl << endl;
}


void Solve()
{
	/*��ʼ����Ϣ*/
	cout << "@��ʼ����Ϣ��" << endl << endl;
	cout << "������ԭ���̣��ÿո��������" << endl;
	for (int i = 0; i < WIDTH*WIDTH; i++){
		cin >> Start[i];      //Start����Ϊ��ʼ����End����ΪĿ�����
	}
	cout << "������Ŀ�����̣��ÿո��������" << endl;
	for (int i = 0; i < WIDTH*WIDTH; i++){
		cin >> End[i];
	}
	cout << "�������ԭ����Ϊ��" << endl;
	for (int i = 0; i < 3; i++){
		cout << Start[i * 3] << "  " << Start[i * 3 + 1] << "  " << Start[i * 3 + 2] << endl;
	}
	cout << "�������Ŀ������Ϊ��" << endl;
	for (int i = 0; i < 3; i++){
		cout << End[i * 3] << "  " << End[i * 3 + 1] << "  " << End[i * 3 + 2] << endl;
	}
	cout << "@�������̼����ۺ�����" << endl << endl;

	Node prob;	//�½�һ�������������浱ǰ
	for (int i = 0; i<9; i++)
	{
		prob.State[i] = Start[i];
	}
	prob.g = 0;
	prob.Parent = HEAD;
	SethANDf(prob);    //�ú����õ�Ŀǰ���е�����״̬
	CopyState(prob, OPEN[O_Num++]);
	while (O_Num>0)
	{
		/*��OPENȡ��f��С��״̬*/
		SortOPEN(OPEN, O_Num);
		CopyState(OPEN[0], n);
		CopyState(OPEN[O_Num - 1], OPEN[0]);//��������ԭ����С�ĺͱ�������
		O_Num--;
		CopyState(n, CLOSE[C_Num++]);

		if (IsEnd(n))
		{
			cout << "�������·����" << endl;
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
