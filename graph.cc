#include <bits/stdc++.h>
#define debug1 cout << "ok" << endl;
#define debug2 cout << "www" << endl;
using namespace std;

struct point{
  int x, y;
  vector<int> neighbors;
};

int getRandomNum(int low, int high) {
  int k;
  double d;
  d = (double) rand()/((double)RAND_MAX+1);
  k = (int)(d*(high-low+1));
  return low+k;
}

int get_root(vector<int> arr, int i, int &height) {
  ++height;
  if(arr[i] == i)
        return i;
  return get_root(arr, arr[i], height);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    srand(time(NULL));
    int n;
    cin >> n;
    int length = 10 * sqrt(n); // the graph would be ~= 1% full

    set_more_than_one: 
    ofstream u_out("Urban.txt"), r_out("Rural.txt");
    vector<point> graph;
    int urban = (n+5) / 5;     // I hope urban have more probabilty can carry, and 20% of cities are urban. 
    int rural = n - urban;     // 80% of cities are rural.
    for(int i = 0 ; i < urban; ++i) {
        int pos_x = getRandomNum(10, length - 10);
        int pos_y = getRandomNum(10, length - 10);
        point center = {pos_x, pos_y, vector<int>()};
        graph.push_back(center);
        u_out << pos_x << ' ' << pos_y << endl;
        for(int j = 0; j < min(9, rural); ++j) {    // One city connects nine rural.
          static const int offset = 16;     
          int new_x = pos_x + getRandomNum(0, 32) - offset;
          int new_y = pos_y + getRandomNum(0, 32) - offset;
          if(new_x < 0) 
            new_x = 0;
          if(new_x > length) 
            new_x = length;
          if(new_y < 0) 
            new_y = 0;
          if(new_y > length) 
            new_y = length;
          point near = {new_x, new_y, vector<int>()};
          graph.push_back(near);
          r_out << new_x << ' ' << new_y << endl;
        }
        rural -= 9;
    }
    
    //Decide neighbor
    ofstream n_out("Neighbor.txt");
    for(int i = 0; i < graph.size(); ++i) {
        for(int j = i + 1; j < graph.size(); ++j) {
          // probability to be neighbor depend on the distance
          int dx = graph[i].x - graph[j].x;
          int dy = graph[i].y - graph[j].y;
          double dis = sqrt(dx*dx + dy*dy);
          // distance between two cities or rural below 10 must be neighbor
          if(double(rand())/ RAND_MAX < 0.8 / dis) {
                graph[i].neighbors.push_back(j);
                graph[j].neighbors.push_back(i);
                n_out << graph[i].x << ' ' << graph[i].y << ' '
                  << graph[j].x << ' ' << graph[j].y << endl;
          }
        }
    }
    
    // Union
    vector<int> disjoint_set(graph.size());
    for(int i = 0 ; i < graph.size(); ++i) {
        disjoint_set[i] = i;
    }
    for(int i = 0 ; i < graph.size(); ++i) {
        for(int j = 0; j < graph[i].neighbors.size(); ++j) {
            int iheight = 0, jheight = 0;
            int ihead = get_root(disjoint_set, i, iheight);
            int jhead = get_root(disjoint_set, graph[i].neighbors[j], jheight);
            if(iheight > jheight)
                swap(ihead, jhead);
            disjoint_set[ihead] = jhead;
        }
    }

    // find
    int count = 0;
    for(int i = 0; i < disjoint_set.size(); ++i) {
        if(disjoint_set[i] == i)
            ++count;
    }
    if(count > 1) {
        goto set_more_than_one;
    }
    ofstream g_out("Graph.txt");
    for(int i = 0; i < graph.size(); ++i) {
      for(int j = 0; j < graph[i].neighbors.size(); ++j) {
        int nbr = graph[i].neighbors[j];
        if(i < nbr) {
              int dx = graph[i].x - graph[nbr].x;
              int dy = graph[i].y - graph[nbr].y;
              double distance = dx*dx + dy*dy;
              g_out << i << ' ' << nbr << ' ' << sqrt(distance) << endl;
        }
      }
    }   
}
