#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // Начальное состояние - страница шифрования
    ui->stackedWidget->setCurrentIndex(0);
    
    // Подключаем переключение режима
    connect(ui->toggleMode, &QCheckBox::stateChanged, this, [this](int state) {
        if (state == Qt::Checked) {
            ui->labelModeTitle->setText("Дешифровать");
            ui->stackedWidget->setCurrentIndex(1); // Страница дешифрования
        } else {
            ui->labelModeTitle->setText("Зашифровать");
            ui->stackedWidget->setCurrentIndex(0); // Страница шифрования
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}