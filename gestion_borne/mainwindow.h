#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "borne.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_2_clicked();

    void on_tab_borne_activated(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Borne B;
};

#endif // MAINWINDOW_H
