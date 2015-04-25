////////////////////////////////////////////////////////////////////////////////
// stringlist.hpp
// Verkettete Listen von Zeichenketten
// TH, 20.4.2015
// Melanie Tosik (759476)
////////////////////////////////////////////////////////////////////////////////
 
#include <string>
#include <iostream>
using namespace std;

/// StringList repr�sentiert eine vorw�rts verkettete Liste von Zeichenketten
class StringList
{
public:
  /// Konstruktor: erzeugt eine leere Liste
  StringList()
  {
    init();
  }

  /// Kopierkonstruktor: erzeugt eine Liste als Kopie einer anderen
  StringList(const StringList& src)
  {
    init();
    // Quell-Liste elementweise kopieren
    ListElement* c = src.first;
    for (; c!= 0; c = c->next) {
      // Elemente an die neu erzeugte Liste anh�ngen
      append_back(c->content);
    }
  }

  /// Destruktor
  ~StringList()
  {
    clear();
  }

  /// Zuweisungsoperator
  const StringList& operator=(const StringList& src)
  {
    if (this != &src) {
      // Erstmal alle vorhandenen Elemente l�schen
      clear();
      // Quell-Liste elementweise durchgehen und kopieren
      for (ListElement* c = src.first; c != 0; c = c->next) {
        append_back(c->content);
      }
    }
    return *this;  
  }

  /// Test auf Listengleichheit
  friend bool operator==(const StringList& s1, const StringList& s2)
  {
    // Listen sind ungleich, wenn sie unterschiedlich lang sind
    if (s1.length() != s2.length()) return false;
    // Sonst beide Listen parallel elementweise durchgehen
    ListElement* c1 = s1.first;
    ListElement* c2 = s2.first;
    // �ber Elementpaare iterieren, bis Ende der Listen erreicht ist
    for(; c1 != 0; ){
      // Listen sind ungleich, wenn Elemente eines Paares ungleich
      if (c1->content != c2->content) return false;
      // Sonst n�chstes Elementpaar ansehen
      c1 = c1->next;
      c2 = c2->next;
    }
    return true;
  }

  /// Test ob s1 kleiner als s2 ist. Es gibt hier z.B. die M�glichkeit,
  /// "lexikographisch kleiner" umzusetzen.
  friend bool operator<(const StringList& s1, const StringList& s2)
  {
    // s1 < s2, wenn s1 weniger Elemente als s2 enth�lt
    if (s1.length() < s2.length()) return true;
    // Wenn Listen gleich viele Elemente enthalten...
    if (s1.length() == s2.length()) {
      // Pr�fen, ob s1 "lexikographisch kleiner" als s2
      ListElement* c1 = s1.first;
      ListElement* c2 = s2.first;
      // Listen parallel elementweise durchgehen
      for(; c1 != 0; ){
        // Wenn Element aus s1 "gr��er" ist als Element aus s2,
        // ist s1 nicht kleiner als s2
        if (c1->content > c2->content) return false;
        // Wenn Element aus s1 "kleiner" ist als Element aus s2,
        // ist s1 kleiner als s2
        if (c1->content < c2->content) return true;
        // Sonst n�chstes Elementpaar ansehen
        c1 = c1->next;
        c2 = c2->next;
      }
      // Wenn Listen gleich sind, ist s1 nicht kleiner als s2
      return false;
    }
    else return false;
  }

  friend ostream& operator<<(ostream& o, const StringList& sl)
  {
    // Gescheitert, aber geht sicher irgendwie so?
    // o << sl.print();
    // return o;

    // Deshalb nochmal wie in print():
    o << "[";
    ListElement* c = sl.first;
    // Suche das Listenende (mit 0 markiert)
    while (c != 0) {
      // Gib den String aus
      if (c != sl.last) 
        o << c->content << ", ";
      else {o << c->content;}
      // Setze unsere Laufvariable c auf das, was in c->next steht
      c = c->next;
    } // while
    o << "]";
    return o;
  }

  /// F�gt einen String am Anfang der Liste an
  void append_front(const string& s)
  {
    // Erzeuge ein neues Listenelement und speichere es im Zeiger e
    ListElement* e = new ListElement;
    // Belege den String-Teil von e (besser: *e) mit s, dem hinzuzuf�genden String
    e->content = s;
    // Fallunterscheidung (ist aber tats�chlich unn�tig. Warum?)
    if (is_empty()) {
      // Die Liste war leer, hat also jetzt ihr erstes Element
      // e wird dieses erste Element
      first = last = e;
      // e ist gleichzeitig auch das letzte, indem wir e->next auf 0 setzen
      e->next = 0;
    }
    else {
      // Liste war nicht leer =>
      // Das alte erste Element wird das zweite, also Nachfolger von e
      e->next = first;
      // e wird das neue erste
      first = e;
    }
  }
  
  /// F�gt einen String am Ende der Liste an
  void append_back(const string& s)
  {
    if (is_empty()) {
      append_front(s);
    }
    else {
      // Erzeuge ein neues Listenelement und speichere es im Zeiger e
      ListElement* e = new ListElement;
      // Belege den String-Teil von e (besser: *e) mit s, dem hinzuzuf�genden String
      e->content = s;
      // Neues Element wird letztes Element und zeigt auf Listenende
      e->next = 0;
      // Letztes Element wird vorletztes Element und zeigt auf neues Element
      last->next = e;
      // Neues Element wird letztes Element
      last = e;
    }
  }
  
  /// Gibt den String am Kopf der Liste zur�ck, falls er existiert, sonst ...
  string head()
  {
  }
  
  /// L�scht alle Listenelemente und gibt den Speicher frei
  void clear()
  {
  // Liste elementweise durchgehen
  for(ListElement* c = first; c != 0; c = c->next){
      // Element zwischenspeichern
      ListElement* tmp = c;
      // Element l�schen
      delete tmp;
    }
    // Achtung: hier beim L�schen aufpassen
    first = last = 0;
  }
  
  /// Gibt die L�nge der Liste zur�ck
  // const, da const StringList& �bergeben wird
  unsigned length() const
  {
    unsigned len = 0;
    // Suche das Listenende (mit 0 markiert)
    for (ListElement* current = first; current != 0; current = current->next) {
      ++len;
    }
    return len;
  }
  
  /// Gibt true zur�ck, wenn die Liste leer ist, sonst false
  bool is_empty()
  {
    return first == 0;
  }
    
  /// Gibt die Liste auf cout aus
  void print() const
  {
    cout << "[";
    // Beginne am Anfang
    ListElement* c = first;
    // Suche das Listenende (mit 0 markiert)
    while (c != 0) {
      // Gib den String aus
      if (c != last) 
        cout << c->content << ", ";
      else {cout << c->content;}
      // Setze unsere Laufvariable current (die auf das aktuelle Element
      // verweist) auf das, was in current->next steht (also entweder das
      // Nachfolgerelement oder 0)
      c = c->next;
    } // while
    cout << "]";
  }
  
private: // Typen
  /// Typ eines Listenelements
  struct ListElement 
  {
    string content;  // der eigentliche Inhalt
    ListElement* next;    // die Verwaltung: Verweis auf das n�chste Element
  }; // ListElement
 
private:
  void init()
  {
    /// Wir setzen bei der leeren Liste first und last auf 0
    first = last = 0;
  }

private:
  /// first zeigt auf das erste Listenelement, falls es existiert
  ListElement* first;    
  /// last zeigt auf das letzte Listenelement, falls es existiert
  ListElement* last;    
}; // StringList