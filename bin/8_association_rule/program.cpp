#include <bits/stdc++.h>
using namespace std;

double calSupport(const vector<string>& transactions, const vector<int>& combination) {
    int cnt = 0;
    for (const auto& it : transactions) {
        bool valid = true;
        for (int idx : combination) {
            if (it[idx] == '0') {
                valid = false;
                break;
            }
        }
        if (valid) cnt++;
    }
    double support = static_cast<double>(cnt) / transactions.size();
    return support;
}

void generateCombinations(int n, int k, int start, vector<int>& current, vector<vector<int>>& Combinations) {
    if (current.size() == k) {
        Combinations.push_back(current);
        return;
    }
    for (int i = start; i < n; i++) {
        current.push_back(i);
        generateCombinations(n, k, i + 1, current, Combinations);
        current.pop_back();
    }
}

vector<vector<int>> findFrequentItemSets(const vector<string>& transactions, const vector<string>& headers, double minSupport) {
    int n = transactions[0].size();
    vector<vector<int>> ans;
    
    cout << "\n--- Frequent Itemset Calculations ---\n";
    for (int i = 1; i <= n; i++) {
        vector<vector<int>> combination;
        vector<int> current;
        generateCombinations(n, i, 0, current, combination);
        for (const auto& it : combination) {
            double support = calSupport(transactions, it);
            
            // Print the combination and its support
            cout << "Combination: { ";
            for (int idx : it) {
                cout << headers[idx] << " ";
            }
            cout << "} -> Support: " << support << endl;

            if (support >= minSupport) {
                ans.push_back(it);
            }
        }
    }
    // After all frequent itemsets are calculated, display them
    cout << "\n--- Frequent Itemsets ---\n";
    for (const auto& itemset : ans) {
        cout << "{ ";
        for (int idx : itemset) {
            cout << headers[idx] << " ";
        }
        cout << "} ";
    }
    cout << endl;
    return ans;
}

// Function to generate all non-empty subsets of a given set
void generateSubsets(const vector<int>& set, vector<vector<int>>& subsets) {
    int n = set.size();
    for (int i = 1; i < (1 << n); i++) {
        vector<int> subset;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                subset.push_back(set[j]);
            }
        }
        subsets.push_back(subset);
    }
}

// Function to calculate and print association rules with confidence
void findAssociationRules(const vector<string>& transactions, const vector<vector<int>>& frequentItemSets, const vector<string>& headers, double minConfidence) {
    cout << "\n--- Association Rule Calculations ---\n";
    
    for (const auto& itemSet : frequentItemSets) {
        vector<vector<int>> subsets;
        generateSubsets(itemSet, subsets);

        for (const auto& subset : subsets) {
            if (subset.size() == itemSet.size()) continue; // skip the full set

            // Calculate confidence
            vector<int> remaining;
            for (int idx : itemSet) {
                if (find(subset.begin(), subset.end(), idx) == subset.end()) {
                    remaining.push_back(idx);
                }
            }
            double supportXY = calSupport(transactions, itemSet);
            double supportX = calSupport(transactions, subset);
            double confidence = supportXY / supportX;

            // Print the rule and its confidence
            cout << "Rule: { ";
            for (int idx : subset) cout << headers[idx] << " ";
            cout << "} -> { ";
            for (int idx : remaining) cout << headers[idx] << " ";
            cout << "} -> Confidence: " << confidence << endl;

            // Display only valid rules with confidence >= minConfidence
            if (confidence >= minConfidence) {
                cout << "Valid Rule (Conf >= " << minConfidence << "): { ";
                for (int idx : subset) cout << headers[idx] << " ";
                cout << "} -> { ";
                for (int idx : remaining) cout << headers[idx] << " ";
                cout << "} with Confidence: " << confidence << endl;
            }
        }
    }
}

int main() {
    ifstream in("transaction.csv");
    vector<string> transactions;
    vector<string> headers;
    string line;

    // Read the first line (headers)
    if (getline(in, line)) {
        stringstream ss(line);
        string token;
        while (getline(ss, token, ',')) {
            headers.push_back(token);
        }
    }

    // Read transactions
    while (getline(in, line)) {
        stringstream ss(line);
        string token, transaction = "";
        while (getline(ss, token, ',')) {
            if (token == "TRUE")
                transaction += '1';
            else if (token == "FALSE")
                transaction += '0';
        }
        if (transaction != "")
            transactions.push_back(transaction);
    }

    double minSupport = 0.5;
    double minConfidence = 0.7;

    // Step 7: Find frequent itemsets
    vector<vector<int>> frequentItemSets = findFrequentItemSets(transactions, headers, minSupport);

    // Step 8: Find association rules
    findAssociationRules(transactions, frequentItemSets, headers, minConfidence);

    return 0;
}
