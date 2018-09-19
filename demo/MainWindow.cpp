#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDesktopWidget>
#include <thread>
#include "widgets/AsyncWidget.h"
#include "values/AsyncValueObtain.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_value(this, AsyncInitByValue{}, "Hello World!")
{
    ui->setupUi(this);
    move(QApplication::desktop()->availableGeometry().center() - rect().center());

    auto valueWidget = new AsyncWidgetFn<QString>(ui->widget);
    valueWidget->createValueWidget = [](QString& value, QWidget* parent) {
        return AsyncWidgetProxy::createLabel(value, parent);
    };
    valueWidget->setValue(&m_value);

    ui->widget->setContentWidget(valueWidget);

    QObject::connect(&m_value, &AsyncQString::stateChanged, this, &MainWindow::OnAsyncValueChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
    m_value.stopAndWait();
}

void MainWindow::OnAsyncValueChanged(ASYNC_VALUE_STATE state)
{
    ui->errorBttn->setEnabled(state != ASYNC_VALUE_STATE::PROGRESS);
    ui->valueBttn->setEnabled(state != ASYNC_VALUE_STATE::PROGRESS);
    ui->stopBttn->setEnabled(state == ASYNC_VALUE_STATE::PROGRESS);
}

void MainWindow::on_errorBttn_clicked()
{
    m_value.emplaceError("Error happened!");
}

void MainWindow::on_valueBttn_clicked()
{
    m_value.emplaceValue("A new value assigned!");
}

void MainWindow::on_startBttn_clicked()
{
    asyncValueObtain(m_value, [](AsyncProgress& progress, AsyncValue<QString>& value){

        using namespace std::chrono_literals;
        for (auto i : {0, 1, 2, 3, 4})
        {
            progress.setProgress((float)i/5.f);
            if (progress.isStopRequested())
            {
                value.emplaceError("Stopped");
                return;
            }

            std::this_thread::sleep_for(1s);
        }

        progress.setProgress(1.f);
        progress.setMessage("Processing...");
        std::this_thread::sleep_for(1s);

        QString val = "Loaded value is 42";
        value.emplaceValue(std::move(val));
    }, "Loading...", ASYNC_CAN_REQUEST_STOP::YES);
}


void MainWindow::on_stopBttn_clicked()
{
    m_value.accessProgress([](AsyncProgress& progress){
        progress.requestStop();
    });
}
