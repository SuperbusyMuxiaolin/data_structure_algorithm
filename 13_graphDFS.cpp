#include <iostream>
#include <vector>
#include <list>

using namespace std;

class WeightedDiGraph
{
    struct Edge
    {
        int to;
        int weight;
        Edge(int to, int weight)
        {
            this->to = to;
            this->weight = weight;
        }
    };
    vector<vector<Edge>> graph;
    // N为传入的节点数
public:
    WeightedDiGraph(int N)
    {
        graph.resize(N);
    }

    int size()
    {
        return graph.size();
    }

    // 添加边
    void addEdge(int from, int to, int weight)
    {
        if (hasEdge(from, to))
        {
            cout << "已经有这个边了" << endl;
            return;
        }
        graph[from].emplace_back(to, weight);
    }

    // 判断有无边
    bool hasEdge(int from, int to)
    {
        for (auto &edge : graph[from])
        {
            if (edge.to == to)
            {
                return true;
            }
        }
        return false;
    }
    // 返回所有边
    vector<Edge> neighbors(int index)
    {
        return graph[index];
    }

    // 删除边
    void removeEdge(int from, int to)
    {
        if (!hasEdge(from, to))
        {
            cout << "没有这个边" << endl;
            return;
        }
        for (auto it = graph[from].begin(); it != graph[from].end(); it++)
        {
            if (it->to == to)
            {
                graph[from].erase(it);
                break;
            }
        }
    }
};

void traverseNode(WeightedDiGraph &graph, int node, vector<bool> &visited)
{
    if (node < 0 || node > graph.size())
        return;

    if (visited[node])
        return;

    // 前序位置
    visited[node] = true;
    cout << node << " ";
    for (auto &edge : graph.neighbors(node))
    {
        traverseNode(graph, edge.to, visited);
    }
}

void traverseEdge(WeightedDiGraph &graph, int node, vector<vector<bool>> &visited)
{
    if (node < 0 || node >= graph.size())
        return;

    for (auto &edge : graph.neighbors(node))
    {
        if (visited[node][edge.to])
            continue;
        visited[node][edge.to] = true;
        cout << node << "->" << edge.to << endl;
        traverseEdge(graph, edge.to, visited);
    }
}

void traversePath(WeightedDiGraph &graph, vector<bool> &onPath, list<int> &path, int src, int dest)
{
    if (src < 0 || src >= graph.size())
        return;
    if (src == dest)
    {
        for (list<int>::iterator it = path.begin(); it != path.end(); it++)
        {
            cout << *it << "\t";
        }
        cout << src << endl;
        return;
    }
    if (onPath[src])
        return;
    onPath[src] = true;
    path.push_back(src);
    for (auto &edge : graph.neighbors(src))
    {
        traversePath(graph, onPath, path, edge.to, dest);
    }
    onPath[src] = false;
    path.pop_back();
}

void test01()
{
    WeightedDiGraph graph(7);
    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 1);
    graph.addEdge(1, 3, 1);
    graph.addEdge(1, 4, 1);
    graph.addEdge(2, 5, 1);
    graph.addEdge(2, 6, 1);
    graph.addEdge(3, 6, 1);
    graph.addEdge(3, 0, 1);
    graph.addEdge(6, 0, 1);
    vector<bool> visited(7, false);
    vector<vector<bool>> visited2(7, vector<bool>(7, false));
    // traverseNode(graph, 0, visited);
    traverseEdge(graph, 0, visited2);
    cout << endl;
}

void test02()
{
    WeightedDiGraph graph(7);
    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 1);
    graph.addEdge(1, 3, 1);
    graph.addEdge(1, 4, 1);
    graph.addEdge(2, 5, 1);
    graph.addEdge(2, 6, 1);
    graph.addEdge(3, 6, 1);
    graph.addEdge(3, 0, 1);
    graph.addEdge(6, 0, 1);
    vector<bool> onpath(graph.size());
    list<int> path;
    traversePath(graph, onpath, path, 0, 6);
}

// 无环图找出所有的路径
class Solution
{
public:
    vector<vector<int>> res;
    vector<int> single_path;
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>> &graph)
    {
        traverse(graph, 0);
        return res;
    }
    void traverse(vector<vector<int>> &graph, int src)
    {
        single_path.push_back(src);

        if (src == graph.size() - 1)
        {
            res.push_back(single_path);
            single_path.pop_back();
            return;
        }

        for (int index : graph[src])
        {
            traverse(graph, index);
        }
        single_path.pop_back();
    }
};

int main()
{
    test02();
    return 0;
}