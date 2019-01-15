#include <iostream>
#include <fstream>
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

struct node{
  int data;
  node *next;
};
struct stack{
  node *head;
	int size;
  int topstack;
  void create();
  void close();
  void push(int);
  int pop();
	void display();
	void reverser(Node*);

};

void stack::create(){
  head = NULL;

}
void stack::close(){
  node *p;
  while(head){
    p = head;
    head = head->next;
    delete p;
  }
}

void stack::push(int newdata){
  node *newnode = new node;
  newnode->data = newdata;
  newnode->next = head;
  head = newnode;
  topstack = newdata;
	size++;
}

int stack::pop(){
  node *topnode;
  int temp;
  topnode = head;
  head = head->next;
  if(head == NULL){
    topstack = 0;
  }
  else{
      topstack = head->data;
  }

  temp = topnode->data;
  delete topnode;
  size--;
  return temp;

}

void stack::reverser(Node* root)
{

		 stack r;
		 r.create();
		 node*iter;
		 iter=head;
		 while(iter)
		 {
			 r.push(iter->data);
			 iter=iter->next;
		 }
		 r.push(root->key);
		 r.display();
		 delete iter;
}


void stack::display()
{

		 node*iter;
		 iter=head;
		 while(iter)
		 {
			 cout<<iter->data<<" ";
			 iter=iter->next;
		 }
		 delete iter;
}





void printPathsUtil(Node* curr_node, int sum,
             int sum_so_far, stack s, Node*root,int &check)
{
		if (curr_node == NULL)
		{
			return;
		}


    // add the current node's value
    sum_so_far += curr_node->key;

    // add the value to path
    s.push(curr_node->key);

    // print the required path
    if (sum_so_far == sum )
    {



			if(check == 0){
        cout << "Path Found: ";
        s.reverser(root);
        cout <<endl;
				check=1;

				}


    }
    // if left child exists

		 if (curr_node->left != NULL)
		{
        printPathsUtil(curr_node->left, sum, sum_so_far, s,root,check);
}
    // if right child exists
     if (curr_node->right != NULL)
		{
        printPathsUtil(curr_node->right, sum, sum_so_far, s,root,check);
}

    // Remove last element from path
  	// and move back to parent
    s.pop();
}

// Wrapper over printPathsUtil
void printPaths(Node *root, int sum,int k )
{
    struct stack s;
    s.create();
		int check=0;
    printPathsUtil(root->left, sum,k, s, root,check);
		if(check == 0)
		{
			cout<<"No Path Found "<<endl;
		}
		check=0;
		  printPathsUtil(root->right, sum,k, s, root,check);
			if(check == 0)
			{
				cout<<"No Path Found "<<endl;
			}
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
// Driver program
int main (int argc , char** argv)
{



int x;
			 stack esek;

			 esek.create();
			 ifstream thatfile(argv[1]);

			 if(thatfile.is_open()){

				 while(true){
		       thatfile>>x;
					 esek.push(x);
		       if(thatfile.eof()){
		        break;
		       }
		     }
		   thatfile.close();
		   }

			 int sum=esek.pop();
       int size = esek.size;


       int array[size];



			 for(int i=size-1;i>-1;i--)
			 {
				  array[i]=esek.pop();

			 }

	 		Node *root  = NULL;
	 		root = insertLevelOrder(array,root,0,size);
			int k = root->key;


      esek.close();

    printPaths(root, sum,k);

    (void)argc;

    return 0;
}
