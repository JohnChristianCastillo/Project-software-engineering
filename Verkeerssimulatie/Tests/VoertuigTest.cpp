//============================================================================
// Name        : VoertuigTest.cpp
// Author      : John Castillo & Tobias Wilfert
// Version     : 1.0
// Copyright   : Project Software Engineering - BA1 Informatica - John Castillo & Tobias Wilfert - University of Antwerp
// Description : Verkeerssimulatie in C++
//============================================================================

#include <iostream>
#include <gtest/gtest.h>

#include "../Baan.h"
#include "../Voertuig.h"

class VoertuigTest: public ::testing::Test {
protected:
    friend class Baan;
    friend class Voertuig;

    // You should make the members protected s.t. they can be
    // accessed from sub-classes.

    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the variables.
    // Otherwise, this can be skipped.
    virtual void SetUp() {
    }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    virtual void TearDown() {
    }

    // Declares the variables your tests want to use.
    Voertuig voertuig = Voertuig();
};

// Tests the default constructor.
TEST_F(VoertuigTest, DefaultConstructor) {

    EXPECT_EQ(voertuig.getLengte(), 0);
    EXPECT_EQ(voertuig.getPositie(), 0);
    EXPECT_EQ(voertuig.getSnelheid(), -1);
    EXPECT_EQ(voertuig.getOldPositie(), 0);
    EXPECT_EQ(voertuig.getBaan(), "");
    EXPECT_EQ(voertuig.getType(), "");
    EXPECT_EQ(voertuig.getNummerPlaat(), "");
    EXPECT_FALSE(voertuig.isDeleteObject());

    EXPECT_TRUE(voertuig.properlyInitialized());
}

TEST_F(VoertuigTest, CheckProperlyInitialized){

    voertuig.set_initCheck(false);
    EXPECT_FALSE(voertuig.properlyInitialized());
}

/// Test Getters ans Setters

/// REQUIRE TESTS Getters
TEST_F(VoertuigTest, GetLengteRequire){

    voertuig.set_initCheck(false);
    EXPECT_DEATH(voertuig.getLengte(),"");
}

TEST_F(VoertuigTest, GetPositieRequire){

    voertuig.set_initCheck(false);
    EXPECT_DEATH(voertuig.getPositie(),"");
}

TEST_F(VoertuigTest, GetSnelheidRequire){

    voertuig.set_initCheck(false);
    EXPECT_DEATH(voertuig.getSnelheid(),"");
}

TEST_F(VoertuigTest, GetOldPositieRequire){

    voertuig.set_initCheck(false);
    EXPECT_DEATH(voertuig.getOldPositie(),"");
}

TEST_F(VoertuigTest, GetBaanRequire){

    voertuig.set_initCheck(false);
    EXPECT_DEATH(voertuig.getBaan(),"");
}

TEST_F(VoertuigTest, GetTypeRequire){

    voertuig.set_initCheck(false);
    EXPECT_DEATH(voertuig.getType(),"");
}

TEST_F(VoertuigTest, GetNummerPlaatRequire){

    voertuig.set_initCheck(false);
    EXPECT_DEATH(voertuig.getNummerPlaat(),"");
}

TEST_F(VoertuigTest, GetBaanObjectRequire){

    voertuig.set_initCheck(false);
    EXPECT_DEATH(voertuig.getBaanObject(),"");
}

TEST_F(VoertuigTest, GetNextVoertuigRequire){

    voertuig.set_initCheck(false);
    EXPECT_DEATH(voertuig.getNextVoertuig(),"");
}

TEST_F(VoertuigTest, IsDeleteObjectRequire){

    voertuig.set_initCheck(false);
    EXPECT_DEATH(voertuig.isDeleteObject(),"");
}

/// REQUIRE TESTS Setters
TEST_F(VoertuigTest, SetLengteRequire){

    voertuig.set_initCheck(false);
    EXPECT_DEATH(voertuig.setLengte(10),"");
}

TEST_F(VoertuigTest, SetPositieRequire){

    voertuig.set_initCheck(false);
    EXPECT_DEATH(voertuig.setPositie(10),"");
}

TEST_F(VoertuigTest, SetSnelheidRequire){

    voertuig.set_initCheck(false);
    EXPECT_DEATH(voertuig.setSnelheid(10),"");
}

TEST_F(VoertuigTest, SetOldPositieRequire){

    voertuig.set_initCheck(false);
    EXPECT_DEATH(voertuig.setOldPositie(10),"");
}

TEST_F(VoertuigTest, SetBaanRequire){

    voertuig.set_initCheck(false);
    EXPECT_DEATH(voertuig.setBaan("A10"),"");
}

TEST_F(VoertuigTest, SetTypeRequire){

    voertuig.set_initCheck(false);
    EXPECT_DEATH(voertuig.setType("Auto"),"");
}

