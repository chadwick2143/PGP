#include "dialog.h"
#include "ui_dialog.h"
#include <QString>
#include <QFileDialog>
#include <QDir>
#include <ctime>

using namespace std;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    genkey = new keygen;
    e = new encrypt;

    QString homePath = QDir::homePath();

    this->ui->label_status_1->setText("");
    this->ui->label_status_2->setText("");
    this->ui->label_status_3->setText("");
    this->ui->ledt_1->setText(homePath);
    this->ui->ledt_pubkey->setText(homePath + "/public.key");
    this->ui->ledt_idea->setText(homePath);
    this->ui->ledt_prikey->setText(homePath + "/private.key");
    this->ui->ledt_key->setText(homePath + "/idea.key");

}

Dialog::~Dialog()
{
    delete ui;
    delete genkey;
}

//生成RSA密钥对
void Dialog::on_rbtn_1_clicked()
{
    QString s = this->ui->rbtn_1->text();
    unsigned int size = s.toUInt();
    genkey->setKeySize(size);
}
void Dialog::on_rbtn_2_clicked()
{
    QString s = this->ui->rbtn_2->text();
    unsigned int size = s.toUInt();
    genkey->setKeySize(size);
}
void Dialog::on_rbtn_3_clicked()
{
    QString s = this->ui->rbtn_3->text();
    unsigned int size = s.toUInt();
    genkey->setKeySize(size);
}

void Dialog::on_pbtn_1_clicked()
{
    QString homePath = QDir::homePath();
    QString dir = QFileDialog::getExistingDirectory(this, "Open Directory",
                                                      homePath,
                                                      QFileDialog::ShowDirsOnly
                                                      | QFileDialog::DontResolveSymlinks);


    this->ui->ledt_1->setText(dir);

    this->ui->label_status_1->setText("");
}

void Dialog::on_pbtn_2_clicked()
{
    if(this->ui->ledt_1->text()=="")
    {
        this->ui->label_status_1->setText("请选择密钥保存位置！");
    }
    else
    {
        clock_t start, end;
        start = clock();

        QString dir = this->ui->ledt_1->text();

        QString pubkeyPath = dir + "/public.key";
        QString prikeyPath = dir + "/private.key";

        genkey->setPubKeypath(pubkeyPath.toStdString());
        genkey->setPriKeypath(prikeyPath.toStdString());

        genkey->saveKey();

        end = clock();

        string m = "密钥已生成,用时" + to_string((end - start)/CLOCKS_PER_SEC) + "s";
        this->ui->label_status_1->setText(QString::fromStdString(m));
    }
}



//文件加密
void Dialog::on_btn_plain_clicked()
{
    QString homePath = QDir::homePath();
    QString s = QFileDialog::getOpenFileName(
                this,
                "Open a file",
                homePath);

    this->ui->ledt_plain->setText(s);
    this->ui->label_status_2->setText("");
}

void Dialog::on_btn_pubkey_clicked()
{
    QString homePath = QDir::homePath();
    QString s = QFileDialog::getOpenFileName(
                this,
                "Open a RSA key",
                homePath,
                "key files(*.key)");

    this->ui->ledt_pubkey->setText(s);
    this->ui->label_status_2->setText("");
}

void Dialog::on_btn_idea_clicked()
{
    QString homePath = QDir::homePath();
    QString s = QFileDialog::getExistingDirectory(this, "Open Directory",
                                                  homePath,
                                                  QFileDialog::ShowDirsOnly
                                                  | QFileDialog::DontResolveSymlinks);

    this->ui->ledt_idea->setText(s);
    this->ui->label_status_2->setText("");
}

void Dialog::on_btn_enc_clicked()
{
    if(this->ui->ledt_plain->text()=="")
        this->ui->label_status_2->setText("请选择文件！");
    else if(this->ui->ledt_pubkey->text()=="")
        this->ui->label_status_2->setText("请选择RSA公钥！");
    else if(this->ui->ledt_idea->text()=="")
        this->ui->label_status_2->setText("请选择对称密钥保存位置！");
    else
    {
        clock_t start, end;
        start = clock();

        //this->ui->label_status_2->setText("文件加密中...");

        string in = this->ui->ledt_plain->text().toStdString();
        string out = in + ".pgp";

        string pubkeyPath = this->ui->ledt_pubkey->text().toStdString();
        this->e->setpubkey(pubkeyPath);

        string dir = this->ui->ledt_idea->text().toStdString();
        this->e->setdir(dir);

        this->e->enc(in, out);

        end = clock();

        string m = "文件加密完成,用时" + to_string((end - start)/CLOCKS_PER_SEC) + "s";
        this->ui->label_status_2->setText(QString::fromStdString(m));
    }
}

//文件解密
void Dialog::on_btn_cipher_clicked()
{
    QString homePath = QDir::homePath();
    QString s = QFileDialog::getOpenFileName(
                this,
                "Open a file",
                homePath,
                "pgp files(*.pgp)");

    this->ui->ledt_cipher->setText(s);
    this->ui->label_status_3->setText("");
}

void Dialog::on_btn_prikey_clicked()
{
    QString homePath = QDir::homePath();
    QString s = QFileDialog::getOpenFileName(
                this,
                "Open a RSA key",
                homePath,
                "key files(*.key)");

    this->ui->ledt_prikey->setText(s);
    this->ui->label_status_3->setText("");
}

void Dialog::on_btn_key_clicked()
{
    QString homePath = QDir::homePath();
    QString s = QFileDialog::getOpenFileName(
                this,
                "Open a IDEA key",
                homePath,
                "key files(*.key)");

    this->ui->ledt_key->setText(s);
    this->ui->label_status_3->setText("");
}

void Dialog::on_btn_dec_clicked()
{
    if(this->ui->ledt_cipher->text()=="")
        this->ui->label_status_3->setText("请选择文件！");
    else if(this->ui->ledt_prikey->text()=="")
        this->ui->label_status_3->setText("请选择RSA私钥！");
    else if(this->ui->ledt_key->text()=="")
        this->ui->label_status_3->setText("请选择对称密钥！");
    else
    {
        clock_t start, end;
        start = clock();

        //this->ui->label_status_3->setText("文件解密中...");

        string in = this->ui->ledt_cipher->text().toStdString();
        string out(in.begin(), in.end()-4);

        string prikeyPath = this->ui->ledt_prikey->text().toStdString();
        this->e->setprikey(prikeyPath);

        string keypath = this->ui->ledt_key->text().toStdString();
        this->e->setkeyiv(keypath);

        this->e->dec(in, out);

        end = clock();

        string m = "文件解密完成，用时" + to_string((end - start)/CLOCKS_PER_SEC) + "s";
        this->ui->label_status_3->setText(QString::fromStdString(m));
    }
}
