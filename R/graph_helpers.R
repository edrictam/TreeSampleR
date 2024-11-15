#get all nodes on the tree
getTreeNodes<- function(g, K_tilde){
  neighborhood(g,order=K_tilde,nodes=1,mode='out')[[1]]
}

#get all child nodes for node v 
getChildren<- function(g,v){
  neighbors(g,as.character(v),mode='out')
}

#check if a node v (v is a vertex name) is in the tree and a leaf
isLeaf<- function(g, v, K_tilde){
  allNodes<- getTreeNodes(g, K_tilde)
  isInTree<- as.character(v)%in%allNodes$name
  if (isInTree){
    return(length(getChildren(g,as.character(v)))==0)
  }
  return(FALSE)
}

## given a graph g, plot it with tree layout
plot_as_tree <- function(g, root = "1"){
  plot(as.undirected(g), layout = layout_as_tree(g, root = root), vertex.label=NA)
}