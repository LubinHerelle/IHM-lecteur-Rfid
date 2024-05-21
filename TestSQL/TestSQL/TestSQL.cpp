#include <iostream>
#include <mysql/jdbc.h>
#include "uFCoder.h"
#include <iomanip>
#include <sstream>

int main() {
    std::cout << "Lecteur ouvert\n";
    while (true) {
        UFR_STATUS status = ReaderOpen();
        if (status == UFR_OK) {
            uint32_t iReaderType;
            uint8_t bDLCardType;
            uint8_t bCardType;
            uint8_t bCardUIDSize;
            uint8_t bTypeOfCard;
            std::string sBuffer;
            uint8_t aucCardUID[255];
            uint8_t* pCardUID = aucCardUID;

            UFR_STATUS iRResult = GetReaderType(&iReaderType);
            if (iRResult == UFR_OK) {
                UFR_STATUS iCResult = GetDlogicCardType(&bDLCardType);
                if (iCResult == UFR_OK) {
                    iCResult = GetCardIdEx(&bCardType, pCardUID, &bCardUIDSize);
                    if (iCResult == UFR_OK) {
                        sBuffer = "";
                        std::stringstream ss;
                        for (char bBr = 0; bBr < bCardUIDSize; bBr++) {
                            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(aucCardUID[bBr]);
                        }
                        sBuffer = ss.str();

                        // Affichage des informations de la carte en hexadécimal
                        std::cout << "CardType: 0x" << std::hex << static_cast<int>(bDLCardType) << std::endl;
                        std::cout << "CardUIDSize: 0x" << std::hex << static_cast<int>(bCardUIDSize) << std::endl;
                        std::cout << "CardUID: 0x" << sBuffer << std::endl;
                    }
                }
            }
        }
    }
    return 0;
}
