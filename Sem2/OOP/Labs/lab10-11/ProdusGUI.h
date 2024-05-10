#pragma once
#include "service.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QFormLayout>
#include <qdebug.h>
#include <qmessagebox.h>
#include <vector>
#include <string>

using std::vector;
using std::string;

class ProdusGUI : public QWidget {
public:
    ProdusGUI(Service& service) : service{ service } {
        initGUI();
        loadData();
        initConnect();
    }
private:
    Service& service;
    vector<Produs> produse;

    QListWidget* lista = new QListWidget;

    QLineEdit* numeEdit = new QLineEdit;
    QLineEdit* tipEdit = new QLineEdit;
    QLineEdit* pretEdit = new QLineEdit;
    QLineEdit* producatorEdit = new QLineEdit;

    QPushButton* butonExit = new QPushButton{ "&Exit" };
    QPushButton* butonAdauga = new QPushButton{ "&Adauga" };
    QPushButton* butonSterge = new QPushButton{ "&Sterge" };
    QPushButton* butonModifica = new QPushButton{ "&Modifica" };
    QPushButton* butonCauta = new QPushButton{ "&Cauta" };
    QPushButton* butonFiltreaza = new QPushButton{ "&Filtreaza" };
    QPushButton* butonSorteaza = new QPushButton{ "&Sorteaza" };
    QPushButton* butonUndo = new QPushButton{ "&Undo" };

    QPushButton* butonBautura = new QPushButton{ "&Bautura" };
    QPushButton* butonPanificatie = new QPushButton{ "&Panificatie" };
    QPushButton* butonFructe = new QPushButton{ "&Fructe" };
    QPushButton* butonLegume = new QPushButton{ "&Legume" };

