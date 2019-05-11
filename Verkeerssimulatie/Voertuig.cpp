//============================================================================
// Name        : Voertuig.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 2.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include <iostream>
#include <cmath>
#include "Voertuig.h"

Voertuig::Voertuig(): fLengte(0), fPositie(0), fSnelheid(-1), fOldPositie(0), fBaan(""), fType(""), fNummerPlaat(""),
fBaanObject(0), fNextVoertuig(0), fDeleteObject(false), fRijstrook(0), fCurrentZone(NULL), fNextBushalte(NULL){

    _initCheck = this;
    ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

Voertuig::~Voertuig() {

}

double Voertuig::getLengte() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getLengte");
    return fLengte;
}

void Voertuig::setLengte(double lengte) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setLengte");
    REQUIRE(lengte > 0, "Lengte must be a positive double");
    Voertuig::fLengte = lengte;
    ENSURE(getLengte() == fLengte, "setLengte post condition failure");
}

double Voertuig::getPositie() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getPositie");
    return fPositie;
}

void Voertuig::setPositie(int positie) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setPositie");
    REQUIRE(positie >= 0, "Positie must be a positive integer");
    Voertuig::fPositie = positie;
    ENSURE(getPositie() == fPositie, "setPositie post condition failure");
}

double Voertuig::getSnelheid() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getSnelheid");
    return fSnelheid;
}

void Voertuig::setSnelheid(int snelheid) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setSnelheid");
    REQUIRE(snelheid >= 0, "Snelheid must be a positive integer");
    Voertuig::fSnelheid = snelheid;
    ENSURE(getSnelheid() == fSnelheid, "setSnelheid post condition failure");
}

double Voertuig::getOldPositie() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getOldPositie");
    return fOldPositie;
}

void Voertuig::setOldPositie(double oldPositie) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setOldPositie");
    REQUIRE(oldPositie >= 0, "oldPositie must be a positive double");
    Voertuig::fOldPositie = oldPositie;
    ENSURE(getOldPositie() == fOldPositie, "setOldPositie post condition failure");
}

const std::string &Voertuig::getBaan() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getBaan");
    return fBaan;
}

void Voertuig::setBaan(const std::string &baan) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setBaan");
    REQUIRE(baan != "", "Baan must be a non empty string");
    Voertuig::fBaan = baan;
    ENSURE(getBaan() == fBaan, "setBaan post condition failure");
}

const std::string &Voertuig::getType() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getType");
    return fType;
}

void Voertuig::setType(const std::string &type) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setType");
    REQUIRE(type != "", "Type must be a non empty string");
    Voertuig::fType = type;
    ENSURE(getType() == fType, "setType post condition failure");
}

const std::string &Voertuig::getNummerPlaat() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getNummerPlaat");
    return fNummerPlaat;
}

void Voertuig::setNummerPlaat(const std::string &nummerPlaat) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setNummerPlaat");
    REQUIRE(nummerPlaat != "", "NummerPlaat must be a non empty string");
    Voertuig::fNummerPlaat = nummerPlaat;
    ENSURE(getNummerPlaat() == fNummerPlaat, "setNummerPlaat post condition failure");
}

Baan *Voertuig::getBaanObject() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getBaanObject");
    return fBaanObject;
}

void Voertuig::setBaanObject(Baan *baanObject) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setBaanObject");
    Voertuig::fBaanObject = baanObject;
    ENSURE(getBaanObject() == fBaanObject, "setBaanObject post condition failure");
}

Voertuig *Voertuig::getNextVoertuig() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getNextVoertuig");
    return fNextVoertuig;
}

void Voertuig::setNextVoertuig(Voertuig *nextVoertuig) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setNextVoertuig");
    Voertuig::fNextVoertuig = nextVoertuig;
    ENSURE(getNextVoertuig() == fNextVoertuig, "setNextVoertuig post condition failure");
}

bool Voertuig::isDeleteObject() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling isDeleteObject");
    return fDeleteObject;
}

void Voertuig::setDeleteObject(bool deleteObject) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setDeleteObject");
    Voertuig::fDeleteObject = deleteObject;
    ENSURE(isDeleteObject() == fDeleteObject, "setDeleteObject post condition failure");
}

void Voertuig::updatePosition() {
    //if type==BUS && nextBushalte == NULL{calculateNextBushalte()
    if(fType == "BUS" && fBaanObject->containsBushalte() &&fNextBushalte == NULL){
        //find nextbushalte
        findNextBushalte();
    }

    //Bereken Positie()
    fPositie = fPositie + fSnelheid;
    //if nieuwepos buiten baan of baanVerbinding exists
    if (fPositie > fBaanObject->getLengte()) {
        if (fBaanObject->getVerbindingObject() != 0) {
            fPositie = fPositie - fBaanObject->getLengte();
            fBaanObject = fBaanObject->getVerbindingObject();
            fBaan = fBaanObject->getNaam();
        } else {
            // Delete voertuig from vector (after the iteration) as it still is needed for the other calulations
            fPositie = 0;
            fDeleteObject = true;
        }
    }
    //if current zone NULL or nieuwe positie groter dan current zone end; try to find current zone {findNextZone()}
    //try to find the new zone if currentZone is NULL or we are past the currentZone
    if (fCurrentZone == NULL or (fCurrentZone != NULL && fPositie > fCurrentZone->getFEndPositie())){
        assignCurrentZone();
    }

    // if(bushalte != NULL){ // dus als type == BUS met BUSHALTE
    if(fNextBushalte != NULL){
        //als
        double dIdeal = 2*((3/4)*fSnelheid + 2);
        double verschil = fNextBushalte->getFPositie() -  fPositie;
        double tempVertraging = -pow(fSnelheid, 2)/(verschil); //mss is de volgende positie pakken beter? dan remt jij harder

        if(verschil <= dIdeal){
            //calculate snelheid
            fSnelheid = fSnelheid + fVersnelling;
            //calculate deceleration
            fVersnelling = tempVertraging;
            if(tempVertraging < -7){
                std::cerr << "BUS MET NUMMERPLAAT: "<< fNummerPlaat << " CAN'T BREAK IN TIME";
            }
        }
        //    o-BUS-o |bushalte| o-BUS-o
        else if(fNextBushalte->getFPositie() >= fPositie-10 && fNextBushalte->getFPositie() <= fPositie){
            if(fSnelheid- tempVertraging <=0){
                fSnelheid = 0;
                fVersnelling = 0;
            }
        }
        else{//anders als wij nog in goede afstand zitten

        }

    }
    // }

    //else if(currentZone == NULL){
            // doe gewoon
            // update speed
            // update acceleration
    //    }
    // elseif(currentZone != NULL){
    //
}

