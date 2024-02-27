#include "insertion.h"

class quick{
public:
    quick(vector<int> v_): v(v_){}
    
    vector<int> sort(){
        quick_sort_partation(0, (int)v.size()-1);
        return v;
    }

    vector<int> sort_print(){
        cout << "Before: \n";
        print_v();
        quick_sort_partation_print(0, (int)v.size()-1);
        
        return v;
    }

    void quick_sort_partation_print(int front, int rear){
        if(front < rear){
            int pivot = v[front]; // pivot
            int i = front;
            int j = rear+1;
            
            while(true){
                while(i++ < rear && v[i] < pivot);
                while(j-- > front && v[j] > pivot);
                if(i >= j) break;
                swap(v[i], v[j]);
            }
            
            swap(v[front], v[j]);
            cout << front << "-" << rear << " : \n";
            print_v();
            quick_sort_partation_print(front, j - 1);
            quick_sort_partation_print(j + 1, rear);
        }
        
        return;
    }
    
    void quick_sort_partation(int front, int rear){
        if(front < rear){
            int pivot = v[rear]; // pivot
            int i = front;
            // index of smaller element = right position of pivot found so far
         
            for (int j=front; j<rear; j++){
                if (v[j] < pivot){
                    swap(v[i], v[j]);
                    i++; // increment index of smaller element
                }
            }
            swap(v[i], v[rear]); // put pivot in place
            quick_sort_partation(front, i - 1);
            quick_sort_partation(i + 1, rear);
        }
        
        return;
    }

    void print_v(){
        for(auto vi : v){
            cout << vi << ",";
        }
        cout << "\n";
    }

public:
    vector<int> v;
};
