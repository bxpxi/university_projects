#include "validator.h"
#include <sstream>

void Validator::valideaza(const Produs& produs) {
    vector<string> mesajEroare;
    if (produs.getNumeProdus().empty()) mesajEroare.push_back("Nume invalid!\n");
    if (produs.getTipProdus().empty()) mesajEroare.push_back("Tip invalid!\n");
    if (produs.getPretProdus() < 0) mesajEroare.push_back("Pret invalid!\n");
    if (produs.getProducatorProdus().empty()) mesajEroare.push_back("Producator invalid!\n");
    if (!mesajEroare.empty()) {
        throw ExceptieValidare(mesajEroare);
    }
}

ostream& operator<<(ostream& out, const ExceptieValidare& exceptie) {
    for (const auto& mesaj : exceptie.mesajEroare) {
        out << mesaj << " ";
    }
    return out;
}