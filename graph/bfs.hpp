////////////////////////////////////////////////////////////////////////////////
// bfs.hpp
// Implements breadth-first search
// MT, 05.07.15
////////////////////////////////////////////////////////////////////////////////

#ifndef __BFS_HPP__
#define __BFS_HPP__

#include <map>
#include <set>
#include <queue>

namespace GraphLibrary {
  
  // Forward declaration of embedded class
  namespace detail {
    template<typename GRAPHEDGE> class GraphBFSSearch;
  }
  
  /**
    @brief breadth_first_search() implements breadth-first search from a given node
    @param g the graph to be searched
    @param start the start node of the graph
    @param the visitor object
  */  
  template<typename GRAPHEDGE, typename VISITOR>
  void breadth_first_search(const LabeledDirectedGraph<GRAPHEDGE>& g, 
                          const typename GRAPHEDGE::Node& start, 
                          VISITOR& visitor)
  {
    // Instantiate the algorithm with the given graph
    detail::GraphBFSSearch<GRAPHEDGE> bfs_algorithm(g);
    // Start the search at the node
    bfs_algorithm.bfs(start,visitor);
  }
  
  // We define a separate sub-namespace for the private definitions
  namespace detail {
  /**
    @brief Breadth-first search class for graphs.
           The template parameter is the type of the graph edge.
  */
  template<typename GRAPHEDGE>
  class GraphBFSSearch
  {
  public:
    typedef typename GRAPHEDGE::Node                      Node;
  
  public:
    /** 
      @brief Constructor
      @param g the graph
    */
    GraphBFSSearch(const LabeledDirectedGraph<GRAPHEDGE>& g) : the_graph(g) 
    {}
    
    /** 
      @brief Start the breadth-first search at a given node and print 
             the discovered nodes in bfs discovery order.
             The template param is the visitor function object
    */
    /// Function for BFS.
    /// Perform a breadth-first search for the given node.
    template<typename VISITOR>
    void bfs(const Node& start_node, VISITOR& visitor)
    {
      // Append start node to queue of nodes yet to visit
    	ToVisit.push(start_node);
      // While there are still unseen nodes...
    	while (!ToVisit.empty()) {
        // Current node is first node in the queue
    		Node& current = ToVisit.front();
        // Take first node from the queue
    		ToVisit.pop();
        // Ignore already visited nodes
    		if (is_already_visited(current)) {
    			continue;
    		}
        // Add the next "layer" of nodes to the queue
    		for (auto e = the_graph[current].begin(); e != the_graph[current].end(); ++e) {
    			ToVisit.push(e->target());
    		}
        // Process current node
    		visitor(current);
        // Current node done
    		AlreadyVisited.insert(current);
    	}
    }

  private:

	std::queue<Node>                 ToVisit;
	std::unordered_set<Node>  AlreadyVisited;
  	
  /// Helper function; returns true if a node has already been visited
  bool is_already_visited(Node& n) {
  	return AlreadyVisited.find(n) != AlreadyVisited.end();
  }

  private: // Member variables
    const LabeledDirectedGraph<GRAPHEDGE>& the_graph;
  }; // GraphDFSSearch

} // namespace detail

} // namespace GraphLibrary

#endif
