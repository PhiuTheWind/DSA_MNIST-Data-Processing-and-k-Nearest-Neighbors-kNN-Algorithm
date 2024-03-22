#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * 
*/

bool Dataset::drop(int axis, int index, std::string column)
{
    if (axis != 0 && axis != 1) {
        return false;
    }
    if (axis == 0) {
        if (index < 0 || index >= this->data->length()) {
            return false;
        }
        this->data->remove(index);
        return true;
    }
    if(this->data->length()==0) return false;
    
    if (axis == 1) 
    {
        int col_del = -1;
        for (int i = 0; i < this->LabelCols->length(); ++i) 
        {
            if (this->LabelCols->get(i) == column) 
            {
                col_del = i;
                break;
            }
        }
        if (col_del == -1) return false;
      
        for (int i = 0; i < this->data->length(); ++i) 
        {
            List<int>* row = this->data->get(i);
            row->remove(col_del);
        } 
        this->LabelCols->remove(col_del);
        return true;
    }
    return false;
}

Dataset Dataset::extract(int startRow, int endRow, int startCol, int endCol) const
{
    justloadfile = false;
    Dataset extracted;
    if (size < 0 || endRow < -1 || endCol < -1 || startRow > endRow && endRow != -1 || startCol > endCol && endCol != -1) {
        throw out_of_range("get(): Out of range");
    }
    // Điều chỉnh endRow và endCol để biểu diễn hàng và cột cuối cùng thực tế nếu chúng bằng -1
    int EndR = (endRow == -1) ? this->data->length() - 1  : endRow;
    int EndC = (endCol == -1) ? this->LabelCols->length() - 1 : endCol;
   
    EndR = std::min(EndR, this->data->length() - 1);
    EndC = std::min(EndC, this->LabelCols->length() - 1);

    for (int col = startCol; col <= EndC; ++col) 
    {
        extracted.LabelCols->push_back(this->LabelCols->get(col));
    }

    // Extract the data rows
    for (int row = startRow; row <= EndR; row++) 
    {
        List<int>* Rowcopied = new UsedList<int>();
        for (int col = startCol; col <= EndC; ++col) 
        {
            Rowcopied->push_back(this->data->get(row)->get(col));
        }
        extracted.data->push_back(Rowcopied);
    }
    return extracted;
}

void kNN::fit(const Dataset &X_train, const Dataset &y_train)
{
    this -> X_training = X_train;
    this -> Y_training = y_train;
}


Dataset kNN::predict(const Dataset& X_test)
{
    if (X_training.getData() -> length() < k)
    {
        throw out_of_range("get(): Out of range");
    }
    return X_test.predict(this->X_training,this->Y_training,this->k);
}

double kNN::score(const Dataset &y_test, const Dataset &y_pred)
{
    return y_test.score(y_pred);
}

void train_test_split(Dataset &X, Dataset &Y, double test_size, Dataset &X_train, Dataset &X_test, Dataset &Y_train, Dataset &Y_test)
{
    if (X.getData()->length() != Y.getData()->length() || test_size >= 1 || test_size <= 0)
    {
        throw out_of_range("get(): Out of range");
    }
    double Min_Double = 1.0e-15;
    int nRow = X.getData()->length();
    double rowSplit = nRow * (1 - test_size);

    if (abs(round(rowSplit) - rowSplit) < Min_Double * nRow)
    rowSplit = round(rowSplit);

    //Test
    X_test = X.extract(rowSplit, -1, 0, -1);
    Y_test = Y.extract(rowSplit, -1, 0, -1);

    //Train
    X_train = X.extract(0, rowSplit - 1, 0, -1);
    Y_train = Y.extract(0, rowSplit - 1, 0, -1);

}


// Function to partition the array and return the pivot index
// Function to partition the array and return the pivot index
int partition(double arr[], int indices[], int low, int high) {
    double pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            // Swap arr[i] and arr[j]
            double temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

            // Swap indices[i] and indices[j]
            int tempIndex = indices[i];
            indices[i] = indices[j];
            indices[j] = tempIndex;
        }
    }
    // Swap arr[i+1] and arr[high] (or pivot)
    double temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    // Swap indices[i+1] and indices[high]
    int tempIndex = indices[i + 1];
    indices[i + 1] = indices[high];
    indices[high] = tempIndex;

    return i + 1;
}

// Function to implement QuickSort
void QuickSort(double arr[], int indices[], int low, int high) {
    if (low < high) {
        // pi is partitioning index, arr[pi] is now at right place
        int pi = partition(arr, indices, low, high);

        // Separately sort elements before and after partition
        QuickSort(arr, indices, low, pi - 1);
        QuickSort(arr, indices, pi + 1, high);
    }
}

// Phương thức predict
Dataset Dataset::predict(const Dataset& X_train, const Dataset& Y_train, const int k) const 
{
    
    Dataset result;
    const int maxLabel = 10;  
    result.LabelCols -> push_back("label");     
    for (int i = 0; i < this->data->length(); ++i) {
        double* distancesLabels = new double[X_train.data->length()]; // Array to store distances
        int* indices_Labels = new int[X_train.data->length()]; // Array to store corresponding indices
        for (int j = 0; j < X_train.data->length(); ++j) 
        {
            distancesLabels[j] = this->Calculate_Euclidean_distance(this->data->get(i), X_train.data->get(j));
            indices_Labels[j] = j;
        }
        
        // Sort the array of distances and corresponding indices
        QuickSort(distancesLabels, indices_Labels, 0, X_train.data->length() - 1);
        
        // Count occurrences of each label among the k nearest neighbors
        int labelCounts[maxLabel] = {0};
        for (int idx = 0; idx < k; idx++) 
        {
            int label = Y_train.data->get(indices_Labels[idx])->get(0);
            labelCounts[label]++;
        }

        // Determine the most common label
        int mostCommonLabel = 0;
        int maxCount = 0;
        for (int idx = 0; idx < 10; ++idx) 
        {
            if (labelCounts[idx] > maxCount || (labelCounts[idx] == maxCount && idx < mostCommonLabel)) 
            {
                maxCount = labelCounts[idx];
                mostCommonLabel = idx;
            }
        }
        
        // Add the predicted label to the result
        List<int>* predictedLabels = new UsedList<int>();
        predictedLabels->push_back(mostCommonLabel);
        result.data->push_back(predictedLabels);
        
        delete[] distancesLabels;  
        delete[] indices_Labels; 
    }
    //kiểm tra y_pred
    return result; 
}


