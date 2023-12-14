#include <iostream>
#include <list>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

enum collision_method {chain_method, chain_method_no_repetition}; 

template<class T>
class hashtable{
    static const int number_of_indexes = 10000;
    list<T> hash_table[number_of_indexes];
    int collisionscounter = 0;
    int count_data_repeated = 0;
    enum collision_method method;


public:

    hashtable(collision_method choosed){
        method = choosed;
    };

    hashtable(vector<T> lst, collision_method choosed){
        method = choosed;
        for (auto& x: lst){
            insertRegister(x);
        }
    };

    void collisions_method(enum collision_method choosed){
        method = choosed;
    }

    unsigned long new_hash(string);

    int index_calculator(unsigned long hash, int table_size);

    bool isEmpty(int index){
        return hash_table[index].empty();
    };

    void insertRegister(T data);
    void deleteRegister(T data);

    vector<T> get_values();

    void printTable(){
        for(auto& x: hash_table){
            for(auto& y: x){
                cout << y << "\t";
            }
            if (!x.empty()){cout << endl; cout << "-------------------" << endl;}
        }
    };
};

template <class T>
unsigned long hashtable<T> :: new_hash(string str){
    unsigned long hash = 5381;
    int index = 0;
    int last_index = str.size();
    int c = 0;
    while (index < last_index){
        c = str[index];
        hash = ((hash << 5) + hash) + c;
        index++;
    }
    return hash;
}

template <class T>
int hashtable<T> :: index_calculator(unsigned long hash, int table_size){
    int index = 0;
    index = hash % table_size;

    return index;
}

template <class T>
vector<T> hashtable<T> :: get_values(){
    vector<T> buffer;
    for(auto& x: hash_table){
        for(auto& y: x){
            buffer.push_back(y);
        }
    }
    return buffer;
};

template <class T>
void hashtable<T> :: insertRegister(T data){
    switch (method)
    {
    case chain_method:{
        unsigned long hash = new_hash(data);
        int index = index_calculator(hash, number_of_indexes);
        hash_table[index].push_back(data);
        break;
    }
        
    case chain_method_no_repetition:{
        unsigned long hash = new_hash(data);
        int index = index_calculator(hash, number_of_indexes);
        cout << index << endl;
        cout << hash << endl;
        if(isEmpty(index)){
            hash_table[index].push_back(data);
        }
        else{
            collisionscounter++;
            if(data == hash_table[index].front()){
                count_data_repeated++;

            }
            else{
                hash_table[index].push_back(data);
            }
        }
        break;
    }
    }
}

template<class T>
void hashtable<T> :: deleteRegister(T data){
    switch (method)
    {
    case chain_method:{
        unsigned long hash = new_hash(data);
        int index = index_calculator(hash, number_of_indexes);
        for (std::list<string>::iterator it= hash_table[index].begin(); it != hash_table[index].end(); ++it){
            if(data == *it){
                hash_table[index].remove(data);
                break;
            }
        }
    
        break;
    }
        
    case chain_method_no_repetition:{
        unsigned long hash = new_hash(data);
        int index = index_calculator(hash, number_of_indexes);
        hash_table[index].remove(data);
        break;
    }
    }
}
