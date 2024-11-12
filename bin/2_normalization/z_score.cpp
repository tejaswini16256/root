#include<bits/stdc++.h>
#include<fstream>
using namespace std;
double normalize(double value, double mean, double sd)
{
    
    return (value-mean)/sd;
}

int main()
{
    ifstream in("input.csv");
    ofstream out("zscore_output.csv");
    
    double new_min = 0;
    double new_max = 1;

    vector<double>data;
    double value;
    while(in>>value)
    data.push_back(value);

    double mean=0,n=data.size(),sd;
    for(auto it:data)
    {
        mean+=it;
    }
    mean=(mean/n);
    for(auto it:data)
    {
        sd+=((it-mean)*(it-mean));
    }
    sd=(sd/n);
    sd=sqrt(sd);


    for(double value:data)
    {
        double normalized_value=normalize(value,mean,sd);
        out<<normalized_value<<"\n";
    }
    in.close();
    out.close();

}