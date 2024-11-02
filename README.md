**MNIST Data Processing and k-Nearest Neighbors (kNN) Algorithm**

**Introduction**

This is a major assignment for the Data Structures and Algorithms course at Ho Chi Minh University of Technology. The aim of this assignment is to familiarize students with the k-nearest neighbors (kNN) classification algorithm and apply it to process and classify data from the MNIST dataset using list-based data structures.

**Objectives**

Upon completing this assignment, students will:
+ Master object-oriented programming.
+ Proficiently use list-based data structures.
+ Understand and implement the kNN algorithm for data classification.
  
**Assignment Overview MNIST Dataset:**

+ The MNIST dataset consists of handwritten images of digits from 0 to 9, each with a resolution of 28x28 pixels. The data is stored as pixel values ranging from 0 to 255, with each image labeled from 0 to 9.
+ k-Nearest Neighbors (kNN) Algorithm: kNN is a classification algorithm that identifies the k closest data points to classify new data. Distances between data points are calculated using the Euclidean distance metric.

**Instruction:**

To compile and run the program, you first need to set up an environment with a C++ compiler installed (specifically g++ with C++11 standard). After preparing the environment, you can compile the program by using the following command in the terminal:
bash
g++ -o main main.cpp kNN.cpp -I . -std=c++11

This command will create an executable file named main. After successfully compiling, you can run the program by typing the command:
bash
./main
