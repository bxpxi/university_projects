#include "LAB10QT.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QFormLayout>
#include "domain.h"
#include "repo.h"
#include "validator.h"
#include "cos.h"
#include "service.h"
#include "ProdusGUI.h"

using std::vector;
using std::string;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Repo repository;
    RepoFile repositoryFile{ "produse.txt" };
    Validator validator;
    CosCumparaturi cosCumparaturi;
    Service service{ repositoryFile, validator, cosCumparaturi };
    ProdusGUI gui{ service };
    gui.show();

    return app.exec();
}
