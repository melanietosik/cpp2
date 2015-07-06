////////////////////////////////////////////////////////////////////////////////
// graph-demo.cpp
// Demonstrates the new graph library
// TH, 29.6.15
// Demonstrates dot format and breadth-first search
// MT,  6.7.15
//
// dot mt.dot -Tpdf -o mt_movies_test.pdf
////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

#include "graph_edge.hpp"
#include "labeled_graph.hpp"
#include "bfs.hpp"
#include "dfs.hpp"
#include "graph_dot.hpp"

// Import some graph data types
using GraphLibrary::SimpleGraphEdge;
using GraphLibrary::LabeledDirectedGraph;

// Define a graph edge
typedef SimpleGraphEdge<std::string,std::string> Edge;

/// Visitor object which prints a node on a stream
template<typename NODE>
struct NodePrinter
{
  /// Constructor
  NodePrinter(std::ostream& o=std::cout) : out(o) {}
  /// Overloaded function call operator which is called when a graph node
  /// is discovered
  void operator()(const NODE& n) { out << n << std::endl; }

  std::ostream& out;  
}; // NodePrinter

/// Visitor object which stores a node in a vector
template<typename NODE>
class NodeStorer
{
public:  
  /// Constructor
  NodeStorer(std::vector<NODE>& v) : store(v) {}
    
  /// Overloaded function call operator which is called when a graph node
  /// is discovered
  void operator()(const NODE& n) { store.push_back(n); }

  // Return the nodes
  const std::vector<NODE>& get_nodes() const { return store; }
    
private: 
  std::vector<NODE>& store;
}; // NodeStorer

  
int main(int argc, char* argv[])
{
  if (argc!=2) {
    std::cerr << "Missing name for dot-file.\n";
    exit(1);
  }

  // Example movie graph
  LabeledDirectedGraph<Edge> movies;
  
  movies.add(Edge("Sigourny Weaver","performed_in","Alien"));
  movies.add(Edge("Ridley Scott ","directed","Alien"));
  movies.add(Edge("Ridley Scott ","directed","Body of lies"));
  movies.add(Edge("John Hurt","performed_in","Alien"));
  movies.add(Edge("Leonardo diCaprio","performed_in","Titanic"));
  movies.add(Edge("Leonardo diCaprio","performed_in","Body of lies"));
  movies.add(Edge("Leonardo diCaprio","performed_in","The Departed"));
  movies.add(Edge("Martin Scorsese","directed","The Departed"));
  movies.add(Edge("Kate Winslet","performed_in","Titanic"));
  movies.add(Edge("James Cameron","directed","Titanic"));
  std::cout << "\n" << movies;

  std::cout << "\nDo a DFS on the graph and print the nodes in the discovery order:\n";
  NodePrinter<Edge::Node> output_nodes_on(std::cout);
  GraphLibrary::depth_first_search(movies,output_nodes_on,true);

  // Create PDF from from dot-file with
  // dot -Tpdf -o dot-file.dot
  GraphLibrary::draw<Edge>(movies, argv[1]);
  
  // Example style guide graph
  LabeledDirectedGraph<Edge> style_guide;

  style_guide.add(Edge("trousers","before","shoes"));
  style_guide.add(Edge("socks","before","shoes"));
  style_guide.add(Edge("slip","before","trousers"));
  style_guide.add(Edge("undershirt","before","shirt"));
  style_guide.add(Edge("shirt","before","jacket"));
  style_guide.add(Edge("jacket","before","coat"));
  style_guide.add(Edge("shirt","before","tie"));
  std::cout << "\n" << style_guide;

  std::cout << "\nDo a DFS on the style guide graph:\n";
  // Create a function object which stores nodes in a vector
  std::vector<Edge::Node> topological_order;
  NodeStorer<Edge::Node> node_storer(topological_order);
  
  // Perform the topological search
  GraphLibrary::depth_first_search(style_guide,node_storer,false);
  
  // Output the topological order
  std::cout << "A possible order for a gentleman to dress is the following:\n";
  for (auto n = topological_order.rbegin(); n != topological_order.rend(); ++n) {
    std::cout << *n << std::endl;
  }

  // // Create PDF from from dot-file with
  // // dot -Tpdf -o dot-file.dot
  // GraphLibrary::draw<Edge>(style_guide, argv[1]);

  // Example lexicon graph
  LabeledDirectedGraph<Edge> lexicon;
  
  lexicon.add(Edge("<>","c","c"));
  lexicon.add(Edge("<>","f","f"));
  lexicon.add(Edge("<>","d","d"));
  lexicon.add(Edge("<>","r","r"));
  lexicon.add(Edge("c","a","ca"));
  lexicon.add(Edge("ca","t","cat"));
  lexicon.add(Edge("d","o","do"));
  lexicon.add(Edge("do","g","dog"));
  lexicon.add(Edge("f","o","fo"));
  lexicon.add(Edge("f","r","fr"));
  lexicon.add(Edge("r","a","ra"));
  lexicon.add(Edge("ra","t","rat"));
  lexicon.add(Edge("fr","o","fro"));
  lexicon.add(Edge("fro","g","frog"));
  std::cout << "\n" << lexicon;

  std::cout << "\nDo a BFS on the lexicon trie:\n";
  GraphLibrary::breadth_first_search(lexicon,"<>",output_nodes_on);

  // // Create PDF from from dot-file with
  // // dot -Tpdf -o dot-file.dot
  // GraphLibrary::draw<Edge>(lexicon, argv[1]);

}
