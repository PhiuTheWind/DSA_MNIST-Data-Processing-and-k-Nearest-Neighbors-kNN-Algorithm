    #include "main.hpp"

    /* TODO: Please design your data structure carefully so that you can work with the given dataset
    *       in this assignment. The below structures are just some suggestions.
    */

    template<typename T>
    class List 
    {
    public:
        virtual ~List() = default;
        virtual void push_back(T value) = 0;
        virtual void push_front(T value) = 0;
        virtual void insert(int index, T value) = 0;
        virtual void remove(int index) = 0;
        virtual T& get(int index) const = 0;
        virtual int length() const = 0 ;
        virtual void clear() = 0;
        virtual void print() const = 0;
        virtual void reverse() = 0;
        virtual List<T>* subList(int start, int end) = 0;
        virtual void printStartToEnd(int start, int end) const = 0; 
    };

template <typename T>
class UsedList: public List<T>
{   
private:
    class Node 
    {
    public:
        T dataN;
        Node* next;
    public:
    Node(T value, Node *next = nullptr) : dataN(value), next(next) {}
    Node() = default;
    };
    Node* head;
    Node* tail;
    int size;
public:
    UsedList()  //Constructor của UsedList
    {
        head = tail = nullptr;
        size = 0;
    }
    ~UsedList()  //Destructor của UsedList
    {
        this->clear();
    }

    void push_back(T value) 
    { 
        if(size == 0)
        {
            head = tail = new Node(value);
        }
        else
        {   
            Node * temp = new Node(value);
            tail -> next  = temp;
            tail = temp;
        }
        this -> size++;
    }

    void push_front(T value)
    {
        Node* New_Node = new Node(value);
        if(head == nullptr || size == 0)
        {
            head = tail = New_Node;
        }
        else 
        {
            New_Node -> next = head; 
            head = New_Node;
        }
        this -> size++;
    };

    void insert(int index, T value)
    {
    if (index < 0 || index > size) return;
    Node* New_Node = new Node(value);
    if (index == 0) 
    {
        New_Node->next = head;
        head = New_Node;
    } 
    else 
    {
        Node* temp = head;
        for (int i = 0; i < index - 1; ++i) {
            temp = temp->next;
        }
        New_Node -> next = temp->next;
        temp -> next = New_Node;
    }
    if (index == size) 
    { // Update tail if inserted at the end
        tail = New_Node;
    }
    size++;
    }

    void remove(int index)
    {
        if(index < 0 || index >= size) return;
        Node *del_Node;
        if(this -> size == 1)
        {
            del_Node = head;
            head = tail = nullptr;
            
        }
        else if(index==0)
        {
            del_Node = head;
            head = head->next;
        }
        else 
        {
            Node *temp = head;
            for(int i=1;i<index;i++) 
            {
                temp = temp -> next;
            }
            del_Node = temp -> next;
            temp -> next = del_Node->next;
            if(index == this-> size-1) tail = temp;
        }
        delete del_Node;
        this->size--;
    }


    T& get(int index) const
    {
        if(index > this-> size || index < 0)
        {
            throw std::out_of_range("get(): Out of range");
        }
        Node *temp= head;
        for(int i=0;i<index;i++)
        {
            temp=temp->next;
        }
        return temp-> dataN;
    }

    int length () const
    {
        return size;
    }

    void clear()
    {
        while (size!=0)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
            size--;
        }
        head = tail = nullptr;
        size = 0;
    }
    void print() const
    {
        Node* temp = head;
        for(int i = 0; i < size; i++)
        {
            if(i == size - 1) 
            {
                cout << temp -> dataN;
            }
            if (temp -> next != nullptr)
            {
                cout << temp -> dataN << " ";
                temp = temp->next;
            }
        }
    }

    void reverse()
    {
        if (this -> size <= 0)
        {   
            return;
        }
        Node* current = head; //con trỏ hiện tại
        Node* pre = head -> next; //con trỏ tiếp theo
        for (int i = 0; i < this -> size - 1 ; i++)
        {
            Node* temp =  pre -> next;
            pre -> next = current;
            current = pre;
            pre = temp;
        }
        this -> head -> next = nullptr;
        this -> tail = this -> head;
        this -> head = current;
    }

    List<T>* subList(int start, int end) 
    {
       if(this->size<=start) return nullptr;
       Node *temp= head;
       for(int i=0;i<start;i++){
        temp=temp->next;
       }
       List<T>* result = new UsedList<T>();
        for(int i=start; i  < this->size && i < end;i++)
        {
            result->push_back(temp -> dataN);
            temp=temp->next;
        }

        return result;

    }

    void printStartToEnd(int start, int end) const
    {
        Node* temp = head;
        for(int i = start; i < end && i < this->size; i++)
        {
            if(i == end - 1 || i == this-> size - 1)
            {
            cout << temp -> dataN << endl;
            }
            else           
            cout << temp-> dataN << " ";
        }
    }
};

