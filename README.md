## Path Integral Solver for Option Pricing

This project implements a **C++ solver for derivative pricing** using the **path integral formulation** of stochastic processes.  
The key idea is to simulate all possible paths of the underlying asset under the chosen **stochastic differential equation (SDE)** and compute the **discounted expected payoff**.

---

### 1) Core Equation

Under the **risk-neutral measure**, an asset price \( S_t \) follows:

\[
dS_t = \mu(S_t, t) \, dt + \sigma(S_t, t) \, dW_t
\]

- \( \mu(S_t, t) \) — **drift term** (expected rate of return under risk-neutral measure)
- \( \sigma(S_t, t) \) — **volatility term** (can be constant or state-dependent)
- \( W_t \) — standard Brownian motion

---

### 2) Feynman–Kac Formula

For a payoff function \( \text{Payoff}(S_T) \) at maturity \( T \):

\[
V(S_0, 0) = e^{-rT} \, \mathbb{E} \big[ \text{Payoff}(S_T) \big]
\]

Using **path integrals**, this expectation becomes:

\[
V(S_0, 0) = e^{-rT} \int \mathcal{D}S(t) \, \text{Payoff}(S_T) \, P[S(t)]
\]

where \( P[S(t)] \) is the path probability density derived from the SDE.

---

### 3) Why This Solver is Flexible

In this implementation:

- The **only part you need to change** for a new model is the **SDE definition**.
- Once the SDE is set, the solver:
  1. Generates many possible paths for \( S_t \) over time.
  2. Computes the payoff at maturity for each path.
  3. Averages and discounts to get the option price.

---

### 4) Example: Black–Scholes Model

```math
dS_t = r S_t \, dt + \sigma S_t \, dW_t
