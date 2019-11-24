#include <iostream>
using namespace std;

int calculateMaxFinProduct
   (int nWorkStation, int* machines, int* productivities, int* productionRates);
void determineProduction
    (int nWorkStation, int curDay, int FinProductAmount,
     int** productions, int* productionRates, int** inventories);
void determinePurAmount
    (int curDay, int* purAmounts, int WSOneProduction, int WSOneRate, int** inventories);
void determineOpenMachine
    (int nWorkStation, int curDay, int** inventories,
     int** productions, int* productivities, int** openMachines);
void calculateInventory
    (int nWorkStation, int curDay, int curDemand, int curPurAmount,
     int** inventories, int** productions, int* productionRates);

int main()
{
  // input data: lines 1 to 2
  int nWorkStation = 0, nDay = 0;
  cin >> nWorkStation >> nDay;
  
  // input data: lines 3 to 8
  // the length of each array is nWorkStation + 1, for work station 0, 1, 2, ..., n
  // work station 0 is only for the purpose of storing raw material
  int* machines = new int[nWorkStation + 1];
  int* openCosts = new int[nWorkStation + 1];
  int* produceCosts = new int[nWorkStation + 1];
  int* productivities = new int[nWorkStation + 1];
  int* productionRates = new int[nWorkStation + 1];
  int* inventoryCosts = new int[nWorkStation + 1];
  // inventories[i][j] is the inventory of work station i at j-th day
  int** inventories = new int*[nWorkStation + 1];
  for(int i = 0; i <= nWorkStation; i++)
    inventories[i] = new int[nDay + 1];
  
  for(int i = 1; i <= nWorkStation; i++)
    cin >> machines[i];
  for(int i = 1; i <= nWorkStation; i++)
    cin >> openCosts[i];
  for(int i = 1; i <= nWorkStation; i++)
    cin >> produceCosts[i];
  for(int i = 1; i <= nWorkStation; i++)
    cin >> productivities[i];
  for(int i = 1; i <= nWorkStation; i++)
    cin >> productionRates[i];
  for(int i = 0; i <= nWorkStation; i++)
    cin >> inventoryCosts[i];
  for(int i = 0; i <= nWorkStation; i++)
    cin >> inventories[i][0];
  
  // input data: lines 9 to 10
  // the length of each array is nDay, for day 0, 1, 2, ..., n
  int* demands = new int[nDay + 1];
  int* purPrices = new int[nDay + 1];
  
  for(int i = 1; i <= nDay; i++)
    cin >> demands[i];
  for(int i = 1; i <= nDay; i++) 
    cin >> purPrices[i];
   
  // there is no corresponding values for work station 0 or day 0
  machines[0] = 0;
  openCosts[0] = 0;
  produceCosts[0] = 0;
  productivities[0] = 0;
  productionRates[0] = 0;
  demands[0] = 0;
  purPrices[0] = 0;
  
  // data that will be filled in by the algorithm
  int* purAmounts = new int[nDay + 1];
  // openMachines[i][j] is amount of machines opened for work station i at j-th day
  int** openMachines = new int*[nWorkStation + 1];
  for(int i = 1; i <= nWorkStation; i++)
    openMachines[i] = new int[nDay + 1];
  // productions[i][j] is the production plan for work station i at j-th day
  int** productions = new int*[nWorkStation + 1];
  for(int i = 1; i <= nWorkStation; i++)
    productions[i] = new int[nDay + 1];
  
  // there is no corresponding values for work station 0 or day 0
  purAmounts[0] = 0;
  openMachines[0] = nullptr;
  productions[0] = nullptr;
  for(int i = 1; i <= nWorkStation; i++)
    openMachines[i][0] = 0;
  for(int i = 1; i <= nWorkStation; i++)
    productions[i][0] = 0;
  
  
  
  // a better algorithm ver.2 
  // the inventory for every work station at every day will be considered in this algorithm
  for(int i = 1; i <= nDay; i++)
  { // for every day, the following 5 steps will be conducted:
    // 1. determine the amount of finished product that will be produced
    // 2. call function determineProduction and put the results in "productions"
    // 3. call function determinePurAmount and put the results in "purAmounts"
    // 4. call function determineOpenMachine and put the results in "openMachines"
    // 5. calculate the inventory for every work station, and put the results in "inventories"
    //  - productions[i][j] is the is the production plan for work station i at j-th day
    //  - purAmounts[i] is the purchase amounts of raw material for the i-th day
    //  - openMachines[i][j] is the amount of machines opened for work station i at j-th day
    //  - inventories[i][j] is the inventory of work station i at j-th day
    int curFinishedProduct = demands[i] - inventories[nWorkStation][i - 1];
    if(curFinishedProduct < 0)
      curFinishedProduct = 0;
    
    determineProduction(nWorkStation, i, curFinishedProduct,
                        productions, productionRates, inventories);
    determinePurAmount(i, purAmounts, productions[1][i], productionRates[1], inventories);
    determineOpenMachine(nWorkStation, i, inventories,
                         productions, productivities, openMachines);
    calculateInventory(nWorkStation, i, demands[i], purAmounts[i],
                       inventories, productions, productionRates);
  }
  
  // output the production plan
  for(int i = 1; i <= nWorkStation; i++)
  {
    for(int j = 1; j <= nDay; j++)
    {
      cout << openMachines[i][j];
      if(j != nDay)
        cout << " ";
    }
    cout << "\n";
  }
  for(int i = 1; i <= nWorkStation; i++)
  {
    for(int j = 1; j <= nDay; j++)
    {
      cout << productions[i][j];
      if(j != nDay)
        cout << " ";
    }
    cout << "\n";
  }
  for(int i = 1; i <= nDay; i++)
  {
    cout << purAmounts[i];
    if(i != nDay)
      cout << " ";
  }
  
  // release memory
  delete [] machines;
  delete [] openCosts;
  delete [] produceCosts;
  delete [] productivities;
  delete [] productionRates;
  delete [] inventoryCosts;
  for(int i = 0; i <= nWorkStation; i++)
    delete [] inventories[i];
  delete [] inventories;
  delete [] demands;
  delete [] purPrices;
  delete [] purAmounts;
  for(int i = 0; i <= nWorkStation; i++)
    delete [] openMachines[i];
  delete [] openMachines;
  for(int i = 0; i <= nWorkStation; i++)
    delete [] productions[i];
  delete [] productions;
  
  return 0;
}

