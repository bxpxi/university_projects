#include "teste.h"

void ruleazaTesteDomeniu() {
	Produs produs;

	produs.setTipProdus("bautura");
	assert(produs.getTipProdus() == "bautura");

	produs.setTipProdus("mancare");
	assert(produs.getTipProdus() == "mancare");

	produs.setPretProdus(5);
	assert(produs.getPretProdus() == 5);

	produs.setPretProdus(4);
	assert(produs.getPretProdus() == 4);

	produs.setProducatorProdus("dorna");
	assert(produs.getProducatorProdus() == "dorna");

	produs.setProducatorProdus("borsec");
	assert(produs.getProducatorProdus() == "borsec");
}

void testRepoAdauga() {
	Repo repository;
	Produs produs{ "apa", "bautura", 5, "dorna" };
	repository.adaugaProdus(produs);
	assert(repository.getAll().size() == 1);

	try {
		repository.adaugaProdus(produs);assert(false);
	}
	catch (const ExceptieRepo&) {
		assert(true);
	}

	try {
		repository.cautaProdus("suc");assert(false);
	}
	catch (const ExceptieRepo& eroare) {
		std::stringstream os;
		os << eroare;
		assert(os.str().find("adaugat") >= 0);
	}
}

void testRepoSterge() {
	Repo repository;
	Produs produs1{ "apa", "bautura", 5, "dorna" };
	repository.adaugaProdus(produs1);
	Produs produs2{ "suc", "bautura", 6, "prigat" };
	repository.adaugaProdus(produs2);
	Produs produs3{ "paine", "panificatie", 7, "dorbob" };
	repository.adaugaProdus(produs3);
	Produs produs4{ "chifla", "panificatie", 3, "dorbob" };
	repository.adaugaProdus(produs4);
	Produs produs5{ "mere", "fruct", 7, "merita" };
	repository.adaugaProdus(produs5);
	assert(repository.getAll().size() == 5);
	repository.stergeProdus(2);
	assert(repository.getAll().size() == 4);
	repository.stergeProdus(3);
}

void testRepoModifica() {
	Repo repository;
	Produs produs1{ "apa", "bautura", 5, "dorna" };
	repository.adaugaProdus(produs1);
	Produs produs2{ "suc", "bautura", 6, "prigat" };
	repository.adaugaProdus(produs2);
	Produs produs3{ "paine", "panificatie", 7, "dorbob" };
	repository.adaugaProdus(produs3);
	assert(repository.getAll().size() == 3);
	Produs produsModificat{ "paine", "panificatie", 12, "elidor" };
	repository.modificaProdus(produsModificat);
	assert(repository.getAll().size() == 3);
	assert(produsModificat.getProducatorProdus() == "elidor");
	Produs produsModificat1{ "chifla", "panificatie", 3, "dorbob" };
	try {
		repository.modificaProdus(produsModificat1);assert(false);
	}
	catch (ExceptieRepo&) {
		assert(true);
	}
}

void testRepoCauta() {
	Repo repository;
	Produs produs{ "chifla", "panificatie", 3, "dorbob" };
	repository.adaugaProdus(produs);
	auto produsCautat = repository.cautaProdus("chifla");
	assert(produsCautat.getNumeProdus() == produs.getNumeProdus());
	assert(produsCautat.getTipProdus() == produs.getTipProdus());
	assert(produsCautat.getPretProdus() == produs.getPretProdus());
	assert(produsCautat.getProducatorProdus() == produs.getProducatorProdus());

	try {
		repository.cautaProdus("suc");assert(false);
	}
	catch (ExceptieRepo&) {
		assert(true);
	}
}

void testRepoCautaPozitieDupaNume() {
	Repo repository;
	Produs produs1{ "apa", "bautura", 5, "dorna" };
	repository.adaugaProdus(produs1);
	Produs produs2{ "suc", "bautura", 6, "prigat" };
	repository.adaugaProdus(produs2);
	Produs produs3{ "paine", "panificatie", 7, "dorbob" };
	repository.adaugaProdus(produs3);
	const int pozitieGasita = repository.cautaPozitieDupaNume("suc");
	assert(pozitieGasita == 1);
	try {
		repository.cautaPozitieDupaNume("clementine");assert(false);
	}
	catch (ExceptieRepo&) {
		assert(true);
	}
}

