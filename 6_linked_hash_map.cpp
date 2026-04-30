// 实际上就是把键-值对改成键-（带前驱指针和后驱指针的节点）
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

template <typename K, typename V>
struct Node
{
    K key;
    V value;
    Node *next;
    Node *prev;
    Node(K k, V v) : key(k), value(v), next(nullptr), prev(nullptr) {};
};

template <typename K, typename V>
class LinkedHashMap
{
    std::unordered_map<K, Node<K, V> *> map;
    Node<K, V> *head; // 虚拟的头节点
    Node<K, V> *tail; // 虚拟的尾节点

public:
    LinkedHashMap()
    {
        head = new Node<K, V>(K(), V());
        tail = new Node<K, V>(K(), V());
        head->next = tail;
        tail->prev = head;
    }

    ~LinkedHashMap()
    {
        // 释放链表中的节点
        Node<K, V> *p = head;
        while (p != nullptr)
        {
            Node<K, V> *next = p->next;
            delete p;
            p = next;
        }
    }

    // 增
    void put(K key, V val)
    {
        // 还要先检查一下有无重复值
        if (map.find(key) != map.end())
        {
            map[key]->value = val;
            return;
        }
        // 把节点加入到链表尾巴
        auto temp = tail->prev;
        Node<K, V> *newnode = new Node<K, V>(key, val);
        temp->next = newnode;
        newnode->prev = temp;
        newnode->next = tail;
        tail->prev = newnode;

        // 把节点加入到hashmap
        map.insert({key, newnode});
    }
    // 删
    void remove(K key)
    {
        auto it = map.find(key);
        if (it != map.end())
        {
            auto node = it->second;
            map.erase(it);
            auto left = node->prev;
            auto right = node->next;
            left->next = right;
            right->prev = left;
            delete node;
            return;
        }
        throw std::runtime_error("没找到对应的key");
    }

    // 查
    V get(K key)
    {
        auto it = map.find(key);
        if (it == map.end())
        {
            throw std::runtime_error("没找到对应的key");
        }
        auto node = it->second;
        return node->value;
    }

    // 其他
    bool containsKey(K key)
    {
        return map.find(key) != map.end();
    }

    std::vector<K> keys()
    {
        std::vector<K> keyslist;
        auto p = head->next;
        while (p != tail)
        {
            keyslist.push_back(p->key);
            p = p->next;
        }
        return keyslist;
    }

    size_t size()
    {
        return map.size();
    }
};

int main()
{
    LinkedHashMap<std::string, int> map;
    map.put("a", 1);
    map.put("b", 2);
    map.put("c", 3);
    map.put("d", 4);
    map.put("e", 5);

    // output: a b c d e
    for (const auto &key : map.keys())
    {
        std::cout << key << " ";
    }
    std::cout << std::endl;

    map.remove("c");
    std::cout << map.containsKey("c") << std::endl;

    // output: a b d e
    for (const auto &key : map.keys())
    {
        std::cout << key << " ";
    }
    std::cout << std::endl;

    return 0;
}