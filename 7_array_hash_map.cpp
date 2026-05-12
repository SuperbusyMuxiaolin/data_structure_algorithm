#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

template <typename K, typename V>
struct Node
{
    K key;
    V value;
    Node(K k, V v) : key(k), value(v) {};
};

template <typename K, typename V>
class array_hash_map
{
public:
    // put
    void put(const K &k, const V &v)
    {
        if (map.count(k) > 0)
        {
            int index = map[k];
            table[index].value = v;
            return;
        }
        table.push_back(Node(k, v));
        map.insert({k, table.size() - 1});
    }

    // remove
    void remove(const K &k)
    {
        if (map.count(k) <= 0)
        {
            throw std::runtime_error("找不到这个key值");
        }
        int index = map[k];
        int lastindex = table.size() - 1;
        auto temp = table[lastindex];
        table[lastindex] = table[index];
        table[index] = temp;

        // 后面一个节点换到前面来了，那后面一个节点在map中的value索引就要变为index
        map[table[index].key] = index;

        // 删除map中原来的key
        map.erase(k);

        // 删除数组中最后一个
        table.pop_back();
    }

    // get
    K get(const K &k)
    {
        if (map.count(k) <= 0)
        {
            throw std::runtime_error("找不到这个key值");
        }
        int index = map[k];
        return table[index].value;
    }

    // return random key
    K randomKey()
    {
        return table[random() % table.size()].key;
    }

private:
    std::unordered_map<K, int> map;
    std::vector<Node<K, V>> table;
};
int main()
{
    array_hash_map<int, int> map;
    map.put(1, 1);
    map.put(2, 2);
    map.put(3, 3);
    map.put(4, 4);
    map.put(5, 5);

    cout << map.get(1) << endl; // 1
    cout << map.randomKey() << endl;

    map.remove(4);
    cout << map.randomKey() << endl;
    cout << map.randomKey() << endl;
    cout << map.randomKey() << endl;
    cout << map.randomKey() << endl;
    cout << map.randomKey() << endl;

    return 0;
}