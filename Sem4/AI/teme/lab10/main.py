import networkx as nx
import matplotlib.pyplot as plt
import community as community_louvain
import random
import time

def remove_duplicate_edges_from_gml(input_path, output_path):
    edges = set()
    unique_lines = []
    with open(input_path, 'r') as file:
        lines = file.readlines()

    inside_edge = False
    current_edge = []

    for line in lines:
        stripped = line.strip()
        if stripped == "edge":
            inside_edge = True
            current_edge = [line]
        elif inside_edge:
            current_edge.append(line)
            if stripped == "]":
                inside_edge = False
                source = target = None
                for edge_line in current_edge:
                    if "source" in edge_line:
                        source = int(edge_line.strip().split()[1])
                    elif "target" in edge_line:
                        target = int(edge_line.strip().split()[1])
                if source is not None and target is not None:
                    edge_tuple = tuple(sorted((source, target)))
                    if edge_tuple not in edges:
                        edges.add(edge_tuple)
                        unique_lines.extend(current_edge)
        else:
            unique_lines.append(line)

    with open(output_path, 'w') as file:
        file.writelines(unique_lines)

    print(f"Duplicate edges removed. Clean file saved at: {output_path}")


def load_graph(gml_path):
    cleaned_path = gml_path.replace(".gml", "_cleaned.gml")
    remove_duplicate_edges_from_gml(gml_path, cleaned_path)
    return nx.read_gml(cleaned_path, label='id')

def draw_communities(graph, partition, title="Communities"):
    pos = nx.spring_layout(graph)
    cmap = plt.get_cmap('viridis')
    max_comm = max(partition.values())
    colors = [cmap(partition[node] / max_comm) for node in graph.nodes()]
    nx.draw(graph, pos, node_color=colors, with_labels=True)
    plt.title(title)
    plt.show()

def detect_communities_louvain(graph):
    start_time = time.time()
    partition = community_louvain.best_partition(graph)
    duration = time.time() - start_time

    num_communities = len(set(partition.values()))
    print(f"[Louvain] Detected {num_communities} communities in {duration:.4f} seconds.")
    return partition


def fitness_modularity(graph, genes):
    community_dict = {}
    for node, community in genes.items():
        community_dict.setdefault(community, []).append(node)
    return nx.algorithms.community.quality.modularity(graph, community_dict.values())

def fitness_density(graph, genes):
    community_dict = {}
    for node, community in genes.items():
        community_dict.setdefault(community, []).append(node)
    densities = []
    for comm_nodes in community_dict.values():
        subgraph = graph.subgraph(comm_nodes)
        n = len(comm_nodes)
        if n <= 1:
            densities.append(0)
            continue
        m = subgraph.number_of_edges()
        max_edges = n * (n - 1) / 2
        densities.append(m / max_edges)
    return sum(densities) / len(densities)

def fitness_conductance(graph, genes):
    community_dict = {}
    for node, community in genes.items():
        community_dict.setdefault(community, []).append(node)

    conductances = []
    for comm_nodes in community_dict.values():
        comm_set = set(comm_nodes)
        cut_edges = 0
        volume = 0
        for node in comm_nodes:
            neighbors = set(graph.neighbors(node))
            degree = len(neighbors)
            volume += degree
            cut_edges += len(neighbors - comm_set)
        if volume == 0:
            conductances.append(1)
        else:
            conductances.append(cut_edges / volume)

    avg_conductance = sum(conductances) / len(conductances)
    return 1 - avg_conductance

class Individual:
    def __init__(self, nodes):
        self.genes = {node: random.randint(0, len(nodes) - 1) for node in nodes}
        self.fitness = 0

    def calculate_fitness(self, graph, fitness_func):
        self.fitness = fitness_func(graph, self.genes)
        return self.fitness

def selection(population):
    return sorted(population, key=lambda x: x.fitness, reverse=True)[:2]

def crossover(parent1, parent2):
    child = Individual(parent1.genes.keys())
    for node in child.genes:
        child.genes[node] = parent1.genes[node] if random.random() < 0.5 else parent2.genes[node]
    return child

def mutation(individual, num_communities):
    for node in individual.genes:
        if random.random() < 0.1:
            individual.genes[node] = random.randint(0, num_communities - 1)

def genetic_algorithm(graph, generations=100, population_size=20, fitness_func=fitness_modularity):
    nodes = list(graph.nodes())
    population = [Individual(nodes) for _ in range(population_size)]
    for ind in population:
        ind.calculate_fitness(graph, fitness_func)

    for generation in range(generations):
        new_population = []
        parents = selection(population)
        for _ in range(population_size):
            child = crossover(parents[0], parents[1])
            mutation(child, len(nodes))
            child.calculate_fitness(graph, fitness_func)
            new_population.append(child)
        population = new_population
        best_fit = max(ind.fitness for ind in population)
        print(f"Gen {generation + 1} - Best fitness: {best_fit:.4f}")

    best = max(population, key=lambda x: x.fitness)
    return best.genes, best.fitness

def main():
    print("=== COMMUNITY DETECTION ===")
    path = input("Path to .gml file: ").strip()
    graph = load_graph(path)

    method = input("Choose method (louvain / ga): ").strip().lower()

    if method == "louvain":
        partition = detect_communities_louvain(graph)
        draw_communities(graph, partition, "Louvain Communities")
    elif method == "ga":
        generations = int(input("Generations: "))
        pop_size = int(input("Population size: "))

        print("Choose fitness function:")
        print("1 - Modularity (default)")
        print("2 - Density")
        print("3 - Conductance")
        fit_choice = input("Your choice: ").strip()

        if fit_choice == "2":
            fitness_func = fitness_density
        elif fit_choice == "3":
            fitness_func = fitness_conductance
        else:
            fitness_func = fitness_modularity

        partition, best_fit = genetic_algorithm(graph, generations, pop_size, fitness_func)
        print(f"[GA] Best fitness: {best_fit:.4f}")
        draw_communities(graph, partition, "GA Communities")
    else:
        print("Invalid method.")


if __name__ == "__main__":
    main()
