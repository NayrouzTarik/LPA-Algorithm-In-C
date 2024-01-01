#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

typedef struct {
    int label;
    int *neighbors;
    int num_neighbors;
} Node;

Node nodes[MAX_NODES];

void initializeNodes(int num_nodes) 
{
    int i = 0;
    while (i < num_nodes) {
        nodes[i].label = i + 1;
        nodes[i].num_neighbors = 0;
        nodes[i].neighbors = NULL;
        i++;
    }
}

void addEdge(int node1, int node2) 
{
    int index1 = node1 - 1;
    int index2 = node2 - 1;

    nodes[index1].neighbors = realloc(nodes[index1].neighbors, (nodes[index1].num_neighbors + 1) * sizeof(int));
    nodes[index1].neighbors[nodes[index1].num_neighbors] = index2;
    nodes[index1].num_neighbors++;

    nodes[index2].neighbors = realloc(nodes[index2].neighbors, (nodes[index2].num_neighbors + 1) * sizeof(int));
    nodes[index2].neighbors[nodes[index2].num_neighbors] = index1;
    nodes[index2].num_neighbors++;
}

void propagateLabels(int num_nodes, int num_edges) 
{
    int iter = 1;
    while (iter <= 20) 
    {
        printf("Iteration %d:\n", iter);
        int i = 0;
        while (i < num_edges) 
        {
            int node1, node2;
            node1 = nodes[i].neighbors[0] + 1;
            node2 = nodes[i].neighbors[1] + 1;

            int index1 = node1 - 1;
            int index2 = node2 - 1;

            int minLabel;
            if (nodes[index1].label < nodes[index2].label)
                minLabel = nodes[index1].label;
            else
                minLabel = nodes[index2].label;
            nodes[index1].label = minLabel;
            nodes[index2].label = minLabel;

            printf("  Edge %d: Nodes %d, %d | Updated labels: %d, %d\n", i + 1, node1, node2, nodes[index1].label, nodes[index2].label);
            i++;
        }
        printf("\n");
        iter++;
    }
}

int main() 
{
    int num_nodes, num_edges;

    printf("Enter the number of nodes: ");
    scanf("%d", &num_nodes);
    if (num_nodes <= 0 || num_nodes > MAX_NODES) 
    {
        printf("Error: Invalid number of nodes\n");
        return EXIT_FAILURE;
    }
    initializeNodes(num_nodes);
    printf("Enter the number of edges: ");
    scanf("%d", &num_edges);
    if (num_edges <= 0) 
    {
        printf("Error: Invalid number of edges\n");
        return EXIT_FAILURE;
    }
    printf("Enter the edges (format: node1 node2):\n");
    int i = 0;
    while (i < num_edges) 
    {
        int node1, node2;
        scanf("%d %d", &node1, &node2);
        addEdge(node1, node2);
        i++;
    }
    printf("\nPropagating labels...\n\n");
    propagateLabels(num_nodes, num_edges);
    return EXIT_SUCCESS;
}
