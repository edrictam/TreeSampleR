[![Build Status](https://travis-ci.com/vittorioorlandi/FLAME.svg?branch=master)](https://travis-ci.com/vittorioorlandi/FLAME)

# Introduction
The `TreeSampleR` package offers fast implementations of the exact random spanning tree samplers, such as the Aldous-Broder sampler, Wilson sampler and the fast-forwarded cover sampler described by Tam, Dunson and Duan [here](https://arxiv.org/pdf/2405.03096). 

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


# Installation 
TreeSampleR can be installed from the author's GitHub, [here](https://github.com/edrictam/TreeSampleR) via `devtools::install_github('https://github.com/edrictam/TreeSampleR')`. 