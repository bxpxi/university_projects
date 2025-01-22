import numpy as np
import matplotlib.pyplot as plt

x_vals = ["0", "A", "B", "AB"]
p_vals = [0.46, 0.40, 0.10, 0.04]

cumulative_probs = np.cumsum(p_vals)

def generate_discrete_random(N, x_vals, cumulative_probs):
    random_values = np.random.uniform(0, 1, N)
    result = []
    for u in random_values:
        for k, cp in enumerate(cumulative_probs):
            if u <= cp:
                result.append(x_vals[k])
                break
    return result

N = 10000
results = generate_discrete_random(N, x_vals, cumulative_probs)

freq_relative = [results.count(x) / N for x in x_vals]

plt.bar(x_vals, freq_relative, alpha=0.7, label="Simulat")
plt.bar(x_vals, p_vals, alpha=0.5, label="Teoretic")
plt.ylabel("Frecvență")
plt.legend()
plt.grid()
plt.title("Distribuția grupei sanguine")
plt.show()
