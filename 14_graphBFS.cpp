#include <iostream>
#include <vector>
#include <list>
#include <queue>

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

void bfs1(WeightedDiGraph &graph, int s)
{
    vector<bool> visited(graph.size(), false);
    queue<int> q;
    q.push(s);
    visited[s] = true;
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        cout << "visited: " << cur << endl;
        for (auto &e : graph.neighbors(cur))
        {
            if (visited[e.to])
                continue;
            q.push(e.to);
            visited[e.to] = true;
        }
    }
}

void bfs2(WeightedDiGraph &graph, int s)
{
    vector<bool> found(graph.size(), false);
    queue<int> q;
    q.push(s);
    found[s] = true;
    int step = 0;
    int size;
    while (!q.empty())
    {
        size = q.size();
        for (int i = 0; i < size; i++)
        {
            int cur = q.front();
            q.pop();
            cout << "经过步数：" << step << "，到达节点" << cur << endl;
            for (auto &e : graph.neighbors(cur))
            {
                if (found[e.to])
                {
                    continue;
                }
                q.push(e.to);
                found[e.to] = true;
            }
        }
        step++;
    }
}
class State
{
public:
    int node;
    int step;

    State(int node, int step) : node(node), step(step) {};
};
void bfs3(WeightedDiGraph &graph, int s)
{
    vector<bool> found(graph.size(), false);
    queue<State> q;
    q.push(State(s, 0));
    found[s] = true;
    while (!q.empty())
    {
        State state = q.front();
        q.pop();
        cout << "经过步数：" << state.step << "，到达节点" << state.node << endl;
        for (auto &e : graph.neighbors(state.node))
        {
            if (found[e.to])
                continue;
            q.push(State(e.to, state.step + e.weight));
            found[e.to] = true;
        }
    }
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
    bfs3(graph, 0);
}

int main()
{
    test01();
}