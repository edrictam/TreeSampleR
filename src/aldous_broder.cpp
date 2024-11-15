#include "RcppArmadillo.h"
#include "helpers.h"
using namespace Rcpp;
using namespace arma;
using namespace std;

//' @name aldous_broder
 //' 
 //' Sample a random spanning tree from a given weighted undirected graph
 //' @param W a matrix.
 //' @param start an non-negative integer indicating the starting point.
 //' @return An adjacency matrix of the random spanning tree. 
// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]
arma::mat aldous_broder(const arma::mat&W, int start) {
  // Initialize variables
  int n = W.n_rows;
  arma::mat A_T_(n, n, arma::fill::zeros);
  arma::Col<int> InTree(n, arma::fill::zeros);
  arma::Col<int> Prev(n);
  
  // Set up starting point
  int r = start;
  InTree(r) = 1;
  
  int u = r;
  int NewNodeVisited = 1;
  
  int v = 0;
  
  // continue process until all nodes are visited
  while (NewNodeVisited<n) {
    
    //draw the next step of the random walk
    arma::vec neighbors = W.col(u); 
    v = sample_categorical_unnormalized(neighbors);
    
    // if new node is visited, add first entrance edge to tree
    if(!InTree(v)){
      Prev(v)= u;
      InTree(v)=1;
      NewNodeVisited += 1;
    };
    u = v;
  }
  
  // Construct adjacency matrix
  for (int u = 1; u < n; ++u)
  {
    A_T_(u, Prev(u)) = 1;
    A_T_(Prev(u), u) = 1;
  } 
  
  return A_T_;
}
