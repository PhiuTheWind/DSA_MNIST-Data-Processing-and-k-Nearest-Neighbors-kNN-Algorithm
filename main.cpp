#include "kNN.hpp"

void tc_knn_p(int k, int size_X)
{
int nRows, nCols;
Dataset dataset;
dataset.loadFromCSV("mnist.csv");

kNN knn = kNN(k);
Dataset X_train, X_test, y_train, y_test;
Dataset feature = dataset.extract(0, size_X, 1, -1);
Dataset label = dataset.extract(0, size_X, 0, 0);

train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
knn.fit(X_train, y_train);
Dataset y_pred = knn.predict(X_test);
cout << "y_pred" << endl;
y_pred.printHead(10, 10);
cout << endl;
cout << "y_test" << endl;
y_test.printHead(10, 10);
cout << endl;
}

void tc_knn_score(int k, int size_X){
int nRows, nCols;
Dataset dataset;
dataset.loadFromCSV("mnist.csv");

kNN knn = kNN(k);
Dataset X_train, X_test, y_train, y_test;
Dataset feature = dataset.extract(0, size_X, 1, -1);
Dataset label = dataset.extract(0, size_X, 0, 0);

train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
knn.fit(X_train, y_train);
Dataset y_pred = knn.predict(X_test);
double accuracy = knn.score(y_test, y_pred);
cout << "Accuracy: " << accuracy << endl;
}


void tc1015()
{
Dataset dataset;
int nRows, nCols;
dataset.loadFromCSV("mnist.csv");
Dataset X_train, X_test, y_train, y_test;
Dataset feature = dataset.extract(0, -1, 1, -1);
Dataset label = dataset.extract(0, 1, 0, 0);
train_test_split(feature, label, 0.5, X_train, X_test, y_train, y_test);
X_train.getShape (nRows, nCols);
cout << "X_train shape: " << nRows << "x" << nCols << endl;
X_test.getShape (nRows, nCols);
cout << "X_test shape: " << nRows << "x" << nCols << endl;
y_train.getShape (nRows, nCols);
cout << "y_train shape: " << nRows << "x" << nCols << endl;
y_test.getShape (nRows, nCols);
cout << "y_test shape: " << nRows << "x" << nCols << endl;
feature.getShape (nRows, nCols);
cout << "X shape: " << nRows << "x" << nCols << endl;
label.getShape (nRows, nCols);
cout << "y shape: "<< nRows << "x" << nCols << endl;
feature.columns();
}

int main()
{
    tc1015();
    return 0;
}

