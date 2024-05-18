#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab11_FINALLL.h"

class lab11_FINALLL : public QMainWindow
{
    Q_OBJECT

public:
    lab11_FINALLL(QWidget *parent = nullptr);
    ~lab11_FINALLL();

private:
    Ui::lab11_FINALLLClass ui;
};
