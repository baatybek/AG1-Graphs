#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <queue>
using namespace std;

class Graph {
    int N, K;
    vector < set < int > > graph;
    vector < bool > visited;
    void addNeigbourVertices ( const string & current_queue, int first_index ) {
        for ( int i = 0; i < N; ++i ) {
            visited.push_back(0);
            if( current_queue[ i ] == '.' && i + 1 < N && current_queue[ i + 1] == '.' ) {
                if( graph[i + first_index].empty() ) {
                    set < int > newset = { i + first_index + 1};
                    graph[i + first_index] = newset;
                } else {
                    graph[i + first_index].insert( i + first_index + 1);
                }

                if( graph[i + first_index + 1].empty() ) {
                    set < int > newset = { i + first_index };
                    graph[i + first_index + 1] = newset;
                } else {
                    graph[i + first_index + 1].insert( i + first_index );
                }
            }

            if( i + 1 == N && current_queue[i + first_index] == '.') {
                if( graph[i + first_index].empty() ) {
                    set < int > newset = { 2 * N };
                    graph[i + first_index] = newset;
                } else {
                    graph[i + first_index].insert( 2 * N );
                }
            }
        }
    }

    void addAdjacentVertices ( const string & left_queue, const string & righ_queue ) {
        for (int i = 0; i < N; ++i) {
            if (left_queue[i] == '.' && i + K < N && righ_queue[i + K] == '.') {
                if (graph[i].empty()) {
                    set<int> newset = {i + N + K};
                    graph[i] = newset;
                } else {
                    graph[i].insert(i + N + K);
                }

                if (graph[i + N + K].empty()) {
                    set<int> newset = {i};
                    graph[i + N + K] = newset;
                } else {
                    graph[i + N + K].insert(i);
                }
            }

            if (righ_queue[i] == '.' && i + K < N && left_queue[i + K] == '.') {
                if (graph[i + N].empty()) {
                    set<int> newset = {i + K};
                    graph[i + N] = newset;
                } else {
                    graph[i + N].insert(i + K);
                }

                if (graph[i + K].empty()) {
                    set<int> newset = {i + N};
                    graph[i + K] = newset;
                } else {
                    graph[i + K].insert(i + N);
                }
            }

            if (left_queue[i] == '.' && i + K >= N) {
                if (graph[i].empty()) {
                    set<int> newset = {2 * N};
                    graph[i] = newset;
                } else {
                    graph[i].insert(2 * N);

                }
            }

            if (righ_queue[i] == '.' && i + K >= N) {
                if (graph[i + N].empty()) {
                    set<int> newset = {2 * N};
                    graph[i + N] = newset;
                } else {
                    graph[i + N].insert(2 * N);
                }
            }
        }
    }
public:
    Graph ( int n, int k ) : N ( n ), K ( k ) {
        graph.reserve( (2 * n) + 1 );
    }

    void printGraph () const {
        for(int i = 0; i <= 2 * N; ++i ) {
            cout << i << ": ";
            if( ! graph[i].empty() ) {
                for( auto j : graph[i] )
                    cout << j << " ";
            }
            cout << endl;
        }
    }

    void createGraph( const string & left_queue, const string & right_queue ) {
        // goes through a string of size N: and makes neighbour i <-> i + 1
        addNeigbourVertices( left_queue,  0 );
        // goes through a string of size N: and makes neighbour i <-> i + 1
        addNeigbourVertices( right_queue, N );
        // checks i + K
        addAdjacentVertices( left_queue, right_queue );
    }

    int minDistance () {
        // first is Index of a Node, second is Distance and second - 1 is Cleaning lady
        queue< pair < int, int > > path_queue;
        path_queue.push( make_pair( 0, 0 ));
        visited[0] = true;
        while ( !path_queue.empty() ) {
            pair < int , int > current_nod = path_queue.front();
            path_queue.pop(); 

            if( ! graph[current_nod.first].empty() ) {
                for( auto neigbour : graph[current_nod.first] ) {
                    if( ! visited[ neigbour ] && neigbour % N  >= current_nod.second + 1 ) {
                        path_queue.push( make_pair ( neigbour, current_nod.second + 1) );
                        visited[ neigbour ] = true;
                    }
                    if( neigbour == 2 * N )
                        return current_nod.second + 1;
                }
            }
        }

        return -1;
    }

};
int main() {
    int N, K;
    string p1, p2;
    cin >> N >> K >> p1 >> p2;
    Graph g( N, K);
    g.createGraph(p1, p2);
    //g.printGraph();
    cout <<  g.minDistance() << endl;
    return 0;
}
