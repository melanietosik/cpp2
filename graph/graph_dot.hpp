////////////////////////////////////////////////////////////////////////////////
// graphdot.hpp
// Writes graph in dot format to 'dot_file' (see graphviz.org)
// MT, 05.07.15
////////////////////////////////////////////////////////////////////////////////

#ifndef __GRAPH_DOT_HPP__
#define __GRAPH_DOT_HPP__

#include <fstream> 

namespace GraphLibrary {
  template<class GRAPHEDGE>

  /// Writes the graph in dot format to dot_file
  void draw(const LabeledDirectedGraph<GRAPHEDGE>& g, const char* dot_file)
  {
    std::ofstream dot_out(dot_file);
    if (dot_out) {
      dot_out << "digraph FSM {\n";
      // Write header
      dot_out << "  graph [rankdir=LR, size=\"6.0,6.0\", fontsize=14, center=1, orientation=Portrait];\n";
      dot_out << "  node  [style=filled, color=blue, fontname=Arial, fontcolor=white, shape=circle];\n";
      dot_out << "  edge  [fontname=Arial];\n\n";

      // Iterate over all graph nodes
      for (auto n = g.nodes().begin(); n != g.nodes().end(); ++n) {
        dot_out << "  \"" << *n << "\" [label=\"" << *n << "\"";
        dot_out << "]\n";
        
        // GRAPHEDGE edges = ;
        for (auto e = g[*n].begin(); e != g[*n].end(); ++e) {
          dot_out << "    \"" << e->source() << "\" -> \"" << e->target() << "\"";
          dot_out << " [label=\"" << e->label() << "\"]\n";
        }
      }
      dot_out << "}\n";
    }
    else {
      std::cerr << "Unable to open " << dot_file  << "\n";
    }
  }
}

#endif