Verkeersteken *Voertuig::getFCurrentZone() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getFCurrentZone");
    return fCurrentZone;
}

void Voertuig::setFCurrentZone(Verkeersteken *fCurrentZone) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setFCurrentZone");

    Voertuig::fCurrentZone = fCurrentZone;
    ENSURE(getFCurrentZone() == fCurrentZone, "setFCurrentZone post condition failure");
}

const std::vector<Verkeersteken *> &Voertuig::getFPassedVerkeerstekens() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getFPassedVerkeerstekens");
    return fPassedVerkeerstekens;
}

void Voertuig::addFPassedVerkeerstekens(Verkeersteken * fPassedVerkeerstekens) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling addFPassedVerkeerstekens");

    REQUIRE(fPassedVerkeerstekens != NULL, "addFPassedVerkeerstekens pre condition failure");
    Voertuig::fPassedVerkeerstekens.push_back(fPassedVerkeerstekens);
    ENSURE(getFPassedVerkeerstekens().back() == fPassedVerkeerstekens, "addFPassedVerkeerstekens post condition failure");
}

double Voertuig::getFVersnelling() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getFVersnelling");

    return fVersnelling;
}

void Voertuig::setFVersnelling(double fVersnelling) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setFVersnelling");

    Voertuig::fVersnelling = fVersnelling;
    ENSURE(getFVersnelling() == fVersnelling, "setFVersnelling post condition failure");
}

void Voertuig::setFMaxSnelheid(double fMaxSnelheid) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setFMaxSnelheid");

    REQUIRE(fMaxSnelheid >= 0, "setFMaxSnelheid pre condition failure" );
    Voertuig::fMaxSnelheid = fMaxSnelheid;
    ENSURE(fMaxSnelheid == Voertuig::fMaxSnelheid, "setFMaxSnelheid post condition failure" );
}

void Voertuig::setFMaxVersnelling(double fMaxVersnelling) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setFMaxVersnelling");

    REQUIRE(fMaxSnelheid >= 0, "setFMaxVersnelling pre condition failure" );
    Voertuig::fMaxVersnelling = fMaxVersnelling;
    ENSURE(fMaxVersnelling == Voertuig::fMaxVersnelling, "setFMaxSnelheid post condition failure" );
}

void Voertuig::setFMinVersnelling(double fMinVersnelling) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setFMinVersnelling");

    REQUIRE(fMinVersnelling <= 0, "setFMinVersnelling pre condition failure" );
    Voertuig::fMinVersnelling = fMinVersnelling;
    ENSURE(Voertuig::fMinVersnelling == fMinVersnelling, "setFMinVersnelling post condition failure" );
}

int Voertuig::getFRijstrook() const {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling getFRijstrook");
    return fRijstrook;
}

void Voertuig::setFRijstrook(int fRijstrook) {
    REQUIRE(this->properlyInitialized(), "Voertuig wasn't initialized when calling setFRijstrook");

    REQUIRE(fRijstrook >= 0, "setFRijstrook pre condition failure");
    Voertuig::fRijstrook = fRijstrook;
    ENSURE(getFRijstrook() == fRijstrook, "setFRijstrook post condition failure");
}

bool Voertuig::properlyInitialized() const{
    return _initCheck == this;
}

void Voertuig::set_initCheck(Voertuig *_initCheck) {
    Voertuig::_initCheck = _initCheck;
}

void Voertuig::findNextBushalte() {
    Verkeersteken* bestGuess = new Verkeersteken();
    bestGuess->setFPositie(fBaanObject->getLengte()+10);

    for(int i = 0; i < fBaanObject->getFVerkeerstekens().size(); i++) {
        Verkeersteken *tempNaam = fBaanObject->getFVerkeerstekens().at(i);
        if(tempNaam->getFType() == "BUSHALTE" and fPositie < tempNaam->getFPositie() and tempNaam->getFPositie() < bestGuess->getFPositie()){
            bestGuess = tempNaam;
        }
    }

    if (bestGuess->getFPositie() == fBaanObject->getLengte()+10){
        bestGuess = NULL;
    }
    fNextBushalte = bestGuess;
}

void Voertuig::assignCurrentZone() {
    for(int i = 0; i < fBaanObject->getFVerkeerstekens().size(); i++){
        Verkeersteken* tempZone = fBaanObject->getFVerkeerstekens().at(i);
        if(tempZone->getFPositie() <= fPositie && fPositie < tempZone->getFEndPositie() && tempZone->getFType() == "ZONE"){
            fCurrentZone = tempZone;
            break;
        }
    }
}
