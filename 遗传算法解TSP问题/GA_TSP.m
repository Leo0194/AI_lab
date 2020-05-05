
clear
clc
close all
%% 加载数据
load CityPosition1.mat
%X=CityPosition1.mat;          
D=Distanse(X); 

N=size(D,1);    %城市个数
%% 遗传参数
NIND=100;                                %种群大小，    假设初始有100个解
MAXGEN=200;                          %按照要求我们设立最大遗传代数为200
Pc=1.0;                
Pm=0.05;             
GGAP=0.9;                               %代沟    （Genaration gap）  每代种群中被替换的比例
%% 初始化种群
Chrom=InitPop(NIND,N);       %初始化    100个解,产生一个100*14的矩阵
%% 画出随机解的路径图
DrawPath(Chrom(1,:),X)           %一个城市对应一个经纬度
pause(0.0001)
%% 输出随机解的路径和总距离
disp('初始种群中的一个随机值:')
OutputPath(Chrom(1,:));
Rlength=PathLength(D,Chrom(1,:));
disp(['总距离：',num2str(Rlength)]);
disp('~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~')
%% 优化
gen=0;
figure;
hold on;box on
xlim([0,MAXGEN])
title('优化过程')
xlabel('代数')
ylabel('最优值')
ObjV=PathLength(D,Chrom);  
preObjV=min(ObjV);
while gen<MAXGEN
    %% 计算适应度
    ObjV=PathLength(D,Chrom);  
    
    line([gen-1,gen],[preObjV,min(ObjV)]);pause(0.0001)
    preObjV=min(ObjV);
    FitnV=Fitness(ObjV);
    %% 选择
    SelCh=Select(Chrom,FitnV,GGAP);
    %% 交叉操作
    SelCh=Recombin(SelCh,Pc);
    %% 变异
    SelCh=Mutate(SelCh,Pm);
    %% 逆转操作
    SelCh=Reverse(SelCh,D);
    %% 重插入子代的新种群
    Chrom=Reins(Chrom,SelCh,ObjV);
    %% 更新迭代次数
    gen=gen+1 ;
end
%% 画出最优解的路径图
ObjV=PathLength(D,Chrom);  
[minObjV,minInd]=min(ObjV);
DrawPath(Chrom(minInd(1),:),X)
%% 输出最优解的路径和总距离
disp('最优解:')
p=OutputPath(Chrom(minInd(1),:));
disp(['总距离：',num2str(ObjV(minInd(1)))]);
disp('-------------------------------------------------------------')
