#' plot a tree graph with root specified
#'
#' @param root the vertex that serves as the root
#' @param tree A graph object from igraph
#' @param vertex_size The size of the vertices in the plot
#' @return A plot of the tree.
plot_as_tree <- function(tree, root = "1", vertex_size = 50){
  plot(as.undirected(tree), layout = layout_as_tree(tree, root = root), vertex.label=seq(1,vcount(tree)), vertex.size = vertex_size)
}

#' plot the underlying graph
#'
#' @param g A graph object from igraph
#' @param vertex_size The size of the vertices in the plot
#' @return A plot of the graph.
plot_underlying <- function(g, vertex_size = 50){
  plot(g, vertex.size = vertex_size)
}
