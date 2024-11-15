#' Sample a random spanning tree 
#' @param W a matrix.
#' @param start an non-negative integer indicating the starting point.
#' @return An adjacency matrix of the random spanning tree. 
#' @examples
#' aldous_broder(A, 1)
aldous_broder <- function(W, start) {
  .Call(`_TreeSampleR_aldous_broder`, W, start)
}

#' Sample a random spanning tree 
#' @param W a matrix.
#' @param start an non-negative integer indicating the starting point.
#' @param threshold an non-negative integer indicating the threshold for deploying fast-forwarding.
#' @return An adjacency matrix of the random spanning tree. 
#' @examples
#' fast_cover(A, 1, 10)
fast_cover <- function(W, start, threshold) {
  .Call(`_TreeSampleR_fast_cover`, W, start, threshold)
}

#' Sample a random spanning tree 
#' @param W a matrix.
#' @param start an non-negative integer indicating the starting point.
#' @return An adjacency matrix of the random spanning tree. 
#' @examples
#' wilson(A, 1)
wilson <- function(W, start) {
  .Call(`_TreeSampleR_wilson`, W, start)
}
