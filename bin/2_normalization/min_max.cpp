#include<bits/stdc++.h>
#include<fstream>
using namespace std;
double normalize(double value,double min,double max,double new_min,double new_max)
{
    return ((value-min)/(max-min))*(new_max-new_min)+new_min;
}

int main()
{
    ifstream in("input.csv");
    ofstream out("minmax_output.csv");
    
    double new_min = 0;
    double new_max = 1;

    vector<double>data;
    double value;
    while(in>>value)
    data.push_back(value);

    double min=*min_element(data.begin(),data.end());
    double max=*max_element(data.begin(),data.end());

    for(double value:data)
    {
        double normalized_value=normalize(value,min,max,new_min,new_max);
        out<<normalized_value<<"\n";
    }
    in.close();
    out.close();

}