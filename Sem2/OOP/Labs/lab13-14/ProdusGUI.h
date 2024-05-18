#pragma once
#include "service.h"
#include "CosCRUDGUI.h"
#include "CosReadOnlyGUI.h"
#include <QApplication>
#include <QTextEdit>
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
#include <qmainwindow.h>
#include <qmenubar.h>
#include <qcombobox.h>
#include <qheaderview.h>
#include <qtablewidget.h>
#include <qfont.h>
#include <qscrollarea.h>
#include <qsplitter.h>
#include <vector>
#include <string>

using std::vector;
using std::string;


class ProdusGUI : public QWidget {
public:
    ProdusGUI(Service& service, CosCumparaturi& cos) : service{ service }, cos{ cos } {
        initGUI();
        loadData();
        initConnect();
    }
private:
    Service& service;
    CosCumparaturi cos;
    vector<Produs> produse;

    //unordered_map<string, QPushButton*>typeButtons;

    //QListWidget* listaProduse = new QListWidget{};
    QScrollArea* scrollArea = new QScrollArea();
    QTableWidget* tabelProduse = new QTableWidget();
    QListWidget* listaCumparaturi = new QListWidget{};

    //QListWidget* lista = new QListWidget;

    QLineEdit* numeEdit = new QLineEdit;
    QLineEdit* tipEdit = new QLineEdit;
    QLineEdit* pretEdit = new QLineEdit;
    QLineEdit* producatorEdit = new QLineEdit;

    QLineEdit* numarAdaugareRandomInCosEdit = new QLineEdit;
    QLineEdit* numeFisierCSV = new QLineEdit;
    QLineEdit* numeFisierHTML = new QLineEdit;

    QPushButton* butonStergereNume = new QPushButton{ "&Sterge" };
    QPushButton* butonStergereTip = new QPushButton{ "&Sterge" };
    QPushButton* butonStergerePret = new QPushButton{ "&Sterge" };
    QPushButton* butonStergereProducator = new QPushButton{ "&Sterge" };
    QPushButton* butonStergere = new QPushButton{ "&Sterge toate campurile" };

    QPushButton* butonExit = new QPushButton{ "&Exit" };
    QPushButton* butonAdauga = new QPushButton{ "&Adauga" };
    QPushButton* butonSterge = new QPushButton{ "&Sterge" };
    QPushButton* butonModifica = new QPushButton{ "&Modifica" };
    QPushButton* butonCauta = new QPushButton{ "&Cauta" };
    QPushButton* butonFiltreaza = new QPushButton{ "&Filtreaza" };
    QPushButton* butonSorteaza = new QPushButton{ "&Sorteaza" };
    QPushButton* butonUndo = new QPushButton{ "&Undo" };

    QPushButton* butonAdaugareInCos = new QPushButton{ "&Adauga in cos" };
    QPushButton* butonStergereDinCos = new QPushButton{ "&Sterge din cos" };
    QPushButton* butonGolireCos = new QPushButton{ "&Goleste cosul" };
    QPushButton* butonAdaugareRandomInCos = new QPushButton{ "&Adauga random in cos" };

    QPushButton* butonExportInCSV = new QPushButton{ "&Exporta cosul in CSV" };
    QPushButton* butonExportInHTML = new QPushButton{ "&Exporta cosul in HTML" };

    QPushButton* butonCosCRUDGUI = new QPushButton{ "&CosCRUDGUI" };
    QPushButton* butonCosReadOnlyGUI = new QPushButton{ "&CosReadOnlyGUI" };

    QLabel* numarProduseLabel = new QLabel("Numar de produse: ");
    QString numarProduse = QString::number(service.getAll().size());

    //QVBoxLayout* layoutDreapta = new QVBoxLayout;
    //QHBoxLayout* layoutButoaneCerintaLab = new QHBoxLayout;

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

        //it2
        /*
        QObject::connect(listaProduse, &QListWidget::itemClicked, [&](QListWidgetItem* item) {
            QString itemText = item->text();
            QStringList parti = itemText.split(", ");
            QString numeProdus = parti[0];
            QString tipProdus = parti[1];
            int pretProdus = parti[2].toInt();
            QString producatorProdus = parti[3];

            numeEdit->setText(numeProdus);
            tipEdit->setText(tipProdus);
            pretEdit->setText(QString::fromStdString(std::to_string(pretProdus)));
            producatorEdit->setText(producatorProdus);
            });
        */

