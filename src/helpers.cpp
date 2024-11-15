#include "RcppArmadillo.h"

using namespace Rcpp;
using namespace arma;
using namespace std;

 //' This function returns a sample from a categorical distribution
 //' whose probabilities are specified by an unnormalized vector
 //' of non-negative real numbers. 
 //' @param probs an arma vector.
 //' @return A non-negative integer.

 unsigned int sample_categorical_unnormalized(const arma::vec& probs) {
   arma::vec normprobs = probs/arma::accu(probs);
   NumericVector p = as<NumericVector>(wrap(normprobs));
   int k = p.size();
   IntegerVector ans(k);
   rmultinom(1, p.begin(), k, ans.begin());
   arma::vec sample = as<arma::vec>(wrap(ans));
   arma::uvec ind = find(sample);
   return (int)ind[0];
 }