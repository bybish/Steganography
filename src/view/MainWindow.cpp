#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "controller/MainController.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->encodeButton, &QPushButton::clicked, this, &MainWindow::onEncodeClicked);
    connect(ui->decodeButton, &QPushButton::clicked, this, &MainWindow::onDecodeClicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onEncodeClicked() {
    MainController::encodeAction();
}

void MainWindow::onDecodeClicked() {
    MainController::decodeAction();
}