        QObject::connect(tabelProduse, &QTableWidget::itemClicked, [&](QTableWidgetItem* item) {
            QString numeProdus = tabelProduse->item(item->row(), 0)->text();
            QString tipProdus = tabelProduse->item(item->row(), 1)->text();
            int pretProdus = tabelProduse->item(item->row(), 2)->text().toInt();
            QString producatorProdus = tabelProduse->item(item->row(), 3)->text();

            numeEdit->setText(numeProdus);
            tipEdit->setText(tipProdus);
            pretEdit->setText(QString::number(pretProdus));
            producatorEdit->setText(producatorProdus);
            });

        QObject::connect(listaCumparaturi, &QListWidget::itemClicked, [&](QListWidgetItem* item) {
            QString itemText = item->text();
            QStringList parti = itemText.split(", ");
            QString numeProdus = parti[0];
            QString tipProdus = parti[1];
            int pretProdus = parti[2].toInt();
            QString producatorProdus = parti[3];

            numeEdit->setText(numeProdus);
            tipEdit->setText(tipProdus);
            pretEdit->setText(QString::fromStdString(std::to_string(pretProdus)));
            producatorEdit->setText(producatorProdus);
            });

        QObject::connect(butonStergereNume, &QPushButton::clicked, [&]() {
            numeEdit->setText("");
            });

        QObject::connect(butonStergereTip, &QPushButton::clicked, [&]() {
            tipEdit->setText("");
            });

        QObject::connect(butonStergerePret, &QPushButton::clicked, [&]() {
            pretEdit->setText("");
            });

        QObject::connect(butonStergereProducator, &QPushButton::clicked, [&]() {
            producatorEdit->setText("");
            });

        QObject::connect(butonStergere, &QPushButton::clicked, [&]() {
            numeEdit->setText("");
            tipEdit->setText("");
            pretEdit->setText("");
            producatorEdit->setText("");
            });

        QObject::connect(butonAdaugareInCos, &QPushButton::clicked, [&]() {
            auto numeProdus = numeEdit->text().toStdString();

            if (numeProdus.empty()) {
                QMessageBox::information(this, "Ceva nu a mers bine!", "Ceva nu a mers bine!");
                return;
            }

            try {
                auto iterator = service.cautaProdus(numeProdus);
            }
            catch (ExceptieRepo& exceptie) {
                QMessageBox::warning(this, "Atentie!", "Produsul nu este disponibil!");
                return;
            }

            for (const auto& produs : service.getAllCosCumparaturi()) {
                if (numeProdus == produs.getNumeProdus()) {
                    QMessageBox::warning(this, "Atentie!", "Produsul este deja in cos!");
                    break;
                }
            }

            try {
                service.adaugaProdusInCosCumparaturi(numeProdus);
            }
            catch (ExceptieCosProduse& exceptie) {
                QMessageBox::warning(this, "Atentie!", QString::fromStdString(exceptie.getMesaj()));
                return;
            }
            updateListaInchirieri();
            });

        QObject::connect(butonStergereDinCos, &QPushButton::clicked, [&]() {
            auto numeProdus = numeEdit->text().toStdString();

            if (numeProdus.empty()) {
                QMessageBox::information(this, "Ceva nu a mers bine!", "Ceva nu a mers bine!");
                return;
            }

            try {
                service.stergeProdusDinCosCumparaturi(numeProdus);
            }
            catch (ExceptieCosProduse& exceptie) {
                QMessageBox::warning(this, "Atentie!", QString::fromStdString(exceptie.getMesaj()));
            }
            updateListaInchirieri();
            });

        QObject::connect(butonGolireCos, &QPushButton::clicked, [&]() {
            service.golesteCosCumparaturi();
            updateListaInchirieri();
            });

        QObject::connect(butonAdaugareRandomInCos, &QPushButton::clicked, [&]() {
            if (numarAdaugareRandomInCosEdit->text().toStdString() == "")
                QMessageBox::information(this, "Atentie!", "Introduceti un numar de produse de cumparat!");

            int numarDeProduseIntroduse = service.getAll().size();
            if (numarAdaugareRandomInCosEdit->text().toInt() <= numarDeProduseIntroduse)
                service.umpleRandomCosCumparaturi(numarAdaugareRandomInCosEdit->text().toInt());
            else
                QMessageBox::warning(this, "Atentie!", "Nu exista suficiente produse introduse!");
            updateListaInchirieri();
            });

