#include<iostream>
using namespace std;
void setTransactions(int**&, int*&, int);
void releaseMemory(int** neighbors, int* degrees, int m);
void InsertionSort(int *arr, int size){
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (key < arr[j] && j >= 0) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}
int main()
{
    int n = 0, m = 0;
    float sup = 0.0;
    cin >> n >> m >> sup;
    int **trans = nullptr;
    int *iTemCnt = nullptr;
    setTransactions(trans, iTemCnt, m);
    int item = 0;
    cin >> item;
    int *buy = new int[item];
    for (int i = 0;i < item;i++)
    {
        cin >> buy[i];
    }
    int cnt[20001] = {};
    for(int i = 0; i < m; i++)
    {
        bool has[n+1];
        for(int j = 0; j <= n; j++)
        {
            has[j] = false;
        }
        for(int j = 0; j < iTemCnt[i]; j++)
        {
            has[trans[i][j]] = true;
        }
        bool flag = true;
        for(int j = 0; j < item; j++)
        {
            if(has[buy[j]] == false)
            {
                flag = false;
                break;
            }
        }
        if(!flag)
        {
            continue;
        }
        for(int j = 0; j < n; j++)
        {
            if(has[j])
            {
                cnt[j]++;
            }
        }
    }
    int rec = -1;
    float max_sup = -100000.0;
    for(int i = 0; i < n; i++)
    {
        bool flag = true;
        for(int j = 0; j < item; j++)
        {
            if(buy[j] == i)
            {
                flag = false;
                break;
            }
        }
        if(!flag)
        {
            continue;
        }
        if((float)cnt[i] / (float)m >= sup)
        {
            if((float)cnt[i] / (float)m > max_sup)
            {
                rec = i;
                max_sup = (float)cnt[i] / (float)m;
            }
        }
    }
    if(rec != -1)
    {
        cout << rec << "," << cnt[rec] << "," << cnt[buy[0]];
    }
    releaseMemory(trans, iTemCnt, m);
    return 0;
}
void setTransactions(int**& trans, int*& itemCnt, int m)
{
    trans = new int*[m];
    itemCnt = new int[m];
     
    for(int i = 0; i < m; i++)
    {
        cin >> itemCnt[i];
        trans[i] = new int[itemCnt[i]];
         
        for(int j = 0; j < itemCnt[i]; j++)
            cin >> trans[i][j];
    }
}
 
void releaseMemory(int** neighbors, int* degrees, int m)
{
    for(int i = 0; i < m; i++)
        delete [] neighbors[i];
    delete [] neighbors;
    delete [] degrees;
}
