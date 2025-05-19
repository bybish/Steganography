#include "MainController.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainController::MainController(MainWindow* view, QObject* parent)
    : QObject(parent), m_view(view)
{
    connect(view->findChild<QPushButton*>("btnLoad"), &QPushButton::clicked, this, &MainController::loadFile);
    connect(view->findChild<QPushButton*>("btnSave"), &QPushButton::clicked, this, &MainController::saveEncryptedFile);
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

    std::string result = m_logic.encrypt(text.toStdString(), message.toStdString(), 0);
    if (result.starts_with("Error"))
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