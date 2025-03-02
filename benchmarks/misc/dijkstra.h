#define DIJKSTRA_INF 65000
#define DIJKSTRA_MAX_NODES 10

int min_distance(volatile int dist[], bool visited[], int n) {
    int min = DIJKSTRA_INF;
    int min_index = -1;

    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

// Dijkstra's Algorithm
void dijkstra(int graph[DIJKSTRA_MAX_NODES][DIJKSTRA_MAX_NODES], volatile int dist[DIJKSTRA_MAX_NODES], int n, int start) {
    bool visited[DIJKSTRA_MAX_NODES];

    for (int i = 0; i < n; i++) {
        dist[i] = DIJKSTRA_INF;
        visited[i] = false;
    }
    dist[start] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = min_distance(dist, visited, n);
        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] != 0 && dist[u] != DIJKSTRA_INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}