static bool justloadfile = true;
static bool invalid = false;
template class UsedList<int>;
template class UsedList<string>;
class Dataset
{
        private:
        List<List<int>*>* data;
        List<string>* LabelCols ;
        int size = 785; // number of Cols includes Labels
        int Rows = 200; //Basic Rows includes Labels
        int nofRows = 199; // number of Rows not include Labels
        int UsedCols = 0;
        int UsedRows = 0;
        string *arrlabel = new string[size];

        //You may need to define more
        public:
       
        Dataset()
        {
            this -> arrlabel = new string[size];
            this -> LabelCols  = new UsedList<string>();
            this -> data = new UsedList<List<int>*>();
        }
        ~Dataset()
        {
            delete data;
            delete LabelCols ;
            delete[] arrlabel;
        }


        // Copy constructor
        Dataset(const Dataset &other)
        {
            if (invalid == true) 
            {
                cout << "Dataset" << endl;
            }
            // Deep copy of arrlabel
            this -> LabelCols  = new UsedList<string>();
            for (int i = 0; i < other.LabelCols ->length(); ++i) 
            {
                this-> LabelCols -> push_back(other.LabelCols ->get(i));
            }
            
            this->data = new UsedList<List<int>*>();
            for (int i = 0; i < other.data->length(); ++i) 
            {
            List<int>* originalList = other.data->get(i);
            List<int>* copiedList = new UsedList<int>();
            for (int j = 0; j < originalList->length(); ++j) 
            {
                copiedList->push_back(originalList->get(j));
            }
                this->data->push_back(copiedList);
            }
        }

        // Assignment operator
        Dataset& operator=(const Dataset& other) 
        {
           
            {
                if (this != &other) 
                { // Protect against self-assignment
                // Clear current contents
                delete this->data;
                delete this->LabelCols ;

                // // Deep copy of LabelCols 
                this->LabelCols  = new UsedList<string>();
                for (int i = 0; i < other.LabelCols ->length(); ++i) 
                {
                    this->LabelCols ->push_back(other.LabelCols ->get(i));
                }
                
                // Deep copy of data
                this -> data = new UsedList<List<int>*>();
                for (int i = 0; i < other.data->length(); ++i) 
                {
                    List<int>* originalList = other.data->get(i);
                    List<int>* copiedList = new UsedList<int>();
                    for (int j = 0; j < originalList->length(); ++j) {
                        copiedList->push_back(originalList->get(j));
                    }
                    this->data->push_back(copiedList);
                }
                }
        return *this;
            }
        }

        bool loadFromCSV(const char* fileName)
        {
            ifstream file(fileName);
            if (!file.is_open())
            {
                return false;
            }
            if (file.is_open())
            {
                string arNew;
                string arNew1;
                file >> arNew;
                // arNew1 = arNew; //arrlabel
                // stringstream ss1(arNew1);
                // for(int i = 0; i < 785; i++)
                // {
                //     getline(ss1, arrlabel[i], ','); //Bỏ label vô từng element của mảng động
                // }

                //LabelCols 
                for(int i =0;i<arNew.length();i++)
                {
                    if(arNew[i]==',') arNew[i]=' ';
                }
                stringstream ss(arNew);
                while(ss >> arNew) LabelCols ->push_back(arNew);
                //Test LabelsCols
                // for (int i = 0; i < LabelCols  -> length(); i++)
                // {
                //     cout << LabelCols  -> get(i) << " ";
                // }


                //Làm mảng số
                string list;
                int list_num;
                while (file >> list)
                {
                    //nofRows++;
                    for(int i=0; i<list.length(); i++)
                    {
                        if(list[i] == ',')
                        {
                            list[i] = ' ';
                        }
                    }
                    stringstream ss2(list);
                    List<int>* temp = new UsedList<int>();
                    while(ss2 >> list_num)
                    {
                        temp -> push_back(list_num);
                    }
                    data -> push_back(temp); // Add parenthesesdata -> push_back(temp); // Add semicolon
                }
                return true;
               
            }
            return false; 
        }
        

