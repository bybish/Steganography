#include "MainController.h"
#include "model/SteganographyLogic.h"
#include <QMessageBox>

void MainController::encodeAction() {
    QString result = SteganographyLogic::encode("Hello");
    QMessageBox::information(nullptr, "Encode", result);
}

void MainController::decodeAction() {
    QString result = SteganographyLogic::decode("SGVsbG8=");
    QMessageBox::information(nullptr, "Decode", result);
}