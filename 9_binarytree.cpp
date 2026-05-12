#include <iostream>
#include <vector>
#include <queue>

struct Node
{
    int val;
    Node *left;
    Node *right;
    Node(int value) : val(value), left(nullptr), right(nullptr) {};
};

class State
{
public:
    Node *node;
    int depth; // 路径权重和
    State(Node *n, int de) : node(n), depth(de) {};
};

void traverse(Node *root)
{
    if (root == nullptr)
    {
        return;
    }

    // 前序位置
    traverse(root->left);
    // 中序位置
    traverse(root->right);
    // 后序位置
}

void forward_traverse(Node *root)
{
    if (root == nullptr)
    {
        return;
    }

    // 前序位置
    std::cout << root->val << " ";
    forward_traverse(root->left);
    forward_traverse(root->right);
}

void middle_traverse(Node *root)
{
    if (root == nullptr)
    {
        return;
    }
    middle_traverse(root->left);
    std::cout << root->val << " ";
    middle_traverse(root->right);
}

void last_traverse(Node *root)
{
    if (root == nullptr)
    {
        return;
    }
    last_traverse(root->left);
    last_traverse(root->right);
    std::cout << root->val << " ";
}

void leveltraverse(Node *root)
{
    if (root == nullptr)
    {
        return;
    }
    std::queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        Node *cur = q.front();
        std::cout << cur->val << "\t";
        q.pop();
        if (cur->left != nullptr)
        {
            q.push(cur->left);
        }
        if (cur->right != nullptr)
        {
            q.push(cur->right);
        }
    }
}

void leveltraverse_depth(Node *root)
{
    if (root == nullptr)
    {
        return;
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
            std::cout << "depth:" << depth << "\tvalue:" << cur->val << std::endl;
            q.pop();
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
}

void leveltraverse_state(Node *root)
{
    if (!root)
    {
        return;
    }
    std::queue<State> q;
    q.push(State(root, 1));
    while (!q.empty())
    {
        State cur = q.front();
        std::cout << "depth:" << cur.depth << "\tvalue" << cur.node->val << std::endl;
        q.pop();
        if (cur.node->left != nullptr)
        {
            q.push(State(cur.node->left, cur.depth + 1));
        }
        if (cur.node->right != nullptr)
        {
            q.push(State(cur.node->right, cur.depth + 1));
        }
    }
}

int main()
{
    // 创建一个二叉树
    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(7);
    root->left->right = new Node(4);
    root->right->left = new Node(5);
    root->right->right = new Node(6);
    forward_traverse(root);
    std::cout << std::endl;
    middle_traverse(root);
    std::cout << std::endl;
    last_traverse(root);
    std::cout << std::endl;
    leveltraverse(root);
    std::cout << std::endl;
    leveltraverse_depth(root);
    std::cout << std::endl;
    leveltraverse_state(root);
    std::cout << std::endl;
    delete root->left->left;
    delete root->left->right;
    delete root->right->left;
    delete root->right->right;
    delete root->left;
    delete root->right;
    delete root;
    return 0;
}