        QObject::connect(butonExportInCSV, &QPushButton::clicked, [&]() {
            if (numeFisierCSV->text().toStdString() == "") {
                QMessageBox::information(this, "Atentie!", "Introduceti un nume de fisier cu extensia .csv!");
                return;
            }

            int numarDeProduseIntroduse = service.getAll().size();
            try {
                service.exportaInCSV(numeFisierCSV->text().toStdString(), service.getAllCosCumparaturi());
            }
            catch (ExceptieRepo& exceptie) {
                QMessageBox::warning(this, "Atentie!", QString::fromStdString(exceptie.getMesaj()));
            }
            updateListaInchirieri();
            });

        QObject::connect(butonExportInHTML, &QPushButton::clicked, [&]() {
            if (numeFisierHTML->text().toStdString() == "") {
                QMessageBox::information(this, "Atentie!", "Introduceti un nume de fisier cu extensia .html!");
                return;
            }

            int numarDeProduseIntroduse = service.getAll().size();
            try {
                service.exportaInHTML(numeFisierHTML->text().toStdString(), service.getAllCosCumparaturi());
            }
            catch (ExceptieRepo& exceptie) {
                QMessageBox::warning(this, "Atentie!", QString::fromStdString(exceptie.getMesaj()));
            }
            updateListaInchirieri();
            });

        QObject::connect(butonCosCRUDGUI, &QPushButton::clicked, [&]() {
            CosCRUDGUI* cosCRUDGUI = new CosCRUDGUI(service, cos);
            cosCRUDGUI->setAttribute(Qt::WA_DeleteOnClose);
            cosCRUDGUI->show();
            });

