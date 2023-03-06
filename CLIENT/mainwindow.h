#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSqlQuery>
#include <QSqlIndex>
#include<QString>
#include <QMainWindow>
#include "client.h"
#include <cctype>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();
    void on_tab_client_activated(const QModelIndex &index);

    void on_pb_modifier_clicked();

    void on_tri_id_clicked();

    void on_tri_nom_clicked();

    void on_tri_date_clicked();

private:
    Ui::MainWindow *ui;
    Client C;
};

#endif // MAINWINDOW_H
