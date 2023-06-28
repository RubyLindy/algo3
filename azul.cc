// Implementatie van klasse Azul

#include <iostream>
#include <fstream>
#include <cstring>
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
  if (lengte == 0) {
    return false;
  }
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
    return;
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

void Azul::decode(int encodedBoard){
  for (int i = 0; i < hoogte; i++) {
    for (int j = 0; j < breedte; j++) {
      int mask = 1 << (i * breedte + j);
      int bit = (encodedBoard & mask) ? 1 : 0;
      bord[i][j] = bit;
    }
  }
}

pair <int,int> Azul::topdownminimax(int &mini, long long &volgordesMini, int &maxi, long long &volgordesMaxi, int* minScores, int* maxScores) {
  int newEncodedBoard = encode();
  if (isvol()) {
    int score = totaalscore;
    if (score < mini) {
      mini = score;
      volgordesMini = 1;
    } else if (score == mini) {
      volgordesMini++;
    }

    if (score > maxi) {
      maxi = score;
      volgordesMaxi = 1;
    } else if (score == maxi) {
      volgordesMaxi++;
    }
    // cout << totaalscore << endl;
    return make_pair(totaalscore, totaalscore);
  }

  if (minScores[newEncodedBoard] != -1 && maxScores[newEncodedBoard] != -1) {
    if (totaalscore + minScores[newEncodedBoard] == mini) {
      volgordesMini++;
    }
    else if ((totaalscore + minScores[newEncodedBoard]) < mini) {
      mini = totaalscore + minScores[newEncodedBoard];
      volgordesMini = 1;
    }
    if (totaalscore + maxScores[newEncodedBoard] == maxi) {
      volgordesMaxi++;
    }
    else if ((totaalscore + maxScores[newEncodedBoard]) > maxi) {
      maxi = totaalscore + maxScores[newEncodedBoard];
      volgordesMaxi = 1;
    }
    return make_pair(totaalscore + maxScores[newEncodedBoard], totaalscore + minScores[newEncodedBoard]);
  }
  int hulp_min = INT_MAX;
  int hulp_max = INT_MIN;
  pair<int, int> hulp;
  for (int i = 0; i < hoogte; i++) {
    for (int j = 0; j < breedte; j++) {
      if (doeZet(i, j)) {
        hulp = topdownminimax(mini, volgordesMini, maxi, volgordesMaxi, minScores, maxScores);
        if (hulp.second < hulp_min){
          hulp_min = hulp.second;
        }
        if (hulp.first > hulp_max) {
          hulp_max = hulp.first;
        }
        unDoeZet();
      }
    }
  }
  minScores[newEncodedBoard] = hulp_min - totaalscore;
  maxScores[newEncodedBoard] = hulp_max - totaalscore;
  return make_pair(hulp_max, hulp_min);
}

bool Azul::bepaalMiniMaxiScoreTD (int &mini, long long &volgordesMini,
                                  int &maxi, long long &volgordesMaxi)
{
  // TODO: implementeer deze memberfunctie
  if (!geldigBord) {
    return false;
  }
  // cout << "a" << endl;
  int size = 1 << (hoogte * breedte);
  int* minScores = new int[size];
  int* maxScores = new int[size];
  memset(minScores, -1, sizeof(int) * size);
  memset(maxScores, -1, sizeof(int) * size);
  // cout << "d" << endl;
  mini = INT_MAX;
  maxi = INT_MIN;
  volgordesMaxi = 0;
  volgordesMini = 0;
  topdownminimax(mini, volgordesMini, maxi, volgordesMaxi, minScores, maxScores);
  delete[] minScores;
  delete[] maxScores;

  return true;

}  // bepaalMiniMaxiScoreTD

//*************************************************************************

