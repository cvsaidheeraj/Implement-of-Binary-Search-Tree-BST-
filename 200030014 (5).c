#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a node in the binary search tree
struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node with the given key
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a new node with the given key into the BST
struct Node* insert(struct Node* root, int key) {
    // If the tree is empty, create a new node and return it as the root
    if (root == NULL)
        return createNode(key);

    // Recursively insert the key in the left or right subtree
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);

    return root;
}

// Function to perform an inorder traversal of the BST and print the nodes
void inorder(struct Node* root, FILE* output) {
    if (root == NULL)
        return;

    // Visit the left subtree, print the current node, then visit the right subtree
    inorder(root->left, output);
    fprintf(output, "%d ", root->key);
    inorder(root->right, output);
}

// Function to perform a preorder traversal of the BST and print the nodes
void preorder(struct Node* root, FILE* output) {
    if (root == NULL)
        return;

    // Print the current node, visit the left subtree, then visit the right subtree
    fprintf(output, "%d ", root->key);
    preorder(root->left, output);
    preorder(root->right, output);
}

// Function to perform a postorder traversal of the BST and print the nodes
void postorder(struct Node* root, FILE* output) {
    if (root == NULL)
        return;

    // Visit the left subtree, visit the right subtree, then print the current node
    postorder(root->left, output);
    postorder(root->right, output);
    fprintf(output, "%d ", root->key);
}

// Function to search for a key in the BST
struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    // Recursively search in the left or right subtree based on the key
    if (key < root->key)
        return search(root->left, key);

    return search(root->right, key);
}

// Function to find the node with the minimum key in the BST
struct Node* minimum(struct Node* root) {
    if (root == NULL)
        return NULL;

    // Keep traversing left until the leftmost leaf is found
    while (root->left != NULL)
        root = root->left;

    return root;
}

// Function to find the node with the maximum key in the BST
struct Node* maximum(struct Node* root) {
    if (root == NULL)
        return NULL;

    // Keep traversing right until the rightmost leaf is found
    while (root->right != NULL)
        root = root->right;

    return root;
}

// Function to find the successor of a node with a given key in the BST
struct Node* successor(struct Node* root, int key, int* found) {
    struct Node* current = search(root, key);
    if (current == NULL) {
        *found = 1;
        return NULL;
    }

    // If the node has a right subtree, find the leftmost node in that subtree
    if (current->right != NULL) {
        current = current->right;
        while (current->left != NULL)
            current = current->left;
        return current;
    } else {
        // If the node does not have a right subtree, find the closest ancestor
        // whose left child is also an ancestor of the given node
        struct Node* succ = NULL;
        struct Node* ancestor = root;
        while (ancestor != current) {
            if (current->key < ancestor->key) {
                succ = ancestor;
                ancestor = ancestor->left;
            } else
                ancestor = ancestor->right;
        }
        return succ;
    }
}

// Function to find the predecessor of a node with a given key in the BST
struct Node* predecessor(struct Node* root, int key, int* found) {
    struct Node* current = search(root, key);
    if (current == NULL) {
        *found = 1;
        return NULL;
    }

    // If the node has a left subtree, find the rightmost node in that subtree
    if (current->left != NULL) {
        current = current->left;
        while (current->right != NULL)
            current = current->right;
        return current;
    } else {
        // If the node does not have a left subtree, find the closest ancestor
        // whose right child is also an ancestor of the given node
        struct Node* pred = NULL;
        struct Node* ancestor = root;
        while (ancestor != current) {
            if (current->key > ancestor->key) {
                pred = ancestor;
                ancestor = ancestor->right;
            } else
                ancestor = ancestor->left;
        }
        return pred;
    }
}

// Function to parse a command and execute the corresponding operation on the BST
void parseCommand(struct Node** root, const char* command, FILE* output) {
    char cmd[15];
    int key;
    int found = 0;

    sscanf(command, "%s %d", cmd, &key);

    if (strcmp(cmd, "insert") == 0) {
        *root = insert(*root, key);
        fprintf(output, "%d inserted\n", key);
    } else if (strcmp(cmd, "inorder") == 0) {
        if (*root == NULL) {
            fprintf(output, "\n");
        } else {
            inorder(*root, output);
            fprintf(output, "\n");
        }
    } else if (strcmp(cmd, "preorder") == 0) {
        if (*root == NULL) {
            fprintf(output, "\n");
        } else {
            preorder(*root, output);
            fprintf(output, "\n");
        }
    } else if (strcmp(cmd, "postorder") == 0) {
        if (*root == NULL) {
            fprintf(output, "\n");
        } else {
            postorder(*root, output);
            fprintf(output, "\n");
        }
    } else if (strcmp(cmd, "successor") == 0) {
        if (*root == NULL) {
            fprintf(output, "Tree is empty\n");
        } else {
            struct Node* succ = successor(*root, key, &found);
            if (*root == NULL) {
                fprintf(output, "Tree is empty\n");
            } else if (found) {
                fprintf(output, "%d does not exist\n", key);
            } else if (succ == NULL) {
                fprintf(output, "successor of %d does not exist\n", key);
            } else {
                fprintf(output, "%d\n", succ->key);
            }
        }
    } else if (strcmp(cmd, "predecessor") == 0) {
        if (*root == NULL) {
            fprintf(output, "Tree is empty\n");
        } else {
            struct Node* pred = predecessor(*root, key, &found);
            if (*root == NULL) {
                fprintf(output, "Tree is empty\n");
            } else if (found) {
                fprintf(output, "%d does not exist\n", key);
            } else if (pred == NULL) {
                fprintf(output, "predecessor of %d does not exist\n", key);
            } else {
                fprintf(output, "%d\n", pred->key);
            }
        }
    } else if (strcmp(cmd, "minimum") == 0) {
        if (*root == NULL) {
            fprintf(output, "\n");
        } else {
            struct Node* min = minimum(*root);
            fprintf(output, "%d\n", min->key);
        }
    } else if (strcmp(cmd, "maximum") == 0) {
        if (*root == NULL) {
            fprintf(output, "\n");
        } else {
            struct Node* max = maximum(*root);
            fprintf(output, "%d\n", max->key);
        }
    } else if (strcmp(cmd, "search") == 0) {
        struct Node* node = search(*root, key);
        if (node == NULL) {
            fprintf(output, "%d not found\n", key);
        } else {
            fprintf(output, "%d found\n", key);
        }
    }
}

// Main function
int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: program_name input_file\n");
        return 1;
    }

    // Open the input and output files
    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen("output.txt", "w");
    struct Node* root = NULL;

    if (input == NULL) {
        printf("Error opening input file\n");
        return 1;
    }

    char command[50];
    // Read commands from the input file and execute them on the BST
    while (fgets(command, sizeof(command), input) != NULL) {
        parseCommand(&root, command, output);
    }

    // Close the input and output files
    fclose(input);
    fclose(output);

    return 0;
}
