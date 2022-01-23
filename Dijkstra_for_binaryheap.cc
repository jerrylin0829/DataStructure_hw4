// Program to find Dijkstra's shortest path using
// priority_queue in STL
#include<bits/stdc++.h>
using namespace std;
# define INF 0x3f3f3f3f
  
// iPair ==>  Integer Pair
typedef pair<int, int> iPair;
  
// This class represents a directed graph using
// adjacency list representation
class Graph
{
    int V;    // No. of vertices
  
    // In a weighted graph, we need to store vertex
    // and weight pair for every edge
    list< pair<int, int> > *adj;
  
public:
    Graph(int V);  // Constructor
  
    // function to add an edge to graph
    void addEdge(int u, int v, int w);
  
    // prints shortest path from s
    double shortestPath(int s);
};
  
// Allocates memory for adjacency list
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<iPair> [V];
}
  
void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}
  
// Prints shortest paths from src to all other vertices
double Graph::shortestPath(int src)
{
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;
    vector<int> dist(V, INF);
    pq.push(make_pair(0, src));
    dist[src] = 0;
  
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
  
        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = (*i).first;
            int weight = (*i).second;
  
            //  If there is shorted path to v through u.
            if (dist[v] > dist[u] + weight)
            {
                // Updating distance of v
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
  
    // Print shortest distances stored in dist[]
    //printf("Vertex   Distance from Source\n");
    double sum = 0.0;
    for (int i = 0; i < V; ++i){
        //printf("%d \t\t %d\n", i, dist[i]);
        sum += dist[i];
    }
    return sum;
}
  
int main()
{
  // create the graph given in above fugure
  int V = 5000;
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
