#include "mainwindow.h"
#include "uFCoder.h"
#include "./ui_mainwindow.h"
#include <sstream>
#include <iomanip>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    BadgeReaderThread *readerThread = new BadgeReaderThread();
    connect(readerThread, &BadgeReaderThread::badgeRead, this, [this](const QString &badgeId) {
        ui->textEdit->append("CardUID: 0x" + badgeId);
    });

    readerThread->start();
}

MainWindow::~MainWindow() {
    delete ui;
}

void BadgeReaderThread::run() {
    while (true) {
        UFR_STATUS status = ReaderOpen();
        if (status == UFR_OK) {
            uint32_t iReaderType;
            uint8_t bDLCardType;
            uint8_t bCardType;
            uint8_t bCardUIDSize;
            uint8_t aucCardUID[255];
            uint8_t* pCardUID = aucCardUID;

            UFR_STATUS iRResult = GetReaderType(&iReaderType);
            if (iRResult == UFR_OK) {
                UFR_STATUS iCResult = GetDlogicCardType(&bDLCardType);
                if (iCResult == UFR_OK) {
                    iCResult = GetCardIdEx(&bCardType, pCardUID, &bCardUIDSize);
                    if (iCResult == UFR_OK) {
                        std::stringstream ss;
                        for (char bBr = 0; bBr < bCardUIDSize; bBr++) {
                            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(aucCardUID[bBr]);
                        }
                        QString sBuffer = QString::fromStdString(ss.str());
                        emit badgeRead(sBuffer);
                    }
                }
            }
        }
    }
}
