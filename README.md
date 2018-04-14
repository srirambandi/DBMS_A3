# KdTree-StarterCode

This repository contains the starter code for the k-d tree assignment in COL362/632 (Intro. to Database Management Systems) being held at IIT Delhi.

The part (d) of the assignment is a competition among all the students based on the time taken by their k-d tree implementation to answer a kNN-query.
 
## Program Structure

The file **parent.py** is provided to you (you are not supposed to edit it). It is the program that will time your submission. You are expected to submit your code along with a **run.sh** which compiles and runs your program (Specifications below).

In order for parent.py to measure the time taken by your program to just answer the query (excluding the k-d tree construction time), the following mechanism has been adopted.

 1. parent.py will execute `sh run.sh <dataset_file>` as a child process. (run.sh should in turn compile and run your program) (Here <**dataset_file**> is the name of the file containing the data points - Format specified below) 
 2. Your program (child) should construct the k-d tree using <dataset_file> and output "0" on the standard output (stdout) when done. This would be read by the parent.
 3. parent.py would then write the name/path of the **<query_file>** (which contains the query points for kNN - Format specified below) and the value of **k** (k in kNN) on your standard input (stdin). It also starts the timer now.
 4. Your program should now read the name of the <query_file> and the value of k from stdin and process the query points using the k-d tree. The output (the k nearest neighbors for each query point) should then be written to **results.txt**. (Format specified below)
 5. Your program should then output "1" on stdout so that the parent can stop the timer and check your results.txt.

**Sample code is provided** - run.sh and sample.cpp (and a sample.py, in case you wish to work in Python) - to demonstrate how to communicate with parent.py. Feel free to extend them as you need.

**NOTE**: The stdout and stdin of your program are used for communication with the parent.py. Hence, for any debugging purposes, do not print anything on stdout, instead use stderr (using cerr in C++ for example).

## File Formats

 - A point is represented as a space separated list of values along each dimension.
 - **<dataset_file>**:
 1. First line is "D N1" where D = numer of dimensions and N1 = number of data points. 
 2. N1 lines follow where each line is a D-dimesnional point.
 - **<query_file>**:
 1. First line is "D N2" where D = number of dimensions and N2 = number of query points.
 2. N2 lines follow where each line is a D-dimensional query point.
 - **results.txt**: 
 1. k*N2 lines where each line should be a point. 
 2. The first k lines are the k-nearest neighbors of the 1st query point, and so on for all N2 query points.
 
 Example: Suppose the points are 2-dimensional and <dataset_file> contains 3 points, it would look something like
> 2 3  
> 0.0 1.0  
> 1.0 0.0  
> 0.0 0.0

Now if the <query_file> is:
> 2 2  
> 1.0 1.0  
> 0.0 0.0

Then for k = 2, results.txt should look like:
> 0.0 1.0  
> 1.0 0.0  
> 0.0 0.0  
> 0.0 1.0

Here, the first 2 points in results.txt correspond to the 2NN of 1st query point. And the next 2 points, correspond to the 2NN of 2nd query point.

**NOTE**: In results.txt file, the k points for each query point **must** be sorted in ascending order of distance to the query point. For a tie-breaker (2 points equi-distant from query point), use lexicographical ordering between the 2 points i.e. if two d-dimensional points A and B are equi-distant from the query point, then A < B if for some 0 <= m < d, A[m] < B[m] and A[i]=B[i] for 0 <= i < m. (where A[i] represents value of A along i-th dimension) (Eg. [1.0 2.0] < [1.0 3.0])

## Command to run

    python parent.py <dataset_file> <query_file> <k>
parent.py is compatible with Python 2.x and Python 3.x and with both Linux and Windows. However final evaluation will be done using Python 3.x. So, for students using Python in your program, it is recommended to use Python 3.x.

For any issues, feel free to post on the Piazza group of this course.