void ruleazaTesteValidator() {
	Validator validator;
	Produs produsValid{ "paine", "panificatie", 7, "dorbob" };
	validator.valideaza(produsValid);
	Produs produsInvalid{ "", "", -1, "" };
	try {
		validator.valideaza(produsInvalid);assert(false);
	}
	catch (const ExceptieValidare& exceptie) {
		std::stringstream sout;
		sout << exceptie;
		assert(sout.str().find("invalid") >= 0);
	}
}

void testServiceAdauga() {
	Repo repository;
	Validator validator;
	CosCumparaturi cosCumparaturi;
	Service service{ repository, validator, cosCumparaturi };
	service.adaugaProdus("paine", "panificatie", 7, "dorbob");
	assert(service.getAll().size() == 1);

	try {
		service.adaugaProdus("", "", -1, "");assert(false);
	}
	catch (ExceptieValidare&) {
		assert(true);
	}

	try {
		service.adaugaProdus("paine", "panificatie", -8, "dorbob");assert(false);
	}
	catch (ExceptieValidare&) {
		assert(true);
	}
}

void testServiceSterge() {
	Repo repository;
	Validator validator;
	CosCumparaturi cosCumparaturi;
	Service service{ repository, validator, cosCumparaturi };
	service.adaugaProdus("apa", "bautura", 5, "dorna");
	service.adaugaProdus("suc", "bautura", 6, "prigat");
	service.adaugaProdus("paine", "panificatie", 7, "bunexim");
	service.adaugaProdus("chifla", "panificatie", 3, "dorbob");
	service.adaugaProdus("mere", "fruct", 8, "merita");
	assert(service.getAll().size() == 5);
	service.stergeProdus("apa");
	assert(service.getAll().size() == 4);

	try {
		service.stergeProdus("clementine");assert(false);
	}
	catch (ExceptieRepo&) {
		assert(true);
	}
}

void testServiceModifica() {
	Repo repository;
	Validator validator;
	CosCumparaturi cosCumparaturi;
	Service service{ repository, validator, cosCumparaturi };
	service.adaugaProdus("apa", "bautura", 5, "dorna");
	service.adaugaProdus("suc", "bautura", 6, "prigat");
	service.adaugaProdus("paine", "panificatie", 7, "bunexim");
	assert(service.getAll().size() == 3);
	service.modificaProdus("suc", "bautura", 7, "sprite");
	assert(service.getAll().size() == 3);
}

void testServiceCauta() {
	Repo repository;
	Validator validator;
	CosCumparaturi cosCumparaturi;
	Service service{ repository, validator, cosCumparaturi };
	service.adaugaProdus("apa", "bautura", 5, "dorna");
	service.adaugaProdus("suc", "bautura", 6, "prigat");
	service.adaugaProdus("paine", "panificatie", 7, "bunexim");
	assert(service.getAll().size() == 3);
	Produs produs = service.cautaProdus("apa");
	assert(produs.getNumeProdus() == "apa");
	assert(produs.getTipProdus() == "bautura");
	assert(produs.getPretProdus() == 5);
	assert(produs.getProducatorProdus() == "dorna");

	try {
		service.cautaProdus("clementine");assert(false);
	}
	catch (ExceptieRepo&) {
		assert(true);
	}
}