        void printHead(int nRows = 5, int nCols = 5) const
        {
        if (nRows > data->length())
        {
            nRows = data->length();
        }
        if (nRows < 0 && nCols < 0)
        {
            return;
        }
        else if (nRows > nofRows && nCols < size) 
        {
            for(int i = 0; i < nCols; i++)
            {
                if (i == nCols - 1) cout << this->LabelCols ->get(i) << endl;
                else
                cout << this->LabelCols -> get(i) << " ";
            }
            for (int i = 0; i < nofRows; i++) 
            {
            for (int j = 0; j < nCols; j++) 
            {
            cout << data->get(i)->get(j);
            if (j != nCols - 1) { // Không in khoảng trắng sau phần tử cuối cùng của hàng
            cout << " ";
            }
            }
            if (i != nofRows - 1) { // Không xuống dòng sau hàng cuối cùng
                cout << endl;
            }
            }   
        }

        else if (nCols > size && nRows < nofRows)
        {
            for(int i=0; i < size; i++)
            {
                if (i == size) cout << this->LabelCols ->get(i) << endl;
                else
                cout << this->LabelCols ->get(i) << " ";
            }
            for (int i = 0; i < nRows; i++) {
            for (int j = 0; j < size; j++) {
            if (j == size - 1 && i == nRows - 1) { // Phần tử cuối cùng
            cout << data->get(i)->get(j);
            } else if (j == size - 1) { // Phần tử cuối hàng
            cout << data->get(i)->get(j);
            } else {
            cout << data->get(i)->get(j) << " ";
            }
            }
            if (i != nRows - 1) // Không in endl sau hàng cuối cùng
                cout << endl;
            }
        }

        else if (nRows > nofRows && nCols > size)
        {
            for(int i=0; i < size; i++)
            {
                if (i == size - 1) cout << this->LabelCols -> get(i)  << endl;
                else
                cout << this->LabelCols -> get(i) << " ";
            }
            for (int i = 0; i < nofRows; i++) {
            for (int j = 0; j < size; j++) {
            if (j == size - 1 && i == nofRows - 1) { // Phần tử cuối cùng
            cout << data->get(i)->get(j);
            } else if (j == size - 1) { // Phần tử cuối hàng
            cout << data->get(i)->get(j);
            } else {
            cout << data->get(i)->get(j) << " ";
            }
            }
            // Không in dư khoảng trắng nếu không phải hàng cuối cùng
            if (i != nofRows - 1) {
                cout << endl;
            }
            }
        }

        
        else //Basic 
        {   
            int nColscopy = nCols;
            for (int i = 0; i < nColscopy; i++)
            {
                if (LabelCols -> length() < nCols)
                {
                    nCols = LabelCols -> length();
                }
                if (i == nCols - 1) 
                {
                    cout << this-> LabelCols -> get(i)  << endl;
                    if (nCols == 1)
                    {
                        break;
                    }
                }
                else
                {
                    cout << this-> LabelCols -> get(i) << " ";
                }
            }
            for (int i = 0; i < nRows; i++) {
            for (int j = 0; j < nCols; j++) {
            cout << data->get(i)->get(j);
            if (j != nCols - 1) // Không phải cột cuối cùng
            cout << " ";
            }
            if (i != nRows - 1) // Không phải hàng cuối cùng
            cout << endl;
            }

        }
    }

        //chỉnh thêm TH data->length() < nRows và LabelCols -> length() < nCoLs
        void printTail(int nRows = 5, int nCols = 5) const
        {
            if (nRows > data->length())
            {
                nRows = data->length();
            }
            if (nRows < 0 && nCols < 0)
            {
                return;
            }

            //hàng nhập lớn hơn dữ liệu cho trước
            else if (nRows > nofRows) 
            {
                int nColscopy = nCols - 1;
                for (int i = nColscopy; i >= 0; i--)
                {
                    cout << this->LabelCols ->get(size-i-1) << " ";
                    if (i == 0)
                    {
                        cout << this-> LabelCols ->get(size - i - 1) << endl;
                    }
                }
                for (int i = 0; i < nofRows; i++) 
                {
                    for (int nColscopy = nCols; nColscopy > 0; nColscopy--) 
                    { 
                    if (nColscopy == 1 && i == nRows - 1) 
                    {
                        cout << data->get(i)->get(size - nColscopy - 1);
                    } 
                    else 
                    {
                    if (nColscopy == 1 && i != nRows - 1) 
                    {
                        cout << data->get(i)->get(size - nColscopy - 1);
                    } 
                    else 
                    {
                        cout << data->get(i)->get(size - nColscopy - 1) << " ";
                    }
                    }
                    }
                    if (i != nRows - 1) 
                    {
                        cout << endl;
                    }
                }
            }
            //cột nhập lớn hơn dữ liệu cho trước
            else if (nCols > size) 
            {
                for(int i=0; i < size; i++)
                {
                    if (i == size) cout << this->LabelCols ->get(i) << endl;
                    cout << this->LabelCols ->get(i) << " ";
                }
                for (int i = 0; i < nRows; i++) 
                {
                bool lastColumn = false; // Biến để kiểm tra xem có phải đang ở cột cuối của hàng không
                for (int j = 0; j < size; j++) 
                {
                    if (j == size - 1) // Nếu là cột cuối của hàng
                        lastColumn = true; // Đặt lastColumn thành true
                    if (j == 1 && i == nRows - 1) {
                        cout << data->get(i)->get(size - j - 1);
                    } 
                else
                    cout << data->get(i)->get(size - j - 1) << (lastColumn ? "" : " "); // Không in khoảng trắng nếu đây là cột cuối
                if (j == 1 && i == nRows - 1);
                else if (j == 1 && i != nRows - 1)
                    cout << endl;
                }
                }           
            }

            //TH Bình thường
            else 
            {
                for (int i = nCols; i > 0; i--)
                {

                    if (i == 1)
                    {
                        cout << this-> LabelCols -> get(size - i) << endl;
                        break;
                    }
                    cout << this-> LabelCols ->get(size - i) << " ";
                }

                for (int i = 0; i < nRows; i++) 
                {
                    for (int nColscopy = nCols; nColscopy > 0; nColscopy--) 
                    { 
                    if (nColscopy == 1 && i == nRows - 1) 
                    {
                        cout << data->get(i)->get(size - nColscopy - 1);
                    } 
                    else 
                    {
                    if (nColscopy == 1 && i != nRows - 1) 
                    {
                        cout << data->get(i)->get(size - nColscopy - 1);
                    } 
                    else 
                    {
                        cout << data->get(i)->get(size - nColscopy - 1) << " ";
                    }
                    }
                    }
                    if (i != nRows - 1) 
                    {
                        cout << endl;
                    }
                }
            }
        }

