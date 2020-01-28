#include "enigma_mainwindow.hxx"
#include "ui_enigma_mainwindow.h"

Enigma_MainWindow::Enigma_MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Enigma_MainWindow)
{
    ui->setupUi(this);
}

void Enigma_MainWindow::update()
{
    ui->InputWindow->setPlainText(current_phrase);
    ui->OutputWindow->setPlainText(current_cipher);
}

void Enigma_MainWindow::enter_letter(const char& letter)
{
    const char encoded_letter = enigma_m3->type_letter(letter);
    illuminate_letter(encoded_letter);
    current_phrase += QString(letter);
    current_cipher += QString(encoded_letter);
    update();
}

void Enigma_MainWindow::keyPressEvent(QKeyEvent* event)
{
    std::map<int, char> _press_to_char = {{Qt::Key_A, 'A'},
                                          {Qt::Key_B, 'B'},
                                          {Qt::Key_C, 'C'},
                                          {Qt::Key_D, 'D'},
                                          {Qt::Key_E, 'E'},
                                          {Qt::Key_F, 'F'},
                                          {Qt::Key_G, 'G'},
                                          {Qt::Key_H, 'H'},
                                          {Qt::Key_I, 'I'},
                                          {Qt::Key_J, 'J'},
                                          {Qt::Key_K, 'K'},
                                          {Qt::Key_L, 'L'},
                                          {Qt::Key_M, 'M'},
                                          {Qt::Key_N, 'N'},
                                          {Qt::Key_O, 'O'},
                                          {Qt::Key_P, 'P'},
                                          {Qt::Key_Q, 'Q'},
                                          {Qt::Key_R, 'R'},
                                          {Qt::Key_S, 'S'},
                                          {Qt::Key_T, 'T'},
                                          {Qt::Key_U, 'U'},
                                          {Qt::Key_V, 'V'},
                                          {Qt::Key_W, 'W'},
                                          {Qt::Key_X, 'X'},
                                          {Qt::Key_Y, 'Y'},
                                          {Qt::Key_Z, 'Z'}
    					 };
    if(_press_to_char.count(event->key()) > 0)
    {
        enter_letter(_press_to_char[event->key()]);
    }
}

void Enigma_MainWindow::illuminate_letter(const char& letter)
{
    std::map<char,QRadioButton*> _char_to_radiob = {{'A', ui->radioButton_A},
                                                    {'B', ui->radioButton_B},
                                                    {'C', ui->radioButton_C},
                                                    {'D', ui->radioButton_D},
                                                    {'E', ui->radioButton_E},
                                                    {'F', ui->radioButton_F},
                                                    {'G', ui->radioButton_G},
                                                    {'H', ui->radioButton_H},
                                                    {'I', ui->radioButton_I},
                                                    {'J', ui->radioButton_J},
                                                    {'K', ui->radioButton_K},
                                                    {'L', ui->radioButton_L},
                                                    {'M', ui->radioButton_M},
                                                    {'N', ui->radioButton_N},
                                                    {'O', ui->radioButton_O},
                                                    {'P', ui->radioButton_P},
                                                    {'Q', ui->radioButton_Q},
                                                    {'R', ui->radioButton_R},
                                                    {'S', ui->radioButton_S},
                                                    {'T', ui->radioButton_T},
                                                    {'U', ui->radioButton_U},
                                                    {'W', ui->radioButton_W},
                                                    {'X', ui->radioButton_X},
                                                    {'Y', ui->radioButton_Y},
                                                    {'Z', ui->radioButton_Z}
                                                   };
    if(_char_to_radiob.count(letter) == 0) return;

    _char_to_radiob[letter]->setChecked(true);
}

Enigma_MainWindow::~Enigma_MainWindow()
{
    delete ui;
}

void Enigma_MainWindow::on_pushButton_Q_clicked()
{
    enter_letter('Q');
}

void Enigma_MainWindow::on_pushButton_W_clicked()
{
    enter_letter('W');
}

void Enigma_MainWindow::on_pushButton_E_clicked()
{
    enter_letter('E');
}

void Enigma_MainWindow::on_pushButton_R_clicked()
{
    enter_letter('R');
}

void Enigma_MainWindow::on_pushButton_T_clicked()
{
    enter_letter('T');
}


