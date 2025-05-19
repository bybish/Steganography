#pragma once

#include <QObject>
#include "../view/MainWindow.h"
#include "../model/SteganographyLogic.h"

class MainController : public QObject
{
    Q_OBJECT

public:
    explicit MainController(MainWindow* view, QObject* parent = nullptr);

private slots:
    void loadFile();
    void saveEncryptedFile();

private:
    MainWindow* m_view;
    SteganographyLogic m_logic;
    QString m_loadedText;
};