#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <fstream>

using namespace std;

int D = 20, N1, N2;

struct Node {
    vector<double> point;
    vector<double> r_max;
    vector<double> r_min;
    Node *left, *right;

    double point_l2(double *arr) {
        double dist = 0;
        for (int i = 0; i < D; i++) {
            dist += (point[i] - arr[i])*(point[i] - arr[i]);
        }
        dist = sqrt(dist);
        return dist;
    }
};

class max_heap_obj {
    struct Node* node;
    double mbr_dist;
};

struct Node* newNode(double *arr) {
    struct Node* temp = new Node;

    for ( int i = 0 ; i < D; i++) {
        temp->point.push_back(arr[i]);
        temp->r_max.push_back(-10);
        temp->r_min.push_back(10);
    }

    temp->left = temp->right = NULL;
    return temp;
}

Node* insert(Node *root, double point[], int depth){

    if(root == NULL) {
        root = newNode(point);
        return root;
    }

    int split_dim = depth % D;

    if(point[split_dim] < root->point[split_dim]) {
        for (int i = 0; i < D; i++) {
            root->r_max[i] = max(root->r_max[i], point[i]);
            root->r_min[i] = min(root->r_min[i], point[i]);
        }
        root->left = insert(root->left, point, depth+1);
    }
    else {
        for (int i = 0; i < D; i++) {
            root->r_max[i] = max(root->r_max[i], point[i]);
            root->r_min[i] = min(root->r_min[i], point[i]);
        }
        root->right = insert(root->right, point, depth+1);
    }

    return root;
}

// Node* constructKdTree(double data_points[][20],int n,int dim,Node* root){
//
//     for(int i=0;i<n;i++){
//         root = insert(root,data_points[i],0,dim);
//     }
//
//     return root;
// }
//
//
//
// struct greaterthan {
//   bool operator()(const node& lhs, const node& rhs) const
//   {
//     return lhs.point < rhs.point;
//   }
// };
//
// struct lesserthan {
//   bool operator()(const node& lhs, const node& rhs) const
//   {
//     return lhs.point > rhs.point;
//   }
// };
//
// int distance(double[] a, double[] b,int d_q) {
//    double sum=0;
//    for(int i=0;i<d_q;i++){
// 	   sum = sum+ pow((a[i]-b[i]),2);
// 	   }
// 	sum = pow(sum,0.5);
//
// 	return sum;
// }


int main(int argc, char* argv[]) {

    char* dataset_file = argv[1];

    // [TODO] Construct kdTree using dataset_file here

    ifstream infile;
    infile.open(dataset_file);
    infile >> D >> N1;

    double data_points[N1][D];
    for ( int i = 0; i < N1; i++) {
        for ( int j = 0; j < D; j++) {
            infile >> data_points[i][j];
            cerr<<data_points[i][j]<<" ";
        }
        cerr<<endl;
    }
    infile.close();

    Node *root = NULL;
    // root = constructKdTree(data_points,n,dim,root);
    cerr << "start construction" << endl;
    for ( int i = 0; i < N1; i++) {
        root = insert(root, data_points[i], 0);
    }
    cerr << "end construction" << endl;

    // Request name/path of query_file from parent by just sending "0" on stdout
    cout << 0 << endl;

    // // Wait till the parent responds with name/path of query_file and k | Timer will start now
    char* query_file = new char[100];
    int k;
    cin >> query_file >> k;
    // cerr << dataset_file << " " << query_file << " " << k << endl;

    // // [TODO] Read the query point from query_file, do kNN using the kdTree and output the answer to results.txt
    infile.open(query_file);
    infile >> D >> N1;

    double query_points[N2][D];
    for ( int i = 0; i < N2; i++) {
        for ( int j = 0; j < D; j++) {
            infile >> query_points[i][j];
            cerr<<query_points[i][j]<<" ";
        }
        cerr<<endl;
    }
    infile.close();

    // priority_queue <Node, vector<Node>, > max_heap;
	// //max_heap(root);
	// priority_queue<node,vector<node>, lessthan> min_heap;
	// min_heap(root);
	// //generate k random points of d_q dimension
    //
	// //double x= rand() % 2.0 +  2.0;
	// for(int i=0;i<k;i++){
	// 	double[] pt;
	// 	for(intj=0;j<d_q;j++){
	// 		pt[j]= rand() % 2.0 +  2.5;
	// 	}
	// 	double x = distance(query_point,pt,d_q);
	// 	max_heap.push(x,pt);
    //
	// }

	// while(distance(min_heap.top(),query_point,d_q)< max_heap.top()){
	// 	Node n = min_heap.top();
	// 	min_heap.pop();
	// 	if(n->left!=NULL || n->right!=NULL){
	// 		if(n->left!=NULL){
	// 		min_heap.push(n->left);
	// 		}
	// 		if(n->right!=NULL){
	// 		min_heap.push(n->right);
	// 		}
	// 	}
	// 	else if(n->left==NULL && n->right==NULL){
	// 		max_heap.push(distance(n,query_point,d_q),n);
	// 	}
	// }

    // Convey to parent that results.txt is ready by sending "1" on stdout | Timer will stop now and this process will be killed
    cout << 1 << endl;
}
