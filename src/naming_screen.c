#include "../include/naming_screen.h"

/*
* Translates to 'OAK'
*/
const u8 gProfessorName[PLAYER_NAME_LENGTH + 1] = { 0xC9, 0xBB, 0xC5, 0xFF, 0x00, 0x00, 0x00, 0x00 };

/*
* Copies the string's content into buffer1
*
* Note: when calling this function using callasm, **do not** use `waitstate`.
*/
void CopyStringToBuffer(void)
{
    StringCopy(gStringVar1, gSaveBlock1ClonePtr->professorName);
}

/*
* Sets a default professor name so that it isn't empty,
* it gets called by NewGameScripts.
*/ 
void SetProfessorName()
{
    StringCopy(gSaveBlock1ClonePtr->professorName, gProfessorName);
}

/*
* Displays the naming screen with the same parameters
* as the rival naming sequence.
*/
void MainRoutine()
{
    DoNamingScreen(4, gSaveBlock1ClonePtr->professorName, 0, 0, 0, 
        CB2_ReturnToFieldContinueScriptPlayMapMusic);
}