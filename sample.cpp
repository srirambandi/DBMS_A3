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

    double mbr_dist(vector<double>& arr) {
        double dist = 0;
        for (int i = 0; i < D; i++) {
            if (arr[i] < r_min[i]) {
                dist += pow((r_min[i] - arr[i]), 2);
            }
            else if (r_max < arr[i]) {
                dist += pow((arr[i] - r_max[i]), 2);
            }
            else {
                continue;
            }
        }
        dist = sqrt(dist);
        return dist;
    }
};

struct max_heap_obj {
    vector<double> point;
    double mbr_dist;
};

struct max_heap_obj* new_max_heap_obj(double *arr, double mbr_dist) {
    struct max_heap_obj* temp = new max_heap_obj;

    for (int i = 0; i < D; i++) {
        temp->point.push_back(arr[i]);
    }

    temp->mbr_dist = mbr_dist;
}

struct Node* newNode(double *arr) {
    struct Node* temp = new Node;

    for (int i = 0 ; i < D; i++) {
        temp->point.push_back(arr[i]);
        temp->r_max.push_back(arr[i]);
        temp->r_min.push_back(arr[i]);
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

int distance(double *a, double *b) {
    double dist = 0;
    for (int i = 0; i < D; i++) {
        sum = sum + pow((a[i] - b[i]),2);
    }
	sum = sqrt(sum,0.5);

	return dist;
}

struct max_heap_comp {
    bool operator() (const max_heap_obj& p1, const max_heap_obj& p2) const {
      return p1.mbr_dist < p2.mbr_dist;
    }
};

struct min_heap_comp {
    vector<double> p;
    min_heap_comp(double *arr) {
        for (int i = 0; i < D; i++) {
            p.push_back(arr[i]);
        }
    }
    bool operator() (const Node& n1, const Node& n2) const {
        return n1.mbr_dist(p) > n2.mbr_dist(p);
    }
};


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
    infile >> D >> N2;

    double query_points[N2][D];
    for ( int i = 0; i < N2; i++) {
        for ( int j = 0; j < D; j++) {
            infile >> query_points[i][j];
            cerr<<query_points[i][j]<<" ";
        }
        cerr<<endl;
    }
    infile.close();

    priority_queue<max_heap_obj, vector<max_heap_obj>, max_heap_comp> max_heap;
    priority_queue<Node, vector<Node>, min_heap_comp> min_heap;

    //generate k random points of d_q dimension
	//double x= rand() % 2.0 +  2.0;
	for (int i = 0; i < k; i++) {
		double[] pt;
		for(intj=0;j<d_q;j++){
			pt[j]= rand() % 2.0 +  2.5;
		}
		double x = distance(query_point,pt,d_q);
		max_heap.push(x,pt);
	}

	for (int i = 0; i < N2; i++) {
        priority_queue<max_heap_obj, vector<max_heap_obj>, max_heap_comp> q_max_heap = max_heap;
        priority_queue<Node, vector<Node>, min_heap_comp> q_min_heap = min_heap;

    }

    // Convey to parent that results.txt is ready by sending "1" on stdout | Timer will stop now and this process will be killed
    cerr << "results generated" << endl;
    cout << 1 << endl;
}
