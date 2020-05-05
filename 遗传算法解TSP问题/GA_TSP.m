
clear
clc
close all
%% ��������
load CityPosition1.mat
%X=CityPosition1.mat;          
D=Distanse(X); 

N=size(D,1);    %���и���
%% �Ŵ�����
NIND=100;                                %��Ⱥ��С��    �����ʼ��100����
MAXGEN=200;                          %����Ҫ��������������Ŵ�����Ϊ200
Pc=1.0;                
Pm=0.05;             
GGAP=0.9;                               %����    ��Genaration gap��  ÿ����Ⱥ�б��滻�ı���
%% ��ʼ����Ⱥ
Chrom=InitPop(NIND,N);       %��ʼ��    100����,����һ��100*14�ľ���
%% ����������·��ͼ
DrawPath(Chrom(1,:),X)           %һ�����ж�Ӧһ����γ��
pause(0.0001)
%% ���������·�����ܾ���
disp('��ʼ��Ⱥ�е�һ�����ֵ:')
OutputPath(Chrom(1,:));
Rlength=PathLength(D,Chrom(1,:));
disp(['�ܾ��룺',num2str(Rlength)]);
disp('~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~')
%% �Ż�
gen=0;
figure;
hold on;box on
xlim([0,MAXGEN])
title('�Ż�����')
xlabel('����')
ylabel('����ֵ')
ObjV=PathLength(D,Chrom);  
preObjV=min(ObjV);
while gen<MAXGEN
    %% ������Ӧ��
    ObjV=PathLength(D,Chrom);  
    
    line([gen-1,gen],[preObjV,min(ObjV)]);pause(0.0001)
    preObjV=min(ObjV);
    FitnV=Fitness(ObjV);
    %% ѡ��
    SelCh=Select(Chrom,FitnV,GGAP);
    %% �������
    SelCh=Recombin(SelCh,Pc);
    %% ����
    SelCh=Mutate(SelCh,Pm);
    %% ��ת����
    SelCh=Reverse(SelCh,D);
    %% �ز����Ӵ�������Ⱥ
    Chrom=Reins(Chrom,SelCh,ObjV);
    %% ���µ�������
    gen=gen+1 ;
end
%% �������Ž��·��ͼ
ObjV=PathLength(D,Chrom);  
[minObjV,minInd]=min(ObjV);
DrawPath(Chrom(minInd(1),:),X)
%% ������Ž��·�����ܾ���
disp('���Ž�:')
p=OutputPath(Chrom(minInd(1),:));
disp(['�ܾ��룺',num2str(ObjV(minInd(1)))]);
disp('-------------------------------------------------------------')
