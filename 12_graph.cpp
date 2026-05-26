#include <iostream>
#include <vector>
using namespace std;
// --------------------邻接表实现----------------------
// 节点只能是0到n-1
// 加权有向图
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

// 无权图--权重全部默认为1即可

// 无向图--双向的有向图，添加边的时候要同时添加两条，删除的时候也是
class WeightedUndiGraph
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

public:
    WeightedUndiGraph(int N)
    {
        graph.resize(N);
    }

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

    // add edge
    void addEdge(int from, int to, int weight)
    {
        if (hasEdge(from, to))
        {
            cout << "已经有这个边了" << endl;
            return;
        }
        graph[from].emplace_back(to, weight);
        graph[to].emplace_back(from, weight);
    }

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
            }
        }
        for (auto it = graph[to].begin(); it != graph[to].end(); it++)
        {
            if (it->to == from)
            {
                graph[to].erase(it);
            }
        }
    }

    vector<Edge> neighbors(int index)
    {
        return graph[index];
    }
};

//----------------------邻接矩阵实现---------------------
// 有向有权图
class WeightedDiGraph_matrix
{
    struct Edge
    {
        int to;
        int weight;
        Edge(int to, int weight) : to(to), weight(weight) {}
    };
    vector<vector<int>> matrix;

public:
    WeightedDiGraph_matrix(int n)
    {
        matrix = vector<vector<int>>(n, vector<int>(n, 0));
    }
    // 添加边
    void addEdge(int from, int to, int weight)
    {
        matrix[from][to] = weight;
    }

    bool hasEdge(int from, int to)
    {
        return matrix[from][to] > 0;
    }

    void removeEdge(int from, int to)
    {
        if (!hasEdge(from, to))
        {
            cout << "没有这个边" << endl;
            return;
        }
        matrix[from][to] = 0;
    }

    vector<Edge> neighbors(int index)
    {
        vector<Edge> res;
        for (int j = 0; j < matrix.size(); j++)
        {
            if (matrix[index][j] > 0)
            {
                res.emplace_back(j, matrix[index][j]);
            }
        }
        return res;
    }
};

void test01()
{
    WeightedDiGraph graph(3);
    // graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 0, 3);
    graph.addEdge(2, 1, 4);

    cout << boolalpha << graph.hasEdge(0, 1) << endl; // true
    cout << boolalpha << graph.hasEdge(1, 0) << endl; // false

    for (const auto &edge : graph.neighbors(2))
    {
        cout << "2 -> " << edge.to << ", wight: " << edge.weight << endl;
    }
    // 2 -> 0, wight: 3
    // 2 -> 1, wight: 4

    graph.removeEdge(0, 1);
    cout << boolalpha << graph.hasEdge(0, 1) << endl; // false
}

void test02()
{
    WeightedUndiGraph graph(3);
    graph.addEdge(0, 1, 1);
    graph.addEdge(2, 0, 3);
    graph.addEdge(2, 1, 4);

    cout << boolalpha << graph.hasEdge(0, 1) << endl; // true
    cout << boolalpha << graph.hasEdge(1, 0) << endl; // true

    for (const auto &edge : graph.neighbors(2))
    {
        cout << "2 <-> " << edge.to << ", weight: " << edge.weight << endl;
    }
    // 2 <-> 0, weight: 3
    // 2 <-> 1, weight: 4

    graph.removeEdge(0, 1);
    cout << boolalpha << graph.hasEdge(0, 1) << endl; // false
    cout << boolalpha << graph.hasEdge(1, 0) << endl; // false
}

void test03()
{
    WeightedDiGraph_matrix graph(3);
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 0, 3);
    graph.addEdge(2, 1, 4);

    cout << boolalpha;
    cout << graph.hasEdge(0, 1) << endl; // true
    cout << graph.hasEdge(1, 0) << endl; // false

    for (const auto &edge : graph.neighbors(2))
    {
        cout << "2 -> " << edge.to << ", weight: " << edge.weight << endl;
    }
    // 2 -> 0, weight: 3
    // 2 -> 1, weight: 4

    graph.removeEdge(0, 1);
    cout << graph.hasEdge(0, 1) << endl; // false
}
int main()
{
    test03();
    return 0;
}