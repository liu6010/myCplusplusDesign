#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

/*

解决的问题：用于计算一个节点到其他节点的最短路径。

1. 先找出从源点出发点v0到终点vk的直达路径
2. 从这条路径里面找出一条长度最短的路径
3. 然后对其余各条路径进行适当调整
    如果图中存在弧(v0,u)+(u,vk)<(v0,vk)，则以路径(v0,u,vk)代替(v0,vk)
*/

int dijkstra(const vector<vector<pair<int, int>>>& graph, const int start){
    size_t n = graph.size();
    // 初始值给最大，代表无法直接到达
    vector<int> distance(n, numeric_limits<int>::max());
    vector<bool> visited(n, false);
    // 每个节点到start节点的最短路径
    distance[start] = 0;
    // 小顶堆，从当前路径中找到一条最短路径
    // key是当前节点到源节点的最短路径，value是当前节点的下标
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pque;      
    pque.push({0,start});
    while(!pque.empty()){
        // 每次取出的是最短的路径
        int u = pque.top().second; pque.pop();
        // 访问过的不再访问
        if(visited[u]) continue;
        visited[u] = true;
        for(const auto& child:graph[u]){
            int v = child.first;
            int dist = child.second;
            // 当前节点的最短路径加上孩子节点的路径，如果小于孩子节点到源节点的路径，则直接替换路径
            if(!visited[v] && distance[u] != numeric_limits<int>::max() && distance[u]+dist < distance[v]){
                distance[v] = distance[u]+dist;
                pque.emplace(distance[v], v);
            } 
        }
    }
    // 输出最短路径
    for (size_t i = 0; i < n; ++i) {
        cout << "Shortest distance from " << start << " to " << i << " is " << distance[i] << endl;
    }
    int ans = *max_element(distance.begin(), distance.end());
    return  ans == numeric_limits<int>::max() ? -1 : ans;
}

int main(){
    // 顶点个数、边的个数
    int n,m;
    cin>>n>>m;
	vector<vector<pair<int, int>>> graph(n);
    for(int i=0;i<m;++i){
        int u, v, dist;
        cin>>u>>v>>dist;
        graph[u-1].push_back({v-1, dist});
        // graph[v].push_back({u-1, dist});  // 有向图就注释该行
    }
    auto res = dijkstra(graph, 0) ;
    cout << "minPathSum:" << res << endl;
    return 0;
}

/*

7 10
1 2 13
1 3 8
1 5 30
1 7 32
2 6 9
2 7 7
3 4 5
4 5 6
5 6 2
6 7 17

*/