void testServiceFiltreazaDupaTipDupaPret() {
	Repo repository;
	Validator validator;
	CosCumparaturi cosCumparaturi;
	Service service{ repository, validator, cosCumparaturi };
	service.adaugaProdus("apa", "bautura", 5, "dorna");
	service.adaugaProdus("suc", "bautura", 6, "prigat");
	service.adaugaProdus("paine", "panificatie", 6, "bunexim");
	service.adaugaProdus("chifla", "panificatie", 3, "dorbob");
	service.adaugaProdus("mere", "fruct", 6, "merita");
	assert(service.getAll().size() == 5);

	vector<Produs> produseFiltrateDupaTip = service.filtreazaDupaTip("bautura");
	assert(produseFiltrateDupaTip.size() == 2);
	assert(produseFiltrateDupaTip[0].getNumeProdus() == "apa");
	assert(produseFiltrateDupaTip[1].getNumeProdus() == "suc");

	vector<Produs> filmeFiltrateDupaPret = service.filtreazaDupaPret(6);
	assert(filmeFiltrateDupaPret.size() == 3);
	assert(filmeFiltrateDupaPret[0].getNumeProdus() == "suc");
	assert(filmeFiltrateDupaPret[1].getNumeProdus() == "paine");
	assert(filmeFiltrateDupaPret[2].getNumeProdus() == "mere");
}

void testServiceSortari() {
	Repo repository;
	Validator validator;
	CosCumparaturi cosCumparaturi;
	Service service{ repository, validator, cosCumparaturi };
	service.adaugaProdus("apa", "bautura", 5, "dorna");
	service.adaugaProdus("suc", "bautura", 6, "prigat");
	service.adaugaProdus("paine", "panificatie", 7, "bunexim");
	service.adaugaProdus("chifla", "panificatie", 3, "dorbob");
	service.adaugaProdus("mere", "fruct", 8, "merita");
	assert(service.getAll().size() == 5);

	vector<Produs> produseSortateDupaNumeCrescator = service.sorteaza(1, 1);
	assert(produseSortateDupaNumeCrescator[0].getNumeProdus() == "apa");
	assert(produseSortateDupaNumeCrescator[1].getNumeProdus() == "chifla");
	assert(produseSortateDupaNumeCrescator[2].getNumeProdus() == "mere");
	assert(produseSortateDupaNumeCrescator[3].getNumeProdus() == "paine");
	assert(produseSortateDupaNumeCrescator[4].getNumeProdus() == "suc");

	vector<Produs> produseFiltrateDupaNumeDescrescator = service.sorteaza(1, 2);
	assert(produseFiltrateDupaNumeDescrescator[4].getNumeProdus() == "apa");
	assert(produseFiltrateDupaNumeDescrescator[3].getNumeProdus() == "chifla");
	assert(produseFiltrateDupaNumeDescrescator[2].getNumeProdus() == "mere");
	assert(produseFiltrateDupaNumeDescrescator[1].getNumeProdus() == "paine");
	assert(produseFiltrateDupaNumeDescrescator[0].getNumeProdus() == "suc");

	vector<Produs> produseFiltrateDupaProducatorCrescator = service.sorteaza(2, 1);
	assert(produseFiltrateDupaProducatorCrescator[0].getProducatorProdus() == "bunexim");
	assert(produseFiltrateDupaProducatorCrescator[1].getProducatorProdus() == "dorbob");
	assert(produseFiltrateDupaProducatorCrescator[2].getProducatorProdus() == "dorna");
	assert(produseFiltrateDupaProducatorCrescator[3].getProducatorProdus() == "merita");
	assert(produseFiltrateDupaProducatorCrescator[4].getProducatorProdus() == "prigat");

	vector<Produs> filmeFiltrateDupaProducatorDescrescator = service.sorteaza(2, 2);
	assert(filmeFiltrateDupaProducatorDescrescator[4].getProducatorProdus() == "bunexim");
	assert(filmeFiltrateDupaProducatorDescrescator[3].getProducatorProdus() == "dorbob");
	assert(filmeFiltrateDupaProducatorDescrescator[2].getProducatorProdus() == "dorna");
	assert(filmeFiltrateDupaProducatorDescrescator[1].getProducatorProdus() == "merita");
	assert(filmeFiltrateDupaProducatorDescrescator[0].getProducatorProdus() == "prigat");

	vector<Produs> produseFiltrateDupaPretSiTipCrescator = service.sorteaza(3, 1);
	assert(produseFiltrateDupaPretSiTipCrescator[0].getTipProdus() == "panificatie");
	assert(produseFiltrateDupaPretSiTipCrescator[1].getTipProdus() == "bautura");
	assert(produseFiltrateDupaPretSiTipCrescator[2].getTipProdus() == "bautura");
	assert(produseFiltrateDupaPretSiTipCrescator[3].getTipProdus() == "panificatie");
	assert(produseFiltrateDupaPretSiTipCrescator[4].getTipProdus() == "fruct");

	vector<Produs> produseFiltrateDupaPretSiTipDescrescator = service.sorteaza(3, 2);
	assert(produseFiltrateDupaPretSiTipDescrescator[4].getTipProdus() == "panificatie");
	assert(produseFiltrateDupaPretSiTipDescrescator[3].getTipProdus() == "bautura");
	assert(produseFiltrateDupaPretSiTipDescrescator[2].getTipProdus() == "bautura");
	assert(produseFiltrateDupaPretSiTipDescrescator[1].getTipProdus() == "panificatie");
	assert(produseFiltrateDupaPretSiTipDescrescator[0].getTipProdus() == "fruct");

	assert(produseFiltrateDupaPretSiTipCrescator[0].getPretProdus() == 3);
	assert(produseFiltrateDupaPretSiTipCrescator[1].getPretProdus() == 5);
	assert(produseFiltrateDupaPretSiTipCrescator[2].getPretProdus() == 6);
	assert(produseFiltrateDupaPretSiTipCrescator[3].getPretProdus() == 7);
	assert(produseFiltrateDupaPretSiTipCrescator[4].getPretProdus() == 8);

	assert(produseFiltrateDupaPretSiTipDescrescator[4].getPretProdus() == 3);
	assert(produseFiltrateDupaPretSiTipDescrescator[3].getPretProdus() == 5);
	assert(produseFiltrateDupaPretSiTipDescrescator[2].getPretProdus() == 6);
	assert(produseFiltrateDupaPretSiTipDescrescator[1].getPretProdus() == 7);
	assert(produseFiltrateDupaPretSiTipDescrescator[0].getPretProdus() == 8);
}

