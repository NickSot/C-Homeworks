#include <iostream>
#include <string>
#include <iterator>
#include <sstream>
#include <vector>

using namespace std;

class LOAException{

};

class ListOfArrays {

    class ArrayNode {
        public:

        int* data_;
        int size_;
        ArrayNode* prev_;
        ArrayNode* next_;

        ArrayNode(int* data, int size)
            : data_(data), size_(size), next_(0), prev_(0) {}

        ~ArrayNode() {
            delete [] data_;
        }
    };

    ArrayNode* head_;
    int size_;

    public:

    class Iterator {

        friend class ListOfArrays;

        ListOfArrays& list_;
        ArrayNode* current_;

        public:

        Iterator(ListOfArrays& list, ArrayNode* current)
            : list_(list), current_(current) {}

        bool operator==(const Iterator& other){
    		if (other.current_ -> size_ != current_->size_){
    			return false;
    		}

        	for (int i = 0; i < current_->size_; i++){
        		if (current_->data_[i] != other.current_->data_[i]){
        			return false;
        		}
        	}

        	return true;
        }

        bool operator!=(const Iterator& other){
        	return !(*this == other);
        }

        Iterator& operator++(){
        	Iterator it(list_, current_->next_);

        	this->current_ = it.current_;

        	return *this;
        }

        Iterator operator++(int){
        	Iterator result(list_, current_->next_);

        	this->current_ = result.current_;

        	return *this;
        }

        int& operator[](const int& index){
        	return current_->data_[index];
        }

        int size(){
        	return current_->size_;
        }

        void show(){
        	for (int i = 0; i < size(); i++){
        		cout << current_->data_[i] << " ";
        	}

        	cout << endl;
        }
        
        double average(){
        	double result = 0;

        	for (int i = 0; i < current_->size_; i++){
        		result += current_->data_[i];
        	}

        	result /= current_->size_;

        	return result;
        }
        
        double median(){
        	if (current_->size_%2 == 0){
        		return (double)(current_->data_[0] + current_->data_[current_->size_ - 1])/2;
        	}

        	return current_->data_[(current_->size_ - 1)/2];
        }
        
        int sum(){
        	double result = 0;

        	for (int i = 0; i < current_->size_; i++){
        		result += current_->data_[i];
        	}

        	return result;
        }
        
        Iterator& ordered(bool ascending = true){
        	bool isSorted = false;

        	while (!isSorted){
        		isSorted = true;

        		for (int i = 0; i < current_->size_ - 1; i++){
        			if (ascending){
	        			if (current_->data_[i] > current_->data_[i + 1]){
	        				isSorted = false;

	        				int temp = current_->data_[i];

	        				current_->data_[i] = current_->data_[i + 1];

	        				current_->data_[i + 1] = temp;
	        			}
        			}
        			else{
        				if (current_->data_[i] < current_->data_[i + 1]){
	        				isSorted = false;

	        				int temp = current_->data_[i];

	        				current_->data_[i] = current_->data_[i + 1];

	        				current_->data_[i + 1] = temp;
	        			}
        			}
        		}
	        }

        	return *this;
        }
    };

    ListOfArrays()
            : size_(0), head_(new ArrayNode(0, 0)) {
        head_->next_ = head_;
        head_->prev_ = head_;
    }

	~ListOfArrays(){
		ArrayNode * curr = head_;

		for (int i = 0; i < size_; i++){
			delete [] curr->data_;
		}
	}

    ListOfArrays(const ListOfArrays& other){
    	head_ = other.head_;
    	head_->next_ = other.head_->next_;
    	head_->prev_ = other.head_->prev_;
    	size_ = other.size_;
    }

	ListOfArrays& operator=(const ListOfArrays& other){
    	head_ = other.head_;
    	head_->next_ = other.head_->next_;
    	head_->prev_ = other.head_->prev_;
    	size_ = other.size_;

		return *this;
	}

    int size(){
    	return size_;
    }

    void push(int array[], int position, int length){
	    int * data = new int[length - position];

	    int counter = 0;

    	for (int i = position; i < length; i++){
    		data[counter] = array[i];
    		counter++;
    	}

    	ArrayNode * to_add = new ArrayNode(data, length - position);

    	ArrayNode * curr = head_->prev_;

    	curr->next_ = to_add;
    	to_add->prev_ = curr;

    	head_->prev_ = to_add;
    	to_add->next_ = head_;

    	size_++;
    }

    void averages(double averages[]){
    	int counter = 0;

    	for (Iterator it = begin(); it != end(); it++){
    		averages[counter] = it.average();

    		cout << averages[counter] << " ";

    		counter++;
    	}

    	cout << endl;
    }

