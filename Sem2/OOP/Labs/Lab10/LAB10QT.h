#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LAB10QT.h"

class LAB10QT : public QMainWindow
{
    Q_OBJECT

public:
    LAB10QT(QWidget *parent = nullptr);
    ~LAB10QT();

private:
    Ui::LAB10QTClass ui;
};
