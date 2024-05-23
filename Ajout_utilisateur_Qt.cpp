#include "QtWidgetsApplication3.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "uFCoder.h"
#include "ui_QtWidgetsApplication3.h"



QtWidgetsApplication3::QtWidgetsApplication3(QWidget* parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);

    // A l'appuie du bouton, le lecteur RFID se met en marche :
    connect(ui.button, &QPushButton::clicked, this, &QtWidgetsApplication3::readRFID);
}

QtWidgetsApplication3::~QtWidgetsApplication3()
{

}

void QtWidgetsApplication3::readRFID()
{
    UFR_STATUS status = ReaderOpen();
    if (status == UFR_OK) {
        uint8_t aucCardUID[255];
        uint8_t* pCardUID = aucCardUID;
        uint8_t bCardUIDSize;
        uint8_t bCardType;
        std::string sBuffer;

        UFR_STATUS iCResult = GetCardIdEx(&bCardType, pCardUID, &bCardUIDSize);
        if (iCResult == UFR_OK) {
            std::stringstream ss;
            for (char bBr = 0; bBr < bCardUIDSize; bBr++) {
                ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(aucCardUID[bBr]);
            }
            sBuffer = ss.str();
            displayCardID(sBuffer);  // Appel de la fonction pour afficher l'ID du badge dans le QTextEdit
        }
        else {
            displayCardID("Erreur de lecture de l'ID de la carte.");
        }
        ReaderClose();
    }
    else {
        displayCardID("Erreur d'ouverture du lecteur RFID.");
    }
}

void QtWidgetsApplication3::displayCardID(const std::string& cardID)
{
    ui.textEdit->setText(QString::fromStdString(cardID)); // affichage de l'id dans la zone de texte
}
