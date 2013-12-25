#include <vector>
#include <iostream>
#include "Matrix.h"
#include <algorithm>
using namespace std;
const int INF=-1;//表示无穷大
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
		if(!pIsOut[i])//如果是未出
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
	//Dijkstra算法。
	int* pMinPathLen=new int[m.getColNum()];//从原点到每个点的最小路径长度数组
	bool* pIsOut=new bool[m.getColNum()];
	//设置所有点未出
	memset(pIsOut,0,m.getColNum());
	//填充所有节点为无穷大
	fill(pMinPathLen,pMinPathLen+m.getColNum(),INF);
	//源节点为0.
	pMinPathLen[s]=0;
	int curNode=s;//当前活动的那个节点
	while((curNode=
		getMinIndexInPath(pMinPathLen,
		pIsOut,m.getColNum()))!=-1)//当前节点等于下一个距原点距离最小的节点
	{
		pIsOut[curNode]=1;//当前节点出
		//遍历与这个节点相连的所有节点
		for(int i=0;i<m.getColNum();i++)
		{
			if(m.valueOf(curNode,i)!=0)//如果存在路径
			{
				//如果源到i的旧路径大于源到当前节点加上当前节点到i的距离
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
