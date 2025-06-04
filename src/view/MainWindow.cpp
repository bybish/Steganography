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
    connect(ui->toggleMode, &QCheckBox::stateChanged, this, &MainWindow::onToggleModeChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onToggleModeChanged(int state)
{
    if (state == Qt::Checked) {
        ui->labelModeTitle->setText("Дешифровать");
        ui->stackedWidget->setCurrentIndex(1); 
    } else {
        ui->labelModeTitle->setText("Зашифровать");
        ui->stackedWidget->setCurrentIndex(0); 
    }
}

Ui::MainWindow* MainWindow::getUi() const
{
    return ui;
}