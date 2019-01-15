/* @Author
Student Name: Raif Mirza Erten
Student ID : 150160022
Date: 24.12.2018 */

#include <iostream>
#include <fstream>
using namespace std;

// A Tree node
struct Node
{
    int info;
    struct Node *left, *right;
};

// Utility function to create a new node
Node* newNode(int info)
{
    Node* temp = new Node;
    temp->info = info;
    temp->left = temp->right = NULL;
    return (temp);
}

struct node{
  int data;
  node *next;
};
//Stack for creating path for result
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
		 r.push(root->info);
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




//Print paths
void printutil(Node* curr_node, int sum,int sum2, stack s, Node*root,int &check)
{
		if (curr_node == NULL)
		{
			return;
		}


    // add the current node's value
    sum2 += curr_node->info;

    // add the value to path
    s.push(curr_node->info);

    // print the required path
    if (sum2 == sum )
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
        printutil(curr_node->left, sum, sum2, s,root,check);
      }
    // if right child exists
     if (curr_node->right != NULL)
		{
        printutil(curr_node->right, sum, sum2, s,root,check);
}
    s.pop();
}


void printPaths(Node *root, int sum,int k )
{
    struct stack s;
    s.create();
		int check=0;
    printutil(root->left, sum,k, s, root,check);
		if(check == 0)
		{
			cout<<"No Path Found"<<endl;
		}
		check=0;
		  printutil(root->right, sum,k, s, root,check);
			if(check == 0)
			{
				cout<<"No Path Found"<<endl;
			}
    s.close();
}
//Inserting nodes to tree
Node* insert(int arr[], Node* root,int i, int n)
{
    // Base case for recursion
    if (i < n)
    {
        Node* temp = newNode(arr[i]);
        root = temp;

        // insert left child
        root->left = insert(arr,root->left, 2 * i + 1, n);

        // insert right child
        root->right = insert(arr,root->right, 2 * i + 2, n);
    }
    return root;
}


int main (int argc , char** argv)
{
    int x;
		stack reading_file;
		reading_file.create();
		ifstream thatfile(argv[1]);
		if(thatfile.is_open()){
			while(true){
		    thatfile>>x;
				reading_file.push(x);
		    if(thatfile.eof()){
		     break;
		   }
		 }
		 thatfile.close();
		}
		int sum=reading_file.pop();
    int size = reading_file.size;
    int *array=new int[size];
		for(int i=size-1;i>-1;i--)
		{
			array[i]=reading_file.pop();
		}
	 	Node *root  = NULL;
	 	root = insert(array,root,0,size);
		int k = root->info;
    reading_file.close();
    printPaths(root, sum,k);

    delete array;
    (void)argc;

    return 0;
}
