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
/// \file B1EventAction.cc
/// \brief Implementation of the B1EventAction class

#include "B1EventAction.hh"
#include "TAMUALP_CalorimeterSD.hh"
#include "TAMUALP_CalorHit.hh"

#include "B1RunAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/*
B1EventAction::B1EventAction(B1RunAction* runAction)
: G4UserEventAction(),
  fAbsHCID(-1)
{}
*/
B1EventAction::B1EventAction(B1RunAction* runAction)
: G4UserEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1EventAction::~B1EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/*
TAMUALP_CalorHitsCollection* B1EventAction::GetHitsCollection(G4int hcID,
                                                              const G4Event* event) const
{
  auto hitsCollection
    = static_cast<TAMUALP_CalorHitsCollection*>(
        event->GetHCofThisEvent()->GetHC(hcID));

  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    G4Exception("B1EventAction::GetHitsCollection()",
        "MyCode0003", FatalException, msg);
  }

  return hitsCollection;
}
*/

/*
void B1EventAction::PrintEventStatistics(
    G4double absoEdep, G4double absoTrackLength) const
{
  // print event statistics
  G4cout
    << "    Absorber: total energy: "
    << std::setw(7) << G4BestUnit(absoEdep, "Energy")
    << "      total track length: "
    << std::setw(7) << G4BestUnit(absoTrackLength, "Length")
    << G4endl;
}
*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1EventAction::BeginOfEventAction(const G4Event*)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1EventAction::EndOfEventAction(const G4Event* event)
{
  /*
  // Get hits collections IDs (only once)
  if ( fAbsHCID == -1 ) {
    fAbsHCID
      = G4SDManager::GetSDMpointer()->GetCollectionID("lArHitsCollection");
  }

  // Get hits collections
  auto absoHC = GetHitsCollection(fAbsHCID, event);

  // Get hit with total values
  auto absoHit = (*absoHC)[absoHC->entries()-1];
  */

  // Print per event (modulo n)
  event->Print();

  // Fill histograms, ntuple

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
