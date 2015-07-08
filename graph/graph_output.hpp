////////////////////////////////////////////////////////////////////////////////
// graph_output.hpp
// Graph output in different formats, for example graphviz dot
// TH, 6.7.15
////////////////////////////////////////////////////////////////////////////////

#ifndef __GRAPHOUTPUT_HPP__
#define __GRAPHOUTPUT_HPP__

#include <iostream>

#include "labeled_graph.hpp"
#include "graph_transform.hpp"

namespace GraphLibrary {

  /** 
    @brief Function object for outputting graphs as dot
           Each outputter function object has 4 functions:
           1. prolog(): output stuff before the actual graph is outputted
           2. operator()(Node&): output a node
           3. operation()(Edge&): output an edge
           4. epilog(): output stuff after the graph has been outputted
  */
  template<typename GRAPHEDGE>
  struct GraphDotOutputter
  {
    /// Constructor takes an ostream reference
    GraphDotOutputter(std::ostream& o) : out(o) {}
     
    /// Write dot prolog
    void prolog()
    {
      out << "digraph Graph {" << std::endl;
      out << "  graph [rankdir = LR, center = 1, orientation = Portrait]" << std::endl;
      out << "  node [fontsize = 14, shape = box, style = filled, color = blue, fontcolor = white]" << std::endl;
      out << "  edge [fontsize = 14 ];" << std::endl << std::endl;
    }
    
    /// Node output
    void operator()(const typename GRAPHEDGE::Node& node)
    {
      out << "  " << "\"" << node << "\"" << std::endl;
    }
      
    /// Edge output
    void operator()(const GRAPHEDGE& edge)
    {
      const char* quote = "\"";
      out << "  " << quote << edge.source() << quote
          << " -> " << quote << edge.target() << quote
          << " [label = " << quote << edge.label() << quote 
          << "]" << std::endl;
    }

    /// Write dot epilog
    void epilog()
    {
      out << "}" << std::endl;
    }
    
    std::ostream& out; ///< Stream everything is written to
  }; // GraphDotOutputter

  /// Output graph in graphviz dot format
  template<typename GRAPHEDGE>
  void graph_as_dot(const LabeledDirectedGraph<GRAPHEDGE>& g,
                    std::ostream& o)
  {
    // Construct dot output function object
    GraphDotOutputter<GRAPHEDGE> dot_outputter(o);
    // Call generic transformation function which creates the dot output
    graph_transform(g,dot_outputter);
  }

} // namespace raphLibrary

#endif