void Enigma_MainWindow::on_pushButton_P_clicked()
{
    enter_letter('P');
}

void Enigma_MainWindow::on_pushButton_Z_clicked()
{
    enter_letter('Z');
}

void Enigma_MainWindow::on_pushButton_U_clicked()
{
    enter_letter('U');
}

void Enigma_MainWindow::on_pushButton_I_clicked()
{
    enter_letter('I');
}

void Enigma_MainWindow::on_pushButton_O_clicked()
{
    enter_letter('O');
}

void Enigma_MainWindow::on_pushButton_A_clicked()
{
    enter_letter('A');
}

void Enigma_MainWindow::on_pushButton_S_clicked()
{
    enter_letter('S');
}

void Enigma_MainWindow::on_pushButton_D_clicked()
{
    enter_letter('D');
}

void Enigma_MainWindow::on_pushButton_F_clicked()
{
    enter_letter('F');
}

void Enigma_MainWindow::on_pushButton_G_clicked()
{
    enter_letter('G');
}

void Enigma_MainWindow::on_pushButton_H_clicked()
{
    enter_letter('P');
}

void Enigma_MainWindow::on_pushButton_J_clicked()
{
    enter_letter('J');
}

void Enigma_MainWindow::on_pushButton_K_clicked()
{
    enter_letter('K');
}

void Enigma_MainWindow::on_pushButton_Y_clicked()
{
    enter_letter('Y');
}

void Enigma_MainWindow::on_pushButton_X_clicked()
{
    enter_letter('X');
}

void Enigma_MainWindow::on_pushButton_C_clicked()
{
    enter_letter('C');
}

void Enigma_MainWindow::on_pushButton_V_clicked()
{
    enter_letter('V');
}

void Enigma_MainWindow::on_pushButton_B_clicked()
{
    enter_letter('B');
}

void Enigma_MainWindow::on_pushButton_N_clicked()
{
    enter_letter('N');
}

void Enigma_MainWindow::on_pushButton_M_clicked()
{
    enter_letter('M');
}

void Enigma_MainWindow::on_pushButton_L_clicked()
{
    enter_letter('L');
}

void Enigma_MainWindow::on_verticalSlider_Left_valueChanged(int value)
{
    const char letter_l = enigma_m3->getAlphabetVector()[value];
    ui->plainTextEdit_Left->setPlainText(QString(letter_l));
    const char letter_m = enigma_m3->getAlphabetVector()[ui->verticalSlider_Middle->value()];
    const char letter_r = enigma_m3->getAlphabetVector()[ui->verticalSlider_Right->value()];
    const std::string key = std::string(1, letter_l)+std::string(1, letter_m)+std::string(1, letter_r);
    enigma_m3->set_key(key);
}

void Enigma_MainWindow::on_verticalSlider_Middle_valueChanged(int value)
{
    const char letter_m = enigma_m3->getAlphabetVector()[value];
    ui->plainTextEdit_Middle->setPlainText(QString(letter_m));
    const char letter_l = enigma_m3->getAlphabetVector()[ui->verticalSlider_Left->value()];
    const char letter_r = enigma_m3->getAlphabetVector()[ui->verticalSlider_Right->value()];
    const std::string key = std::string(1, letter_l)+std::string(1, letter_m)+std::string(1, letter_r);
    enigma_m3->set_key(key);
}

void Enigma_MainWindow::on_verticalSlider_Right_valueChanged(int value)
{
    const char letter_r = enigma_m3->getAlphabetVector()[value];
    ui->plainTextEdit_Right->setPlainText(QString(letter_r));
    const char letter_m = enigma_m3->getAlphabetVector()[ui->verticalSlider_Middle->value()];
    const char letter_l = enigma_m3->getAlphabetVector()[ui->verticalSlider_Left->value()];
    const std::string key = std::string(1, letter_l)+std::string(1, letter_m)+std::string(1, letter_r);
    enigma_m3->set_key(key);
}

void Enigma_MainWindow::on_pushButton_clicked()
{
    enigma_m3->reset();
    ui->OutputWindow->clear();
    ui->InputWindow->clear();
    current_phrase = "";
    current_cipher = "";
}

void Enigma_MainWindow::on_pushButton_Help_clicked()
{
       help_window->show();
}