void testRepoCosCumparaturi() {
	CosCumparaturi cosCumparaturi;
	assert(cosCumparaturi.getAllCosCumparaturi().empty());

	// Test adaugaCosCumparaturi()
	Produs produs1("apa", "bautura", 5, "dorna");
	cosCumparaturi.adaugaCosCumparaturi(produs1);
	assert(cosCumparaturi.getAllCosCumparaturi().size() == 1);
	assert(cosCumparaturi.getAllCosCumparaturi()[0].getNumeProdus() == "apa");

	// Test golesteCosCumparaturi()
	cosCumparaturi.golesteCosCumparaturi();
	assert(cosCumparaturi.getAllCosCumparaturi().empty());

	// Test umpleRandomCosCumparaturi()
	vector<Produs> listaProduse = { Produs("apa", "bautura", 5, "dorna"),
								Produs("suc", "bautura", 6, "sprite"),
								Produs("chifla", "panificatie", 3, "dorbob"),
								Produs("paine", "panificatie", 8, "elidor"),
								Produs("mere", "fruct", 8, "merita") };

	// Test case 1: Umple cosul cu 3 produse random din lista de produse
	cosCumparaturi.umpleRandomCosCumparaturi(3, listaProduse);
	assert(cosCumparaturi.getAllCosCumparaturi().size() == 3);

	// Test case 2: Umple cosul cu un numar mai mare decat exista in lista de produse
	cosCumparaturi.umpleRandomCosCumparaturi(10, listaProduse);
	assert(cosCumparaturi.getAllCosCumparaturi().size() == 10);
}

