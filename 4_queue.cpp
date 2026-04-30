#include <iostream>
#include <vector>

// 用链表实现队列，比较简单，略

// 用环形数组实现（双端）队列
template <typename T>
class CircleArray
{
    T *data;
    int size;
    int start;
    int end;
    int cap;

public:
    CircleArray()
    {
        cap = 10;
        data = new T[cap];
        size = 0;
        start = 0;
        end = 0;
    }
    CircleArray(int cap)
    {
        this->cap = cap;
        data = new T[cap];
        size = 0;
        start = 0;
        end = 0;
    }
    void resize(int newcap)
    {
        T *newdata = new T[newcap];
        for (int i = 0; i < size; i++)
        {
            newdata[i] = data[(start + i) % this->cap];
        }
        delete data;
        data = newdata;
        cap = newcap;
        start = 0;
        end = size;
    }

    // 头部增加节点
    void add_first(const T &t)
    {
        if (this->size == this->cap)
        {
            resize(2 * this->cap);
        }
        start = (start - 1 + cap) % cap;
        data[start] = t;
        size++;
    }

    // 头部删除节点
    void removefirst()
    {
        if (this->size == 0)
        {
            throw std::runtime_error("循环数组为空");
            return;
        }
        start = (start + 1) % cap;
        size--;
        if (this->size <= 0.25 * this->cap)
        {
            resize(this->cap / 2);
        }
    }

    // 尾部增加节点
    void addlast(const T &t)
    {
        if (this->size == this->cap)
        {
            resize(2 * this->cap);
        }
        data[end] = t;
        end = (end + 1) % cap;
        size++;
    }

    // 尾部删除节点

    void removelast()
    {
        if (this->size == 0)
        {
            throw std::runtime_error("循环数组为空");
            return;
        }
        end = (end - 1 + cap) % cap;
        size--;
        if (this->size <= 0.25 * this->cap)
        {
            resize(this->cap / 2);
        }
    }

    // 返回头部节点
    T getfirst()
    {
        if (this->size == 0)
            throw std::runtime_error("数据为空");
        return data[start];
    }
    T getlast()
    {
        if (this->size == 0)
        {
            throw std::runtime_error("数据为空");
        }
        return data[(end - 1 + cap) % cap];
    }

    void printall()
    {
        for (int i = 0; i < size; i++)
        {
            std::cout << data[(start + i) % cap] << " ";
        }
        std::cout << std::endl;
    }
};

template <typename T>
class SingleArrayQueue
{
    CircleArray<T> circlearray;

public:
    SingleArrayQueue() = default;
    // 队尾插入
    void push_back(const T &t)
    {
        circlearray.addlast(t);
    }

    // 对头弹出
    T pop_first()
    {
        T temp = circlearray.getfirst();
        circlearray.removefirst();
        return temp;
    }

    // 获取对头
    T get_first()
    {
        return circlearray.getfirst();
    }
};

int main()
{
    CircleArray<int> c1(2);
    c1.add_first(4);
    c1.addlast(5);
    c1.add_first(3);
    c1.printall();
    c1.printall();
    std::cout << c1.getfirst() << std::endl;

    SingleArrayQueue<int> que;
    que.push_back(4);
    que.push_back(5);
    que.pop_first();
    que.pop_first();
    std::cout << que.get_first() << std::endl;
}