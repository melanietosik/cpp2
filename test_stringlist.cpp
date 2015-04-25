////////////////////////////////////////////////////////////////////////////////
// test_stringlist.cpp
// Test für verkettete Listen von Zeichenketten
// Melanie Tosik (759476)
////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>
using namespace std;

#include "stringlist.hpp"

int main() {
	cout << "\n" << "ZEICHENKETTENTEST!\n\n";

	cout << "Neue Liste l erzeugen...\n";
	StringList l;
	cout << "Ist anfangs noch leer: ";
	l.print();
	cout << "\n\n";

	cout << "Machen wir eine Einkaufsliste draus...\n\n";
	cout << "Butter und Zucker vorne dran...\n";
	l.append_front("Butter");
	l.append_front("Zucker");
	cout << "Tatsache: ";
	l.print();
	cout << "\n\n";

	cout << "Mehl und Ei nach hinten...\n";
	l.append_back("Mehl");
	l.append_back("Ei");
	cout << "Geht auch: ";
	l.print();
	cout << "\n\n";

	cout << "Kopieren wir l nach l2, für den Rest der Familie...\n";
	StringList l2(l);
	cout << "Ist kopiert: ";
	l2.print();
	cout << "\n\n";

	cout << "Radieren wir die Elemente aus l2 nochmal aus...\n\n";
	l2.clear();

	cout << "Liste auch wirklich leer?\n";
	if (l2.is_empty()) {
		cout << "Leer!\n";
	} else {
		cout << "Nicht leer!\n"; 
	}
	l2.print();
	cout << "\n\n";

	cout << "Und benutzen stattdessen den Zuweisungsoperator...\n";
	l2 = l;
	cout << "Da ist sie wieder: ";
	l2.print();
	cout << "\n\n";

	cout << "Wie viele Sachen brauchen wir jetzt nochmal?\n";
	cout << l2.length() << "\n\n";

	cout << "Waren die beiden Listen auch gleich?\n";
	if (l == l2) {
		cout << "Gleich!\n\n";
	} else {
		cout << "Nicht gleich!\n\n"; 
	}

	cout << "Oder ist l vielleicht kleiner als l2?\n";
	if (l < l2) {
		cout << "Kleiner!\n\n";
	} else {
		cout << "Nicht kleiner!\n\n"; 
	}

	cout << "Machen wir aus einem Ei doch besser mehrere Eier...\n\n";
	l2.clear();
	l2.append_back("Zucker");
	l2.append_back("Butter");
	l2.append_back("Mehl");
	l2.append_back("Eier");

	cout << "Erste Liste:\t";
	l.print();
	cout << "\n";
	cout << "Zweite Liste:\t";
	l2.print();
	cout << "\n\n";

	cout << "Sind die beiden Listen immer noch gleich?\n";
	if (l == l2) {
		cout << "Gleich!\n\n";
	} else {
		cout << "Nicht gleich!\n\n"; 
	}

	cout << "Oder ist l vielleicht kleiner als l2?\n";
	if (l < l2) {
		cout << "Kleiner!\n\n";
	} else {
		cout << "Nicht kleiner!\n\n"; 
	}

	cout << "Aber l2 ist hoffentlich nicht kleiner als l?\n";
	if (l2 < l) {
		cout << "Kleiner!\n\n";
	} else {
		cout << "Nicht kleiner!\n\n"; 
	}

	cout << "Hätte ich mir die ganze Printerei auch sparen können, und die Listen direkt ausgeben?\n\n";
	cout << l << "\n";
	cout << l2 << "\n\n";
	cout << "Sieht so aus!\n";
}