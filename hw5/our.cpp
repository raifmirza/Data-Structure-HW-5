#include<iostream>
#include<vector>
using namespace std;

// A Tree node
struct Node
{
    int key;
    struct Node *left, *right;
};

// Utility function to create a new node
Node* newNode(int key)
{
    Node* temp = new Node;
    temp->key = key;
    temp->left = temp->right = NULL;
    return (temp);
}


void printPathsUtil(Node* curr_node, int sum,
             int sum_so_far, vector<int> &path)
{
    if (curr_node == NULL)
        return;

    // add the current node's value
    sum_so_far += curr_node->key;

    // add the value to path
    path.push_back(curr_node->key);

    // print the required path
    if (sum_so_far == sum )
    {
        cout << "Path found: ";
        for (unsigned int i=0; i<path.size(); i++)
            cout << path[i] << " ";

        cout << endl;
    }

    // if left child exists
    if (curr_node->left != NULL)
        printPathsUtil(curr_node->left, sum, sum_so_far, path);

    // if right child exists
    if (curr_node->right != NULL)
        printPathsUtil(curr_node->right, sum, sum_so_far, path);


    // Remove last element from path
    // and move back to parent
    path.pop_back();
}
Node* insertLevelOrder(int arr[], Node* root,
                       int i, int n)
{
    // Base case for recursion
    if (i < n)
    {
        Node* temp = newNode(arr[i]);
        root = temp;

        // insert left child
        root->left = insertLevelOrder(arr,
                   root->left, 2 * i + 1, n);

        // insert right child
        root->right = insertLevelOrder(arr,
                  root->right, 2 * i + 2, n);
    }
    return root;
}
// Wrapper over printPathsUtil
void printPaths(Node *root, int sum)
{
    vector<int> path;
    printPathsUtil(root, sum, 0, path);
}

// Driver program
int main ()
{
    /*   10
       /     \
     28       13
           /     \
         14       15
        /   \     /  \
       21   22   23   24*/
      int array[7]={10, 13, 28, 25, 15, 45,53};
   		Node *root  = NULL;
   		root = insertLevelOrder(array,root,0,7);
      int sum = 38;

    printPaths(root, sum);

    return 0;
}
