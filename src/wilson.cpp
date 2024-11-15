#include "RcppArmadillo.h"
#include "helpers.h"
using namespace Rcpp;
using namespace arma;
using namespace std;

//' @name wilson
//' 
//' This function returns a random spanning tree from a given 
//' weighted undirected graph (specified by an adjacency matrix) 
//' using a loop-erased random walk. 
//' The starting point does not affect sampling properties for undirected graphs.
//' @param W a matrix.
//' @param start an non-negative integer indicating the starting point.
//' @return An adjacency matrix of the random spanning tree. 
// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::export]]
arma::mat wilson(const arma::mat&W, int start) {
  // initialize variables
  int n = W.n_rows;
  
  // handle trivial case
  if (n == 1){
    return arma::zeros(1);
  }
  
  // ensure input is correct
  if (!approx_equal(W, W.t(), "absdiff", 1e-10))
    throw Rcpp::exception("The matrix provided is not symmetric");
  
  if (!all(all(W >= 0)))
    throw Rcpp::exception("The matrix provided has negative entries");
  
  if (start < 0)
    throw Rcpp::exception("The starting point provided has to be non-negative");
  
  if (start > (n - 1))
    throw Rcpp::exception("The starting point provided is out of range. It cannot be larger than n - 1 since C++ uses 0 based indexing.");
  
  if (!all(diagvec(W) == 0))
    throw Rcpp::exception("The diagonal has to be all 0's. No self loops allowed in adjacency matrix.");
  
  arma::mat D = arma::diagmat(sum(W, 1));
  arma::mat L = D - W;
  
  arma::vec eigval;
  arma::eig_sym(eigval, L); 
  
  // second smallest eigenvalue of Laplacian is 0 if and only if graph is not connected
  if (eigval(1) == 0)
    throw Rcpp::exception("The graph is not connected. You need to provide a connected graph.");
  
  // Initialize variables
  arma::mat A_T_(n, n, arma::fill::zeros);
  arma::Col<int> InTree(n, arma::fill::zeros);
  arma::Col<int> InPath(n, arma::fill::zeros);
  arma::Col<int> Prev(n);
  arma::uvec nodes(n, fill::zeros);
  arma::uvec path(n, fill::ones);
  path = (n + 1) * path; // n + 1 is an impossible value used as placeholder
  arma::uvec dummies(n-1, fill::ones);
  nodes.subvec(1, n-1) = cumsum(dummies);
  
  // set up starting point
  int r = start;
  InTree(r) = 1;
  int NewNodeVisited = 1;
  int path_step = 0;
  arma::uvec visited = nodes.elem(find(InTree == 1));
  arma::uvec unvisited = nodes.elem(find(InTree == 0));
  
  // start with an unvisited node that is distinct from nodes already in the tree
  // add it to path
  int u = unvisited.back();
  path(path_step) = u;
  InPath(u) = 1;
  int y, index; 

  // continue the process until all nodes are visited
  while (NewNodeVisited<n) {
    // sample next step in path
    arma::vec neighbors = W.col(u); 
    y = sample_categorical_unnormalized(neighbors);
    
    // if next step is already in tree, then add entire path to tree
    if(InTree(y)){
      // find the elements that need to be added to tree
      arma::uvec newpath = path.elem(find(path != (n + 1)));
      // the last element is added first
      int v = newpath.back();
      Prev(v) = y;
      InTree(v)=1;
      NewNodeVisited += 1;
      // if there is only one element then we are done
      // if there is more than one, loop through and add them 
      if (newpath.size() > 1) {
        for (int i = (newpath.size() - 2); i >= 0; i--){
          Prev(path(i))= path(i + 1);
          InTree(path(i))=1;
          NewNodeVisited += 1;
        }
      }
      
      // update visited and unvisited nodes
      // if visited all nodes, call it a day
      visited = nodes.elem(find(InTree == 1));
      unvisited = nodes.elem(find(InTree == 0));
      if (visited.size() == n){
        break;
      }
      // if not visited all nodes yet
      // start from arbitrary unvisited node
      // update path variables to reflect this
      u = unvisited.back();
      path.ones();
      path = path*(n + 1);
      path_step = 0;
      path(path_step) = u;
      InPath(u) = 1;

    } else{
      // the drawn node is not in tree yet 
      // check if it is in path already
      arma::uvec indices = find(path == y);
      
      // if already in path, erase loops
      if (indices.size() > 0){
        index = indices(0);
        path(span(index + 1, n - 1)).fill(n + 1); 
        path_step = index;
        InPath.zeros();
        for (int i = 0; i <= index; i ++){
          InPath(path(i)) = 1;
        }
        u = y;
      // if not already in path, append
      } else{
        path_step += 1;
        path(path_step) = y;
        InPath(y) = 1;
        u = y;
      }
    }
  }
  
  // Construct adjacency matrix
  for (int u = 1; u < n; ++u)
  {
    A_T_(u, Prev(u)) = 1;
    A_T_(Prev(u), u) = 1;
  } 
  
  return A_T_;
}
