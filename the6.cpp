#include "the6.h"

// do not add extra libraries here


#define DEBUG 
#define DEBUG_STDERR(x) do { std::cerr << (x) << endl; } while(0)
#define DEBUG_ARRAY(a, n) do { for (int i = 0; i < n; i++) std::cerr << a[i] << " "; std::cerr << endl; } while(0)

// for example usage of DEBUG macros check test.cpp


void addCycle(stack<int> Stack, int x, vector<vector<int>>& scc){
  stack<int> stack2; 
  vector<int> cycle; 
  stack2.push(Stack.top());
  Stack.pop();
  do{
    stack2.push(Stack.top());
    Stack.pop();
  }
  while(stack2.top() != x);
  do{
    cycle.push_back(stack2.top());
    Stack.push(stack2.top());
    stack2.pop();
  }
  while(!stack2.empty());
  scc.push_back(cycle);
}

void dfsSearch(int **& graph, stack<int> Stack, int* visited, int n, vector<vector<int>>& scc, vector<int>& topSort){
  int i; 

  for(i = 0 ; i < n ; i++){
    if(graph[Stack.top()][i] == 1){
      if(visited[i] == 1){
        addCycle(Stack, i, scc);
      }else if (visited[i] == 0){
        Stack.push(i);
        visited[i] = 1; 
        dfsSearch(graph, Stack, visited, n, scc, topSort);
      }
    }
  }
  visited[Stack.top()] = 2;
  Stack.pop();
}

void topologicalSort(int**& graph,int v, int*visited, stack<int>& Stack,int n){
  visited[v] = 1 ; 

  for(int i = 0; i < n; i++){
    if(graph[v][i] ==  1){
      if(!visited[i]){
        topologicalSort(graph, i, visited, Stack, n);
      }
    }
  }

  Stack.push(v);

}

void SCC_TopSort (int**& graph, int n, vector<vector<int>>& scc, vector<int>& topSort){
    int i;
    int *visited = new int[n+1];
    for(i = 0 ; i < n; i++){
      visited[i] = 0;
    }

    stack<int> Stack; 

    for (i = 0; i < n ; i++){
      if(visited[i]==0){
       
        Stack.push(i);
        visited[i] = 1;
        dfsSearch(graph, Stack, visited, n, scc, topSort);
      }
    }

    if(scc.size() > 0){
      int *cycled = new int[n+1];
      for(i = 0 ; i < n; i++){
        cycled[i] = 0;
      }

      for(i = 0; i < scc.size(); i++){
        for(int j=0; j< scc[i].size();  j++){
          cycled[scc[i][j]] = 1;
        }
      }
      for(i = 0 ; i < n; i++){
        if(cycled[i] == 0){
          vector<int> temp; 
          temp.push_back(i);
          scc.push_back(temp);
        }
      }
    }
    else{
      for(i = 0 ; i < n; i++){
        visited[i] = 0;  
      }

      stack<int> Stack2;

      for(i = 0; i < n; i++){
        if(visited[i] == 0 ){
          topologicalSort(graph, i, visited, Stack2, n );
        }
      }

      while(!Stack2.empty()){
        topSort.push_back(Stack2.top());
        Stack2.pop();
      }
      
    }
}
