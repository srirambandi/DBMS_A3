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
            else if (r_max[i] < arr[i]) {
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

struct Node* newNode(double *arr) {
    struct Node* temp = new Node;

    for (int i = 0 ; i < D; i++) {
        temp->point.push_back(arr[i]);
        temp->r_max.push_back(arr[i]);
        temp->r_min.push_back(arr[i]);
    }

    temp->left = temp->right = NULL;
    return temp;
};

struct max_heap_obj {
    vector<double> point;
    double point_dist;
};

struct max_heap_obj* new_max_heap_obj(vector<double>& arr, double point_dist) {
    struct max_heap_obj* temp = new max_heap_obj;

    for (int i = 0; i < D; i++) {
        temp->point.push_back(arr[i]);
    }

    temp->point_dist = point_dist;
    return temp;
};

struct min_heap_obj {
    struct Node* node;
    double mbr_dist;
};

struct min_heap_obj* new_min_heap_obj(Node *node, double mbr_dist) {
    struct min_heap_obj* temp = new min_heap_obj;

    temp->node = node;
    temp->mbr_dist = mbr_dist;
    return temp;
};

bool isLeaf(min_heap_obj &obj) {
    if (obj.node->left == NULL && obj.node->right == NULL) {
        return true;
    }
    return false;
}

Node* insert(Node *root, double point[], int depth){

    if(root == NULL) {
        root = newNode(point);
        return root;
    }

    unsigned cut = depth % D;

    if(point[cut] < root->point[cut]) {
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

double distance(vector<double>& a, vector<double>& b) {
    double dist = 0;
    for (int i = 0; i < D; i++) {
        dist = dist + pow((a[i] - b[i]),2);
    }
    dist = sqrt(dist);

    return dist;
}

struct max_heap_comp {
    bool operator() (const max_heap_obj &p1, const max_heap_obj &p2) const {
        return p1.point_dist < p2.point_dist;
    }
};

struct min_heap_comp {
    bool operator() (const min_heap_obj &n1, const min_heap_obj &n2) const {
        return n1.mbr_dist > n2.mbr_dist;
    }
};


int main(int argc, char* argv[]) {

    char* dataset_file = argv[1];

    // [TODO] Construct kdTree using dataset_file here

    ifstream data;
    data.open(dataset_file);
    data >> D >> N1;

    double data_points[N1][D];
    for ( int i = 0; i < N1; i++) {
        for ( int j = 0; j < D; j++) {
            data >> data_points[i][j];
        }
    }
    data.close();

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
    data.open(query_file);
    data >> D >> N2;

    double query_points[N2][D];
    for ( int i = 0; i < N2; i++) {
        for ( int j = 0; j < D; j++) {
            data >> query_points[i][j];
        }
    }
    data.close();

    double ddd;
    vector<double> query_point,rand_points;
    min_heap_obj* min_temp;
    max_heap_obj* max_temp;
    priority_queue<max_heap_obj, vector<max_heap_obj>, max_heap_comp> max_heap;
    priority_queue<min_heap_obj, vector<min_heap_obj>, min_heap_comp> min_heap;
    for (int q = 0; q < N2; q++) {
        query_point.clear();
        for (int i = 0; i < D; i++) {
            query_point.push_back(query_points[q][i]);
        }
        max_heap = priority_queue<max_heap_obj, vector<max_heap_obj>, max_heap_comp>();
        min_heap = priority_queue<min_heap_obj, vector<min_heap_obj>, min_heap_comp>();
        ddd = root->mbr_dist(query_point);
        min_temp = new_min_heap_obj(root, ddd);
        min_heap.push(*min_temp);
        for (int i = 0; i < k; i++) {
            rand_points.clear();
            for (int j = 0; j < D; j++) {
                rand_points.push_back(((double)rand()/RAND_MAX + 2.0));
            }
            double point_dist = distance(query_point, rand_points);
            max_temp = new_max_heap_obj(rand_points, point_dist);
            max_heap.push(*max_temp);
        }
        cerr << root->point[0] << " " << root->point[1] << endl;
        cerr << min_heap.top().mbr_dist << " " << max_heap.top().point_dist << endl;
        while (!min_heap.empty() && min_heap.top().mbr_dist < max_heap.top().point_dist) {
            cerr<< "loop" <<endl;
            double dd = max_heap.top().point_dist;
            min_heap_obj temp1 = min_heap.top();
            if (!isLeaf(temp1) && temp1.mbr_dist > dd) {
                break;
            }
            else {
                if (isLeaf(temp1) && temp1.mbr_dist < dd) {
                    cerr << "is leaf" <<endl;
                    if (temp1.mbr_dist < dd) {
                        max_temp = new_max_heap_obj(temp1.node->point, temp1.mbr_dist);
                        max_heap.pop();
                        max_heap.push(*max_temp);
                    }
                }
                else {
                    // cerr << "not leaf" <<endl;
                    // Node* curr_node = temp1.node->right;
                    // cerr << root << " " << temp1.node << " " << curr_node <<endl;
                    // for (int i = 0; i < D; i++) {
                    //     cerr << "reached" <<endl;
                    //     cerr << curr_node->point[i] << " ";
                    // }
                    // cerr << endl;
                    min_heap_obj* temp2;
                    if (temp1.node->left != NULL) {
                        ddd = temp1.node->left->mbr_dist(query_point);
                        cerr << ddd <<endl;
                        temp2 = new_min_heap_obj(temp1.node->left, ddd);
                        if (temp2->mbr_dist < dd) {
                            min_heap.push(*temp2);
                        }
                    }

                    if (temp1.node->right != NULL) {
                        ddd = temp1.node->right->mbr_dist(query_point);
                        temp2 = new_min_heap_obj(temp1.node->right, ddd);
                        if (temp2->mbr_dist < dd) {
                            min_heap.push(*temp2);
                        }
                    }

                    ddd = distance(temp1.node->point, query_point);
                    if (ddd < dd) {
                        max_temp = new_max_heap_obj(temp1.node->point, ddd);
                        max_heap.pop();
                        max_heap.push(*max_temp);
                    }
                }
            }
            min_heap.pop();
        }
        cerr << "===============" << endl;
        while (!max_heap.empty()) {
            cerr << max_heap.top().point_dist << " : ";
            for (int i = 0; i < D; i++) {
                cerr << max_heap.top().point[i] << " ";
            }
            cerr << endl;
            max_heap.pop();
        }
        cerr << "===============" << endl;
    }

    // Convey to parent that results.txt is ready by sending "1" on stdout | Timer will stop now and this process will be killed
    cerr << "results generated" << endl;
    cout << 1 << endl;
}
