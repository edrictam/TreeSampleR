#include "RcppArmadillo.h"
#include "helpers.h"
#include "fast_forwarding_helpers.h"

using namespace Rcpp;
using namespace arma;
using namespace std;

//' @title Sample a random spanning tree from a graph
//' 
//' @name fast_cover
//' 
//' This function returns a random spanning tree from a given 
//' weighted undirected graph (specified by an adjacency matrix). 
//' The starting point does not affect sampling properties for undirected graphs.
//' The threshold parameter specifies how frequently the user wants to employ 
//' the fast forwarding step to bypass bottlenecks
//' @param W a matrix.
//' @param start an non-negative integer indicating the starting point.
//' @param threshold an non-negative integer indicating the threshold for deploying fast forwarding.
//' @return An adjacency matrix of the random spanning tree. 
// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]
arma::mat fast_cover(const arma::mat&W, int start, int threshold) {
  // Initialize variables
  int n = W.n_rows;

  arma::uvec dummies(n-1, fill::ones);
  arma::uvec nodes(n, fill::zeros);
  nodes.subvec(1, n-1) = cumsum(dummies);
  arma::mat A_T_(n, n, arma::fill::zeros);
  arma::Col<int> InTree(n, arma::fill::zeros);
  arma::Col<int> Prev(n);

  // Set up initial starting point
  int r = start;
  InTree(r) = 1;
  int numVisited = 1;
  arma::uvec visited = nodes.elem(find(InTree == 1));
  arma::uvec unvisited = nodes.elem(find(InTree == 0));
  int u = r;
  int v;
  int revisit_counter = 0;
  
  // continue until all nodes are visited
  while (numVisited<n) {

    // sample next step of the random walk
    arma::vec neighbors = W.col(u);
    v = sample_categorical_unnormalized(neighbors);

    // if we are visited a new node, add the first entrance edge to the tree
    if(InTree(v) == 0){

      Prev(v)= u;
      InTree(v)=1;
      numVisited += 1;
      visited = nodes.elem(find(InTree == 1));
      unvisited = nodes.elem(find(InTree == 0));

      // if we did not visit a new node
      // keep track of how long we have been stuck 
    } else if((InTree(v) == 1) && (revisit_counter < threshold)){
      revisit_counter += 1;

    } else {
      // if we did not visit a new node and we have been stuck for a number of
      // steps that exceed the threshold, employ fast-forwarding to bypass bottleneck.
      revisit_counter = 0;
      arma::uvec ind(visited.n_elem, arma::fill::zeros);
      arma::uvec loc = find(visited == v);
      ind(loc[0]) = 1;

      //create escape probability vector 
      arma::mat x_escape = create_Escape(W, visited, unvisited);

      //create P_A the transition matrix within the already visited vertices
      arma::mat P_A = create_PA(W, visited);

      //create P_{A,A^C} the transition matrix from the visited vertices to the unvisited
      arma::mat P_A_escape = create_PA_Escape(W, visited, unvisited);

      //Compute x_exit_A 
      arma::vec x_exit_A = compute_x_Escape_A_solve(P_A, x_escape, ind);

      //sample m, the node from which the exit occurred
      int m_loc = sample_categorical_unnormalized(x_exit_A);
      int m = visited(m_loc);

      //sample m*, the node to which the exit occurred
      arma::vec ind2(visited.n_elem, arma::fill::zeros);
      ind2(m_loc) = 1;
      int m_star_loc = sample_categorical_unnormalized(P_A_escape.t() * ind2);
      int m_star = unvisited(m_star_loc);

      // add first entrance edge to tree
      u = m;
      v = m_star;
      Prev(v)= u;
      InTree(v)=1;
      numVisited += 1;
      visited = nodes.elem(find(InTree == 1));
      unvisited = nodes.elem(find(InTree == 0));
    }
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
