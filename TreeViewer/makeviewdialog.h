#pragma once

#include <QDialog>

namespace Ui {
class MakeViewDialog;
}

class MakeViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MakeViewDialog(QString databaseId = "db", QWidget *parent = nullptr);
    ~MakeViewDialog();

private:
    Ui::MakeViewDialog *ui;
    QString mDatabaseId;
};

