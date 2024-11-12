#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
using namespace std;

// Function to split string based on a delimiter
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    ifstream in("input.csv");
    ofstream out("output.csv");

    string line;
    vector<vector<string>> data;

    // Reading the CSV file line by line
    while (getline(in, line)) {
        data.push_back(split(line, ','));
    }

    // Column indices (dynamic, based on header)
    int item_col = 0;
    int state1_col = 1;
    int state2_col = 2;
    int both_state_col = 3;

    // Write header to output.csv
    out << data[0][item_col] << "," << data[0][state1_col] << "," << "t-wt(state1),d-wt(state1),"
        << data[0][state2_col] << "," << "t-wt(state2),d-wt(state2),"
        << data[0][both_state_col] << "," << "t-wt(both_state),d-wt(both_state)\n";

    // Calculating t_weight and d_weight for each state
    for (size_t i = 1; i < data.size() - 1; i++) { // Exclude the last row (total row)
        string item = data[i][item_col];
        double state1_count = stod(data[i][state1_col]);
        double state2_count = stod(data[i][state2_col]);
        double both_state_count = stod(data[i][both_state_col]);

        // Get total counts from the 'total' row (last row in the input file)
        double total_state1_count = stod(data[data.size() - 1][state1_col]);
        double total_state2_count = stod(data[data.size() - 1][state2_col]);
        double total_both_state_count = stod(data[data.size() - 1][both_state_col]);

        // Calculate t_weight and d_weight for state1
        double t_weight_state1 = (state1_count / both_state_count) * 100;
        double d_weight_state1 = (state1_count / total_state1_count) * 100;

        // Calculate t_weight and d_weight for state2
        double t_weight_state2 = (state2_count / both_state_count) * 100;
        double d_weight_state2 = (state2_count / total_state2_count) * 100;

        // Calculate t_weight and d_weight for both_state
        double t_weight_both_state = (both_state_count / total_both_state_count) * 100;
        double d_weight_both_state = (both_state_count / total_both_state_count) * 100;

        // Write to output.csv
        out << item << "," << data[i][state1_col] << "," << t_weight_state1 << "%," << d_weight_state1 << "%,"
            << data[i][state2_col] << "," << t_weight_state2 << "%," << d_weight_state2 << "%,"
            << data[i][both_state_col] << "," << t_weight_both_state << "%," << d_weight_both_state << "%\n";
    }

    // Finally for the total row
    out << data[data.size() - 1][item_col] << "," << data[data.size() - 1][state1_col] << ",100%,100%,"
        << data[data.size() - 1][state2_col] << ",100%,100%,"
        << data[data.size() - 1][both_state_col] << ",100%,100%\n";

    in.close();
    out.close();

    cout << "Output file 'output.csv' generated successfully!" << endl;
    return 0;
}
