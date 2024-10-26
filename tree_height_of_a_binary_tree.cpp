// https://www.hackerrank.com/challenges/tree-height-of-a-binary-tree/problem

#include <iostream>
#include <vector>
#include <memory>

class BinaryTree {
    public:
        struct Node {
            int data;
            std::unique_ptr<Node> left;
            std::unique_ptr<Node> right;

            explicit Node(int data) : data(data) {}
        };

        BinaryTree() = delete;
        explicit BinaryTree(int data) : root(std::make_unique<Node>(data)) {}

        void insert(int data) {
            root = insert_node(std::move(root), data);
        }

        int height() {
            return calculate_height(root);
        }

    private:
        std::unique_ptr<Node> insert_node(std::unique_ptr<Node> root, int data) {
            if (!root) {
                return std::make_unique<Node>(data);
            }

            if (data < root->data) {
                root->left = insert_node(std::move(root->left), data);
            } else {
                root->right = insert_node(std::move(root->right), data);
            }

            return root;
        }

        int calculate_height(const std::unique_ptr<Node>& root) {
            if (!root) {
                return -1;
            }

            int left_height = calculate_height(root->left);
            int right_height = calculate_height(root->right);

            return std::max(left_height, right_height) + 1;
        }

    private:
        std::unique_ptr<Node> root;
};

int main () {
    int n, root;
    std::cin >> n;
    std::cin >> root;

    BinaryTree tree(root);

    for (int i = 0; i < n-1; i++) {
        int data;
        std::cin >> data;

        tree.insert(data);
    }

    std::cout << tree.height() << std::endl;
    return 0;
}
