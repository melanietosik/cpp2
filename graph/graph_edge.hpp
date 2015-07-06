////////////////////////////////////////////////////////////////////////////////
// graph_edge.hpp
// Implements a simple graph edge type based on template parameters
// TH, 29.6.15
////////////////////////////////////////////////////////////////////////////////

#ifndef __GRAPH_EDGE_HPP__
#define __GRAPH_EDGE_HPP__

namespace GraphLibrary {

/// SimpleGraphEdge represents a simple unweighted directed graph edge
template<typename NODE,typename LABEL>
struct SimpleGraphEdge
{
public:
  typedef NODE    Node;
  typedef LABEL   Label;
  
  SimpleGraphEdge(const Node& s, const Label& l, const Node& t)
  : m_source(s), m_label(l), m_target(t)
  {}
  
  const Node& source() const { return m_source; }
  const Node& target() const { return m_target; }
  const Node& label()  const { return m_label; }
  
protected: // "protected" means that the following is accessible for derived classes
  Node  m_source;
  Node  m_target;
  Label m_label;
}; // SimpleGraphEdge

} // namespace GraphLibrary

#endif
