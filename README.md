# Introduction
The `TreeSampleR` package offers fast C++ implementations of several exact random spanning tree samplers, such as the Aldous-Broder sampler, Wilson sampler and the fast-forwarded cover sampler described by Tam, Dunson and Duan [here](https://arxiv.org/pdf/2405.03096). The implementations here focus on sampling an undirected spanning tree from a potentially weighted undirected graph. Generalization of these algorithms to certain directed graphs is possible but not pursued here. 

# An Example
We start by generating some toy graph data, from which we can sample random spanning trees. 

```

# generate adjacency matrix for a complete graph with 40 nodes
A = matrix(rep(1, 40*40), 40, 40)
diag(A) = rep(0, 40)

# use all 3 algorithms for sampling trees
aldous_broder(A, 1)
fast_cover(A, 0, 1)
wilson(A, 1)
```

# Testing

One main challenge in implementing random spanning tree samplers as software is testing. 
A complete graph with n nodes has n^(n - 2) spanning trees, which is astronomical even for small n. 
The number of random spanning trees that any practitioner can generate will generally be far smaller than n^(n - 2), and as such it is difficult to directly test whether any random spanning tree sampler is implemented correctly.  

We propose a novel way to principally probe the correctness of random spanning tree samplers

The main idea for the test is to consider the “marginal edge inclusion probability”, i.e. the frequency at which a given edge is included in a sample of random spanning trees. There is a simple, closed form mathematical expression for the marginal edge inclusion probability that is easily computed. One can then compare the empirical frequency of edge inclusion observed in random spanning tree samples to the theoretical value. It is unlikely that an incorrectly implemented sampler would yield highly accurate edge inclusion frequencies over multiple test edges.

This gives us a computationally very tractable way to test spanning tree samplers. This is implemented and detailed the `tests` directory.


# Installation 
TreeSampleR can be installed from the author's GitHub, [here](https://github.com/edrictam/TreeSampleR) via `devtools::install_github('https://github.com/edrictam/TreeSampleR')`. 

# Troubleshooting

For Mac Apple Silicon (M1 and above) machines, when using R packages with C++ code sometimes the compiler complains that "ld: Library 'gfortran' not found". If this is the case, this can be resolved by [the answer by chermen in this post](https://stackoverflow.com/questions/69639782/installing-gfortran-on-macbook-with-apple-m1-chip-for-use-in-r). In summary, you need to specify to R in the Makevars file the locations of your gcc/gfortran libraries. 

