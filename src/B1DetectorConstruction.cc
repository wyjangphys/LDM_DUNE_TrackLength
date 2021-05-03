//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"
#include "LArSD.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4FieldManager.hh"
#include "G4MagneticField.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4UniformMagField.hh"
#include "G4SDManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fWorldVolume(0),
  fScoringVolume(0),
  fMagBoxVolume(0),
  fDetectorVolume(0),
  fTargetVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  // Envelope parameters
  //
  G4double env_sizeXY = 0.85 * cm, env_sizeZ = 1.5 * m;
  //G4double env_sizeXY = 8.5 * cm, env_sizeZ = 1.5 * m;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_C");

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //
  // World
  //
  G4double world_sizeXY = 3.0*env_sizeXY;
  G4double world_sizeZ  = 1.5*env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");

  G4Box* solidWorld =
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  //
  // Graphite target
  //
  G4Tubs* target =
    new G4Tubs("target",
        0,
        env_sizeXY,
        env_sizeZ,
        0,
        2.*3.14159265358979323846);

  G4LogicalVolume* logicTarget =
    new G4LogicalVolume(target,            //its solid
                        env_mat,             //its material
                        "Target");         //its name

  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicTarget,                //its logical volume
                    "Target",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  // Magnetic Field Box
  /*
    G4Box* magBox =
    new G4Box("magBox",
        0.5*1*m,
        0.5*1*m,
        0.5*1*m);
  G4LogicalVolume* logicMagBox =
    new G4LogicalVolume(magBox,
        world_mat,
        "magBox");
  new G4PVPlacement(0,
      G4ThreeVector(0, 0, 5*m),
      logicMagBox,
      "magBox",
      logicWorld,
      false,
      0,
      checkOverlaps);
      */

  // LAr Detector Volume
  /*
  G4double ndx = 7.0*m;
  G4double ndy = 3.0*m;
  G4double ndz = 5.0*m;
  G4double a = 207.19*g/mole;
  G4double density = 11.35*g/cm3;
  G4double z = 18;
  G4Material* LiquidArgon = new G4Material("LiquidArgon", z, a, density);
  G4Box* detVolume =
    new G4Box("detVolume",
        0.5*ndx,
        0.5*ndy,
        0.5*ndz);
  G4LogicalVolume* logicDetectorVolume =
    new G4LogicalVolume(detVolume,
        LiquidArgon,
        "detVolume");
  new G4PVPlacement(0,
      G4ThreeVector(0, 0, 0.75*m + 574.*m + 0.5*ndz),
      logicDetectorVolume,
      "detVolume",
      logicWorld,
      false,
      0,
      checkOverlaps);
      */


  // Set iron dump as scoring volume
  //
  fScoringVolume = logicTarget;
  fTargetVolume = logicTarget;
  //fMagBoxVolume = logicMagBox;
  //fDetectorVolume = logicDetectorVolume;
  fDetectorVolume = logicTarget; // 임시로 이렇게 저장함. 나중에 고쳐야함.

  //
  //always return the physical World
  //
  return physWorld;
}

/*
void B1DetectorConstruction::ConstructSDandField()
{
  // Field setup
  G4MagneticField* magField = new G4UniformMagField(G4ThreeVector(0.*tesla, 0., 0.)); // currently, turned off (zero tesla)
  G4FieldManager* localFieldMgr = new G4FieldManager(magField);
  fMagBoxVolume->SetFieldManager(localFieldMgr, true);

  // Sensitive detectors
  auto lArSD = new LArSD("lArSD", "lArHitsCollection", 1);
  G4SDManager::GetSDMpointer()->AddNewDetector(lArSD);
  SetSensitiveDetector("detVolume", lArSD);
}
*/