void testAdaugaGolesteProdusInCosCumparaturi() {
	Repo repository;
	Validator validator;
	CosCumparaturi cosCumparaturi;
	Service service{ repository, validator, cosCumparaturi };

	service.adaugaProdus("apa", "bautura", 5, "dorna");
	const vector<Produs>& cosInitial = service.getAllCosCumparaturi();
	assert(cosInitial.empty());
	const vector<Produs>& cosModificat = service.adaugaProdusInCosCumparaturi("apa");
	assert(cosModificat.size() == 1);
	assert(cosModificat[0].getNumeProdus() == "apa");
	service.adaugaProdusInCosCumparaturi("apa");
	try {
		service.adaugaProdusInCosCumparaturi("apaaa");assert(false);
	}
	catch (ExceptieRepo&) {
		assert(true);
	}
	const vector<Produs>& cosGol = service.golesteCosCumparaturi();
	assert(cosGol.empty());
}

void testUmpleRandomCosCumparaturi() {
	Repo repository;
	Validator validator;
	CosCumparaturi cosInchirieri;
	Service service{ repository, validator, cosInchirieri };

	service.adaugaProdus("apa", "bautura", 5, "dorna");
	service.adaugaProdus("suc", "bautura", 6, "prigat");
	service.adaugaProdus("paine", "panificatie", 7, "bunexim");
	service.adaugaProdus("chifla", "panificatie", 3, "dorbob");

	service.umpleRandomCosCumparaturi(3);
	assert(cosInchirieri.getAllCosCumparaturi().size() == 3);

	vector<Produs> cosInchirieri2 = service.getAllCosCumparaturi();
	assert(cosInchirieri2.size() == 3);
}

void testExportaCSV() {
	Repo repository;
	Validator validator;
	CosCumparaturi cosCumparaturi;
	Service service{ repository, validator, cosCumparaturi };

	service.adaugaProdus("apa", "bautura", 5, "dorna");
	service.umpleRandomCosCumparaturi(2);
	const vector<Produs>& produse = service.getAllCosCumparaturi();
	service.exportaInCSV("testcsv.csv", produse);
	std::ifstream fin("testcsv.csv");
	string line;
	getline(fin, line);
	assert(line == "apa,bautura,5,dorna");
	fin.close();
	std::ofstream ofs("testcsv.csv", std::ios::trunc);
	ofs.close();
}

void testExportaHTML() {
	Repo repository;
	Validator validator;
	CosCumparaturi cosCumparaturi;
	Service service{ repository, validator, cosCumparaturi };

	service.adaugaProdus("apa", "bautura", 5, "dorna");
	service.umpleRandomCosCumparaturi(1);
	const vector<Produs>& produse = service.getAllCosCumparaturi();
	service.exportaInHTML("testhtml.html", produse);
	std::ifstream fin("testhtml.html");
	string line;
	getline(fin, line);
	assert(line == "<html><body>");
	getline(fin, line);
	assert(line == "<table border=\"1\" style=\"width:100 % \">");
	getline(fin, line);
	assert(line == "<tr>");
	getline(fin, line);
	assert(line == "<td>apa</td>");
	getline(fin, line);
	assert(line == "<td>bautura</td>");
	getline(fin, line);
	assert(line == "<td>5</td>");
	getline(fin, line);
	assert(line == "<td>dorna</td>");
	getline(fin, line);
	assert(line == "</tr>");
	getline(fin, line);
	assert(line == "</table>");
	getline(fin, line);
	assert(line == "</body></html>");
	fin.close();
	std::ofstream fout("testhtml.html", std::ios::trunc);
	fout.close();
}

void testExportaFilmeFisier() {
	try {
		RepoFile repositoryFileInexistent{ "abcd.txt" };assert(false);
	}
	catch (ExceptieRepo&) {
		assert(true);
	}

	Repo repository;
	RepoFile repositoryFile{ "produsetest.txt" };
	Validator validator;
	CosCumparaturi cosCumparaturi;
	Service service{ repositoryFile, validator, cosCumparaturi };
	Service serviceFile(repositoryFile, validator, cosCumparaturi);

	service.adaugaProdus("apa", "bautura", 5, "dorna");
	service.adaugaProdus("suc", "bautura", 6, "prigat");
	service.adaugaProdus("paine", "panificatie", 7, "bunexim");
	service.adaugaProdus("chifla", "panificatie", 3, "dorbob");
	service.adaugaProdus("mere", "fruct", 8, "merita");

	assert(repositoryFile.getAll().size() == 5);

	Produs produsModificatNumeInexistent{ "portocale", "fruct", 7, "abc" };
	try {
		repositoryFile.modificaProdus(produsModificatNumeInexistent);assert(false);
	}
	catch (ExceptieRepo&) {
		assert(true);
	}
	std::ofstream fout("produsetest.txt", std::ios::trunc);
	fout.close();
}

