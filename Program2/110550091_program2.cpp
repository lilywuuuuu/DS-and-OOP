#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

class Nodes {
public:
    char data;
    int freq;
 
    Nodes* left;
    Nodes* right;
 
    Nodes(char c, int f){
        data = c;
        freq = f;
        left = right = NULL;
    }
};
 

class Compare { // custom comparator class for the priority queue
public:
    bool operator()(Nodes* a, Nodes* b){
        return a->freq > b->freq;
    }
};
 

Nodes* generateTree(priority_queue<Nodes*, vector<Nodes*>, Compare> pq){
    
    while (pq.size() != 1) { // stop untill there's only one tree left
        
        Nodes* left = pq.top(); // left = tree with smallest frequency in the current queue
        pq.pop();
 
        Nodes* right = pq.top(); // right = tree with the next smallest frequency in the current queue
        pq.pop();
 
        Nodes* node = new Nodes('Z', left->freq + right->freq); // create a new node with the two freq added
        node->left = left;
        node->right = right;
        pq.push(node); // add the new node to the priority queue
    }
 
    return pq.top(); // return the ultimate tree
}

void Code(char data[], int order[][100], Nodes* root, int *arr, int level, int size){
    
    if (root->left != NULL) { // Assign 0s to the left branches
        arr[level] = 0;
        Code(data, order, root->left, arr, level + 1, size);
    }
 
    if (root->right != NULL) { // Assign 1s to the right branches
        arr[level] = 1;
        Code(data, order, root->right, arr, level + 1, size);
    }
 
    if ((root->left == NULL) && (root->right == NULL)) { // Save the code if it's a leaf node
        int place = 0;
        
        for(int i=0; i<size; i++){
            if(root->data == data[i]) place = i;
        }
        
        copy(arr, arr+level, order[place]); // deep copy the code to its corresponding element
        order[place][level] = root->freq+1; // to diff between its freq and 1s and 0s and also know its length
    }
}

int Print(char data[], int order[][100], int size){
    
    int wepl = 0;
    for(int i=0; i<size; i++){
        cout << data[i] << " : ";
        int j;
        for (j=0; (order[i][j] == 1) || (order[i][j] == 0); j++){
            cout << order[i][j];
        }
        cout << "\n";
        wepl += (order[i][j]-1) * j; // order[i][j]-1 = frequency, j = length, wepl = frequency x length
    }
    cout << "\n";
    return wepl;
}
 
void Huffman1(char data[], int freq[], int size){

    priority_queue<Nodes*, vector<Nodes*>, Compare> pq;
    for (int i = 0; i < size; i++) {
        Nodes* newNode = new Nodes(data[i], freq[i]); // create a new node for each element
        pq.push(newNode); // push it to the priority queue
    }
 
    Nodes* root = generateTree(pq); // genenerate the Huffman tree
 
    int arr[100], level = 0, order[100][100]={0};
    Code(data, order, root, arr, level, size); // get the code for each element
    int wepl = Print(data, order, size); // print its code and also calculate the wepl
    cout << "WEPL : " << wepl << "\n";
}

string Decode(Nodes* root, string s){
    string ans = "";
    Nodes* curr = root;
    
    for (int i=0; i<s.size(); i++){
        bool flag = 0;
        if (s[i] == '0') curr = curr->left;
        else if (s[i] == '1') curr = curr->right;

        if ((curr->left == NULL) && (curr->right == NULL)){
            ans += curr->data; // append the letter to the answer
            curr = root; // reset
            flag = 1; // to determine if there are extra code
        }
        
        if(!flag && i==s.size()-1) ans += " -wrong decode-";
    }
    return ans + '\0';
}

void Huffman2(char data[], int freq[], int size, string decode){

    priority_queue<Nodes*, vector<Nodes*>, Compare> pq;
    for (int i = 0; i < size; i++) {
       Nodes* newNode = new Nodes(data[i], freq[i]); // create a new node for each element
       pq.push(newNode); // push it to the priority queue
    }

    Nodes* root = generateTree(pq); // genenerate the Huffman tree

    int arr[100], level = 0, order[100][100]={0};
    Code(data, order, root, arr, level, size); // get the code for each element
    int wepl = Print(data, order, size); // print its code and also calculate the wepl
    string answer = Decode(root, decode); // decode to get the answer
    cout << "Huffman code : " << decode << "\n";
    cout << "decode : " << answer << "\n";
    cout << "WEPL : " << wepl << "\n";

}

int main(int argc, const char* argv[]){
    vector<string> all_args;
    all_args.assign(argv, argv + argc); // convert command line argument to string 

    cout << "DSOO-Program2-Demo: ";
    for(auto a : all_args){
        cout << a << " ";
    }
    cout << "\n\n";
    
    if(argc != 2){
        cout << "part1\n";
        char data[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                       'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
        int freq[] = {11, 5, 2, 3, 12, 3, 5, 6, 8, 1, 2, 4, 8, 7, 2, 2, 1, 9, 6, 2, 4, 1, 10, 10, 1, 1};

        for(int i=0; i<26; i++){
            cout << data[i] << " = " << setw(2) << freq[i] << " | ";
            if(i%10 == 9) cout << "\n"; // print the elements with 10 in a row
            else if (i == 25) cout << "\n\n";
        }

        Huffman1(data, freq, 26);
    }
    else {
        string filename = argv[1];
        cout << "read file from : " << "test/" << filename << "\n";
        
        ifstream test;
        test.open(filename);// open the file

        string text, encode;
        getline(test, text, ' '); // get the characters
        getline(test, encode); // get the Huffman code
        test.close();

        cout << "characters : " << text << "\n\n";

        int input[52] = {0};
        int freq[52] = {0};
        char data[52] = {0};

        for(int i=0; i<text.length(); i++){
            if(text[i] >= 'a' ) input[text[i] - 'a' + 26]++; // store the lower case at the latter half of the list
            else input[text[i] - 'A']++; // store the capital case at the former half of the list
        }

        int size = 0;
        for(int i=0; i<52; i++){
            if(input[i] > 0){
                if((size % 10 == 0) && (size != 0)) cout << "\n"; // print the letters by 10s
                data[size] = (i<26) ? (char)(i + 'A') : (char)(i + 'a' - 26); // create the data list
                freq[size] = input[i]; // create the frequency list
                cout << data[size] << " = " << setw(2) << freq[size] << " | ";
                size++; // get the size
            }
            if(i == 51) cout << "\n\n";
        }

        Huffman2(data, freq, size, encode);
        
    }

    return 0;
}