        void getShape(int& nRows, int& nCols) const
        {
            if(invalid == true)
            {
                nRows = 1;
                nCols = (nRows > 0) ? this-> data-> get(-1) -> length() : 0;
            }
            if (justloadfile == true)
            {
                nRows = size;
                nCols = nofRows;
            }
            nRows = this -> data -> length();
            nCols = (nRows > 0) ? this-> data-> get(0) -> length() : 0;
            
        }
        void columns() const
        {
            this->LabelCols ->print();
        }

        bool drop(int axis = 0, int index = 0, std::string columns = "");
        Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const;

        int getSize() const
        {
            return size;
        }
      
        int getRows() const
        {
            return nofRows;
        }
       
        string getarrlabel()
        {
            for (int i = 0; i < size; i++)
            {
                return arrlabel[i];
            }
        }
    
    Dataset predict(const Dataset& X_train, const Dataset& Y_train, const int k) const;
    double Calculate_Euclidean_distance(const List<int>* point1, const List<int>* point2) const
    {
        double distance = 0.0;
        int min_length = std::min(point1->length(), point2->length());

        for (int i = 0; i < min_length; i++)
        {
            int diff = point1->get(i) - point2->get(i);
            distance += diff * diff;
        }

        // Add remaining elements from the longer list
        if (point1->length() > min_length)
        {
            for (int i = min_length; i < point1->length(); i++)
            {
                distance += point1->get(i) * point1->get(i);
            }
        }
        else if (point2->length() > min_length)
        {
            for (int i = min_length; i < point2->length(); i++)
            {
                distance += point2->get(i) * point2->get(i);
            }
        }

        return sqrt(distance);
    }


        List<List<int>*>* getData() const
        {
            return data;
        }

        double score(const Dataset& y_test) const
        {

            if (this->data->length() != y_test.data->length()) 
                return -1; // Không thể tính toán tỷ lệ đúng nếu số lượng mẫu không khớp

            int correct_predictions = 0;

            for (int i = 0; i < this->data->length(); i++) 
            {
                int thisDataLength = this->data->get(i)->length();
                int yTestDataLength = y_test.data->get(i)->length();

                // Kiểm tra xem cả hai mẫu có cùng độ dài hay không
                if (thisDataLength > 0 && yTestDataLength > 0 &&
                    thisDataLength == yTestDataLength &&
                    this->data->get(i)->get(thisDataLength - 1) == y_test.data->get(i)->get(yTestDataLength - 1)) 
                {
                    correct_predictions++;
                }
            }
            return static_cast<double>(correct_predictions) / this->data->length();
        }

};


class kNN 
{
    private:
        int k;
        Dataset X_training;
        Dataset Y_training;
        //You may need to define more
    public:
        kNN(int k = 5):k(k){};
        void fit(const Dataset& X_train, const Dataset& y_train);
        Dataset predict(const Dataset& X_test);
        double score(const Dataset& y_test, const Dataset& y_pred);
};

void train_test_split(Dataset& X, Dataset& y, double test_size, Dataset& X_train, Dataset& X_test, Dataset& y_train, Dataset& y_test);
// Please add more or modify as needed

