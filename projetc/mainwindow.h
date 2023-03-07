#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"employee.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_tab_employe_activated(const QModelIndex &index);

    void on_pb_modifier_clicked();

    void on_tri_id_clicked();

    void on_tri_nom_clicked();

    void on_tri_cin_clicked();

private:
    Ui::MainWindow *ui;
    Employee E;

};
#endif // MAINWINDOW_H
