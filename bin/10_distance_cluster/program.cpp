#include <bits/stdc++.h>
#include <fstream>
using namespace std;

// Function to compute Euclidean distance between two points
double euclideanDistance(const vector<double>& point1, const vector<double>& point2) {
    double sum = 0;
    for (size_t i = 0; i < point1.size(); ++i) {
        sum += pow(point1[i] - point2[i], 2);
    }
    return sqrt(sum);
}

// Function to compute the center of the cluster
vector<double> computeClusterCenter(const vector<vector<double>>& points) {
    size_t dimensions = points[0].size();
    vector<double> center(dimensions, 0.0);

    for (const auto& point : points) {
        for (size_t i = 0; i < dimensions; ++i) {
            center[i] += point[i];
        }
    }

    for (size_t i = 0; i < dimensions; ++i) {
        center[i] /= points.size(); // Calculate mean for each dimension
    }

    return center;
}

// Function to write the upper triangular distance matrix with headings
void writeUpperTriangularMatrix(ofstream& out, const vector<vector<double>>& distanceMatrix, const vector<string>& labels) {
    size_t n = distanceMatrix.size();
    
    // Write column headings
    out << "Point,";
    for (const auto& label : labels) {
        out << label << ",";
    }
    out << endl;

    for (size_t i = 0; i < n; ++i) {
        // Write row heading
        out << labels[i] << ",";
        
        for (size_t j = 0; j < n; ++j) {
            if (i <= j) {
                out << fixed << setprecision(2) << distanceMatrix[i][j] << ",";
            } else {
                out << ","; // Write empty space for lower triangular part
            }
        }
        out << endl; // New line after each row
    }
}

int main() {
    ifstream in("input.csv");
    ofstream out("output.csv");

    if (!in.is_open()) {
        cerr << "Error opening input file!" << endl;
        return 1;
    }

    if (!out.is_open()) {
        cerr << "Error opening output file!" << endl;
        return 1;
    }

    vector<vector<double>> points;
    vector<string> labels; // To store point labels (e.g., Point 1, Point 2, etc.)
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
        labels.push_back("Point " + to_string(points.size())); // Generate label for each point
    }

    // Compute the center of the cluster
    vector<double> clusterCenter = computeClusterCenter(points);

    // Display the cluster center
    cout << "Cluster center: ";
    for (const auto& coord : clusterCenter) {
        cout << coord << " ";
    }
    cout << endl;

    // Calculate the distances of all points from the cluster center
    vector<vector<double>> distanceMatrix(points.size(), vector<double>(points.size(), 0.0));

    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i; j < points.size(); ++j) {
            distanceMatrix[i][j] = euclideanDistance(points[i], points[j]);
        }
    }

    // Write the distance matrix in upper triangular form with headings to the output file
    out << "Distance Matrix:\n"; // Optional header for clarity
    writeUpperTriangularMatrix(out, distanceMatrix, labels);

    in.close();
    out.close();

    return 0;
}
