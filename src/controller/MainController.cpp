#include "MainController.h"
#include <QTextStream>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QFileDialog>
#include <QMessageBox>
#include "../view/ui_MainWindow.h"

MainController::MainController(MainWindow* view, QObject* parent)
    : QObject(parent), m_view(view)
{
    auto ui = m_view->getUi();

    connect(ui->btnLoad, &QPushButton::clicked, this, &MainController::loadFile);
    connect(ui->btnSave, &QPushButton::clicked, this, &MainController::saveEncryptedFile);
    connect(ui->btnLoad_2, &QPushButton::clicked, this, &MainController::loadEncryptedFile);
    connect(ui->btnDecrypt, &QPushButton::clicked, this, &MainController::decryptText);
}

void MainController::loadFile()
{
    QString filename = QFileDialog::getOpenFileName(m_view, "Открыть текстовый файл", "", "Text Files (*.txt)");
    if (filename.isEmpty())
        return;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(m_view, "Ошибка", "Не удалось открыть файл.");
        return;
    }

    QTextStream in(&file);
    m_loadedText = in.readAll();
    file.close();

    m_view->getUi()->textEditMainEncrypt->setPlainText(m_loadedText);
}

void MainController::saveEncryptedFile()
{
    auto ui = m_view->getUi();
    QString message = ui->lineEditMessage->text();
    QString text = ui->textEditMainEncrypt->toPlainText();

    std::string result = SteganographyLogic::encrypt(text.toStdString(), message.toStdString(), 0);
    if (QString::fromStdString(result).startsWith("Error")) {
        QMessageBox::critical(m_view, "Ошибка шифрования", QString::fromStdString(result));
        return;
    }

    QString filename = QFileDialog::getSaveFileName(m_view, "Сохранить зашифрованный файл", "", "Text Files (*.txt)");
    if (filename.isEmpty())
        return;

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(m_view, "Ошибка", "Не удалось сохранить файл.");
        return;
    }

    QTextStream out(&file);
    out << QString::fromStdString(result);
    file.close();

    QMessageBox::information(m_view, "Успех", "Файл зашифрован и сохранен.");
}

void MainController::loadEncryptedFile()
{
    QString filename = QFileDialog::getOpenFileName(m_view, "Открыть зашифрованный файл", "", "Text Files (*.txt)");
    if (filename.isEmpty())
        return;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(m_view, "Ошибка", "Не удалось открыть зашифрованный файл.");
        return;
    }

    QTextStream in(&file);
    m_encryptedText = in.readAll();
    file.close();

    m_view->getUi()->textEditMainDecrypt->setPlainText(m_encryptedText);
}

void MainController::decryptText()
{
    auto ui = m_view->getUi();

    QString encryptedText = ui->textEditMainDecrypt->toPlainText();
    bool ok;
    int messageSize = ui->lineEditMsgLength->text().toInt(&ok);

    if (!ok || messageSize <= 0) {
        QMessageBox::warning(m_view, "Ошибка", "Введите корректную длину скрытого сообщения.");
        return;
    }

    std::string decrypted = SteganographyLogic::decrypt(encryptedText.toStdString(), messageSize, 0);
    ui->lineEditDecrypted->setText(QString::fromStdString(decrypted));
}