// ==================================================
int calculateMaxFinProduct
   (int nWorkStation, int* machines, int* productivities, int* productionRates)
{
  if(nWorkStation == 1)
    return machines[1] * productivities[1];
  int finishedProduct = machines[1] * productivities[1];
  for(int i = 2; i <= nWorkStation; i++)
  {
    finishedProduct /= productionRates[i];
    if(finishedProduct > machines[i] * productivities[i])
      finishedProduct = machines[i] * productivities[i];
  }
  return finishedProduct;
}

void determineProduction
    (int nWorkStation, int curDay, int FinProductAmount,
     int** productions, int* productionRates, int** inventories)
{
  for(int i = nWorkStation; i >= 1; i--)
  {
    if(i == nWorkStation)
      productions[i][curDay] = FinProductAmount;
    else
      productions[i][curDay] = productions[i + 1][curDay] * productionRates[i + 1]
                               - inventories[i][curDay - 1];
    // production may be negative after the above calculation
    if(productions[i][curDay] < 0)
      productions[i][curDay] = 0;
    // cout << i << "'s production: " << productions[i][curDay] << "...\n";
  }
}

void determinePurAmount
    (int curDay, int* purAmounts, int WSOneProduction, int WSOneRate, int** inventories)
{
  purAmounts[curDay] = WSOneProduction * WSOneRate - inventories[0][curDay - 1];
  // purchase amount may be negative after the above calculation
  if(purAmounts[curDay] < 0)
    purAmounts[curDay] = 0;
}

void determineOpenMachine
    (int nWorkStation, int curDay, int** inventories,
     int** productions, int* productivities, int** openMachines)
{
  for(int i = 1; i <= nWorkStation; i++)
  {
    openMachines[i][curDay] = productions[i][curDay] / productivities[i];
    if(productions[i][curDay] % productivities[i] != 0)
      openMachines[i][curDay]++;
  }
}

void calculateInventory
    (int nWorkStation, int curDay, int curDemand, int curPurAmount,
     int** inventories, int** productions, int* productionRates)
{
  for(int i = 0; i <= nWorkStation; i++)
  {
    // for work station 0
    if(i == 0)
      inventories[i][curDay] = inventories[i][curDay - 1] + curPurAmount
                               - productions[i + 1][curDay] * productionRates[i + 1];
    // for the last work station
    else if(i == nWorkStation)
      inventories[i][curDay] = inventories[i][curDay - 1] + productions[i][curDay] - curDemand;
    else
      inventories[i][curDay] = inventories[i][curDay - 1] + productions[i][curDay]
                               - productions[i + 1][curDay] * productionRates[i + 1];
  }
}



