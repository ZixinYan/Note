#include <stdio.h>
#include <stdbool.h>

#define MAX 100  // Assume a maximum number of vertices

// Define the Status type
typedef int Status;
#define OK 1
#define ERROR 0

// Define the Graph structure
typedef struct {
    int vexnum;  // Number of vertices
    int adjMatrix[MAX][MAX];  // Adjacency matrix
} Graph;

bool visited[MAX];  // Visit flag array
Status(*VisitFunc)(int v);  // Function pointer to a visit function


//Spanning tree
// The cost of a spanning tree is the sum of the costs of the edges in the tree.
//Every spanning tree with n vertices contains exactly n - 1 edges.
//If we add any edge to a free tree, we get a cycle.
//

//
// directed tree(有向树): 
// the tree with one node whose in-degree is zero. Other nodes’s in-degree is 1.
//

//Adjacency Matrix(邻接矩阵)
//有向图中看出度看行，看入度看列
//带权如果没有连接用无穷表示

//存储在普通数组占用N^2,比较浪费，所以存在邻接表(Adjacency List )中，空间需求为O(E+N),仅用于稀疏图,记录出度(记录入度的逆邻接表),无向图有关系就记录


//------------------------Graph Traversal-------------------------
//Depth-First Traversal  O(n^2)
void DFS(Graph G, int v) {
    visited[v] = true;  // Mark the current vertex as visited
    VisitFunc(v);  // Perform the visit operation

    // Recur for all adjacent vertices
    for (int w = 0; w < G.vexnum; ++w) {
        if (G.adjMatrix[v][w] != 0 && !visited[w]) {
            DFS(G, w);
        }
    }
}
void DFSTraverse(Graph G, Status(*Visit)(int v)) {
    // Assign the function pointer to the provided function
    VisitFunc = Visit;

    // Initialize the visited array to false
    for (int v = 0; v < G.vexnum; ++v) {
        visited[v] = false;
    }

    // Perform DFS on each vertex that has not been visited
    for (int v = 0; v < G.vexnum; ++v) {
        if (!visited[v]) {
            DFS(G, v);  // Call DFS on unvisited vertex
        }
    }
}
// Example visit function
Status Visit(int v) {
    printf("Visited vertex: %d\n", v);
    return OK;
}

//Breadth-First Traversal
//O(n^2)
typedef struct {
    int data[MAX];
    int front;
    int rear;
} Queue;
void InitQueue(Queue* Q) {
    Q->front = 0;
    Q->rear = 0;
}
bool IsQueueEmpty(Queue* Q) {
    return Q->front == Q->rear;
}
bool EnQueue(Queue* Q, int e) {
    if ((Q->rear + 1) % MAX == Q->front) {
        return false;  // 队列满
    }
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAX;
    return true;
}
bool DeQueue(Queue* Q, int* e) {
    if (IsQueueEmpty(Q)) {
        return false;  // 队列空
    }
    *e = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAX;
    return true;
}

void BFSTraverse(Graph G, Status(*Visit)(int v)) {
    // 初始化访问标志数组为false
    for (int v = 0; v < G.vexnum; ++v) {
        visited[v] = false;
    }

    Queue Q;
    InitQueue(&Q);

    // 对每个未访问的顶点执行BFS
    for (int v = 0; v < G.vexnum; ++v) {
        if (!visited[v]) {
            visited[v] = true;
            VisitFunc(v);
            EnQueue(&Q, v);

            while (!IsQueueEmpty(&Q)) {
                //拿出下一次进行遍历的结点
                int u;
                DeQueue(&Q, &u);
                for (int w = 0; w < G.vexnum; ++w) {
                    if (G.adjMatrix[u][w] != 0 && !visited[w]) {
                        visited[w] = true;
                        VisitFunc(w);
                        EnQueue(&Q, w);
                    }
                }
            }
        }
    }
}

//---------------------------------Topological Sort------------------------------------
void TopologicalSort(Graph G) {
    int inDegree[MAX] = { 0 };  // 入度数组
    int topologicalOrder[MAX];  // 存储拓扑排序结果
    int index = 0;
    // 计算每个顶点的入度
    for (int i = 0; i < G.vexnum; ++i) {
        for (int j = 0; j < G.vexnum; ++j) {
            if (G.adjMatrix[i][j] != 0) {
                inDegree[j]++;
            }
        }
    }
    Queue Q;
    InitQueue(&Q);
    // 将所有入度为0的顶点入队
    for (int i = 0; i < G.vexnum; ++i) {
        if (inDegree[i] == 0) {
            EnQueue(&Q, i);
        }
    }
    // 执行拓扑排序
    while (!IsQueueEmpty(&Q)) {
        int u;
        DeQueue(&Q, &u);
        topologicalOrder[index++] = u;

        for (int v = 0; v < G.vexnum; ++v) {
            if (G.adjMatrix[u][v] != 0) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    EnQueue(&Q, v);
                }
            }
        }
    }
    // 检查是否存在环
    if (index != G.vexnum) {
        printf("图中存在环，无法进行拓扑排序。\n");
        return;
    }
    // 打印拓扑排序结果
    printf("拓扑排序结果：\n");
    for (int i = 0; i < index; ++i) {
        printf("%d ", topologicalOrder[i]);
    }
    printf("\n");
}

