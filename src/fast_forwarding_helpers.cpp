#include "RcppArmadillo.h"

using namespace Rcpp;
using namespace arma;
using namespace std;

// create an escape probability vector from the set of visited vertices
arma::mat create_Escape(const arma::mat& W, const arma::uvec& visited,
                        const arma::uvec& unvisited){
  
  arma::rowvec degree = sum(W, 0);
  arma::rowvec denominator = degree.cols(visited);
  arma::mat boundaryEdges = W.submat(visited, unvisited);
  arma::vec numerator = sum(boundaryEdges, 1);
  return diagmat(numerator.t()/denominator);
  
}

// create normalized transition probability vector for transitions within the set of visited vertices
arma::mat create_PA(const arma::mat& W, const arma::uvec& visited){
  arma::mat within_transitions = W.submat(visited, visited);
  return normalise(within_transitions, 1, 1);
  
}

// create normalized transition probability vector for transitions from visited vertices to not yet visited vertices
arma::mat create_PA_Escape(const arma::mat& W, const arma::uvec& visited, const arma::uvec& unvisited){
  arma::mat between_transitions = W.submat(visited, unvisited);
  return normalise(between_transitions, 1, 1);
  
}

// compute the distribution on the set of visited vertices that indicate
// the probability that the walk eventually exits via that vertex
arma::vec compute_x_Escape_A_solve(const arma::mat& P_A, const arma::mat& x_escape, const arma::uvec& ind){
  arma::mat I = eye(ind.n_elem, ind.n_elem);
  arma::vec temp_product_solved = arma::solve((I - P_A.t() * (I - x_escape)), arma::conv_to<arma::vec>::from(ind));
  return x_escape* temp_product_solved;
}