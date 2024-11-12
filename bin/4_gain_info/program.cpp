#include <bits/stdc++.h>
#include <fstream>
using namespace std;

// Function to calculate entropy
double entropy(const vector<string> &classes)
{
    map<string, int> classCounts;
    for (auto classLabel : classes)
    {
        classCounts[classLabel]++;
    }

    double entropy = 0.0;
    int total = classes.size();
    for (auto pair : classCounts)
    {
        double p = (double)pair.second / total;
        entropy -= p * log2(p);
    }
    return entropy;
}

// Function to calculate conditional entropy for a given attribute
double conditional_entropy(const vector<string> &attribute, const vector<string> &classes)
{
    map<string, vector<string>> subsets;

    for (int i = 0; i < attribute.size(); i++)
    {
        subsets[attribute[i]].push_back(classes[i]);
    }

    double condEntropy = 0.0;
    int total = attribute.size();
    for (const auto &pair : subsets)
    {
        double subsetSize = pair.second.size();
        condEntropy += (subsetSize / total) * entropy(pair.second);
    }
    return condEntropy;
}

// Function to calculate information gain
double information_gain(const vector<string> &attribute, const vector<string> &classes)
{
    double baseEntropy = entropy(classes);
    double condEntropy = conditional_entropy(attribute, classes);
    return baseEntropy - condEntropy;
}

int main()
{
    ifstream in("input.csv");
    ofstream out("output.csv");

    vector<string> outlook, temp, humidity, windy, classLabel;
    string value, line;

    // Skip header line
    getline(in, line);

    // Read data from the CSV file
    while (getline(in, line))
    {
        stringstream ss(line);
        vector<string> row;
        while (getline(ss, value, ','))
        {
            row.push_back(value);
        }

        // Assuming columns are: outlook, temp, humidity, windy, class
        outlook.push_back(row[0]);
        temp.push_back(row[1]);
        humidity.push_back(row[2]);
        windy.push_back(row[3]);
        classLabel.push_back(row[4]);
    }
    
    out<<"info(T): "<<entropy(classLabel)<<endl;

    out<<"attribute,info(X T),info_gain(X T)\n";
    out<<"outlook,"<<conditional_entropy(outlook,classLabel)<<","<<information_gain(outlook, classLabel)<<",\n";
    out<<"temp,"<<conditional_entropy(temp,classLabel)<<","<<information_gain(temp, classLabel)<<",\n";
    out<<"humidity,"<<conditional_entropy(humidity,classLabel)<<","<<information_gain(humidity, classLabel)<<",\n";
    out<<"windy,"<<conditional_entropy(windy,classLabel)<<","<<information_gain(windy, classLabel)<<",\n";


    in.close();
    out.close();
}
