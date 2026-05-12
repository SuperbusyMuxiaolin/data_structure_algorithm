#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct Node
{
    int val;
    Node *left;
    Node *right;
    Node(int value) : val(value), left(nullptr), right(nullptr) {};
};

class solution1
{
public:
    int minDepth(Node *root)
    {
        if (root == nullptr)
            return 0;
        if (root->left == nullptr && root->right == nullptr)
            return 1;
        if (root->left == nullptr)
            return minDepth(root->right) + 1;
        if (root->right == nullptr)
            return minDepth(root->left) + 1;
        return std::min(minDepth(root->left), minDepth(root->right)) + 1;
    }
};

class solution2
{
public:
    int mindepth = __INT_MAX__;
    int currentdepth = 0;

    int minDepth(Node *root)
    {
        if (root == nullptr)
        {
            return 0;
        }
        traverse(root);
        return mindepth;
    }

    void traverse(Node *root)
    {
        if (root == nullptr)
            return;
        currentdepth++;
        if (root->left == nullptr && root->right == nullptr)
        {
            mindepth = std::min(currentdepth, mindepth);
        }
        traverse(root->left);
        traverse(root->right);
        currentdepth--;
    }
};

class solution3
{
public:
    int minDepth(Node *root)
    {
        if (root == nullptr)
        {
            return 0;
        }
        std::queue<Node *> q;
        q.push(root);
        int depth = 1;
        while (!q.empty())
        {
            int size = q.size();
            for (int i = 0; i < size; i++)
            {
                Node *cur = q.front();
                q.pop();
                if (cur->left == nullptr && cur->right == nullptr)
                {
                    return depth;
                }
                if (cur->left != nullptr)
                {
                    q.push(cur->left);
                }
                if (cur->right != nullptr)
                {
                    q.push(cur->right);
                }
            }
            depth++;
        }
        return depth;
    }
};

int main()
{
    // 创建一个二叉树
    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    // root->left->left = new Node(7);
    // root->left->right = new Node(4);
    root->left->left = nullptr;
    root->left->right = nullptr;
    root->right->left = new Node(5);
    root->right->right = new Node(6);
    solution3 s;
    std::cout << s.minDepth(root) << std::endl;
    delete root->left->left;
    delete root->left->right;
    delete root->right->left;
    delete root->right->right;
    delete root->left;
    delete root->right;
    delete root;
    return 0;
}