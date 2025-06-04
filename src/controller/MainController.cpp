#include "MainController.h"
#include <QTextStream>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QFileDialog>
#include <QMessageBox>

MainController::MainController(MainWindow* view, QObject* parent)
    : QObject(parent), m_view(view)
{
    connect(view->findChild<QPushButton*>("btnLoad"), &QPushButton::clicked, this, &MainController::loadFile);
    connect(view->findChild<QPushButton*>("btnSave"), &QPushButton::clicked, this, &MainController::saveEncryptedFile);
    connect(view->findChild<QPushButton*>("btnLoadEncrypted"), &QPushButton::clicked, this, &MainController::loadEncryptedFile);
    connect(view->findChild<QPushButton*>("btnDecrypt"), &QPushButton::clicked, this, &MainController::decryptText);
}

void MainController::loadFile()
{
    QString filename = QFileDialog::getOpenFileName(m_view, "Open Text File", "", "Text Files (*.txt)");
    if (filename.isEmpty())
        return;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(m_view, "Error", "Cannot open file.");
        return;
    }

    QTextStream in(&file);
    m_loadedText = in.readAll();
    file.close();

    m_view->findChild<QTextEdit*>("textEditInput")->setPlainText(m_loadedText);
}

void MainController::saveEncryptedFile()
{
    QString message = m_view->findChild<QLineEdit*>("lineEditMessage")->text();
    QString text = m_view->findChild<QTextEdit*>("textEditInput")->toPlainText();

    std::string result = SteganographyLogic::encrypt(text.toStdString(), message.toStdString(), 0);
    if (QString::fromStdString(result).startsWith("Error"))
    {
        QMessageBox::critical(m_view, "Encryption Error", QString::fromStdString(result));
        return;
    }

    QString filename = QFileDialog::getSaveFileName(m_view, "Save Encrypted File", "", "Text Files (*.txt)");
    if (filename.isEmpty())
        return;

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(m_view, "Error", "Cannot save file.");
        return;
    }

    QTextStream out(&file);
    out << QString::fromStdString(result);
    file.close();

    QMessageBox::information(m_view, "Success", "Encrypted file saved.");
}

void MainController::loadEncryptedFile()
{
    QString filename = QFileDialog::getOpenFileName(m_view, "Open Encrypted Text File", "", "Text Files (*.txt)");
    if (filename.isEmpty()) return;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(m_view, "Error", "Cannot open encrypted file.");
        return;
    }

    QTextStream in(&file);
    m_encryptedText = in.readAll();
    file.close();

    m_view->findChild<QTextEdit*>("textEditMainDecrypt")->setPlainText(m_encryptedText);
}

void MainController::decryptText()
{
    QString encryptedText = m_view->findChild<QTextEdit*>("textEditMainDecrypt")->toPlainText();
    bool ok;
    int messageSize = m_view->findChild<QLineEdit*>("lineEditMsgLength")->text().toInt(&ok);

    if (!ok || messageSize <= 0) {
        QMessageBox::warning(m_view, "Error", "Invalid message size entered");
        return;
    }

    std::string decryptedResult = SteganographyLogic::decrypt(encryptedText.toStdString(), messageSize, 0);

    m_view->findChild<QLineEdit*>("lineEditDecrypted")->setText(QString::fromStdString(decryptedResult));
}