    void initConnect() {
        QObject::connect(butonExit, &QPushButton::clicked, []() {
            qApp->quit();
            });
        QObject::connect(butonAdauga, &QPushButton::clicked, [&]() {
            auto numeProdus = numeEdit->text().toStdString();
            auto tipProdus = tipEdit->text().toStdString();
            auto pretProdus = pretEdit->text().toInt();
            auto producatorProdus = producatorEdit->text().toStdString();

            if (numeProdus.empty() || tipProdus.empty() || !pretProdus || producatorProdus.empty()) {
                QMessageBox::information(this, "Ceva nu a mers bine!", "Ceva nu a mers bine!");
                return;
            }

            try {
                service.adaugaProdus(numeProdus, tipProdus, pretProdus, producatorProdus);
            }
            catch (ExceptieRepo& exceptie) {
                QMessageBox::warning(this, "Atentie!", QString::fromStdString(exceptie.getMesaj()));
            }
            catch (ExceptieValidare& exceptie) {
                QMessageBox::warning(this, "Atentie!", QString::fromStdString(exceptie.getMesaj()[0]));
            }

            loadData();
            });

        QObject::connect(butonSterge, &QPushButton::clicked, [&]() {
            auto numeProdus = numeEdit->text().toStdString();

            if (numeProdus.empty()) {
                QMessageBox::information(this, "Ceva nu a mers bine!", "Ceva nu a mers bine!");
                return;
            }

            try {
                service.stergeProdus(numeProdus);
            }
            catch (ExceptieRepo& exceptie) {
                QMessageBox::warning(this, "Atentie!", QString::fromStdString(exceptie.getMesaj()));
            }
            catch (ExceptieValidare& exceptie) {
                QMessageBox::warning(this, "Atentie!", QString::fromStdString(exceptie.getMesaj()[0]));
            }

            loadData();
            });

        QObject::connect(butonModifica, &QPushButton::clicked, [&]() {
            auto numeProdus = numeEdit->text().toStdString();
            auto tipProdus = tipEdit->text().toStdString();
            auto pretProdus = pretEdit->text().toInt();
            auto producatorProdus = producatorEdit->text().toStdString();

            if (numeProdus.empty() || tipProdus.empty() || !pretProdus || producatorProdus.empty()) {
                QMessageBox::information(this, "Ceva nu a mers bine!", "Ceva nu a mers bine!");
                return;
            }

            try {
                service.modificaProdus(numeProdus, tipProdus, pretProdus, producatorProdus);
            }
            catch (ExceptieRepo& exceptie) {
                QMessageBox::warning(this, "Atentie!", QString::fromStdString(exceptie.getMesaj()));
            }
            catch (ExceptieValidare& exceptie) {
                QMessageBox::warning(this, "Atentie!", QString::fromStdString(exceptie.getMesaj()[0]));
            }

            loadData();
            });

        QObject::connect(butonCauta, &QPushButton::clicked, [&]() {
            QDialog* dialogCautare = new QDialog(this);
            QVBoxLayout* layoutDialog = new QVBoxLayout(dialogCautare);
            QPushButton* butonCautareDialog = new QPushButton{ "&Cauta" };

            QLineEdit* lineEditNume = new QLineEdit(dialogCautare);
            QListWidget* listaProduse = new QListWidget(dialogCautare);

            layoutDialog->addWidget(new QLabel("Nume:", dialogCautare));
            layoutDialog->addWidget(lineEditNume);
            layoutDialog->addWidget(listaProduse);
            layoutDialog->addWidget(butonCautareDialog);

            QObject::connect(butonCautareDialog, &QPushButton::clicked, [=]() {
                if (lineEditNume->text() != "") {
                    try {
                        auto produs = service.cautaProdus(lineEditNume->text().toStdString());
                        listaProduse->clear();
                        QString item = QString::fromStdString(produs.getNumeProdus() + ", " + produs.getTipProdus() + ", " +
                            std::to_string(produs.getPretProdus()) + ", " + produs.getProducatorProdus());
                        listaProduse->addItem(item);
                    }
                    catch (ExceptieRepo& exceptie) {
                        QMessageBox::warning(this, "Atentie!", QString::fromStdString(exceptie.getMesaj()));
                    }
                    catch (ExceptieValidare& exceptie) {
                        QMessageBox::warning(this, "Atentie!", QString::fromStdString(exceptie.getMesaj()[0]));
                    }
                }
                });
            dialogCautare->show();
            });

        QObject::connect(butonFiltreaza, &QPushButton::clicked, [&]() {
            QDialog* dialogFiltrare = new QDialog(this);
            QVBoxLayout* layoutDialog = new QVBoxLayout(dialogFiltrare);
            QPushButton* butonFiltrareDialog = new QPushButton{ "&Filtreaza" };

            QLineEdit* lineEditTip = new QLineEdit(dialogFiltrare);
            QLineEdit* lineEditPret = new QLineEdit(dialogFiltrare);
            QListWidget* listaProduse = new QListWidget(dialogFiltrare);

            layoutDialog->addWidget(new QLabel("Tip:", dialogFiltrare));
            layoutDialog->addWidget(lineEditTip);
            layoutDialog->addWidget(new QLabel("Pret:", dialogFiltrare));
            layoutDialog->addWidget(lineEditPret);
            layoutDialog->addWidget(listaProduse);
            layoutDialog->addWidget(butonFiltrareDialog);

            QObject::connect(butonFiltrareDialog, &QPushButton::clicked, [=]() {
                if (lineEditTip->text() != "" && lineEditPret->text() == "") {
                    auto produse = service.filtreazaDupaTip(lineEditTip->text().toStdString());
                    listaProduse->clear();
                    for (const auto& produs : produse) {
                        QString item = QString::fromStdString(produs.getNumeProdus() + ", " + produs.getTipProdus() + ", " +
                            std::to_string(produs.getPretProdus()) + ", " + produs.getProducatorProdus());
                        listaProduse->addItem(item);
                    }
                }
                if (lineEditTip->text() == "" && lineEditPret->text() != "") {
                    auto produse = service.filtreazaDupaPret(lineEditPret->text().toInt());
                    listaProduse->clear();
                    for (const auto& produs : produse) {
                        QString item = QString::fromStdString(produs.getNumeProdus() + ", " + produs.getTipProdus() + ", " +
                            std::to_string(produs.getPretProdus()) + ", " + produs.getProducatorProdus());
                        listaProduse->addItem(item);
                    }
                }
                });
            dialogFiltrare->show();
            });

        QObject::connect(butonSorteaza, &QPushButton::clicked, [&]() {
            QDialog* dialogSortare = new QDialog(this);
            QVBoxLayout* layoutDialog = new QVBoxLayout(dialogSortare);
            QPushButton* butonSortareDialog = new QPushButton{ "&Sorteaza" };

            QLineEdit* lineEditReperSortare = new QLineEdit(dialogSortare);
            QLineEdit* lineEditOrdineSortare = new QLineEdit(dialogSortare);
            QListWidget* listaProduse = new QListWidget(dialogSortare);

            layoutDialog->addWidget(new QLabel("Sortare dupa (1 -> nume / 2 -> producator / 3 -> tip+pret):", dialogSortare));
            layoutDialog->addWidget(lineEditReperSortare);
            layoutDialog->addWidget(new QLabel("Ordine sortare (1 -> crescator / 2 -> descrescator):", dialogSortare));
            layoutDialog->addWidget(lineEditOrdineSortare);
            layoutDialog->addWidget(listaProduse);
            layoutDialog->addWidget(butonSortareDialog);

            QObject::connect(butonSortareDialog, &QPushButton::clicked, [=]() {
                if (lineEditReperSortare->text() != "" && lineEditOrdineSortare->text() != "") {
                    auto produse = service.sorteaza(lineEditReperSortare->text().toInt(), lineEditOrdineSortare->text().toInt());
                    listaProduse->clear();
                    for (const auto& produs : produse) {
                        QString item = QString::fromStdString(produs.getNumeProdus() + ", " + produs.getTipProdus() + ", " +
                            std::to_string(produs.getPretProdus()) + ", " + produs.getProducatorProdus());
                        listaProduse->addItem(item);
                    }
                }
                });
            dialogSortare->show();
            });

        QObject::connect(butonUndo, &QPushButton::clicked, [&]() {
            try {
                service.undo();
            }
            catch (ExceptieRepo& exceptie) {
                QMessageBox::warning(this, "Atentie!", QString::fromStdString(exceptie.getMesaj()));
            }
            catch (ExceptieValidare& exceptie) {
                QMessageBox::warning(this, "Atentie!", QString::fromStdString(exceptie.getMesaj()[0]));
            }
            loadData();
            });
    }

