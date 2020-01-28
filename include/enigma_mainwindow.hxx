#ifndef ENIGMA_MAINWINDOW_HXX
#define ENIGMA_MAINWINDOW_HXX

#include <QMainWindow>
#include <map>

#include "Enigma.hxx"
#include "helpdialog.hxx"
#include "QKeyEvent"
#include "QDebug"
#include "QString"

QT_BEGIN_NAMESPACE
namespace Ui { class Enigma_MainWindow; }
QT_END_NAMESPACE

class Enigma_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Enigma_MainWindow(QWidget *parent = nullptr);
    ~Enigma_MainWindow();
    Enigma* enigma_m3 = new Enigma;
    QString current_cipher = "", current_phrase = "";
    void enter_letter(const char&);
    void update();

private slots:

    void keyPressEvent( QKeyEvent* event);

    void on_pushButton_Q_clicked();

    void on_pushButton_W_clicked();

    void on_pushButton_E_clicked();

    void on_pushButton_R_clicked();

    void on_pushButton_T_clicked();

    void on_pushButton_P_clicked();

    void on_pushButton_Z_clicked();

    void on_pushButton_U_clicked();

    void on_pushButton_I_clicked();

    void on_pushButton_O_clicked();

    void on_pushButton_A_clicked();

    void on_pushButton_S_clicked();

    void on_pushButton_D_clicked();

    void on_pushButton_F_clicked();

    void on_pushButton_G_clicked();

    void on_pushButton_H_clicked();

    void on_pushButton_J_clicked();

    void on_pushButton_K_clicked();

    void on_pushButton_Y_clicked();

    void on_pushButton_X_clicked();

    void on_pushButton_C_clicked();

    void on_pushButton_V_clicked();

    void on_pushButton_B_clicked();

    void on_pushButton_N_clicked();

    void on_pushButton_M_clicked();

    void on_pushButton_L_clicked();

    void on_verticalSlider_Left_valueChanged(int value);

    void on_verticalSlider_Middle_valueChanged(int value);

    void on_verticalSlider_Right_valueChanged(int value);

    void on_pushButton_clicked();

    void illuminate_letter(const char&);

    void on_pushButton_Help_clicked();

private:
    Ui::Enigma_MainWindow *ui;
    HelpDialog* help_window = new HelpDialog;
};
#endif // ENIGMA_MAINWINDOW_HXX
