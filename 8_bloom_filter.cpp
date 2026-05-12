#include <iostream>
#include <vector>
using namespace std;
#include <cmath>
#include <functional>

class Bitmap
{
    vector<unsigned long> v;
    // 能存多少位
    int size;

public:
    Bitmap(int size)
    {
        v.resize((size >> 6) + 1, 0);
        this->size = size;
    }

    // 查某一位是否为1
    bool get(int bitIndex)
    {
        if (bitIndex < 0 || bitIndex >= this->size)
        {
            throw runtime_error("索引越界");
        }
        int arrindex = bitIndex >> 6;
        int offindex = bitIndex & 63;
        return (v[arrindex] & (1ULL << offindex)) != 0;
    }

    // 把某一位设置为1
    void settrue(int bitIndex)
    {
        if (bitIndex < 0 || bitIndex >= this->size)
        {
            throw runtime_error("索引越界");
        }
        int arrindex = bitIndex >> 6;
        int offindex = bitIndex & 63;

        v[arrindex] = v[arrindex] | (1ULL << offindex);
    }

    // 把某一位设置为0
    void setfalse(int bitIndex)
    {
        if (bitIndex < 0 || bitIndex >= this->size)
            throw runtime_error("索引越界");
        int arrindex = bitIndex >> 6;
        int offindex = bitIndex & 63;

        v[arrindex] = v[arrindex] & ~(1ULL << offindex);
    }
};

template <typename T>
class simple_bloom_filter
{
    Bitmap *bitmap;
    int bitsize;
    int k;
    // 模拟多个哈希函数，实际生产环境中应该使用更复杂的哈希算法
    int hash(const T &element, int seed)
    {
        // 这里简化处理，用内置的 hash 函数和递增的索引作为种子来模拟多个哈希函数
        // 在实际应用中，为了减少哈希冲突，应该使用更复杂的哈希函数
        // 同时，种子也应该选择无规律的大质数，而不是简单的递增索引
        std::hash<T> hasher;
        size_t h = hasher(element);
        return abs(static_cast<int>(h) + seed) % bitsize;
    }

public:
    simple_bloom_filter(int bits, int hashnum) : bitsize(bits), k(hashnum)
    {
        bitmap = new Bitmap(bits);
    }
    ~simple_bloom_filter()
    {
        delete bitmap;
    }

    // 增加
    void add(const T &element)
    {
        for (int i = 0; i < k; i++)
        {
            int index = hash(element, i);
            bitmap->settrue(index);
        }
    }

    // 查找，返回bool
    bool find(const T &element)
    {
        for (int i = 0; i < k; i++)
        {
            int index = hash(element, i);
            if (bitmap->get(index) != true)
            {
                return false;
            }
        }
        return true;
    }
};

int main()
{
    // 创建一个位数组大小为 1000000，使用 3 个哈希函数的布隆过滤器
    simple_bloom_filter<string> bloomFilter(1000000, 3);

    // 添加元素
    bloomFilter.add("apple");
    bloomFilter.add("banana");
    bloomFilter.add("orange");

    // 检查元素是否存在
    cout << "Contains apple: " << (bloomFilter.find("apple") ? "true" : "false") << endl;   // true
    cout << "Contains banana: " << (bloomFilter.find("banana") ? "true" : "false") << endl; // true
    cout << "Contains grape: " << (bloomFilter.find("grape") ? "true" : "false") << endl;   // false

    return 0;
}