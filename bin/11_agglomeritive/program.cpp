#include <bits/stdc++.h>
#include <fstream>
using namespace std;
double euclideanDistance(const vector<double>& point1, const vector<double>& point2) {
    double sum = 0;
    for (size_t i = 0; i < point1.size(); ++i) {
        sum += pow(point1[i] - point2[i], 2);
    }
    return sqrt(sum);
}
void displayDistanceMatrix(const vector<vector<double>>& distanceMatrix, const vector<string>& labels) {
    int n = distanceMatrix.size();
    cout << "   \t";
    for (const auto& label : labels) {
        cout << label << "\t";
    }
    cout << endl;
    for (int i = 0; i < n; ++i) {
        cout << labels[i] << "\t";
        for (int j = 0; j < n; ++j) {
            cout << fixed << setprecision(2) << distanceMatrix[i][j] << "\t";
        }
        cout << endl; 
    }
}
void agglomerativeClustering(vector<vector<double>>& points) {
    int n = points.size();
    vector<vector<double>> distanceMatrix(n, vector<double>(n, 0.0));
    vector<bool> clustered(n, false);
    vector<pair<int, int>> clusters;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            distanceMatrix[i][j] = euclideanDistance(points[i], points[j]);
            distanceMatrix[j][i] = distanceMatrix[i][j]; 
        }
    }
    vector<string> labels; 
    for (int i = 0; i < n; ++i) {
        labels.push_back("Point " + to_string(i + 1)); 
    }
    cout << "Initial Distance Matrix:\n";
    displayDistanceMatrix(distanceMatrix, labels);
    while (n > 1) {
        double minDistance = numeric_limits<double>::max();
        int clusterA = -1, clusterB = -1;
        for (int i = 0; i < distanceMatrix.size(); ++i) {
            for (int j = i + 1; j < distanceMatrix.size(); ++j) {
                if (distanceMatrix[i][j] < minDistance) {
                    minDistance = distanceMatrix[i][j];
                    clusterA = i;
                    clusterB = j;
                }
            }
        }
        cout << "\nMerging clusters: " << labels[clusterA] << " and " << labels[clusterB] << " with distance: " << minDistance << endl;
        for (int i = 0; i < distanceMatrix.size(); ++i) {
            if (i != clusterA && i != clusterB) {
                distanceMatrix[clusterA][i] = min(distanceMatrix[clusterA][i], distanceMatrix[clusterB][i]);
                distanceMatrix[i][clusterA] = distanceMatrix[clusterA][i]; 
            }
        }
        clustered[clusterB] = true;
        for (int i = 0; i < distanceMatrix.size(); ++i) {
            distanceMatrix[clusterB][i] = numeric_limits<double>::max();
            distanceMatrix[i][clusterB] = numeric_limits<double>::max(); 
        }
        labels[clusterA] = labels[clusterA] + " & " + labels[clusterB]; 
        labels.erase(labels.begin() + clusterB); 
        distanceMatrix.erase(distanceMatrix.begin() + clusterB); 
        for (auto& row : distanceMatrix) {
            row.erase(row.begin() + clusterB); 
        }
        n--; 
        cout << "\nUpdated Distance Matrix after merging:\n";
        displayDistanceMatrix(distanceMatrix, labels);
    }
    cout << "\nFinal cluster: " << labels[0] << endl; 
}
int main() {
    fstream in("input.csv");
    vector<vector<double>> points;
    string line;

    // Read points from the CSV file
    while (getline(in, line)) {
        stringstream ss(line);
        string value;
        vector<double> point;

        while (getline(ss, value, ',')) {
            point.push_back(stod(value)); // Convert string to double and store in point
        }
        points.push_back(point); // Add point to the points vector
    }

    in.close();

    // Perform agglomerative clustering
    agglomerativeClustering(points);

    return 0;
}
