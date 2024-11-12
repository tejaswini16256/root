#include <bits/stdc++.h>
using namespace std;

// Function to calculate mean
double calculateMean(const vector<double>& values) {
    double sum = 0;
    for (double value : values) {
        sum += value;
    }
    return sum / values.size();
}

// Function to calculate median using vector<int>
double calMedian(vector<int>& data) {
    int n = data.size();
    sort(data.begin(), data.end()); // Sorting the data
    if (n % 2 == 0) {
        return (data[n / 2 - 1] + data[n / 2]) / 2.0;
    } else {
        return data[n / 2];
    }
}

// Binning and smoothing function
void binData(const vector<double>& data, int binSize) {
    vector<double> sortedData = data;
    sort(sortedData.begin(), sortedData.end());

    int numBins = sortedData.size() / binSize;
    vector<vector<double>> bins(numBins);

    for (int i = 0; i < sortedData.size(); ++i) {
        bins[i / binSize].push_back(sortedData[i]);
    }

    cout << "Sorted Data: ";
    for (double value : sortedData) {
        cout << value << " ";
    }
    cout << "\n\n";

    cout << "Partition into Equidepth (" << binSize << ") Bins ->\n";
    for (int i = 0; i < numBins; ++i) {
        cout << "Bin " << i + 1 << ": { ";
        for (double value : bins[i]) {
            cout << value << " ";
        }
        cout << "}\n";
    }

    // Make copies of bins for each smoothing operation
    vector<vector<double>> binsForMean = bins;
    vector<vector<double>> binsForMedian = bins;
    vector<vector<double>> binsForBoundaries = bins;

    cout << "\nSmoothing by Mean ->\n";
    for (int i = 0; i < numBins; ++i) {
        if (!binsForMean[i].empty()) {
            double mean = calculateMean(binsForMean[i]);
            for (double& value : binsForMean[i]) {
                value = mean;
            }
            cout << "Bin " << i + 1 << ": { ";
            for (double value : binsForMean[i]) {
                cout << value << " ";
            }
            cout << "}\n";
        }
    }

    cout << "\nSmoothing by Median ->\n";
    for (int i = 0; i < numBins; ++i) {
        if (!binsForMedian[i].empty()) {
            vector<int> binValues(binsForMedian[i].begin(), binsForMedian[i].end()); // Convert to int
            double median = calMedian(binValues);  // Use calMedian function
            for (double& value : binsForMedian[i]) {
                value = median;  // Replace all values with the median
            }
            cout << "Bin " << i + 1 << ": { ";
            for (double value : binsForMedian[i]) {
                cout << value << " ";
            }
            cout << "}\n";
        }
    }

    cout << "\nSmoothing by Bin Boundaries ->\n";
    for (int i = 0; i < numBins; ++i) {
        double lowerBoundary = binsForBoundaries[i].front();  // Minimum value in the bin
        double upperBoundary = binsForBoundaries[i].back();   // Maximum value in the bin

        for (double& value : binsForBoundaries[i]) {
            if (abs(value - lowerBoundary) < abs(value - upperBoundary)) {
                value = lowerBoundary;  // Replace with the closest boundary
            } else {
                value = upperBoundary;
            }
        }

        cout << "Bin " << i + 1 << ": { ";
        for (double value : binsForBoundaries[i]) {
            cout << value << " ";
        }
        cout << "}\n";
    }
}

int main() {
    ifstream in("input.csv");

    vector<double> data;
    double value;
    while (in >> value) {
        data.push_back(value);
    }

    int binSize = 3;  // Number of values per bin
    binData(data, binSize);

    in.close();
    return 0;
}
