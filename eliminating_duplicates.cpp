/* Leonardo Dias Pertuzzatti - Data Structure Project 

You can get the same dataset in https://archive.ics.uci.edu/dataset/602/dry+bean+dataset

*/

#include "hash_table.h"
#include <fstream>
#include <chrono>
#include <sstream>



int main(){
    string line;
    ifstream file("Dry_Bean_Dataset.csv", ios::in | ios::ate);
    file.seekg (0, ios::beg);
    ofstream file2("Dry_Bean_Dataset_after_data_cleaning.csv", ios::out| ios::ate);

    hashtable<string> table(chain_method_no_repetition);
    vector<string> hashtable_elements;

    while (getline(file, line))
    {
        std::stringstream linestream(line);
        std::string value;
        while (getline(linestream, value, ';'))
        {
            table.insertRegister(value);
            cout << value << endl;
            std::cout << "Value(" << value << ")\n";
        }
    }

    hashtable_elements = table.get_values();
    for (auto& x: hashtable_elements){
        file2 << x << '\n';
    }
}