#include "src/messagedialog.h"
#include "ui_messagedialog.h"

MessageDialog::MessageDialog(QWidget *parent, QString text) :
    QDialog(parent),
    ui(new Ui::MessageDialog)
{
    ui->setupUi(this);
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(close()));

    ui->messageLabel->setText(text);
}

MessageDialog::~MessageDialog()
{
    delete ui;
}
