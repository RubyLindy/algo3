// Implementatie van klasse Azul

#include <iostream>
#include <fstream>
#include "standaard.h"
#include "azul.h"
using namespace std;

//*************************************************************************

Azul::Azul ()
{
  geldigBord = false;
  totaalscore = 0;
}  // default constructor

//*************************************************************************

Azul::Azul (int nwHoogte, int nwBreedte)
{
  if(!integerInBereik(nwHoogte, MinDimensie, MaxDimensie) || 
    !integerInBereik(nwBreedte, MinDimensie, MaxDimensie)){
    return;
  }
  totaalscore = 0;
  geldigBord = true;
  hoogte = nwHoogte;
  breedte = nwBreedte;
  for (int i = 0; i < hoogte; i++) {
    for (int j = 0; j < breedte; j++) {
      bord[i][j] = 0;
    }
  }

}  // constructor met parameters

//*************************************************************************

Azul::~Azul ()
{
  // TODO: implementeer zo nodig deze destructor

}  // destructor

//*************************************************************************

int Azul::getVakje (int rij, int kolom)
{ 
  if (!geldigBord) {
    return -1;
  }

  if(!integerInBereik(rij, 0, hoogte-1) || 
    !integerInBereik(kolom, 0, breedte-1)){
    return -1;
  }

  return bord[rij][kolom];

}  // getVakje

//*************************************************************************

bool Azul::leesInBord (const char* invoerNaam)
{
  ifstream fin;
  fin.open(invoerNaam);
  int getal;

  //Controleer of het bestand te openen is
  if ( fin.fail() ) {
    cerr << endl << "Could not open file " << invoerNaam << endl;
    return false;
  }
  //cout << "aaaa" << endl;
  fin >> hoogte;
  fin >> breedte;
  if(!integerInBereik(hoogte, MinDimensie, MaxDimensie) || 
    !integerInBereik(breedte, MinDimensie, MaxDimensie)){
      cerr << endl << "File "<< invoerNaam << " is not valid " << endl;
      return false;
  }
  //cout << "a" << endl;
  for (int i = 0; i < hoogte; i++) {
    for (int j = 0; j < breedte; j++) {
      fin >> getal;
      if ((getal != 0) && (getal != 1)) {
        cerr << endl << "File "<< invoerNaam << " is not valid " << endl;
        return false;
      }
      bord[i][j] = getal;
    }
  }
  //cout << "test" << endl;
  geldigBord = true;
  return geldigBord;

}  // leesInBord

//*************************************************************************

void Azul::drukAfBord ()
{
  if (!geldigBord) {
    return;
  }
  cout << "Totaalscore: " << totaalscore << endl;
  for (int i = 0; i < hoogte; i++) {
    for (int j = 0; j < breedte; j++) {
      cout << bord[i][j] << " ";
    }
    cout<< endl;
  }

  return;
}  // drukAfBord

//****************************************************************************

bool Azul::doeZet (int rij, int kolom)
{
  if (!geldigBord) {
    cout << "test" << endl;
    return false;
  }
  if(!integerInBereik(rij, 0, hoogte-1) || 
    !integerInBereik(kolom, 0, breedte-1)){
    cout << "teste" << endl;
    return false;
  }
  if (bord[rij][kolom] == 1) {
    cout << "testen" << endl;
    return false;
  }

  bord[rij][kolom] = 1;
  zetten.push_back(make_pair(rij, kolom));
  return true;
}  // doeZet

//****************************************************************************

bool Azul::unDoeZet ()
{
  if (!geldigBord) {
    return false;
  }
  // TODO: implementeer deze memberfunctie
  int lengte =zetten.size();
  pair<int, int> zet = zetten[lengte-1];
  bord[zet.first][zet.second] = 0;
  zetten.pop_back();
  return false;

}  // unDoeZet

//****************************************************************************

bool Azul::bepaalMiniMaxiScoreRec (int &mini, long long &volgordesMini,
                                   int &maxi, long long &volgordesMaxi)
{
  // TODO: implementeer deze memberfunctie
  
  return false;

}  // bepaalMiniMaxiScoreRec

//*************************************************************************

bool Azul::bepaalMiniMaxiScoreTD (int &mini, long long &volgordesMini,
                                  int &maxi, long long &volgordesMaxi)
{
  // TODO: implementeer deze memberfunctie

  return false;

}  // bepaalMiniMaxiScoreTD

//*************************************************************************

bool Azul::bepaalMiniMaxiScoreBU (int &mini, long long &volgordesMini,
                                  int &maxi, long long &volgordesMaxi,
                                  vector< pair<int,int> > &zettenReeksMini,
                                  vector< pair<int,int> > &zettenReeksMaxi)
{
  // TODO: implementeer deze memberfunctie

  return false;

}  // bepaalMiniMaxiScoreBU

//*************************************************************************

void Azul::drukAfZettenReeksen (vector<pair <int,int> > &zettenReeksMini,
                                vector<pair <int,int> > &zettenReeksMaxi)
{
  // TODO: implementeer deze memberfunctie

}  // drukAfZettenReeksen

//*************************************************************************

// TODO: implementatie van uw eigen private memberfuncties

