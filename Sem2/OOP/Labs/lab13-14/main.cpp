#include "Lab1314.h"
#include "CosReadOnlyGUI.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QFormLayout>
#include <iostream>
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
#include <qfont.h>
#include <QGraphicsOpacityEffect>
#include <qpropertyanimation.h>
#include <qstackedlayout.h>
#include <qpalette.h>
#include <QRandomGenerator>
#include <QTimer>
#include "consola.h"
#include <iostream>
#include "domain.h"
#include "repo.h"
#include "validator.h"
#include "cos.h"
#include "service.h"
#include "ProdusGUI.h"

using std::vector;
using std::string;


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QMainWindow fereastraPrincipala;

    fereastraPrincipala.setWindowTitle("Magazin");
    fereastraPrincipala.showMaximized();
    fereastraPrincipala.setMinimumSize(1250, 850);

    //QPixmap backgroundImage("magazin.jpg");
    //backgroundImage = backgroundImage.scaled(fereastraPrincipala.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    //QPalette palette;
    //palette.setBrush(QPalette::Window, backgroundImage);
    //fereastraPrincipala.setPalette(palette);

    QPushButton* butonPornire = new QPushButton("Intrati in magazin", &fereastraPrincipala);
    QLabel* textAplicatiaMea = new QLabel("Aplicatie magazin", &fereastraPrincipala);
    textAplicatiaMea->setAlignment(Qt::AlignCenter);

    QFont fontButonPornire = textAplicatiaMea->font();
    fontButonPornire.setPointSize(20);
    butonPornire->setFont(fontButonPornire);

    QFont fontText = textAplicatiaMea->font();
    fontText.setPointSize(30);
    fontText.setBold(true);
    textAplicatiaMea->setFont(fontText);

    //Adaugam widgets la widgetPrincipal
    QVBoxLayout* layoutPrincipal = new QVBoxLayout(&fereastraPrincipala);
    layoutPrincipal->addWidget(textAplicatiaMea, 0, Qt::AlignCenter);
    layoutPrincipal->addWidget(butonPornire, 0, Qt::AlignCenter);

    QWidget* widgetPrincipal = new QWidget(&fereastraPrincipala);
    widgetPrincipal->setLayout(layoutPrincipal);
    fereastraPrincipala.setCentralWidget(widgetPrincipal);


    //Afisam fereastra
    Repo repository;
    RepoFile repositoryFile{ "produse.txt" };
    Validator validator;
    CosCumparaturi cosCumparaturi;
    Service service{ repositoryFile, validator, cosCumparaturi };
    ProdusGUI* gui = new ProdusGUI{ service, cosCumparaturi };

    QObject::connect(butonPornire, &QPushButton::clicked, [&]() {

        gui->showMaximized();
        gui->setAttribute(Qt::WA_DeleteOnClose);
        gui->show();

        fereastraPrincipala.hide();
        });

    QFont font("Comic Sans MS");
    app.setFont(font);

    fereastraPrincipala.show();

    return app.exec();
}
