////////////////////////////////////////////////////////////////////////////////
// labeled_graph.hpp
// Labeled directed graphs in C++
// TH, 29.6.15
////////////////////////////////////////////////////////////////////////////////

#ifndef __LABELED_GRAPH_HPP__
#define __LABELED_GRAPH_HPP__

#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <vector>
#include <iostream>
#include <string>

// Separate name space for the library
namespace GraphLibrary {

/** 
  @brief LabeledDirectedGraph represents a labeled directed graph
         templated on the edge type
*/
template<typename GRAPHEDGE>
class LabeledDirectedGraph 
{
public: // Types
  typedef GRAPHEDGE                         GraphEdge;
  // Note: 'typename' is necessary if a nested type is addressed
  // within a template context
  typedef typename GraphEdge::Node          Node;
  typedef typename GraphEdge::Label         Label;
  typedef std::vector<GraphEdge>            EdgeVector;

private: // Types
  typedef std::set<Node>                    NodeSet;  // or unordered_set
  typedef std::map<Node,EdgeVector>         GraphMap; // or unordered_map

public:
  /// Add an edge src --label--> tgt
  void add(const GraphEdge& e) 
  {
    m_nodes.insert(e.source());
    m_nodes.insert(e.target());
    // We simply add the complete edge to the adjacency list of the source
    // This is not very memory efficient, but does the job for the moment
    m_matrix[e.source()].push_back(e);
  }

  /// Access to the adjacency vector of node n
  /// Note: currently not very good since we're exposing implementation details
  /// A better idea would be an iterator
  const EdgeVector& operator[](const Node& n) const
  { 
    // static trick!
    static EdgeVector no_neighbours;
    auto it = m_matrix.find(n);
    // By returning a const reference, we avoid copying
    return (it != m_matrix.end()) ? it->second : no_neighbours;
  }

  /// Accessor for node set
  const NodeSet& nodes() const { return m_nodes; }
  
  /// Stream output
  friend std::ostream& operator<<(std::ostream& o, const LabeledDirectedGraph& g)
  {
    g.print(o);
    return o;
  }

private: // Functions
  /// Print the relation of the graph
  void print(std::ostream& o) const
  {
    o << "graph({" << std::endl;
    for (auto n = m_matrix.begin(); n != m_matrix.end(); ++n) {
      for (auto e = n->second.begin(); e != n->second.end(); ++e) {
        o << n->first << " -- " << e->label() <<  " --> " << e->target() << "\n";
      }
    }
    o << "})" << std::endl;
  }
    
private:
  GraphMap m_matrix;  ///< Maps nodes to vector of leaving edges
  NodeSet m_nodes;    ///< Set to keep track of all used nodes. 
}; // LabeledDirectedGraph

} // namespace
#endif
