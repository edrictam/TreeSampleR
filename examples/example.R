library(TreeSampleR)
# generate a complee graph with 40 nodes 
A = matrix(rep(1, 40*40), 40, 40)
diag(A) = rep(0, 40)
aldous_broder(A, 1)
fast_cover(A, 0, 1)
wilson(A, 1)
