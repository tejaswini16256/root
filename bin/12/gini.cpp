#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <cmath>

using namespace std;
double entropy(const vector<int>& labels) {
    map<int, int> count;
    for (int label : labels) {
        count[label]++;
    }
    double total = labels.size();
    double ent = 0.0;
    for (const auto& pair : count) {
        double p = pair.second / total;
        ent -= p * log2(p);
    }
    return ent;
}
double gain(const vector<vector<string>>& data, int attributeIndex, const vector<int>& labels) {
    double totalEntropy = entropy(labels);
    
    map<string, vector<int>> subsets;
    for (int i = 0; i < data.size(); ++i) {
        subsets[data[i][attributeIndex]].push_back(labels[i]);
    }

    double weightedEntropy = 0.0;
    for (const auto& pair : subsets) {
        double subsetEntropy = entropy(pair.second);
        weightedEntropy += (pair.second.size() / (double)labels.size()) * subsetEntropy;
    }
    return totalEntropy - weightedEntropy;
}
double gini(const vector<int>& labels) {
    map<int, int> count;
    for (int label : labels) {
        count[label]++;
    }

    double total = labels.size();
    double giniIndex = 1.0;

    for (const auto& pair : count) {
        double p = pair.second / total;
        giniIndex -= p * p;
    }
    return giniIndex;
}
double giniAttribute(const vector<vector<string>>& data, int attributeIndex, const vector<int>& labels) {
    map<string, vector<int>> subsets;
    for (int i = 0; i < data.size(); ++i) {
        subsets[data[i][attributeIndex]].push_back(labels[i]);
    }
    double weightedGini = 0.0;
    for (const auto& pair : subsets) {
        double giniValue = gini(pair.second);
        weightedGini += (pair.second.size() / (double)labels.size()) * giniValue;
    }
    return weightedGini;
}
int main() {
    string line;
    ifstream file("gini.csv"); 
    vector<vector<string>> data;
    vector<int> labels;   
    getline(file, line); 
    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            vector<string> row;
            string value;
            while (getline(ss, value, ',')) {
                row.push_back(value);
            }
            data.push_back(row);
            labels.push_back(stoi(row.back())); 
        }
        file.close();
    } else {
        cout << "Unable to open file" << endl;
        return 1;
    }
    double gainColor = gain(data, 0, labels);
    cout << "Information Gain for attribute 'Color': " << gainColor << endl;
    double gainSize = gain(data, 1, labels);
    cout << "Information Gain for attribute 'Size': " << gainSize << endl;
    double giniValue = gini(labels);
    cout << "Gini Index for the entire dataset: " << giniValue << endl;
    double giniColor = giniAttribute(data, 0, labels);
    cout << "Gini Index for attribute 'Color': " << giniColor << endl;
    double giniSize = giniAttribute(data, 1, labels);
    cout << "Gini Index for attribute 'Size': " << giniSize << endl;
    return 0;
}
