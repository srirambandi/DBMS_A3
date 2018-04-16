#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

class Node{
public:
    double point[20];
    Node *left,*right;
};

Node* insert(Node *root, double point[20],int depth,int dim){

    if(root==NULL)
    {
        root = new Node();
        for(int i=0; i<dim; i++)
        {
            root->point[i] = point[i];
            root->left = root->right = NULL;
        }
        return root;
    }

    int split_dim = depth % dim;

    if(point[split_dim] < root->point[split_dim] )
    {
        root->left = insert(root->left, point, depth+1, dim);
    }
    else
        root->right = insert(root->right, point, depth+1, dim);

    return root;
}

Node* constructKdTree(double points[][20],int n,int dim,Node* root){

    for(int i=0;i<n;i++){
        root = insert(root,points[i],0,dim);
    }

    return root;
}


int distance(){}



struct greaterthan
{
  bool operator()(const node& lhs, const node& rhs) const
  {
    return lhs.point < rhs.point;
  }
};

struct lesserthan
{
  bool operator()(const node& lhs, const node& rhs) const
  {
    return lhs.point > rhs.point;
  }
};

int distance(double[] a, double[] b,int d_q){
   double sum=0;
   for(int i=0;i<d_q;i++){
	   sum = sum+ pow((a[i]-b[i]),2);
	   }
	sum = pow(sum,0.5);

	return sum;
}


int main(int argc, char* argv[]) {

    char* dataset_file = argv[1];


    // [TODO] Construct kdTree using dataset_file here
    int n,dim;
    ifstream infile;
    infile.open(dataset_file);
    infile >> dim >> n;

    double points[n][20];
    for(int i=0;i<n;i++){
        for(int j=0;j<dim;j++){
            infile >> points[i][j];
//            cerr<<points[i][j]<<" ";
        }
//        cerr<<endl;
    }
    infile.close();

    Node *root = NULL;
    root = constructKdTree(points,n,dim,root);






    // Request name/path of query_file from parent by just sending "0" on stdout
    cout << 0 << endl;

    // Wait till the parent responds with name/path of query_file and k | Timer will start now
    char* query_file = new char[100];
    int k;
    cin >> query_file >> k;
    // cerr << dataset_file << " " << query_file << " " << k << endl;


    // [TODO] Read the query point from query_file, do kNN using the kdTree and output the answer to results.txt
    infile.open(query_file);
    int d_q;
    cin>>d_q;
    double query_point[20];
    for(int i=0;i<d_q;i++){
        infile>>query_point[i];
    }
    infile.close();

    priority_queue <node, vector<node>, greaterthan > max_heap;
	//max_heap(root);
	priority_queue<node,vector<node>, lessthan> min_heap;
	min_heap(root);
	//generate k random points of d_q dimension

	//double x= rand() % 2.0 +  2.0;
	for(int i=0;i<k;i++){
		double[] pt;
		for(intj=0;j<d_q;j++){
			pt[j]= rand() % 2.0 +  2.5;
		}
		double x = distance(query_point,pt,d_q);
		max_heap.push(x,pt);

	}

	while(distance(min_heap.top(),query_point,d_q)< max_heap.top()){
		Node n = min_heap.top();
		min_heap.pop();
		if(n->left!=NULL || n->right!=NULL){
			if(n->left!=NULL){
			min_heap.push(n->left);
			}
			if(n->right!=NULL){
			min_heap.push(n->right);
			}
		}
		else if(n->left==NULL && n->right==NULL){
			max_heap.push(distance(n,query_point,d_q),n);
		}
	}



	//

    // Convey to parent that results.txt is ready by sending "1" on stdout | Timer will stop now and this process will be killed
    cout << 1 << endl;
}
