//============================================================================
// Name        : Baan.h
// Author      : John Castillo & Tobias Wilfert
// Version     : 3.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#ifndef VERKEERSSIMULATIE_BAAN_H
#define VERKEERSSIMULATIE_BAAN_H

#include <string>
#include <vector>

#include "Verkeersteken.h"
#include "DesignByContract.h"

// Forward declaration
class Voertuig;

class Baan {
private:

    /// Length of the Baan in meters
    double fLengte;

    /// The speed Limit of the Baan in km/h represented as an integer
    int fSnelheidsLimiet;

    /// The Name of the Baan represented as a string
    std::string fNaam;

    /// The Name of the Baan that this Baan has a Verbinding with
    std::string fVerbinding;

    /// A pointer to the instance of Baan that this Instance has a Verbining with
    Baan* fVerbindingObject;

    /// A collection of road regulations
    std::vector<Verkeersteken*> fVerkeerstekens;

    /// The number of Lanes a Baan has
    unsigned int fRijstroken;

    /// Indicates if this baan has a bushalte
    bool fContainsBushalte;

    /// Pointer to the last vehicle on the baan
    Voertuig* flastVoertuig;

    ///Use pointer to myself to verify whether I am properly initialized
    Baan * _initCheck;

public:

    /// Consturctor

    /**
    \n ENSURE(properlyInitialized(), "Constructor must end in properly initialized state");
    */
    Baan();

    /// Getters and Setters

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling getLengte()");
    */
    const double &getLengte() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling setLengte()");
    \n REQUIRE(lengte > 0, "setLengte precondition failure");
    \n ENSURE(getLengte() == fLengte, "setLengte ()post condition failure");
    \n ENSURE(fLengte > 0, "setLengte postcondition failure");
    */
    void setLengte(const double &lengte);

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling getNaam()");
    */
    const std::string &getNaam() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling setNaam()");
    \n REQUIRE(!naam.empty(), "setNaam() precondition failure");
    \n ENSURE(getNaam() == fNaam, "setNaam() post condition failure");
    */
    void setNaam(const std::string &naam);

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling getSnelheidsLimiet()");
    */
    const int &getSnelheidsLimiet() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling setSnelheidsLimiet()");
    \n REQUIRE(snelheidsLimiet > 0, "setSnelheidsLimiet() precondition failure");
    \n ENSURE(snelheidsLimiet == fSnelheidsLimiet, "setSnelheidsLimiet() postcondition failure");
    */
    void setSnelheidsLimiet(const int &snelheidsLimiet);

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling getVerbinding");
    */
    const std::string &getVerbinding() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling setVerbinding");
    \n REQUIRE(fVerbinding != "", "setVerbinding() precondition failure");
    \n ENSURE(getVerbinding() == fVerbinding, "setVerbinding() postcondition failure");
    */
    void setVerbinding(const std::string &verbinding);

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling getVerbindingObject()");
    */
    Baan *getVerbindingObject() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling setVerbindingObject()");
    \n REQUIRE(verbinding != NULL, "setVerbindingObject() precondition failure");
    \n ENSURE(fVerbindingObject == getVerbindingObject(), "setVerbindingObject() postcondition failure");
    */
    void setVerbindingObject(Baan *verbinding);

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling getFRijstroken()");
    */
    unsigned int getFRijstroken() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling setFRijstroken()");
    \n REQUIRE(fRijstroken >= 1, "setFRijstroken() precondition failure");
    \n ENSURE(fRijstroken == getFRijstroken(), "setFRijstroken() postcondition failure");
     */
    void setFRijstroken(unsigned int fRijstroken);

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling addFVerkeersteken()");
    \n REQUIRE(verkeersteken != NULL, "addFVerkeersteken() precondition failure");
    \n ENSURE(getFVerkeerstekens().back() == verkeersteken, "addFVerkeersteken() postcondition failure" );
     */
    void addFVerkeersteken(Verkeersteken* verkeersteken);

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling getFVerkeerstekens()");
     */
    const std::vector<Verkeersteken *> &getFVerkeerstekens() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling setfContainsBushalte()");
     */
    void setfContainsBushalte();

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling containsBushalte()");
     */
    const bool containsBushalte() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling getfLastVoertuig()");
     */
    Voertuig *getfLastVoertuig() const;

    /**
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling setfLastVoertuig()");
    \n ENSURE(this->getfLastVoertuig() == lastVoertuig, "setfLastVoertuig() postcondition failure" );
     */
    void setfLastVoertuig(Voertuig *lastVoertuig);

    /// Methods

    /**
     * Assigns an end position to all Zones on this baan. This is the begin position of the
     * next zone or if there is no next zone then the end of the baan.
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling assignZoneLimit()");
    \n ENSURE(fVerkeerstekens.at(i)->getFPositie() <= fVerkeerstekens.at(i)->getFEndPositie(),
                "assignZoneLimit post condition failure");
     */
    void assignZoneLimit();

    /**
     * Checks whether the vector of Verkeersteken is sorted
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling isSorted()");
     */
    bool isSorted();

    /**
     * Sorts the vector of Verkeersteken by position
    \n REQUIRE(this->properlyInitialized(), "Baan wasn't initialized when calling sortVerkeersteken()");
     */
    void sortVerkeersteken();


    //-----------------------------------------
    ///auxiliary routines (private use)
    //-----------------------------------------

    bool properlyInitialized() const;

};


#endif //VERKEERSSIMULATIE_BAAN_H