//--------------------------------Shortest Paths Problem------------------------------------
//Strategy: Breadth-first search
#define INF 9999  // 用于表示无穷大的值
void Dijkstra(Graph G, int start, int dist[], int prev[]) {
    bool visited[MAX] = { false };  // 访问标志数组
    for (int i = 0; i < G.vexnum; ++i) {
        dist[i] = INF;
        prev[i] = -1;
    }
    dist[start] = 0;

    for (int i = 0; i < G.vexnum; ++i) {
        int u = -1;
        int minDist = INF;
        for (int j = 0; j < G.vexnum; ++j) {
            if (!visited[j] && dist[j] < minDist) {
                u = j;
                minDist = dist[j];
            }
        }

        if (u == -1) break;  // 剩余顶点不连通

        visited[u] = true;

        for (int v = 0; v < G.vexnum; ++v) {
            if (!visited[v] && G.adjMatrix[u][v] != 0 && dist[u] + G.adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + G.adjMatrix[u][v];
                prev[v] = u;
            }
        }
    }
}


//---------------------------------Minimum Spanning Tree------------------------------------------
//In the minimum spanning tree
//n vertices and n - 1 edges
//it is acyclic
//It has the lowest total cost.

//!!!!Prim's Algorithm  and Kruskal's Algorithm. 
//! Prim's Algorithm
int MinKey(int key[], bool mstSet[], int vexnum) {
    int min = INF, minIndex;

    for (int v = 0; v < vexnum; v++) {
        if (mstSet[v] == false && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}
void PrimMST(Graph G) {
    int parent[MAX];  // 用于存储最小生成树
    int key[MAX];  // 用于存储最小权值
    bool mstSet[MAX];  // 用于表示顶点是否包含在最小生成树中

    // 初始化所有键值为无穷大，mstSet[] 为 false
    for (int i = 0; i < G.vexnum; i++) {
        key[i] = INF;
        mstSet[i] = false;
    }
    // 选择第一个顶点作为起始点
    key[0] = 0;  // 使第一个顶点作为根节点
    parent[0] = -1;  // 第一个节点没有父节点
    for (int count = 0; count < G.vexnum - 1; count++) {
        // 从未包含在最小生成树中的顶点中选取权值最小的顶点
        int u = MinKey(key, mstSet, G.vexnum);
        // 将选取的顶点添加到最小生成树集合中
        mstSet[u] = true;
        // 更新与选取顶点相邻的顶点的键值和父节点
        for (int v = 0; v < G.vexnum; v++) {
            // 更新顶点v的键值只在它不在最小生成树中，存在从u到v的边，且权值小于v当前的键值
            if (G.adjMatrix[u][v] && mstSet[v] == false && G.adjMatrix[u][v] < key[v]) {
                parent[v] = u;
                key[v] = G.adjMatrix[u][v];
            }
        }
    }
    // 打印最小生成树
    printf("边 \t权值\n");
    for (int i = 1; i < G.vexnum; i++) {
        printf("%d - %d \t%d \n", parent[i], i, G.adjMatrix[i][parent[i]]);
    }
}

//Kruskal's Algorithm. 
typedef struct {
    int u, v, weight;
} Edge;

int Find(int parent[], int i) {
    if (parent[i] == i)
        return i;
    return Find(parent, parent[i]);
}
// 并查集的合并操作
void Union(int parent[], int rank[], int x, int y) {
    int xroot = Find(parent, x);
    int yroot = Find(parent, y);

    if (rank[xroot] < rank[yroot]) {
        parent[xroot] = yroot;
    }
    else if (rank[xroot] > rank[yroot]) {
        parent[yroot] = xroot;
    }
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}
// 按边的权值排序
int compare(const void* a, const void* b) {
    Edge* a1 = (Edge*)a;
    Edge* b1 = (Edge*)b;
    return a1->weight > b1->weight;
}