void testReadAllFromFile() {
	std::ofstream fout("filmetest.txt");
	fout << "apa\n";
	fout << "bautura\n";
	fout << "5\n";
	fout << "dorna\n";

	fout << "paine\n";
	fout << "panificatie\n";
	fout << "10\n";
	fout << "elidor\n";
	fout.close();

	RepoFile repositoryFile{ "filmetest.txt" };
	assert(repositoryFile.getAll().size() == 2);
	assert(repositoryFile.getAll()[0].getNumeProdus() == "apa");
	assert(repositoryFile.getAll()[0].getTipProdus() == "bautura");
	assert(repositoryFile.getAll()[0].getPretProdus() == 5);
	assert(repositoryFile.getAll()[0].getProducatorProdus() == "dorna");

	assert(repositoryFile.getAll()[1].getNumeProdus() == "paine");
	assert(repositoryFile.getAll()[1].getTipProdus() == "panificatie");
	assert(repositoryFile.getAll()[1].getPretProdus() == 10);
	assert(repositoryFile.getAll()[1].getProducatorProdus() == "elidor");

	std::ofstream out("filmetest.txt", std::ios::trunc);
	out.close();
}

void testUndo() {
	RepoFile repositoryFile{ "produsetest.txt" };
	Validator validator;
	CosCumparaturi cosCumparaturi;
	Service service{ repositoryFile, validator, cosCumparaturi };

	service.adaugaProdus("apa", "plata", 5, "dorna");
	assert(repositoryFile.getAll().size() == 1);
	service.modificaProdus("apa", "minerala", 4, "borsec");
	assert(repositoryFile.getAll().size() == 1);
	service.stergeProdus("apa");
	assert(repositoryFile.getAll().size() == 0);

	service.undo();
	assert(repositoryFile.getAll().size() == 1);
	assert(repositoryFile.getAll()[0].getNumeProdus() == "apa");
	assert(repositoryFile.getAll()[0].getTipProdus() == "minerala");
	assert(repositoryFile.getAll()[0].getPretProdus() == 4);
	assert(repositoryFile.getAll()[0].getProducatorProdus() == "borsec");

	service.undo();
	assert(repositoryFile.getAll().size() == 1);
	assert(repositoryFile.getAll()[0].getNumeProdus() == "apa");
	assert(repositoryFile.getAll()[0].getTipProdus() == "plata");
	assert(repositoryFile.getAll()[0].getPretProdus() == 5);
	assert(repositoryFile.getAll()[0].getProducatorProdus() == "dorna");

	service.undo();
	assert(repositoryFile.getAll().size() == 0);
}

void ruleazaTesteCosCumparaturi() {
	testRepoCosCumparaturi();
	testAdaugaGolesteProdusInCosCumparaturi();
	testUmpleRandomCosCumparaturi();
	testExportaCSV();
	testExportaHTML();
}

void ruleazaTesteRepo() {
	testRepoAdauga();
	testRepoSterge();
	testRepoModifica();
	testRepoCauta();
	testRepoCautaPozitieDupaNume();
	testExportaFilmeFisier();
	testReadAllFromFile();
}

void ruleazaTesteService() {
	testServiceAdauga();
	testServiceSterge();
	testServiceModifica();
	testServiceCauta();
	testServiceFiltreazaDupaTipDupaPret();
	testServiceSortari();
	testUndo();
}

void ruleazaToateTestele() {
	ruleazaTesteDomeniu();
	ruleazaTesteRepo();
	ruleazaTesteValidator();
	ruleazaTesteService();
	ruleazaTesteCosCumparaturi();
}
