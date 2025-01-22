import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import expon

alpha = 1 / 12
def generate_exponential_random(N, alpha):
    uniform_random = np.random.uniform(0, 1, N)  # Numere uniforme între 0 și 1
    return -np.log(1 - uniform_random) / alpha   # Transformarea pentru distribuția exponențială

N = 10000  # Număr de mostre
data = generate_exponential_random(N, alpha)

plt.hist(data, bins=12, density=True, range=(0, 60), alpha=0.7, label="Simulat")


x_vals = np.linspace(0, 60, 500)
plt.plot(x_vals, expon.pdf(x_vals, scale=1/alpha), 'r-', label="Densitate teoretică")
plt.xlabel("Timp (secunde)")
plt.ylabel("Densitate")
plt.legend()
plt.grid()
plt.title("Timpul de printare")
plt.show()

simulated_prob = np.mean(data >= 5)
theoretical_prob = 1 - expon.cdf(5, scale=1/alpha)


print(f"Probabilitatea simulată P(T >= 5): {simulated_prob:.4f}")
print(f"Probabilitatea teoretică P(T >= 5): {theoretical_prob:.4f}")
