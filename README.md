## Path Integral Solver for Option Pricing

This project implements a **C++ solver for derivative pricing** using the **path integral formulation** of stochastic processes.  
The key idea is to simulate all possible paths of the underlying asset under the chosen **stochastic differential equation (SDE)** and compute the **discounted expected payoff**.

---

### 1) Core Equation

Under the **risk-neutral measure**, an asset price $ S_t $ follows:

$$
dS_t = \mu(S_t, t) \, dt + \sigma(S_t, t) \, dW_t
$$

- $ \mu(S_t, t) $ — **drift term** (expected rate of return under risk-neutral measure)
- $ \sigma(S_t, t) $ — **volatility term** (can be constant or state-dependent)
- $ W_t $ — standard Brownian motion

---

### 2) Feynman–Kac Formula

For a payoff function $ \text{Payoff}(S_T) $ at maturity $ T $:

$$
V(S_0, 0) = e^{-rT} \, \mathbb{E} \big[ \text{Payoff}(S_T) \big]
$$

Using **path integrals**, this expectation becomes:

$$
V(S_0, 0) = e^{-rT} \int \mathcal{D}S(t) \, \text{Payoff}(S_T) \, P[S(t)]
$$

where $ P[S(t)] $ is the path probability density derived from the SDE.

---

### 3) Why This Solver is Flexible

In this implementation:

- The **only part you need to change** for a new model is the **SDE definition**.
- Once the SDE is set, the solver:
  1. Generates many possible paths for $ S_t $ over time.
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

## 5️⃣ Algorithm Outline

**Pseudocode:**
```cpp
for each path p in N_paths:
    S = S0
    for t in timesteps:
        S += mu(S, t) * dt + sigma(S, t) * sqrt(dt) * random_gaussian()
    payoff_sum += payoff(S)
option_price = exp(-r * T) * payoff_sum / N_paths
```

6️⃣ How to Adapt for Different Models

To switch models, only change:
- mu(S, t) — the drift term
- sigma(S, t) — the volatility term
- payoff(S) — the payoff at maturity

For example:
- Heston model → stochastic volatility
- Merton model → jump term added to the SDE
- Barrier option → payoff set to 0 if barrier breached


7️⃣ Advantages
- Modular: swap in any SDE
- Supports exotic payoffs
- Numerical: works without closed-form solutions
- Physics-inspired: path integrals allow a direct connection between finance and quantum mechanics-style methods


8️⃣ References
- Black, F. & Scholes, M. (1973) The Pricing of Options and Corporate Liabilities. Journal of Political Economy.
- Feynman, R. (1948) Space-Time Approach to Non-Relativistic Quantum Mechanics.
- Wilmott, P., Howison, S., Dewynne, J. (1995) The Mathematics of Financial Derivatives