TEST_F(VoertuigTest, SetNummerPlaatRequire){

    voertuig.set_initCheck(false);
    EXPECT_DEATH(voertuig.setNummerPlaat("123-ABC-456"),"");
}

TEST_F(VoertuigTest, SetBaanObjectRequire){

    voertuig.set_initCheck(false);
    EXPECT_DEATH(voertuig.setBaanObject(0),"");
}

TEST_F(VoertuigTest, SetNextVoertuigRequire){

    voertuig.set_initCheck(false);
    EXPECT_DEATH(voertuig.setNextVoertuig(0),"");
}

TEST_F(VoertuigTest, SetDeleteObjectRequire){

    voertuig.set_initCheck(false);
    EXPECT_DEATH(voertuig.setDeleteObject(true),"");
}

/// ENSURE TESTS Setters
TEST_F(VoertuigTest, SetLengteEnsureNegative){

    EXPECT_DEATH(voertuig.setLengte(-10),"");
}

TEST_F(VoertuigTest, SetLengteEnsureNull){

    EXPECT_DEATH(voertuig.setLengte(0),"");
}

TEST_F(VoertuigTest, SetPositieEnsure){

    EXPECT_DEATH(voertuig.setPositie(-10),"");
}

TEST_F(VoertuigTest, SetSnelheidEnsure){

    EXPECT_DEATH(voertuig.setSnelheid(-10),"");
}

TEST_F(VoertuigTest, SetOldPositieEnsure){

    EXPECT_DEATH(voertuig.setOldPositie(-10),"");
}

TEST_F(VoertuigTest, SetBaanEnsure){

    EXPECT_DEATH(voertuig.setBaan(""),"");
}

TEST_F(VoertuigTest, SetTypeEnsure){

    EXPECT_DEATH(voertuig.setType(""),"");
}

/// ENSURE Setters Effectiveness (and implying Setters)
TEST_F(VoertuigTest, GetLengteWorking){

    voertuig.setLengte(7);
    EXPECT_EQ(voertuig.getLengte(),7);
}

TEST_F(VoertuigTest, GetPositieWorking){

    voertuig.setPositie(7);
    EXPECT_EQ(voertuig.getPositie(),7);
}

TEST_F(VoertuigTest, GetSnelheidWorking){

    voertuig.setSnelheid(7);
    EXPECT_EQ(voertuig.getSnelheid(),7);
}

TEST_F(VoertuigTest, GetOldPositieWorking){

    voertuig.setOldPositie(7);
    EXPECT_EQ(voertuig.getOldPositie(),7);
}

TEST_F(VoertuigTest, GetBaanWorking){

    voertuig.setBaan("E17");
    EXPECT_EQ(voertuig.getBaan(),"E17");
}

TEST_F(VoertuigTest, GetTypeWorking){

    voertuig.setType("auto");
    EXPECT_EQ(voertuig.getType(),"auto");
}

TEST_F(VoertuigTest, GetNummerPlaatWorking){

    voertuig.setNummerPlaat("123BCD");
    EXPECT_EQ(voertuig.getNummerPlaat(),"123BCD");
}

TEST_F(VoertuigTest, GetBaanObjectWorking){

    Baan* baan = new Baan();
    voertuig.setBaanObject(baan);
    EXPECT_EQ(voertuig.getBaanObject(),baan);
}

TEST_F(VoertuigTest, GetNextVoertuigWorking){

    Voertuig* voertuig1 = new Voertuig();
    voertuig.setNextVoertuig(voertuig1);
    EXPECT_EQ(voertuig.getNextVoertuig(),voertuig1);
}

TEST_F(VoertuigTest, GetDeleteObjectWorking){

    voertuig.setDeleteObject(true);
    EXPECT_EQ(voertuig.isDeleteObject(),true);
}

/// TEST updatePosition
TEST_F(VoertuigTest, UpdatePositionRequire){

    voertuig.set_initCheck(false);
    EXPECT_DEATH(voertuig.updatePosition(),"");
}

TEST_F(VoertuigTest, UpdatePositionEnsureMaxSpeed){

    Baan* baan = new Baan();
    baan->setSnelheidsLimiet(120);
    baan->setLengte(1000);
    baan->setNaam("E12");

    voertuig.setBaanObject(baan);
    voertuig.setSnelheid(120);
    voertuig.setBaan("E12");
    voertuig.setPositie(10);

    voertuig.updatePosition();
    EXPECT_EQ(voertuig.getSnelheid(),120);
}

TEST_F(VoertuigTest, UpdatePositionEnsureMaxPosition){

    Baan* baan = new Baan();
    baan->setSnelheidsLimiet(120);
    baan->setLengte(1000);
    baan->setNaam("E12");

    voertuig.setBaanObject(baan);
    voertuig.setSnelheid(120);
    voertuig.setBaan("E12");
    voertuig.setPositie(999);

    voertuig.updatePosition();
    EXPECT_EQ(voertuig.getPositie(),0);
}
