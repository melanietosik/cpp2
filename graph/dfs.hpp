////////////////////////////////////////////////////////////////////////////////
// dfs.hpp
// Implements depth-first search
// TH, 29.6.15
////////////////////////////////////////////////////////////////////////////////

#ifndef __DFS_HPP__
#define __DFS_HPP__

#include <map>

#include "labeled_graph.hpp"

namespace GraphLibrary {
  
  // Forward declaration of embedded class
  namespace detail {
    template<typename GRAPHEDGE> class GraphDFSSearch;
  }
  
  /**
    @brief depth_first_search() implements depth-first search from a given node
    @param g the graph to be searched
    @param start the start node of the graph
    @param the visitor object
  */  
  template<typename GRAPHEDGE, typename VISITOR>
  void depth_first_search(const LabeledDirectedGraph<GRAPHEDGE>& g, 
                          const typename GRAPHEDGE::Node& start, 
                          VISITOR& visitor)
  {
    // Instantiate the algorithm with the given graph
    detail::GraphDFSSearch<GRAPHEDGE> dfs_algorithm(g);
    // Start the search at the node
    dfs_algorithm.dfs(start,visitor);
  }

  /** 
    @brief depth_first_search() implements depth-first search for all graph nodes
    @param g the graph to be searched
    @param visitor the visitor function object
    @param action_on_grey_nodes
  */  
  template<typename GRAPHEDGE, typename VISITOR>
  void depth_first_search(const LabeledDirectedGraph<GRAPHEDGE>& g, 
                          VISITOR& visitor,
                          bool action_on_grey_nodes)
  {
    typedef detail::GraphDFSSearch<GRAPHEDGE> DFSSearch;
    
    DFSSearch dfs_algorithm(g,action_on_grey_nodes);
    // Iterate over all graph nodes
    for (auto n = g.nodes().begin(); n != g.nodes().end(); ++n) {
      // If the node color is white, start a new search
      if (dfs_algorithm.get_color(*n) == DFSSearch::dfsWHITE) {
        //std::cout << "Exploring " << *n << std::endl;
        dfs_algorithm.dfs(*n,visitor);
      }
    }
  }

  // We define a separate sub-namespace for the private definitions
  namespace detail {
  /**
    @brief Depth-first search class for graphs.
           The template parameter is the type of the graph edge.
  */
  template<typename GRAPHEDGE>
  class GraphDFSSearch
  {
  public:
    typedef typename GRAPHEDGE::Node                      Node;
    typedef enum { dfsWHITE, dfsGREY, dfsBLACK, dfsNONE } NodeColor;
  
  public:
    /** 
      @brief Constructor
      @param g the graph
      @param action_when_first_discovered when true, the action defined by
             the visitor object will be performed when a node is seen for
             the first time (when it gets grey). Otherwise, the action takes
             place when the node gets black
    */
    GraphDFSSearch(const LabeledDirectedGraph<GRAPHEDGE>& g, 
                   bool action_when_first_discovered = true) 
    : the_graph(g), do_action_on_grey_node(action_when_first_discovered)
    {  
      // Paint all nodes white (= not seen yet)
      // Note: in principle, not necessary, since a node not found in
      // the map could be interpreted as a white node
      for (auto it = g.nodes().begin(); it != g.nodes().end(); ++it) {
        colors[*it] = dfsWHITE;
      }  
    }
    
    /** 
      @brief Start the depth-first search at a given node and print 
             the discovered nodes in dfs discovery order.
             The template param is the visitor function object
    */
    template<typename VISITOR>
    void dfs(const Node& start_node, VISITOR& visitor)
    {
      // Start the recursive function
      dfs_rec(start_node,visitor);
    }

    /** 
      @brief Returns the color for a node.
      /// If the node is not present in the colormap, return NONE.
      /// Colors:
    /// * WHITE = Unseen node
    /// * GREY  = Seen node, that is currently processed
    /// * BLACK = Seen node, that is finished 
    /// * NONE  = 'Fail state'
    */
    NodeColor get_color(const Node& node) const
    {
      auto it = colors.find(node);
      return (it == colors.end() ? dfsNONE : it->second);
    }
  
  private:
    /// Recursive function for DFS.
    /// Perform a depth-first search for the given node.
    template<typename VISITOR>
    void dfs_rec(const Node& node, VISITOR& visitor) 
    {
      switch (get_color(node)) {
        case dfsGREY:
          // If we discover a state that we have already seen,
          // the graph is cyclic and don't continue to avoid loops.
          break;
          
        case dfsBLACK:
          break;
        
        // Recursive case:
        case dfsWHITE:
          // First, mark the node as GREY. This is the beginning of its lifecycle.
          colors[node] = dfsGREY;

          // Call visitor
          if (do_action_on_grey_node)
            visitor(node);

          // Continue recursion: Get all direct successing states
          auto& neighbours = the_graph[node];

          // Iterate over them and start the dfs again.
          for (auto e = neighbours.begin(); e != neighbours.end(); ++e) {
            if (get_color(e->target()) == dfsWHITE) { 
              dfs_rec(e->target(),visitor);
            }
          } // for e
          
          // Eventually, all connected nodes have been processed. 
          // Mark it as black.
          colors[node] = dfsBLACK;
          if (!do_action_on_grey_node)
            visitor(node);
          break;
      } // switch
    }

  private: // Types
    typedef std::map<Node,NodeColor>            NodeColorMap;

  private: // Member variables
    const LabeledDirectedGraph<GRAPHEDGE>& the_graph;
    NodeColorMap colors; ///< Assigns a color to each node
    bool do_action_on_grey_node;
  }; // GraphDFSSearch

} // namespace detail

} // namespace GraphLibrary

#endif
