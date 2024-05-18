#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lab1314.h"

class Lab1314 : public QMainWindow
{
    Q_OBJECT

public:
    Lab1314(QWidget *parent = nullptr);
    ~Lab1314();

private:
    Ui::Lab1314Class ui;
};
