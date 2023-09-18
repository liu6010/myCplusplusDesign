#include <bits/stdc++.h>
using namespace std;
// [最小生成树](https://blog.csdn.net/Newin2020/article/details/125123616)
/*
最小生成树：基于并查集的思想
Prim算法采用贪心算法的思想，运行时间为O(n^2)
Kruskal算法采用贪心算法的思想，运行时间为O（nlogn）对边的排序


- 设连通网N，令最小生成树初始状态只有n个顶点而没有边
- 在连通网中选取代价最小的边，如果该边依附的顶点落在最小生成树的边集合T中不同的连通的分量上
（也就是不会在最小生成树的边集合中形成环），就将此边加入到最小生成树的边集合T中，否则舍弃此边，选取下一条代价最小的边
- 依次忒累，直至T中的所有的顶点都在同一条连通分量上为止。


*/

struct Edge{
    int u, v, w;
    // 按权重进行排序
    bool operator<(const Edge& E) const{
        return w < E.w;
    }
};
// 并查集，找根节点
int findFather(vector<int>& father, int x){
    if(father[x] != x) return findFather(father, father[x]);
    return father[x];
}


int kruskal(vector<Edge>& edges, int n, vector<Edge>& MST){
    sort(edges.begin(), edges.end());
    vector<int> father(n);
    // 初始化并查集
    for(int i=1;i<=n;++i) father[i]=i;      // 顶点下标从1开始
    // 枚举每一条边，满足要求就加入集合中
    int res=0, cnt=0;
    MST.clear();
    for(size_t i=0;i<edges.size();++i){
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        // 查找u和v的父节点，如果其父节点相同则说明两节点已经连通，则直接舍弃该边
        u = findFather(father, u);
        v = findFather(father, v);
        if(u!=v){
            father[u] = v;  // 合并
            res += w;
            MST.push_back(edges[i]);        // 将边加入到集合
            cnt++;
        }
    }
    return cnt < n-1? -1 : res;
}

int main()
{
	//假设有n个结点，m条边
    // int n, m;
    // cin >> n >> m;
	// vector<Edge> edges(m);
	// //输入每一条边
    // for (int i = 0; i < m; i++)
    // {
    //     int a, b, w;
    //     cin>>a>>b>>w;
    //     edges[i] = { a,b,w };
    // }
    int n=5;
	vector<Edge> edges{
        {1,2,3},
        {1,3,2},
        {1,4,1},
        {1,5,7},
        {2,5,5},
        {2,4,6},
        {3,4,4}
    };
   
    vector<Edge> MST;
    int t = kruskal(edges, n, MST);	//判断该图是否有最小生成树

    if(t == -1)  puts("impossible");
    else    cout << t << endl;

    return 0;
}
