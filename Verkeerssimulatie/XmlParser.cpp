//============================================================================
// Name        : XmlParser.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include <cstring>
#include "XmlParser.h"

XmlParser::XmlParser(const char* nameOfFile): fkFileName(nameOfFile) {

    _initCheck = this;

    fVoertuigen = new  std::vector<Voertuig*>;
    fBanen = new  std::vector<Baan*>;
    fWegenNetwerk = new  std::vector<Baan*>;
    // If file can't be read stop the program
    try {
        isReadable();
    }
    catch (const char* &error){
        std::cerr <<"Program was terminated because of an "<< error <<" thrown by isReadable()"<< std::endl;
        exit(1);
    }

    // Parse the file
    parseFile();
    ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

std::vector<Baan *> *XmlParser::getBanen() const {
    REQUIRE(this->properlyInitialized(), "XmlParser wasn't initialized when calling getBanen");
    return fBanen;
}

std::vector<Baan *> *XmlParser::getWegenNetwerk() const {
    REQUIRE(this->properlyInitialized(), "XmlParser wasn't initialized when calling getWegenNetwerk");
    return fWegenNetwerk;
}

std::vector<Voertuig *> *XmlParser::getVoertuigen() const {
    REQUIRE(this->properlyInitialized(), "XmlParser wasn't initialized when calling getVoertuigen");
    return fVoertuigen;
}

void XmlParser::parseFile() {
    REQUIRE(this->properlyInitialized(), "XmlParser wasn't initialized when calling parseFile");
    REQUIRE(isReadable(), "File to parse must be parse-able");

    // Define the root of the file
    TiXmlElement* root = fDocument.FirstChildElement();

    // Loop over all elements in the most outer scope
    for (TiXmlElement* rootElement = root; rootElement != NULL; rootElement = rootElement->NextSiblingElement()) {

        if (is_equal(rootElement->Value(),"VOERTUIG")) {
            Voertuig *voertuig = new Voertuig();
            voertuig->setFVersnelling(0);
            // Loop over all child elements of rootElement
            for (TiXmlElement *childOfRootElement = rootElement->FirstChildElement();
                 childOfRootElement != NULL; childOfRootElement = childOfRootElement->NextSiblingElement()) {

                // Get the value and text of the element
                std::string elementText;
                std::string elementValue;
                try {
                    if (childOfRootElement->GetText() != NULL) {
                        elementText = childOfRootElement->GetText();
                    } else {
                        throw "InvalidText";
                    }

                    if (childOfRootElement->Value() != NULL) {
                        elementValue = childOfRootElement->Value();
                    } else {
                        throw "InvalidValue";
                    }
                }
                catch (const char* &error) {
                    if (is_equal(error, "InvalidValue")) {
                        std::cerr << childOfRootElement << "->Value() is NULL." << std::endl;
                    } else if (is_equal(error, "InvalidText")) {
                        std::cerr << childOfRootElement->Value() << " tag is NULL." << std::endl;
                    }
                }

                // Check the value of element Value
                if (elementValue == "type") {
                    voertuig->setType(elementText);
                    if(elementText == "MOTORFIETS"){
                        voertuig->setLengte(1);
                        voertuig->setFMaxSnelheid(180);
                        voertuig->setFMaxVersnelling(4);
                        voertuig->setFMinVersnelling(-10);
                    }
                    else if(elementText == "AUTO"){
                        voertuig->setLengte(3);
                        voertuig->setFMaxSnelheid(150);
                        voertuig->setFMaxVersnelling(2);
                        voertuig->setFMinVersnelling(-8);
                    }
                    else if(elementText == "BUS"){
                        voertuig->setLengte(10);
                        voertuig->setFMaxSnelheid(70);
                        voertuig->setFMaxVersnelling(1);
                        voertuig->setFMinVersnelling(-7);
                    }
                    else if(elementText == "VRACHTWAGEN"){
                        voertuig->setLengte(15);
                        voertuig->setFMaxSnelheid(90);
                        voertuig->setFMaxVersnelling(1);
                        voertuig->setFMinVersnelling(-6);
                    }

                } else if (elementValue == "nummerplaat") {
                    voertuig->setNummerPlaat(elementText);

                } else if (elementValue == "baan") {
                    voertuig->setBaan(elementText);

                } else if (elementValue == "positie") {
                    try {
                        voertuig->setPositie(stoi(elementText));
                        voertuig->setOldPositie(stoi(elementText));
                    }
                    catch (const char* &error) {
                        std::cerr << elementText << " can't be converted to a number." << std::endl;
                    }

                } else if (elementValue == "snelheid") {
                    try {
                        voertuig->setSnelheid(stoi(elementText));
                    }
                    catch (const char* &error) {
                        std::cerr << elementText << " can't be converted to a number." << std::endl;
                    }

                }
            }
            //check if baan nog niet bestaat
            bool geldigVoertuigObject = true;
            for(unsigned int i = 0; i < fVoertuigen->size(); i++){
                if(fVoertuigen->at(i)->getNummerPlaat() == voertuig->getNummerPlaat()){
                    geldigVoertuigObject = false;
                }
            }
            if(geldigVoertuigObject){
                // Add the new instance of 'voertuig' to 'voertuigen'
                fVoertuigen->push_back(voertuig);
            }
        }

        if (is_equal(rootElement->Value(),"BAAN")) {
            Baan *baan = new Baan;

            // Set 'isWegenNetwerk' to false as default
            bool isWegenNetwerk = false;

            // Loop over all child elements of rootElement
            for (TiXmlElement *childOfRootElement = rootElement->FirstChildElement();
                 childOfRootElement != NULL; childOfRootElement = childOfRootElement->NextSiblingElement()) {


                // Get the value and text of the element
                std::string elementText;
                std::string elementValue;
                try {
                    if (childOfRootElement->GetText() != NULL) {
                        elementText = childOfRootElement->GetText();
                    } else {
                        throw "InvalidText";
                    }

                    if (childOfRootElement->Value() != NULL) {
                        elementValue = childOfRootElement->Value();
                    } else {
                        throw "InvalidValue";
                    }
                }
                catch (const char* &error) {
                    if (is_equal(error, "InvalidValue")) {
                        std::cerr << childOfRootElement << "->Value() is NULL." << std::endl;
                    } else if (is_equal(error, "InvalidText")) {
                        std::cerr << childOfRootElement->Value() << " tag is NULL." << std::endl;
                    }
                }


                // Check the value of element Value
                if (elementValue == "naam") {
                    baan->setNaam(elementText);

                } else if (elementValue == "snelheidslimiet") {
                    try {
                        baan->setSnelheidsLimiet(stoi(elementText));
                    }
                    catch (const char* &error) {
                        std::cerr << elementText << " can't be converted to a number." << std::endl;
                    }


                } else if (elementValue == "lengte") {
                    try {
                        baan->setLengte(stoi(elementText));
                    }
                    catch (const char* &error) {
                        std::cerr << elementText << " can't be converted to a number." << std::endl;
                    }

                } else if (elementValue == "verbinding") {
                    isWegenNetwerk = true;
                    baan->setVerbinding(elementText);
                }
            }
            bool geldigObject = true;
            if (isWegenNetwerk) {
                //check if wegenNetwerk nog niet bestaat
                for(unsigned int i = 0; i < fWegenNetwerk->size(); i++){
                    if(fWegenNetwerk->at(i)->getNaam() == baan->getNaam()){
                        geldigObject = false;
                    }
                }
                if(geldigObject){
                    // Add the new instance of 'wegenNetwerk' to 'wegenNetwerken'
                    fWegenNetwerk->push_back(baan);
                }
            } else {
                //check if Baan nog niet bestaat
                for(unsigned int i = 0; i < fBanen->size(); i++){
                    if(fBanen->at(i)->getNaam() == baan->getNaam()){
                        geldigObject = false;
                    }
                }
                if(geldigObject){
                    // Add the new instance of 'Baan' to 'Banen'
                    fBanen->push_back(baan);
                }
            }
        }
    }

    // Close file
    fDocument.Clear();
}

bool XmlParser::isReadable(){
    REQUIRE(this->properlyInitialized(), "XmlParser wasn't initialized when calling isReadable");

    if(!fDocument.LoadFile(fkFileName)) {
        std::cerr << fDocument.ErrorDesc() << std::endl;
        std::cerr << "Error in document row: "<< fDocument.ErrorRow() << std::endl;
        throw "FormattingError";

    }
    if(fDocument.FirstChildElement() == NULL) { //if root == NULL
        std::cerr << "Failed to load file: No root element." << std::endl;
        fDocument.Clear();
        return "FormattingError";

    }
    return true;
}

int XmlParser::stoi(std::string &string) const {
    REQUIRE(this->properlyInitialized(), "XmlParser wasn't initialized when calling stoi");

    int integer;
    if (is_digits(string)) {
        std::istringstream(string) >> integer;
    } else {
        throw "ConversionFailed";
    }
    return integer;
}

bool XmlParser::is_digits(const std::string &string) const {
    REQUIRE(this->properlyInitialized(), "XmlParser wasn't initialized when calling is_digits");
    return string.find_first_not_of("0123456789") == std::string::npos;
}

bool XmlParser::is_equal(const char *cc1, const char *cc2) const {
    REQUIRE(this->properlyInitialized(), "XmlParser wasn't initialized when calling is_equal");
    return 0 == std::strncmp(cc1, cc2, std::strlen(cc1)+1);
}

bool XmlParser::properlyInitialized() const{
    return _initCheck == this;
}