        QObject::connect(butonCosReadOnlyGUI, &QPushButton::clicked, [&]() {
            CosReadOnlyGUI* cosReadOnlyGUI = new CosReadOnlyGUI(cos);
            cosReadOnlyGUI->setAttribute(Qt::WA_DeleteOnClose);
            cosReadOnlyGUI->show();
            });

    }

    void updateListaInchirieri() {
        listaCumparaturi->clear();
        for (const auto& produs : service.getAllCosCumparaturi()) {
            QString item = QString::fromStdString(produs.getNumeProdus() + ", " + produs.getTipProdus() + ", " +
                std::to_string(produs.getPretProdus()) + ", " + produs.getProducatorProdus());
            listaCumparaturi->addItem(item);
        }
    }

    void loadData() {
        tabelProduse->clearContents();
        tabelProduse->setRowCount(0);
        //listaProduse->clear();

        //lista->clear();
        auto produse = service.getAll();

        //unordered_map<string, int>typeCount;
        for (const auto& produs : produse) {
            int row = tabelProduse->rowCount();
            tabelProduse->insertRow(row);

            QTableWidgetItem* numeItem = new QTableWidgetItem(QString::fromStdString(produs.getNumeProdus()));
            QTableWidgetItem* tipItem = new QTableWidgetItem(QString::fromStdString(produs.getTipProdus()));
            QTableWidgetItem* pretItem = new QTableWidgetItem(QString::number(produs.getPretProdus()));
            QTableWidgetItem* producatorItem = new QTableWidgetItem(QString::fromStdString(produs.getProducatorProdus()));

            tabelProduse->setItem(row, 0, numeItem);
            tabelProduse->setItem(row, 1, tipItem);
            tabelProduse->setItem(row, 2, pretItem);
            tabelProduse->setItem(row, 3, producatorItem);
        }
        /*
            QString itemText = QString::fromStdString(produs.getNumeProdus() + ", " + produs.getTipProdus() + ", " +
                std::to_string(produs.getPretProdus()) + ", " + produs.getProducatorProdus());
            QListWidgetItem* listItem = new QListWidgetItem(itemText);
            listaProduse->addItem(listItem);

            //typeCount[produs.getTipProdus()]++;
        */

            for (int column = 0; column < tabelProduse->columnCount() - 1; ++column) {
                tabelProduse->horizontalHeader()->setSectionResizeMode(column, QHeaderView::ResizeToContents);
            }
            tabelProduse->horizontalHeader()->setSectionResizeMode(tabelProduse->columnCount() - 1, QHeaderView::Stretch);


            int numarProduse = service.getAll().size();
            numarProduseLabel->setText("Numar de produse: " + QString::number(numarProduse));
        
    }

    void initGUI() {
        QHBoxLayout* layoutPrincipal = new QHBoxLayout{};
        //QHBoxLayout* Secundar = new QHBoxLayout{};
        auto layoutDreapta = new QVBoxLayout;
        auto layoutStanga = new QVBoxLayout;
        //auto LayoutNou = new QVBoxLayout;
        auto layoutDreaptaSus = new QVBoxLayout;
        auto layoutDreaptaCentru = new QVBoxLayout;
        auto layoutDreaptaCentruJos = new QVBoxLayout;
        auto layoutDreaptaJos = new QVBoxLayout;

        setLayout(layoutPrincipal);

        //Layout Stanga
        auto layoutLista = new QHBoxLayout{};
        //auto layoutLista2 = new QVBoxLayout{};
        //listaProduse = new QListWidget{}; // Create the QListWidget
        //layoutDreapta->addWidget(listaProduse); // Add it to the layout

        tabelProduse->setColumnCount(4);
        tabelProduse->setHorizontalHeaderLabels(QStringList() << "Nume" << "Tip" << "Pret" << "Producator");

        numarProduseLabel->setText("Numar poduse: " + numarProduse);
        layoutStanga->addWidget(tabelProduse, 1);
        layoutStanga->addWidget(numarProduseLabel);

        //Layout Dreapta Sus
        auto formLayout = new QFormLayout;
        formLayout->addRow("Nume", numeEdit);
        formLayout->addRow("Tip", tipEdit);
        formLayout->addRow("Pret", pretEdit);
        formLayout->addRow("Producator", producatorEdit);

        QFont fontText = tabelProduse->font();
        fontText.setPointSize(12);
        numeEdit->setFont(fontText), tipEdit->setFont(fontText), pretEdit->setFont(fontText), producatorEdit->setFont(fontText);

        auto butoaneStergereLayout = new QVBoxLayout;
        butoaneStergereLayout->addWidget(butonStergereNume);
        butoaneStergereLayout->addWidget(butonStergereTip);
        butoaneStergereLayout->addWidget(butonStergerePret);
        butoaneStergereLayout->addWidget(butonStergereProducator);
        butoaneStergereLayout->addWidget(butonStergere);

        QFont fontButoaneStergere = tabelProduse->font();
        fontButoaneStergere.setPointSize(10);
        butonStergereNume->setFont(fontButoaneStergere), butonStergereTip->setFont(fontButoaneStergere), butonStergerePret->setFont(fontButoaneStergere), butonStergereProducator->setFont(fontButoaneStergere);

        auto layoutButoaneCerintaLab = new QHBoxLayout{};

        /*map<string, int> dictFilme;
        auto filme = service.getAll();
        for (const auto& film : filme) {
            QString item = QString::fromStdString(film.getGenFilm());
            if (dictFilme[item.toStdString()] == 0) {
                QPushButton* buton = new QPushButton{ item };
                QObject::connect(buton, &QPushButton::clicked, [this, dictFilme, item]() {
                    auto filmeDupaGen = service.filtreazaDupaGen(item.toStdString());
                    string numarFilme = std::to_string(filmeDupaGen.size());
                    QMessageBox::warning(this, "Numar de filme", "Numarul de filme este: " + QString::fromStdString(numarFilme));
                });
                layoutButoaneCerintaLab->addWidget(buton);
            }
            dictFilme[item.toStdString()] ++;
        }*/

        //Layout Dreapta Centru
        auto layoutButoaneCosCumparaturi = new QHBoxLayout{};
        auto casetaAdaugareRandom = new QFormLayout;

        QLabel* textCosCumparaturi = new QLabel("Cos de cumparaturi");
        layoutDreaptaCentru->addWidget(textCosCumparaturi);
        QFont fontTextCosCumparaturi = tabelProduse->font();
        fontTextCosCumparaturi.setPointSize(18);
        textCosCumparaturi->setFont(fontTextCosCumparaturi);
        textCosCumparaturi->setAlignment(Qt::AlignCenter);

        casetaAdaugareRandom->addRow(numarAdaugareRandomInCosEdit);
        numarAdaugareRandomInCosEdit->setPlaceholderText("Introduceti un numar de produse");
        numarAdaugareRandomInCosEdit->setFixedWidth(185);
        casetaAdaugareRandom->setContentsMargins(380, 0, 0, 0);

        layoutButoaneCosCumparaturi->addWidget(butonAdaugareInCos);
        layoutButoaneCosCumparaturi->addWidget(butonStergereDinCos);
        layoutButoaneCosCumparaturi->addWidget(butonAdaugareRandomInCos);
        layoutButoaneCosCumparaturi->addWidget(butonGolireCos);

        //Layout Exporturi
        auto layoutButoaneExporturi = new QHBoxLayout{};
        auto layoutCaseteTextFisiereExport = new QHBoxLayout{};
        auto casetaNumeFisierCSV = new QFormLayout;
        auto casetaNumeFisierHTML = new QFormLayout;

        casetaNumeFisierCSV->addRow(numeFisierCSV);
        casetaNumeFisierHTML->addRow(numeFisierHTML);
        numeFisierCSV->setPlaceholderText("Introduceti fisier.csv");
        numeFisierCSV->setFixedWidth(185);
        numeFisierHTML->setPlaceholderText("Introduceti fisier.html");
        numeFisierHTML->setFixedWidth(185);

        layoutButoaneExporturi->addWidget(butonExportInCSV);
        layoutButoaneExporturi->addWidget(butonExportInHTML);
        layoutCaseteTextFisiereExport->addLayout(casetaNumeFisierCSV);
        layoutCaseteTextFisiereExport->addLayout(casetaNumeFisierHTML);

        //Layout Ferestre Observer
        auto layoutButoaneObserver = new QHBoxLayout{};
        layoutButoaneObserver->addWidget(butonCosCRUDGUI);
        layoutButoaneObserver->addWidget(butonCosReadOnlyGUI);

        //Layout Dreapta Jos
        auto layoutButoaneAdaugareStergereModificareCautare = new QHBoxLayout{};
        auto layoutButoaneFiltrareSortare = new QHBoxLayout{};
        auto layoutButoaneUndoExit = new QHBoxLayout{};
        auto formLayoutCuButoane = new QHBoxLayout{};

        layoutButoaneAdaugareStergereModificareCautare->addWidget(butonAdauga);
        layoutButoaneAdaugareStergereModificareCautare->addWidget(butonSterge);
        layoutButoaneAdaugareStergereModificareCautare->addWidget(butonModifica);
        layoutButoaneAdaugareStergereModificareCautare->addWidget(butonCauta);
        layoutButoaneFiltrareSortare->addWidget(butonFiltreaza);
        layoutButoaneFiltrareSortare->addWidget(butonSorteaza);
        layoutButoaneUndoExit->addWidget(butonUndo);
        layoutButoaneUndoExit->addWidget(butonExit);

        QFont fontButoane = tabelProduse->font();
        fontButoane.setPointSize(10);
        butonAdauga->setFont(fontButoane), butonSterge->setFont(fontButoane), butonModifica->setFont(fontButoane), butonCauta->setFont(fontButoane);
        butonFiltreaza->setFont(fontButoane), butonSorteaza->setFont(fontButoane), butonUndo->setFont(fontButoane), butonExit->setFont(fontButoane);


        QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
        splitter->setOpaqueResize(false);
        layoutPrincipal->addWidget(splitter);
        QWidget* widgetStanga = new QWidget();
        widgetStanga->setLayout(layoutStanga);
        QWidget* widgetDreapta = new QWidget();
        widgetDreapta->setLayout(layoutDreapta);
        splitter->addWidget(widgetStanga);
        splitter->addWidget(widgetDreapta);
        splitter->setStretchFactor(0, 1);


        formLayoutCuButoane->addLayout(formLayout);
        formLayoutCuButoane->addLayout(butoaneStergereLayout);
        layoutDreaptaSus->addLayout(formLayoutCuButoane);
        layoutDreaptaSus->addStretch();

        layoutDreaptaCentru->addWidget(listaCumparaturi);
        layoutDreaptaCentru->addLayout(layoutButoaneCosCumparaturi);
        layoutDreaptaCentru->addLayout(casetaAdaugareRandom);

        layoutDreaptaCentruJos->addLayout(layoutButoaneExporturi);
        layoutDreaptaCentruJos->addLayout(layoutCaseteTextFisiereExport);

        layoutDreaptaJos->addStretch();
        layoutDreaptaJos->addLayout(layoutButoaneAdaugareStergereModificareCautare);
        layoutDreaptaJos->addLayout(layoutButoaneFiltrareSortare);
        layoutDreaptaJos->addLayout(layoutButoaneUndoExit);
        //QListWidget* listaProduse = new QListWidget{};

        layoutLista->addLayout(layoutStanga);
        layoutLista->addLayout(layoutDreapta);

        layoutDreapta->addLayout(layoutDreaptaSus);
        layoutDreapta->addLayout(layoutDreaptaCentru);
        layoutDreapta->addLayout(layoutDreaptaCentruJos);
        layoutDreapta->addLayout(layoutButoaneObserver);
        //layoutDreapta->addLayout(layoutButoaneCerintaLab);
        layoutDreapta->addLayout(layoutDreaptaJos);

        layoutPrincipal->addLayout(layoutLista);
        //Secundar->addLayout(layoutLista2);

    }

};


