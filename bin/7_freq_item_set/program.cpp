#include <bits/stdc++.h>
using namespace std;

double calSupport(vector<string> transactions, vector<int> combination)
{
    int cnt = 0;
    for (auto it : transactions)
    {
        bool valid = true;
        for (int idx : combination)
        {
            if (it[idx] == '0')
            {
                valid = false;
                break;
            }
        }
        if (valid)
            cnt++;
    }
    return static_cast<double>(cnt) / transactions.size();
}

void generateCombinations(int n, int k, int start, vector<int> &current, vector<vector<int>> &Combinations)
{
    if (current.size() == k)
    {
        Combinations.push_back(current);
        return;
    }
    for (int i = start; i < n; i++)
    {
        current.push_back(i);
        generateCombinations(n, k, i + 1, current, Combinations);
        current.pop_back();
    }
}

vector<vector<int>> findFrequentItemSets(vector<string> transactions, vector<string> headers, double minSupport)
{
    int n = transactions[0].size();
    vector<vector<int>> ans;
    for (int i = 1; i <= n; i++)
    {
        vector<vector<int>> combination;
        vector<int> current;
        generateCombinations(n, i, 0, current, combination);
        for (auto it : combination)
        {
            double support = calSupport(transactions, it);
            cout << "Combination: { ";
            for (int idx : it)
            {
                cout << headers[idx] << " ";
            }
            cout << "} -> Support: " << support << endl;

            if (support >= minSupport)
            {
                ans.push_back(it);
            }
        }
    }
    return ans;
}

int main()
{
    ifstream in("transaction.csv");
    vector<string> transactions;
    vector<string> headers;
    string line;

    // Read the first line (headers)
    if (getline(in, line))
    {
        stringstream ss(line);
        string token;
        while (getline(ss, token, ','))
        {
            headers.push_back(token);
        }
    }

    // Read transactions
    while (getline(in, line))
    {
        stringstream ss(line);
        string token, transaction = "";
        while (getline(ss, token, ','))
        {
            if (token == "TRUE")
                transaction += '1';
            else if (token == "FALSE")
                transaction += '0';
        }
        if (transaction != "")
            transactions.push_back(transaction);
    }

    double minSupport = 0.5;
    vector<vector<int>> frequentItemSets = findFrequentItemSets(transactions, headers, minSupport);

    // Final frequent itemsets
    cout << "\nFinal Frequent Item Sets: \n";
    for (auto it : frequentItemSets)
    {
        cout << "{ ";
        for (int idx : it)
        {
            cout << headers[idx] << " ";
        }
        cout << "}, ";
    }

    return 0;
}