    void loadData() {
        lista->clear();
        auto produse = service.getAll();
        for (const auto& produs : produse) {
            QString item = QString::fromStdString(produs.getNumeProdus() + ", " + produs.getTipProdus() + ", " +
                std::to_string(produs.getPretProdus()) + ", " + produs.getProducatorProdus());
            lista->addItem(item);
        }
    }

    void initGUI() {
        QHBoxLayout* layoutPrincipal = new QHBoxLayout{};
        setLayout(layoutPrincipal);

        layoutPrincipal->addWidget(lista);

        auto layoutDreapta = new QVBoxLayout;

        auto formLayout = new QFormLayout;
        formLayout->addRow("Nume", numeEdit);
        formLayout->addRow("Tip", tipEdit);
        formLayout->addRow("Pret", pretEdit);
        formLayout->addRow("Producator", producatorEdit);
        layoutDreapta->addLayout(formLayout);

        auto layoutButoaneCerintaLab = new QHBoxLayout{};

        /*
        map<string, int> dictProduse;
        auto produse = service.getAll();
        for (const auto& produs : produse) {
            QString item = QString::fromStdString(produs.getTipProdus());
            if (dictProduse[item.toStdString()] == 0) {
                QPushButton* buton = new QPushButton{ item };
                QObject::connect(buton, &QPushButton::clicked, [&]() {
                    QMessageBox::warning(this, "Numar de filme", "Numarul de filme este: " + QString::fromStdString(dictProduse[item.toStdString()]));
                    });
                layoutButoaneCerintaLab->addWidget(buton);
            }
            dictProduse[item.toStdString()] ++;
        }
        */

        auto layoutButoane = new QHBoxLayout{};
        layoutButoane->addWidget(butonAdauga);
        layoutButoane->addWidget(butonSterge);
        layoutButoane->addWidget(butonModifica);
        layoutButoane->addWidget(butonCauta);
        layoutButoane->addWidget(butonFiltreaza);
        layoutButoane->addWidget(butonSorteaza);
        layoutButoane->addWidget(butonUndo);
        layoutButoane->addWidget(butonExit);

        layoutDreapta->addLayout(layoutButoaneCerintaLab);
        layoutDreapta->addLayout(layoutButoane);
        layoutPrincipal->addLayout(layoutDreapta);


    }
};