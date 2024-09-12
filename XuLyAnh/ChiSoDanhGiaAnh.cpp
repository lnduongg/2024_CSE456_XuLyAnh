#include <bits/stdc++.h>
using namespace std;

const int MAX = 100;

float avgLightIntensity(float a[MAX][MAX], int n)
{   
    float sum = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            sum += a[i][j];
    return sum/(n*n);
}

float contrastValue(float a[MAX][MAX], int n)
{
    float sum = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            sum += a[i][j]*a[i][j];
    return sum/(n*n) - avgLightIntensity(a, n)*avgLightIntensity(a, n);
}

float entropyValue(float a[MAX][MAX], int n)
{
//count how many time a pixel value has appeared
    map<float, float> countLibrary;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            countLibrary[a[i][j]]++;
//calculate entropy
    float E = 0;
    for (auto pair : countLibrary)
        E += pair.second/(n*n) * log2(pair.second/(n*n));
    return -E;
}

void copyMatrix(float a[MAX][MAX], float b[MAX][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            b[i][j] = a[i][j];
        }
    }
}

float sharpnessValue(float a[MAX][MAX], int n)
{   
//create Gx matrix
    float gx[MAX][MAX];
    copyMatrix(a, gx, n);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            gx[i][j] = gx[i][j + 1] - gx[i][j];
    for(int i = 0; i < n; i++) gx[i][n - 1] = 0;

//create Gy matrix
    float gy[MAX][MAX];
    copyMatrix(a, gy, n);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            gy[i][j] = gy[i + 1][j] - gy[i][j];
    for(int j = 0; j < n; j++) gy[n - 1][j] = 0;

//calculate sharpness value
    float G = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
                G += sqrt(gx[i][j]*gx[i][j] + gy[i][j]*gy[i][j]);
    return G / (n * n);
}

int main()
{   
    // float a[MAX][MAX] = 
    // {
    //      {1, 0.4, 0.2}, 
    //      {0.2, 0.6, 0.8}, 
    //      {0.6, 0, 0.6},
    // };
    // int n = 3;
    float a[MAX][MAX] =
    {
        {1, 4, 1, 7, 6}, 
        {6, 5, 5, 4, 7}, 
        {4, 7, 6, 7, 6}, 
        {5, 4, 5, 1, 3}, 
        {2, 1, 3, 2, 2}
    };
    int n = 5;
    cout<<"Cuong do anh sang trung binh = "<<avgLightIntensity(a, n)<<endl;
    cout<<"Do tuong phan = "<<contrastValue(a, n)<<endl;
    cout<<"Luong thong tin = "<<entropyValue(a, n)<<endl;
    cout<<"Do sac net = "<<sharpnessValue(a, n);
}