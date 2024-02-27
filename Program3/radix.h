#include "quick.h"
#include <math.h>
#include <list>


class radix{
public:
    radix(vector<int> v_) : v(v_){
        // maybe ?
    }

    vector<int> sort(){
        int max = 0;
        int length = (int)v.size();
        for(int i=0; i<length; i++){
            if(v[i]>max) max = v[i];
        } // find how many digits
        // use count sort for every digit
        for (int exp = 1; max / exp > 0; exp *= 10){
            countSort(length, exp);
        }
        return v;
    }

    vector<int> sort_print(){
        int max = 0;
        int length = (int)v.size();
        for(int i=0; i<length; i++){
            if(v[i]>max) max = v[i];
        } // find how many digits
        // use count sort for every digit
        for (int exp = 1; max / exp > 0; exp *= 10){
            if(exp == 1) cout << "\nFirst-pass:\n";
            else if (exp == 2) cout << "\nSecond-pass:\n";
            else cout << "\nThird-pass:\n";
            countSortPrint(length, exp);
            print_v();
        }
        return v;
    }

    void countSortPrint(int length, int exp){
        int output[length];
        int i;
        int count[10] = {0};
        list<int> *bucket;
        bucket = new list<int>[10];
        // put numbers in the right bucket
        for (i = 0; i < length; i++) {
            bucket[(v[i] / exp) % 10].push_back(v[i]);
            count[(v[i] / exp) % 10]++;
        }
        for(int i=0; i<10; i++){
            cout << i << " | ";
            for(auto j : bucket[i])
                cout << " --> " << j;
            cout << "\n";
        }
        // accumulate the occurences to get to the right pos
        for (i = 1; i < 10; i++) count[i] += count[i - 1];
      
        for (i = length - 1; i >= 0; i--) { // build output array
            output[count[(v[i] / exp) % 10] - 1] = v[i];
            count[(v[i] / exp) % 10]--;
        }
        // copy over
        for (i = 0; i < length; i++) v[i] = output[i];
        
    }
    
    void countSort(int length, int exp){
        int output[length];
        int i;
        int count[10] = {0};
        // put numbers in the right bucket
        for (i = 0; i < length; i++) count[(v[i] / exp) % 10]++;
        // accumulate the occurences to get to the right pos
        for (i = 1; i < 10; i++) count[i] += count[i - 1];
      
        for (i = length - 1; i >= 0; i--) { // build output array
            output[count[(v[i] / exp) % 10] - 1] = v[i];
            count[(v[i] / exp) % 10]--;
        }
        // copy over
        for (i = 0; i < length; i++) v[i] = output[i];
        
    }

    void print_v(){

        cout << "Resulting chain : ";
        for(auto vi : v){
            cout << vi << ",";
        }
        cout << "\n";
    }

public:
    vector<int> v;
    // maybe ?
};
