//============================================================================
// Name        : Verkeersteken.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 3.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include "Verkeersteken.h"

Verkeersteken::Verkeersteken(): fSnelheidslimiet(2000) {
    _initCheck = this;

    ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

const std::string &Verkeersteken::getFBaan() const {
    REQUIRE(this->properlyInitialized(), "Verkeersteken wasn't initialized when calling getFBaan");

    return fBaan;
}

void Verkeersteken::setFBaan(const std::string &baan) {
    REQUIRE(this->properlyInitialized(), "Verkeersteken wasn't initialized when calling setFBaan");

    Verkeersteken::fBaan = baan;
    ENSURE(getFBaan() == baan, "setFType pre condition failure");
}


const std::string &Verkeersteken::getFType() const {
    REQUIRE(this->properlyInitialized(), "Verkeersteken wasn't initialized when calling getFType");

    return fType;
}

void Verkeersteken::setFType(const std::string &type) {
    REQUIRE(this->properlyInitialized(), "Verkeersteken wasn't initialized when calling setFType");

    REQUIRE(type == "BUSHALTE" or type == "ZONE" or type == "VERKEERSLICHT","setFType pre condition failure" );
    Verkeersteken::fType = type;
    ENSURE(getFType() == type, "setFType post condition failure");
}

unsigned int Verkeersteken::getFPositie() const {
    REQUIRE(this->properlyInitialized(), "Verkeersteken wasn't initialized when calling getFPositie");

    return fPositie;
}

void Verkeersteken::setFPositie(unsigned int positie) {
    REQUIRE(this->properlyInitialized(), "Verkeersteken wasn't initialized when calling setFPositie");

    REQUIRE( positie >= 0, "setFPositie pre condition failure");
    Verkeersteken::fPositie = positie;
    ENSURE(getFPositie() == positie, "setFPositie post condition failure");
}

int Verkeersteken::getFSnelheidslimiet() const {
    REQUIRE(this->properlyInitialized(), "Verkeersteken wasn't initialized when calling getFSnelheidslimiet");
    return fSnelheidslimiet;
}

void Verkeersteken::setFSnelheidslimiet(int snelheidslimiet) {
    REQUIRE(this->properlyInitialized(), "Verkeersteken wasn't initialized when calling setFSnelheidslimiet");

    REQUIRE( fSnelheidslimiet >= 0, "setFSnelheidslimiet pre condition failure");
    Verkeersteken::fSnelheidslimiet = snelheidslimiet;
    ENSURE(getFSnelheidslimiet() == fSnelheidslimiet, "setFSnelheidslimiet post condition failure");
}

unsigned int Verkeersteken::getFEndPositie() const {
    REQUIRE(this->properlyInitialized(), "Verkeersteken wasn't initialized when calling getFEndPositie");
    return fEndPositie;
}

void Verkeersteken::setFEndPositie(unsigned int fEndPositie) {
    REQUIRE(this->properlyInitialized(), "Verkeersteken wasn't initialized when calling setFEndPositie");

    REQUIRE(fEndPositie >= 0,"setFEndPositie pre condition failure" );
    Verkeersteken::fEndPositie = fEndPositie;
    ENSURE(getFEndPositie() == fEndPositie,"setFSnelheidslimiet post condition failure");
}

bool Verkeersteken::properlyInitialized() const {
    return _initCheck == this;
}
