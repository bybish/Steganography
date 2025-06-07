#include "MainController.h"
#include "../view/MainWindow.h"
#include "../view/ui_MainWindow.h"
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>

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
    if (filename.isEmpty()) return;

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

    try {
        std::string encrypted = SteganographyLogic::encrypt(
            text.toStdString(),
            message.toStdString()
        );

        QString filename = QFileDialog::getSaveFileName(m_view, "Сохранить зашифрованный файл", "", "Text Files (*.txt)");
        if (filename.isEmpty()) return;

        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(m_view, "Ошибка", "Не удалось сохранить файл.");
            return;
        }

        QTextStream out(&file);
        out << QString::fromStdString(encrypted);
        file.close();

        QMessageBox::information(m_view, "Успех", "Файл зашифрован и сохранен.");
    } catch (const std::exception& e) {
        QMessageBox::critical(m_view, "Ошибка шифрования", e.what());
    }
}

void MainController::loadEncryptedFile()
{
    QString filename = QFileDialog::getOpenFileName(m_view, "Открыть зашифрованный файл", "", "Text Files (*.txt)");
    if (filename.isEmpty()) return;

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

    try {
        std::string decrypted = SteganographyLogic::decrypt(encryptedText.toStdString());
        ui->lineEditDecrypted->setText(QString::fromStdString(decrypted));
    } catch (const std::exception& e) {
        QMessageBox::warning(m_view, "Ошибка дешифрования", e.what());
    }
}