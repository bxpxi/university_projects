#pragma once
#include "service.h"
#include "observator.h"
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qmessagebox.h>
#include <qtablewidget.h>
#include <qdebug.h>
#include <QFormLayout>
#include <qfont.h>
#include <QTextEdit>
#include <vector>
#include <string>

class CosCRUDGUI : public QWidget, public Observator {
public:
    CosCRUDGUI(Service& service, CosCumparaturi& cos) : service{ service }, cos{ cos } {
        initGUI();
        loadData();
        initConnect();
    }

    void updateaza() override {
        loadData();
    }

private:
    Service& service;
    CosCumparaturi& cos;
    vector<Produs> produse;

    QListWidget* listaCumparaturi = new QListWidget{};
    QLineEdit* numarAdaugareRandomInCosEdit = new QLineEdit;
    QPushButton* butonGolireCos = new QPushButton{ "&Goleste cosul" };
    QPushButton* butonAdaugareRandomInCos = new QPushButton{ "&Adauga random in cos" };

    void initGUI() {
        auto layoutPrincipalCos = new QVBoxLayout{};
        auto layoutButoaneCosCumparaturi = new QHBoxLayout{};
        auto casetaAdaugareRandom = new QFormLayout;

        QLabel* textCosCumparaturi = new QLabel("Cos de inchirieri");

        casetaAdaugareRandom->addRow(numarAdaugareRandomInCosEdit);
        numarAdaugareRandomInCosEdit->setPlaceholderText("Introduceti un numar de produse");
        numarAdaugareRandomInCosEdit->setFixedWidth(185);

        layoutButoaneCosCumparaturi->addWidget(butonAdaugareRandomInCos);
        layoutButoaneCosCumparaturi->addWidget(butonGolireCos);

        setLayout(layoutPrincipalCos);

        layoutPrincipalCos->addWidget(textCosCumparaturi);
        layoutPrincipalCos->addWidget(listaCumparaturi);
        layoutPrincipalCos->addLayout(layoutButoaneCosCumparaturi);
        layoutPrincipalCos->addLayout(casetaAdaugareRandom);
    }

    void loadData() {
        listaCumparaturi->clear();
        for (const auto& produs : cos.getAllCosCumparaturi()) {
            QString item = QString::fromStdString(produs.getNumeProdus() + ", " + produs.getTipProdus() + ", " +
                std::to_string(produs.getPretProdus()) + ", " + produs.getProducatorProdus());
            listaCumparaturi->addItem(item);
        }
        produse.clear();
    }

    void initConnect() {
        cos.adaugaObservator(this);
        QObject::connect(butonGolireCos, &QPushButton::clicked, [&]() {
            service.golesteCosCumparaturi();
            loadData();
            });

        QObject::connect(butonAdaugareRandomInCos, &QPushButton::clicked, [&]() {
            produse = service.getAll();
            if (numarAdaugareRandomInCosEdit->text().toStdString() == "")
                QMessageBox::information(this, "Atentie!", "Introduceti un numar de produse de cumparat!");

            int numarDeProduseIntroduse = produse.size();
            if (numarAdaugareRandomInCosEdit->text().toInt() <= numarDeProduseIntroduse)
                cos.umpleRandomCosCumparaturi(numarAdaugareRandomInCosEdit->text().toInt(), produse);
            else
                QMessageBox::warning(this, "Atentie!", "Nu exista suficiente produse introduse!");
            loadData();
            });
    }

    ~CosCRUDGUI() {
        cos.stergeObservator(this);
    }
};