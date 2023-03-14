#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"station.h"
#include <QMainWindow>

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

    void on_pb_supp_clicked();

    void on_pb_modifier_clicked();

    void on_le_id_tri_clicked();

    void on_le_nom_tri_clicked();

    void on_le_emp_tri_clicked();

    void on_tab_stat_activated(const QModelIndex &index);

    void on_le_recherhe_textChanged(const QString &arg1);

    void on_le_pdf_clicked();

    void on_le_stat_clicked();

    void on_le_map_clicked();


private:
    Ui::MainWindow *ui;
    station s;
};
#endif // MAINWINDOW_H
