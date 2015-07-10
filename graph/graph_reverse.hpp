////////////////////////////////////////////////////////////////////////////////
// graph_reverse.hpp
// Graph reverse
// MT, 6.7.15
////////////////////////////////////////////////////////////////////////////////

#ifndef __GRAPH_REVERSE_HPP__
#define __GRAPH_REVERSE_HPP__

#include <iostream>

#include "labeled_graph.hpp"
#include "graph_transform.hpp"
#include "graph_output.hpp"

namespace GraphLibrary {
  typedef SimpleGraphEdge<std::string,std::string> Edge;
    
  /// Reverse graph
  template<typename GRAPHEDGE>
  LabeledDirectedGraph<GRAPHEDGE> reverse(const LabeledDirectedGraph<GRAPHEDGE>& g)
  {
    /// New reversed graph
    LabeledDirectedGraph<Edge> reverse_graph;

    // Iterate over all nodes
    for (auto n = g.nodes().begin(); n != g.nodes().end(); ++n) {
      // Transform edges
      auto& neighbours = g[*n];
      // Iterate over all leaving edges
      for (auto e = neighbours.begin(); e != neighbours.end(); ++e) {
        // Reverse edges
        // (source becomes target, target becomes source)
        reverse_graph.add(Edge(e->target(), e->label(), e->source()));
      }
    }
    return reverse_graph;
  }

} // namespace GraphLibrary

#endif