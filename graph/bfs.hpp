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

#include "labeledgraph.hpp"

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
    GraphBFSSearch(const LabeledDirectedGraph<GRAPHEDGE>& g)
    : the_graph(g) {}
    
    /** 
      @brief Start the breadth-first search at a given node and print 
             the discovered nodes in bfs discovery order.
             The template param is the visitor function object
    */
    /// Function for BFS.
    /// Perform a breadth-first search for the given node.
    template<typename VISITOR>
    void bfs(const Node& start, VISITOR& visitor)
    {
      // For bfs, we maintain a queue (agenda, todo list) of nodes yet
      // to be processed and a set containing those nodes already seen
      // Initialise queue with start node
      std::queue<Node> unprocessed;
      std::set<Node> processed;
      unprocessed.push(start);
      
      while (!unprocessed.empty()) {
        // Pop node from queue and add it to processed set
        Node n = unprocessed.front();
        unprocessed.pop();
        processed.insert(n);
        // Call visitor
        visitor(n);
        // Get neighbours of n ('auto&' to be sure to use the reference)
        auto& neighbours = the_graph[n];
        for (auto e = neighbours.begin(); e != neighbours.end(); ++e) {
          if (processed.find(e->target()) == processed.end()) {
            // neighbour is yet unprocessed
            unprocessed.push(e->target());
          }
        } // for e        
      } // while
    }

  private: // Member variables
    const LabeledDirectedGraph<GRAPHEDGE>& the_graph;
  }; // GraphBFSSearch

  } // namespace detail
} // namespace MyCoolGraphLibrary

#endif
