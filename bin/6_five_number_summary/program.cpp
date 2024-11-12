#include <bits/stdc++.h>
using namespace std;

double calMedian(vector<int>& data)
{
    int n=data.size();
    if (n%2==0) 
    {
        return (data[n/2-1]+data[n/2])/2.0;
    } 
    else
    {
        return data[n/2];
    }
}

int main()
{
    ifstream in("input.csv");
    vector<int>data;
    int value;
    while(in>>value)
    data.push_back(value);
    int n=data.size();

    sort(data.begin(),data.end());
    int min=data[0],max=data[n-1];
    double median=calMedian(data);

    vector<int>lowerHalf(data.begin(),data.begin()+n/2);
    double q1=calMedian(lowerHalf);
    double q3;
    if(n%2==0)
    {
        vector<int>upperHalf(data.begin()+n/2 ,data.end());
        q3=calMedian(upperHalf);
    }
    else
    {
        vector<int>upperHalf(data.begin()+n/2 +1,data.end());
        q3=calMedian(upperHalf);
    }
    cout<<"sorted data: ";
    for(auto it:data)
    cout<<it<<" ";
    cout<<"\n";
    cout << "Min: " << min << endl;
    cout << "Q1: " << q1 << endl;
    cout << "Median: " << median << endl;
    cout << "Q3: " << q3 << endl;
    cout << "Max: " << max << endl;

}