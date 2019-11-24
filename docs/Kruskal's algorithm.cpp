#include<iostream>
using namespace std;
bool cycle(int c[][500], int);
bool tlimit(int u[][500], int, int);
int min(int, int);
int main ()
{
	int n, m, t, aa[500][3], a[500][500], b[500][500] = {0}, output[12000] = {0};
	cin >> n >> m >> t;
	for (int i = 0;i <= n;i++)
    {
        for (int j = 0;j <= n;j++)
        {
            a[i][j] = 101;
        }

    }
	for (int i = 0;i < m;i++)
	{
		for (int j = 0;j < 3;j++)
		{
			cin >> aa[i][j]; 
		}
	}
	for (int i = 0;i < m;i++)
    {
    	int xx = aa[i][0];
    	int yy = aa[i][1];
    	a[xx][yy] = aa[i][2];
    	a[yy][xx] = aa[i][2];
	}
	int minn = 101, num = 0, dis = 0;
	int x = 501, y = 501;
	for(int l = 1;l <= n-1;l++)
	{
		for (int i = 1;i <= n;i++)
		{
			for (int j = i;j <= n;j++)
			{
				if (a[i][j] < minn)
				{
					minn = a[i][j];
					x = i;
					y = j;
				}
				if (a[i][j] == minn)
				{
					if (i + j < x + y)
					{
						minn = a[i][j];
						x = i;
						y = j;
					}
					else if (i + j == x + y)
					{
						int sm1, sm2;
						sm1 = min(i,j);
						sm2 = min(x,y);	
						int smallest = min(sm1, sm2);
						if (smallest == i)
						{
							minn = a[i][j];
							x = i;
							y = j;
						}
						if (smallest == j)
						{
							minn = a[i][j];
							x = i;
							y = j;
						}								
					}								
				}
			}	
		}
	b[x][y] = 1;
	b[y][x] = 1;
	if (cycle(b, n) == true || tlimit(b, n, t) == true)
	{
		b[x][y] = 0;
		b[y][x] = 0;
		l--;
		a[x][y] = 101;
		a[y][x] = 101;
	}
	else
	{ 
		dis += minn;
		output[num] = x;
		num++;
		output[num] = y;
		num++;
		a[x][y] = 101;
	}
	minn = 101;
	x = 501;
	y = 501;
	}
	cout << dis << endl;
	for (int i = 0;i < 2*(n-1);i++)
	{
		cout << output[i] << ",";
		i++;
		cout << output[i];
		if (i != 2*(n-1)-1)
		{
			cout << ";";	
		} 
	}
}
bool cycle(int c[][500], int n)
{
	int **g;
	g = new int *[n+1];
	for(int i = 0;i < n+1;i++)
	{
		g[i] = new int[n+1];
	}
	for (int i = 1;i <= n;i++)
    {
    	for (int j = 1;j <= n;j++)
    	{
    		g[i][j] = c[i][j];
		}
	}
    int d[501] = {0};
    for(int i = 1; i <= n; i++)
    {
    	for(int j = 1; j <= n; j++)
    	{
        	if(g[i][j] == 1)
        		d[i]++;
    	}
    }
    
    int d1 = 0;
    for(int i = 1; i <= n; i++)
    	if(d[i] == 1)
        d1++;
  
    while(d1 != 0)
    {
    	for(int i = 1; i <= n; i++)
    	{
        	for(int j = 1; j <= n; j++)
      		{
       			if(d[i] == 1 && g[i][j] == 1)
        		{
	          		g[i][j] = 0;
	          		g[j][i] = 0;
	          		d[i]--;
	          		d[j]--;
	        	}
      		}
    	}
    
    d1 = 0;
    for(int i = 1; i <= n; i++)
      	if(d[i] == 1)
        	d1++;
  	}

  	int d2 = 0;
  	for(int i = 1; i <= n; i++)
   		if(d[i] >= 2)
      	d2++;
  
  	if(d2 >= 3)
    	return true;
  	return false;
  	for(int i = 0;i < n+1;i++)
  	{
  		delete [] g[i];
	}
	delete [] g;
}
int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}
bool tlimit(int u[][500], int n, int t)
{
	int d[501] = {0};
    for(int i = 1; i <= n; i++)
    {
    	for(int j = 1; j <= n; j++)
    	{
        	if(u[i][j] == 1)
        	d[i]++;
    	}
    }
    for(int i = 1; i <= n; i++)
    {
    	if (d[i] > t)
    		return true;
    }
    return false;
}
