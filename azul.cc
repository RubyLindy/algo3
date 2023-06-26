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
}  // drukAfBord

//****************************************************************************
int Azul::extrascore(pair <int, int> zet){
  int rij = zet.first;
  int kolom = zet.second;
  int score_h = 0;
  int score_v = 0;

  for (int i = rij; i >= 0; i--){
    if (bord[i][kolom] == 1) {
      score_v++;
    }
    else {
      break;
    }
  }
  for (int i = rij + 1; i < hoogte; i++){
    if (bord[i][kolom] == 1) {
      score_v++;
    }
    else {
      break;
    }
  }
  for (int i = kolom; i >= 0; i--){
    if (bord[rij][i] == 1) {
      score_h++;
    }
    else {
      break;
    }
  }
  for (int i = kolom + 1; i < breedte; i++){
    if (bord[rij][i] == 1) {
      score_h++;
    }
    else {
      break;
    }
  }
  if (score_h == 1) {
    return score_v;
  }
  if (score_v == 1) {
    return score_h;
  }
  else {
    return score_h + score_v;
  }
};

//****************************************************************************
bool Azul::doeZet (int rij, int kolom)
{
  if (!geldigBord) {
    // cout << "test" << endl;
    return false;
  }
  if(!integerInBereik(rij, 0, hoogte-1) || 
    !integerInBereik(kolom, 0, breedte-1)){
    // cout << "teste" << endl;
    return false;
  }
  if (bord[rij][kolom] == 1) {
    // cout << "testen" << endl;
    return false;
  }

  bord[rij][kolom] = 1;
  zetten.push_back(make_pair(rij, kolom));
  totaalscore += extrascore(make_pair(rij,kolom));
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
  totaalscore -= extrascore(zet);
  bord[zet.first][zet.second] = 0;
  zetten.pop_back();
  return true;

}  // unDoeZet

//****************************************************************************
bool Azul::isvol() {
  for (int i = 0; i < hoogte; i++) {
    for (int j = 0; j < breedte; j++) {
      if (bord[i][j] == 0) {
        return false;
      }
    }
  }
  return true;
}


void Azul:: recursiefminimaxi(int &mini, long long &volgordesMini, 
                                int &maxi, long long &volgordesMaxi) {
  if(isvol()){
    if (totaalscore > maxi) {
      maxi = totaalscore;
      volgordesMaxi = 1;
    }
    else if (totaalscore == maxi) {
      volgordesMaxi++;
    }
    if (totaalscore < mini) {
      mini = totaalscore;
      volgordesMini = 1;
    }
    else if (totaalscore == mini) {
      volgordesMini++;
    }
    // return;
  }

  for(int i = 0; i < hoogte; i++){
    for(int j = 0; j < breedte; j++){
      if(doeZet(i,j)){
        recursiefminimaxi(mini, volgordesMini, maxi, volgordesMaxi);
        unDoeZet();
      }
    }
  }

}

bool Azul::bepaalMiniMaxiScoreRec (int &mini, long long &volgordesMini,
                                   int &maxi, long long &volgordesMaxi)
{
    // Bepaal rechtstreeks recursief de minimale en de maximale totaalscore
    // die gehaald kunnen worden als je het bord compleet wil bedekken met
    // tegels, uitgaande van de huidige bedekking van het bord.
    // Bepaal ook met hoeveel volgordes je deze scores kunt bereiken.
    // Controleer eerst of er een geldig bord is.
    // Retourneer:
    // * true, als er een geldig bord is
    // * false, anders
    // Post:
    // * Als er een geldig bord is, bevatten parameters mini, volgordesMini,
    //   maxi en volgordesMaxi de gezochte waardes.
    // * De bedekking van het bord is niet veranderd.
  // TODO: implementeer deze memberfunctie
  if (!geldigBord) {
    return false;
  }
  mini = INT_MAX;
  maxi = INT_MIN;
  volgordesMaxi = 0;
  volgordesMini = 0;
  recursiefminimaxi(mini,volgordesMini, maxi, volgordesMaxi);
  return true;

}  // bepaalMiniMaxiScoreRec

//*************************************************************************
int Azul::encode() {
  int encoded = 0;
  int index = 0;
  for (int i = 0; i < hoogte; i++) {
      for (int j = 0; j < breedte; j++) {
          if (bord[i][j] == 1) {
              encoded |= (1 << index);
          }
          else if (bord[i][j] == 0) {
            encoded &= ~(1 << index);
          }
          index++;
      }
  }
  return encoded;
}

void Azul::decode(){

}

void Azul::topdownminimax(int &mini, long long &volgordesMini, 
                          int &maxi, long long &volgordesMaxi) {
  
}

bool Azul::bepaalMiniMaxiScoreTD (int &mini, long long &volgordesMini,
                                  int &maxi, long long &volgordesMaxi)
{
  // TODO: implementeer deze memberfunctie
  if (!geldigBord) {
    return false;
  }
  mini = INT_MAX;
  maxi = INT_MIN;
  volgordesMaxi = 0;
  volgordesMini = 0;
  cout << encode() << endl;
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

