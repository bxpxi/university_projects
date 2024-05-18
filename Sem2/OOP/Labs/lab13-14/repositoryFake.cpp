#include "repositoryFake.h"

const vector<Produs>& RepositoryFake::getAll() const noexcept {
	static vector<Produs> produse;
	produse.clear();
	if (caz == 1) {
		produse.push_back(Produs("Capsuni", "Fructe", 20, "Export"));
		return produse;
	}
	else if (caz == 2) {
		produse.push_back(Produs("Apa", "Bautura", 5, "Dorna"));
		produse.push_back(Produs("Suc", "Bautura", 10, "Prigat"));
		produse.push_back(Produs("Cartofi", "Legume", 3, "Import"));
		return produse;
	}
}