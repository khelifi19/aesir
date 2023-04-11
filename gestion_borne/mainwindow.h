#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "borne.h"
#include <QSystemTrayIcon>

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




    void on_tri_voltage_clicked();

    void on_trie_type_clicked();

    void on_le_recherche_textChanged(const QString &arg1);

    void on_pdf_clicked();

    void on_statistique_clicked();



    void on_pushButton_clicked();

    void on_le_supp_clicked();

private:
    Ui::MainWindow *ui;
    Borne B;
private:
    QSystemTrayIcon *trayIcon;
};

#endif // MAINWINDOW_H
