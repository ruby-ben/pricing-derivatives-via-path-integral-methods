## Path Integral Solver for Option Pricing

This repository implements a **C++ framework for pricing financial derivatives** using the **path integral method**, a numerical technique inspired by physics.
It works by simulating possible paths of the underlying asset under a chosen **stochastic differential equation (SDE)** and computing the **discounted expected payoff.**

---
### 1) Core Idea
The aim is to compute the price of financial derivatives (e.g., options) by modeling the stochastic evolution of the underlying asset.
The price is obtained as the **expected payoff at maturity**, discounted back to the present.

Mathematically:
- The asset price follows an SDE.
- The derivative price is the expected value of the payoff under the **risk-neutral measure**, discounted at the risk-free rate.

---

### 2 Mathematical Formulation
#### 2.1) Stochastic Differential Equation (SDE)
Under the **risk-neutral measure**, an asset price $S_t$ follows:

$$
dS_t = \mu(S_t, t) \, dt + \sigma(S_t, t) \, dW_t
$$

- $\mu(S_t, t)$ — **drift term** (expected rate of return under risk-neutral measure)
- $\sigma(S_t, t)$ — **volatility term** (can be constant or state-dependent)
- $W_t$ — standard Brownian motion


#### 2.2) Feynman–Kac Formula

For a payoff function $\text{Payoff}(S_T)$ at maturity $T$:

$$
V(S_0, 0) = e^{-rT} \, \mathbb{E} \big[ \text{Payoff}(S_T) \big]
$$

Using **path integrals**, this expectation becomes:

$$
V(S_0, 0) = e^{-rT} \int \mathcal{D}S(t) \, \text{Payoff}(S_T) \, P[S(t)]
$$

where $P[S(t)]$ is the path probability density derived from the SDE.

---



### 3) Why This Solver is Flexible

In this implementation:

- The **only part you need to change** for a new model is the **SDE definition**.
- Once the SDE is set, the solver:
  1. Generates many possible paths for $S_t$ over time.
  2. Computes the payoff at maturity for each path.
  3. Averages and discounts to get the option price.

---

### 4) Example: Black–Scholes Model

Under Black–Scholes assumptions:

$$
dS_t = r S_t \, dt + \sigma S_t \, dW_t
$$

Payoff for a European call option:

$$
\text{Payoff}(S_T) = \max(S_T - K, 0)
$$

---

### 5) Algorithm Outline

**Pseudocode:**
```cpp
for each path p in N_paths:
    S = S0
    for t in timesteps:
        S += mu(S, t) * dt + sigma(S, t) * sqrt(dt) * random_gaussian()
    payoff_sum += payoff(S)
option_price = exp(-r * T) * payoff_sum / N_paths
```

---

### 6) Extending the Solver

To switch models, only change:
- mu(S, t) — the drift term
- sigma(S, t) — the volatility term
- payoff(S) — the payoff at maturity

For example:
- Heston model → stochastic volatility
- Merton model → jump term added to the SDE
- Barrier option → payoff set to 0 if barrier breached

---

### 7) Code Structure
```
include/
  black_scholes.h         # Drift & volatility for Black–Scholes
  path_integral_solver.h  # Core solver interface

src/
  black_scholes.cpp       # Implementation of Black–Scholes dynamics
  path_integral_solver.cpp# Monte Carlo path integral solver
  main.cpp                # Example usage

```

---

### 8) Advantages
- Modular: swap in any SDE
- Supports exotic payoffs
- Numerical: works without closed-form solutions
- Physics-inspired: path integrals allow a direct connection between finance and quantum mechanics-style methods

---

### 9) References
- Black, F. & Scholes, M. (1973) The Pricing of Options and Corporate Liabilities. Journal of Political Economy.
- Feynman, R. (1948) Space-Time Approach to Non-Relativistic Quantum Mechanics.
- Wilmott, P., Howison, S., Dewynne, J. (1995) The Mathematics of Financial Derivatives
