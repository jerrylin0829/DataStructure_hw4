// Program to find Dijkstra's shortest path using
// priority_queue in STL
#include<bits/stdc++.h>
using namespace std;
# define INF 0x3f3f3f3f

typedef pair<int, double> iPair;

class Graph
{
  int V; // No. of vertices
  list< pair<int, double> > *adj;
  public:
  Graph(int V); // Constructor
  void addEdge(int u, int v, double w);
  double shortestPath(int s);
};

// Allocates memory for adjacency list
Graph::Graph(int V)
{
  this->V = V;
  adj = new list<iPair> [V];
}

void Graph::addEdge(int u, int v, double w)
{
  adj[u].push_back(make_pair(v, w));
  adj[v].push_back(make_pair(u, w));
}

// Prints shortest paths from src to all other vertices
double Graph::shortestPath(int src)
{

  vector<double> dist(V, INF);
  vector<bool> visited(V, false);
  visited[src] = true;
  int u=src, u_val;
  dist[src] = 0;

  for(int j = 0; j < V; ++j) {

        list< pair<int, double> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
          // Get vertex label and weight of current adjacent
          // of u.
          int v = (*i).first;
          double weight = (*i).second;

          // If there is shorted path to v through u.
          if (dist[v] > dist[u] + weight)
          {
                // Updating distance of v
                dist[v] = dist[u] + weight;
          }
        }
        u_val = INF;
        for(int k = 0; k < V; ++k) {
          if(!visited[k] && dist[k] < u_val) {
                u_val = dist[k];
                u = k;
          }
        }
        visited[u] = true;
  }

  // Print shortest distances stored in dist[]

  //printf("Vertex Distance from Source\n");
  double sum = 0.0;
  for (int i = 0; i < V; ++i) {
        //printf("%d \t\t %lf\n", i, dist[i]);
        sum += dist[i];
  }
  return sum;
}

// Driver program to test methods of graph class
int main()
{
  // create the graph given in above fugure
  int V = 2000;
  Graph g(V);

  // making above shown graph
  int p1, p2;
  double dist;
  clock_t begin, end;
  double total_time = 0.0;
  while(cin >> p1 >> p2 >> dist){
        g.addEdge(p1, p2, dist);
  }
  double total_dist = 0.0;
  begin = clock();
  for(int i = 0; i < V; ++i) {
        //cout << g.shortestPath(i) << endl;
        total_dist += g.shortestPath(i);
  }
  end = clock();
  total_time += double(end - begin)/ CLOCKS_PER_SEC;
  cout << total_time << endl;

  total_dist /= 2.0;
  cout << total_dist/V/(V-1) << endl;

  return 0;
}