    void medians(double medians[]){
    	int counter = 0;

    	for (Iterator it = begin(); it != end(); it++){
			medians[counter] = it.median();

			cout << medians[counter] << " ";

    		counter++;
    	}

    	cout << endl;
    }
    
    void sizes(int sizes[]){
    	int counter = 0;

    	for (Iterator it = begin(); it != end(); it++){
    		sizes[counter] = it.size();

    		cout << sizes[counter] << " ";

    		counter++;
    	}

    	cout << endl;
    }
    
    void sums(int sums[]){
    	int counter = 0;

    	for (Iterator it = begin(); it != end(); it++){

    		sums[counter] = it.sum();

    		cout << sums[counter] << " ";

    		counter++;
    	}

    	cout << endl;
    }

    Iterator begin(){
    	return Iterator(*this, head_->next_);
    }

    Iterator end(){
    	return Iterator(*this, head_);
    }

    ListOfArrays& ordered(bool ascending = true){
    	for (Iterator it = begin(); it != end(); it++){
    		it.ordered(ascending);
    	}

    	return *this;
    }

    ListOfArrays& operator*=(const int& coef){
    	for (Iterator it = begin(); it != end(); it++){
    		for (int i = 0; i < it.size(); i++){
    			it[i] *= coef;
    		}
    	}

    	return *this;
    }

    ListOfArrays& operator+=(const int& value){
    	for (Iterator it = begin(); it != end(); it++){
    		for (int i = 0; i < it.size(); i++){
    			it[i] += value;
    		}
    	}

    	return *this;
    }

    void show(){
    	for (Iterator it = begin(); it != end(); it++){
    		it.show();
    	}
    }
};

ListOfArrays splitAndConvert(string str){
	stringstream in(str);

	vector<string> v(istream_iterator<string>(in), (istream_iterator<string>()));

	int arr[v.size()];

	int previous = 0;

	int current;

	ListOfArrays ret_val;

	for (int i = 0; i < v.size(); i++){
		current = v[i].find(";");

		if (current != string::npos){
			v[i].erase(1);
			
			arr[i] = stoi(v[i]);

			ret_val.push(arr, previous, i + 1);

			previous = i + 1;
		}
		else{
			arr[i] = stoi(v[i]);
		}
	}

	return ret_val;
}

void parseAndExecute(ListOfArrays ll, vector<string> v){
	int current;

	int previous;

	string to_execute;

	for (int i = 0; i < v.size(); i++){
		string command = v[i];

		previous = 0;

		while (current != string::npos){
			current = command.find(".");

			to_execute = command.substr(previous, current);

			if (to_execute == "show"){
				cout << ">> ";
				ll.show();
			}

			if (to_execute == "averages"){
				double arr[ll.size()];
				cout << ">> ";
				ll.averages(arr);
			}

			if (to_execute == "medians"){
				double arr[ll.size()];
				cout << ">> ";
				ll.medians(arr);
			}

			if (to_execute == "sizes"){
				int arr[ll.size()];
				cout << ">> ";
				ll.sizes(arr);
			}

			if (to_execute == "sums"){
				int arr[ll.size()];
				cout << ">> ";
				ll.sums(arr);
			}

			if (to_execute.find("mul:") != string::npos){
				to_execute.erase(0, to_execute.find(":") + 1);

				int coef = stoi(to_execute);

				ll *= coef;
			}

			if (to_execute.find("add:") != string::npos){
				to_execute.erase(0, to_execute.find(":") + 1);

				int addend = stoi(to_execute);

				ll += addend;
			}

			if (to_execute.find("ordered:") != string::npos){
				to_execute.erase(0, to_execute.find(":") + 1);

				if (to_execute == "true"){
					ll.ordered();
				}
				else{
					ll.ordered();
				}
			}

			if (to_execute == "size"){
				cout << ">> ";
				cout << ll.size() << endl;
			}

			if (to_execute.find("begin.") != string::npos){
				ListOfArrays::Iterator it = ll.begin();

				to_execute.erase(0, to_execute.find(".") + 1);

				if (to_execute.find("next") != string::npos){
					it++;
				}

				if (to_execute == "sum"){
					cout << ">> " << it.sum() << endl;
				}
			}

			command.erase(0, current + 1);
		}
	}
}

int main(){
	string input = "";

	int lines = 0;

	ListOfArrays ll;

	vector<vector<string>> commands;

	while (input != "quit"){
		getline(cin, input);

		stringstream in(input);

		if (lines == 0){
			ll = splitAndConvert(input);
		}

		if (lines != 0 && input != "quit"){
			vector<string> v(istream_iterator<string>(in), (istream_iterator<string>()));
			commands.push_back(v);
		}

		lines++;
	}

	for (int i = 0; i < commands.size(); i++){
		parseAndExecute(ll, commands[i]);
	}

	cout << ">" << endl;

	return 0;
}