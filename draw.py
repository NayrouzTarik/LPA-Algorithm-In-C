import tkinter as tk
import networkx as nx
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import matplotlib.pyplot as plt

MAX_NODES = 100

class GraphVisualization:
    def __init__(self, master, num_nodes, edges):
        self.master = master
        self.master.title("LPA Algorithm Visualization")
        self.num_nodes = num_nodes
        self.edges = edges

        self.graph = nx.Graph()
        self.initialize_nodes()
        self.add_edges()

        self.figure, self.ax = plt.subplots()
        self.canvas = FigureCanvasTkAgg(self.figure, master=self.master)
        self.canvas_widget = self.canvas.get_tk_widget()
        self.canvas_widget.pack(side=tk.TOP, fill=tk.BOTH, expand=1)

        self.draw_graph()

    def initialize_nodes(self):
        for i in range(self.num_nodes):
            self.graph.add_node(i + 1, label=i + 1)

    def add_edges(self):
        for edge in self.edges:
            self.graph.add_edge(edge[0], edge[1])

    def draw_graph(self):
        pos = nx.spring_layout(self.graph)
        labels = nx.get_edge_attributes(self.graph, 'label')

        nx.draw_networkx_nodes(self.graph, pos, node_size=700, node_color='skyblue')
        nx.draw_networkx_labels(self.graph, pos)
        nx.draw_networkx_edges(self.graph, pos, edgelist=self.edges, edge_color='black')

        nx.draw_networkx_edge_labels(self.graph, pos, edge_labels=labels)

        self.canvas.draw()


def main():
    num_nodes = int(input("Enter the number of nodes: "))
    if num_nodes <= 0 or num_nodes > MAX_NODES:
        print("Error: Invalid number of nodes")
        return

    edges = []
    num_edges = int(input("Enter the number of edges: "))
    if num_edges <= 0:
        print("Error: Invalid number of edges")
        return

    print("Enter the edges (format: node1 node2):")
    for _ in range(num_edges):
        node1, node2 = map(int, input().split())
        edges.append((node1, node2))

    root = tk.Tk()
    app = GraphVisualization(root, num_nodes, edges)
    root.mainloop()


if __name__ == "__main__":
    main()
