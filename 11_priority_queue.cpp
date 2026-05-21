#include <iostream>
#include <vector>
#include <functional>
using namespace std;

class mini_PriorityQueue
{
    std::vector<int> heap;
    // 当前堆中的元素
    int size;
    int parent(int node)
    {
        return (node - 1) / 2;
    }
    int left(int node)
    {
        return 2 * node + 1;
    }
    int right(int node)
    {
        return node * 2 + 2;
    }
    // 下沉
    void sink(int node)
    {
        while (left(node) < size)
        {
            int min = left(node);
            if (right(node) < size && heap[right(node)] < heap[min])
            {
                min = right(node);
            }
            if (heap[node] <= heap[min])
            {
                break;
            }
            std::swap(heap[node], heap[min]);
            node = min;
        }
    }

    void swim(int node)
    {
        while (node > 0 && heap[node] < heap[parent(node)])
        {
            std::swap(heap[parent(node)], heap[node]);
            node = parent(node);
        }
    }

public:
    // 创建一个容量为 capacity 的优先级队列
    mini_PriorityQueue(int capacity) : size(0)
    {
        heap.resize(capacity);
    }

    // 返回队列中的元素个数
    int get_size()
    {
        return this->size;
    }

    // 向队列中插入一个元素
    void push(int val)
    {
        heap[size] = val;
        swim(size);
        size++;
    }

    // 返回队列中的最小元素（堆顶元素）
    int peek()
    {
        return heap[0];
    }

    // 删除并返回队列中的最小元素（堆顶元素）
    int pop()
    {
        int temp = heap[0];
        heap[0] = heap[size - 1];
        size--;
        sink(0);
        return temp;
    }
};

template <typename T>
class PriorityQueue
{
    std::vector<T> heap;
    int size;
    function<bool(T &t1, T &t2)> compare;
    // 父节点的索引
    int parent(int node)
    {
        return (node - 1) / 2;
    }
    // 左子节点的索引
    int left(int node)
    {
        return node * 2 + 1;
    }
    // 右子节点的索引
    int right(int node)
    {
        return node * 2 + 2;
    }

    void swim(int node)
    {
        while (node > 0 && compare(heap[node], heap[parent(node)]))
        {
            swap(heap[node], heap[parent(node)]);
            node = parent(node);
        }
    }
    void sink(int node)
    {
        while (left(node) < size)
        {
            int com = left(node);
            if (right(node) < size && compare(heap[right(node)], heap[left(node)]))
            {
                com = right(node);
            }
            if (compare(heap[node], heap[com]) || heap[node] == heap[com])
            {
                break;
            }
            swap(heap[node], heap[com]);
            node = com;
        }
    }

public:
    PriorityQueue(function<bool(T &t1, T &t2)> com) : size(0), compare(std::move(com))
    {
    }

    // push
    void push(T val)
    {
        heap.push_back(val);
        swim(size);
        size++;
    }

    // pop
    T pop()
    {
        T temp = heap[0];
        heap[0] = heap[size - 1];
        heap.pop_back();
        size--;
        sink(0);
        return temp;
    }
};

void test01()
{
    mini_PriorityQueue pq(5);
    pq.push(3);
    pq.push(2);
    pq.push(1);
    pq.push(5);
    pq.push(4);

    cout << pq.pop() << endl; // 1
    cout << pq.pop() << endl; // 2
    cout << pq.pop() << endl; // 3
    cout << pq.pop() << endl; // 4
    cout << pq.pop() << endl; // 5
}

void test02()
{
    PriorityQueue<int> pq([](int &t1, int &t2)
                          { return t1 > t2; });
    pq.push(3);
    pq.push(2);
    pq.push(1);
    pq.push(5);
    pq.push(4);

    cout << pq.pop() << endl; // 1
    cout << pq.pop() << endl; // 2
    cout << pq.pop() << endl; // 3
    cout << pq.pop() << endl; // 4
    cout << pq.pop() << endl; // 5
}

int main()
{
    test02();
}