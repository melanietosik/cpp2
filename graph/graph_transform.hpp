////////////////////////////////////////////////////////////////////////////////
// graph_transform.hpp
// Generic graph transformation
// TH, 6.7.15
////////////////////////////////////////////////////////////////////////////////

#ifndef __GRAPH_TRANSFORM_HPP__
#define __GRAPH_TRANSFORM_HPP__

namespace GraphLibrary {

  /// Transform a graph into some other representation
  template<typename GRAPHEDGE, typename TRANSFORMER>
  void graph_transform(const LabeledDirectedGraph<GRAPHEDGE>& g, 
                       TRANSFORMER& transform)
  {
    transform.prolog();
    // Iterate over all nodes
    for (auto n = g.nodes().begin(); n != g.nodes().end(); ++n) {
      // Transform node
      transform(*n);
      // Transform edges
      auto& neighbours = g[*n];
      // Iterate over all leaving edges
      for (auto e = neighbours.begin(); e != neighbours.end(); ++e) {
        transform(*e);
      }
    }
    transform.epilog();
  }
}

#endif