bool Azul::bepaalMiniMaxiScoreBU (int &mini, long long &volgordesMini,
                                  int &maxi, long long &volgordesMaxi,
                                  vector< pair<int,int> > &zettenReeksMini,
                                  vector< pair<int,int> > &zettenReeksMaxi) {
  //this doesnt work
  if (!geldigBord) {
    return false;
  }
  mini = INT_MAX;
  maxi = INT_MIN;
  volgordesMaxi = 0;
  volgordesMini = 0;
  // int size = 1 << (hoogte * breedte);
  // int* minScores = new int[size];
  // int* maxScores = new int[size];
  // memset(minScores, -1, sizeof(int) * size);
  // memset(maxScores, -1, sizeof(int) * size);
    // Initialize the necessary data structures
  vector<int> minScoreTable(1 << (hoogte * breedte), INT_MAX);
  vector<int> maxScoreTable(1 << (hoogte * breedte), INT_MIN);
  vector<long long> volgordesTable(1 << (hoogte * breedte), 0);
  vector<vector<pair<int, int>>> zettenReeksTable(1 << (hoogte * breedte));

  // Set the initial board state
  int initialEncodedBoard = encode();
  minScoreTable[initialEncodedBoard] = totaalscore;
  maxScoreTable[initialEncodedBoard] = totaalscore;
  volgordesTable[initialEncodedBoard] = 1;

  // Perform the bottom-up dynamic programming
  for (int encodedBoard = initialEncodedBoard; encodedBoard < (1 << (hoogte * breedte)); encodedBoard++) {
    if (minScoreTable[encodedBoard] == INT_MAX)
      continue;

    // Decode the board state
    decode(encodedBoard);

    // Perform all possible moves and update the scores
    for (int i = 0; i < hoogte; i++) {
      for (int j = 0; j < breedte; j++) {
        if (doeZet(i, j)) {
          int newEncodedBoard = encode();

          // Update the minimum score and count
          int minScore = minScoreTable[encodedBoard];
          int maxScore = maxScoreTable[encodedBoard];

          if (minScore < minScoreTable[newEncodedBoard]) {
            minScoreTable[newEncodedBoard] = minScore;
            volgordesTable[newEncodedBoard] = volgordesTable[encodedBoard];
            zettenReeksTable[newEncodedBoard] = zettenReeksTable[encodedBoard];
          } else if (minScore == minScoreTable[newEncodedBoard]) {
            volgordesTable[newEncodedBoard] += volgordesTable[encodedBoard];
          }

          // Update the maximum score and count
          if (maxScore > maxScoreTable[newEncodedBoard]) {
            maxScoreTable[newEncodedBoard] = maxScore;
            volgordesTable[newEncodedBoard] = volgordesTable[encodedBoard];
            zettenReeksTable[newEncodedBoard] = zettenReeksTable[encodedBoard];
          } else if (maxScore == maxScoreTable[newEncodedBoard]) {
            volgordesTable[newEncodedBoard] += volgordesTable[encodedBoard];
          }

          // Add the current move to the move sequence
          zettenReeksTable[newEncodedBoard].push_back({i, j});

          unDoeZet();
        }
      }
    }
  }

  // Retrieve the final scores and move sequences
  mini = minScoreTable[initialEncodedBoard];
  volgordesMini = volgordesTable[initialEncodedBoard];
  zettenReeksMini = zettenReeksTable[initialEncodedBoard];

  maxi = maxScoreTable[initialEncodedBoard];
  volgordesMaxi = volgordesTable[initialEncodedBoard];
  zettenReeksMaxi = zettenReeksTable[initialEncodedBoard];
  return true; 
}  // bepaalMiniMaxiScoreBU

//*************************************************************************

void Azul::drukAfZettenReeksen (vector<pair <int,int> > &zettenReeksMini,
                                vector<pair <int,int> > &zettenReeksMaxi)
{
  for (int i = 0; i < zettenReeksMini.size(); i++) {
    cout << zettenReeksMini[i].first << "," << zettenReeksMini[i].second << endl;
  }
}  // drukAfZettenReeksen

//*************************************************************************

// TODO: implementatie van uw eigen private memberfuncties

