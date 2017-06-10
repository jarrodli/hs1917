/**********************************************
 * testgame.c
 * 26 April 2017
 * tests the Game ADT interface functions
 * Mirela && Stanley && Jarrod
 */

#include <stdlb.h>
#include <assert.h>

#include "Game.h"

#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ,\
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, \
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, 	   \
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, 	    \
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS}

#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}

void testNewGame(void);
void testmakeAction(void);
void testThrowDice(void);
void testGetDiscipline(void);
void testGetDiceValue(void);
void testGetMostARCs(void);
void testGetMostPublications(void);
void testGetTurnNumber(void);
void testGetWhoseTurn(void);
void testgetCampus(void);
void testGetARC(void);
void testIsLegalAction(void);
void testGetKPIPoints(void);
void testGetARCs(void);
void testGerGO8s(void);
void testGetCampuses(void);
void testsGetIPs(void);
void testsGetPublications(void);
void testGetStudents(void);
void testGetExchangeRate(void);
 
int main(void) {
    // calls test functions
    testNewGame(void);
	testmakeAction(void);
    testThrowDice(void);
	testGetDiscipline(void);
	testGetDiceValue(void);
	testGetMostARCs(void);
	testGetMostPublications(void);
	testGetTurnNumber(void);
	testGetWhoseTurn(void);
	testgetCampus(void);
	testGetARC(void);
	testIsLegalAction(void);
	testGetKPIPoints(void);
	testGetARCs(void);
	testGerGO8s(void);
	testGetCampuses(void);
	testsGetIPs(void);
	testsGetPublications(void);
	testGetStudents(void);
	testGetExchangeRate(void);

    Game newGame (int discipline[], int dice[]);
    void makeAction (Game g, action a);
    void throwDice (Game g, int diceScore);
    int getDiscipline (Game g, int regionID);
    int getDiceValue (Game g, int regionID);
    int getMostARCs (Game g);
    int getMostPublications (Game g);
    int getTurnNumber (Game g);
    int getWhoseTurn (Game g);
    int getCampus(Game g, path pathToVertex);
    int getARC(Game g, path pathToEdge);
    int isLegalAction (Game g, action a);
    int getKPIpoints (Game g, int player);
    int getARCs (Game g, int player);
    int getGO8s (Game g, int player);
    int getCampuses (Game g, int player);
    int getIPs (Game g, int player);
    int getPublications (Game g, int player);
    int getStudents (Game g, int player, int discipline);
    int getExchangeRate (Game g, int player, 
                     int disciplineFrom, int disciplineTo);
    
    return EXIT_SUCCESS;
}

void testNewGame(void) {}
void testmakeAction(void) {}
void testThrowDice(void) {}
void testGetDiscipline(void) {}
void testGetDiceValue(void) {}
void testGetMostARCs(void) {}
void testGetMostPublications(void) {}
void testGetTurnNumber(void) {}
void testGetWhoseTurn(void) {}
void testgetCampus(void) {}
void testGetARC(void) {}
void testIsLegalAction(void) {}
void testGetKPIPoints(void) {}
void testGetARCs(void) {}
void testGerGO8s(void) {}
void testGetCampuses(void) {}
void testsGetIPs(void) {}
void testsGetPublications(void) {}
void testGetStudents(void) {}
void testGetExchangeRate(void) {}