#include<bits/stdc++.h>

using namespace std;

#define Fast1 ios_base::sync_with_stdio(0)
#define Fast2 cin.tie(0)
#define Fast3 cout.tie(0)
#define max(a, b) (a < b ? b : a)
#define min(a, b) ((a > b) ? b : a)
#define mod 1e9 + 7
#define FOR(a, c) for (int(a) = 0; (a) < (c); (a)++)
#define FORL(a, b, c) for (int(a) = (b); (a) <= (c); (a)++)
#define FORR(a, b, c) for (int(a) = (b); (a) >= (c); (a)--)
#define INF 1000000000000000003
typedef long long int ll;
typedef short int SI;
typedef vector<int> vi;
typedef pair<int, int> pi;
#define F first
#define S second
#define PB push_back
#define POB pop_back
#define MP make_pair

// Binary Search Tree

class binarySearchTree
{
public:
	int data;
	binarySearchTree* left;
	binarySearchTree* right;
	binarySearchTree(int data){
		this->data = data;
		left = NULL;
		right = NULL;
	}
	~binarySearchTree(){
		delete left;
		delete right;
	}
	
};

void LevelOrderTraversal(binarySearchTree* root){

	if(!root) return;

	queue<binarySearchTree*> node;
	node.push(root);

	while(!node.empty()){

		int count = node.size();
		while(count--){

			binarySearchTree* ptr = node.front();
			cout<<ptr->data<<" ";
			node.pop();

			if(ptr->left) node.push(ptr->left);

			if(ptr->right) node.push(ptr->right);
		}
		cout<<"\n";

	}
}

binarySearchTree* builtBinaryTree(binarySearchTree* root,int key){

	if(!root) return new binarySearchTree(key);

	if( root->data > key){
		root->left = builtBinaryTree(root->left,key);
	}
	else{
		root->right = builtBinaryTree(root->right,key);
	}
	return root;
}


/// in O(n)
pair<pair<int,int> , bool> isBST(binarySearchTree* root){

	pair<pair<int,int>,bool> res;
	if( !root){
		res = make_pair(make_pair(INT_MIN,INT_MAX),true);
		return res;
	}

	pair<pair<int,int> , bool> leftT = isBST(root->left);
	pair<pair<int,int> , bool> rightT = isBST(root->right);

	int maximum = max(root->data,max(leftT.F.F,rightT.F.F));
	int minimum = min(root->data,min(leftT.F.S,rightT.F.S));
	bool check = ((root->data > leftT.F.F) && (root->data <= rightT.F.S) && leftT.S && rightT.S);

	res = make_pair(make_pair(maximum,minimum),check);
	return res;
}

bool isBST2(binarySearchTree* root, int max = INT_MAX, int min = INT_MIN){

	if( !root) return true;

	if( root->data < min || root->data > max) return false;


	bool leftR = isBST2(root->left, root->data - 1, min);
	bool rightR = isBST2(root->right, max, root->data + 1);

	return (leftR && rightR) ;
}

////Duplicate Node Insertion
binarySearchTree* duplicateInsert( binarySearchTree* root){

	if(!root) return root;

	binarySearchTree* duplicate = new binarySearchTree(root->data);

	duplicate->left = root->left;
	root->left = duplicate;

	root->right = duplicateInsert(root->right);
	duplicate->left = duplicateInsert(duplicate->left);

	return root;
}

int main()
{
	int n;
	cin>>n;
	binarySearchTree* root = NULL;
	FOR(i,n){
		int x;
		cin>>x;
		root = builtBinaryTree(root , x);
	}

	cout<<"\n Level Order Traversal : \n";
	LevelOrderTraversal(root);

	cout<<"\n Duplicate Node Insertion :";
	root = duplicateInsert(root);

	LevelOrderTraversal(root);

	delete root;
	return 0;
}

/*
Input :-
9
8 3 10 1 6 14 4 7 13
11
3 10

output:-


 Level Order Traversal : 
8 
3 10 
1 6 14 
4 7 13 

 Duplicate Node Insertion :8 
8 10 
3 10 14 
3 6 14 
1 6 7 13 
1 4 7 13 
4 
*/
