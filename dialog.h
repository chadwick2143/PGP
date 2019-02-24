#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "keygen.h"
#include "encrypt.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_rbtn_1_clicked();
    void on_rbtn_2_clicked();
    void on_rbtn_3_clicked();
    void on_pbtn_1_clicked();
    void on_pbtn_2_clicked();

    void on_btn_plain_clicked();

    void on_btn_pubkey_clicked();

    void on_btn_idea_clicked();

    void on_btn_enc_clicked();

    void on_btn_cipher_clicked();

    void on_btn_prikey_clicked();

    void on_btn_key_clicked();

    void on_btn_dec_clicked();

private:
    Ui::Dialog *ui;
    keygen *genkey;
    encrypt *e;
};

#endif // DIALOG_H
