#include <vector>
#include <iostream>
#include "Matrix.h"
#include <algorithm>
using namespace std;
const int INF=-1;//��ʾ�����
bool isLess(int a,int b)
{
	if(a==INF&&b!=INF)
	{
		return false;
	}else if(b==INF&&a!=INF)
	{
		return true;
	}else if(a!=INF&&b!=INF)
	{
		return a<b;
	}else
	{
		return false;
	}
}
int getMinIndexInPath(int* pMinPathLen,bool* pIsOut,int n)
{
	int indexOfMin=-1;
	for(int i=0;i<n;i++)
	{
		if(!pIsOut[i])//�����δ��
		{
			if(indexOfMin!=-1)
			{
				if(isLess(pMinPathLen[i],pMinPathLen[indexOfMin]))
				{
					indexOfMin=i;
				}
			}else
			{
				indexOfMin=i;
			}
		}
	}
	return indexOfMin;
}
int getMinPath(CMatrix<int>& m,int s)
{
	//Dijkstra�㷨��
	int* pMinPathLen=new int[m.getColNum()];//��ԭ�㵽ÿ�������С·����������
	bool* pIsOut=new bool[m.getColNum()];
	//�������е�δ��
	memset(pIsOut,0,m.getColNum());
	//������нڵ�Ϊ�����
	fill(pMinPathLen,pMinPathLen+m.getColNum(),INF);
	//Դ�ڵ�Ϊ0.
	pMinPathLen[s]=0;
	int curNode=s;//��ǰ����Ǹ��ڵ�
	while((curNode=
		getMinIndexInPath(pMinPathLen,
		pIsOut,m.getColNum()))!=-1)//��ǰ�ڵ������һ����ԭ�������С�Ľڵ�
	{
		pIsOut[curNode]=1;//��ǰ�ڵ��
		//����������ڵ����������нڵ�
		for(int i=0;i<m.getColNum();i++)
		{
			if(m.valueOf(curNode,i)!=0)//�������·��
			{
				//���Դ��i�ľ�·������Դ����ǰ�ڵ���ϵ�ǰ�ڵ㵽i�ľ���
				if(isLess(pMinPathLen[curNode]+m.valueOf(curNode,i),pMinPathLen[i]))
				{
					pMinPathLen[i]=pMinPathLen[curNode]+m.valueOf(curNode,i);
				}
			}
		}
	}
	for_each(pMinPathLen,pMinPathLen+m.getColNum(),[](int& a){cout<<a<<' ';});
	cout<<endl;
	delete[] pIsOut;
	delete[] pMinPathLen;
	return 0;
}
int main()
{
	CMatrix<int> m(5,5);
	m.valueOf(0,1)=1;
	m.valueOf(1,2)=2;
	m.valueOf(2,3)=3;
	m.valueOf(4,3)=2;
	m.valueOf(3,4)=2;
	m.valueOf(0,4)=5;
	m.valueOf(1,3)=1;
	getMinPath(m,0);
	getchar();
	return EXIT_SUCCESS;
}
