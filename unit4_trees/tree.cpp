#include <iostream>
#include <cstddef>

using std::cout;
using std::endl;

class Node {
    int value;
public:
    Node* left;       // left child
    Node* right;      // right child
    Node* p;          // parent
    Node(int data) {
        value = data;
        left = NULL;
        right = NULL;
        p  = NULL;
    }
    ~Node() {
    }
    int d() {
        return value;
    }
    void set_data(int value_given) {
    	value = value_given;
	}
    void print() {
        std::cout << value << std::endl;
    }
};

void print_tree(Node *tree_root);
void insert(Node *insert_node, Node *&tree_root);
void delete_node(int value, Node *&tree_root);
Node* search(int value, Node *tree_root);

int main(int argc, const char * argv[])
{
	Node *root = NULL;
 	int inserted[] = {2, 1, 4, 5, 9, 3, 6, 7, 10, 12, 11};
	for (int i = 0; i <= 10; i++)
	{
		Node* newNode = new Node(inserted[i]);
		insert(newNode, root);	
	}  
	
	cout << "Printing values in tree after inserts: " <<"\n";
	print_tree(root);
	
	delete_node(4, root);
	cout << "Printing values in tree after deleting 4: " <<"\n";
	print_tree(root);
	
	delete_node(9, root);
	cout << "Printing values in tree after deleting 9: " <<"\n";
	print_tree(root);
	
	Node *search_twelve = search(12, root);
	if (search_twelve == NULL)
		cout << "Twelve was not found in the tree" <<"\n";
	else
		cout << "Node value found when searching for 12: " << search_twelve->d() <<"\n";
	
	Node *search_four = search(4, root);
	if (search_four == NULL)
		cout << "Four was not found in the tree" <<"\n";
	else
		cout << "Node value found when searching for 4: " << search_four->d() <<"\n";
	
	system("pause");
}

// For Testing
void print_tree(Node *tree_root){
	if (tree_root != NULL)
	{
		tree_root->print();
		print_tree(tree_root->left);
		print_tree(tree_root->right);
	}
}

void insert(Node *insert_node, Node *&tree_root){ 
	if (tree_root == NULL)
	{
		 tree_root = insert_node;
	//	 cout << "insert_node value is " << insert_node->d() << "\n";
	//	 cout << "tree_root value is " << tree_root->d() << "\n";
		 return;
	}
	else if (insert_node->d() < tree_root->d())
	{
		insert(insert_node, tree_root->left);
	}
	else
	{
		insert(insert_node, tree_root->right);
	}
}

void delete_node(int value, Node *&tree_root){
//	cout << "tree_root value is " << &tree_root << "\n";
	if (tree_root == NULL)
	{
		return;
	}
	else if (tree_root->d() < value)
	{
		delete_node(value, tree_root->right);
	}
	else if (tree_root->d() > value)
	{
		delete_node(value, tree_root->left);
	}
	else 
	{
		if ((tree_root->left == NULL) && (tree_root->right == NULL))
		{
			delete tree_root;
			tree_root = NULL;
		}
		else if (tree_root->left == NULL)
		{
			Node *temp = tree_root;
			tree_root = tree_root->right;
			delete temp;
		}
		else if (tree_root->right == NULL)
		{
			Node *temp = tree_root;
			tree_root = tree_root->left;
			delete temp;
		}
		else 
		{
			Node *temp = tree_root->right;
			while (temp->left != NULL)
			{
				temp = temp->left;
			}
			tree_root->set_data(temp->d());
			//cout << "temp value is " << temp->d() << "\n";
			delete_node(tree_root->d(), tree_root->right);
		}
	}
}

Node* search(int value, Node *tree_root){
	if (tree_root != NULL)
	{
		if (tree_root->d() == value)
		{
			//cout << "tree root value is " << tree_root->d() <<"\n";
			return tree_root;
		}
		else if (tree_root->d() > value)
		{
			
			tree_root = search(value, tree_root->left);
		}
		else
		{
			tree_root = search(value, tree_root->right);
		}
	}
}
