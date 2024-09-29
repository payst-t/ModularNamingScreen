#ifndef NAMING_SCREEN_H_INCLUDED
#define NAMING_SCREEN_H_INCLUDED

#include "../pret_include/naming_screen.h"
#include "../pret_include/overworld.h"
#include "../pret_include/string_util.h"
#include "../pret_include/event_data.h"
#include "../pret_include/global.h"
#include "../pret_include/characters.h"

enum
{
    WIN_KB_PAGE_1, // Which of these two windows is in front is cycled as the player swaps
    WIN_KB_PAGE_2, // Initially WIN_KB_PAGE_1 is in front, with WIN_KB_PAGE_2 on deck
    WIN_TEXT_ENTRY,
    WIN_TEXT_ENTRY_BOX,
    WIN_BANNER,
    WIN_COUNT,
};

enum
{
    PALTAG_MENU, // Also the PC icon
    PALTAG_PAGE_SWAP_UPPER,
    PALTAG_PAGE_SWAP_LOWER,
    PALTAG_PAGE_SWAP_OTHERS, // Also the input arrow/underscore
    PALTAG_PAGE_SWAP,
    PALTAG_CURSOR,
    PALTAG_BACK_BUTTON,
    PALTAG_OK_BUTTON,
    PALTAG_RIVAL = 255,
};

enum
{
    KBPAGE_SYMBOLS,
    KBPAGE_LETTERS_UPPER,
    KBPAGE_LETTERS_LOWER,
    KBPAGE_COUNT,
};

struct NamingScreenTemplate
{
    u8 copyExistingString;
    u8 maxChars;
    u8 iconFunction;
    u8 addGenderIcon;
    u8 initialPage;
    const u8 *title;
};

struct NamingScreenData
{
    /*0x0*/ u8 tilemapBuffer1[0x800];
    /*0x800*/ u8 tilemapBuffer2[0x800];
    /*0x800*/ u8 tilemapBuffer3[0x800];
    /*0x1800*/ u8 textBuffer[0x10];
    /*0x1810*/ u8 tileBuffer[0x600];
    /*0x1E10*/ u8 state;
    /*0x1E11*/ u8 windows[WIN_COUNT];
    /*0x1E16*/ u16 inputCharBaseXPos;
    /*0x1E18*/ u16 bg1vOffset;
    /*0x1E1A*/ u16 bg2vOffset;
    /*0x1E1C*/ u16 bg1Priority;
    /*0x1E1E*/ u16 bg2Priority;
    /*0x1E20*/ u8 bgToReveal;
    /*0x1E21*/ u8 bgToHide;
    /*0x1E22*/ u8 currentPage;
    /*0x1E23*/ u8 cursorSpriteId;
    /*0x1E24*/ u8 swapBtnFrameSpriteId;
    /*0x1E25*/ u8 keyRepeatStartDelayCopy;
    /*0x1E28*/ const struct NamingScreenTemplate *template;
    /*0x1E2C*/ u8 templateNum;
    /*0x1E30*/ u8 *destBuffer;
    /*0x1E34*/ u16 monSpecies;
    /*0x1E36*/ u16 monGender;
    /*0x1E38*/ u32 monPersonality;
    /*0x1E3C*/ MainCallback returnCallback;
};

// Alternative save block struct that uses
// some of the unused bytes for a professorName field.
typedef struct
{
    /*0x0000*/ struct Coords16 pos;
    /*0x0004*/ struct WarpData location;
    /*0x000C*/ struct WarpData continueGameWarp;
    /*0x0014*/ struct WarpData dynamicWarp;
    /*0x001C*/ struct WarpData lastHealLocation;
    /*0x0024*/ struct WarpData escapeWarp;
    /*0x002C*/ u16 savedMusic;
    /*0x002E*/ u8 weather;
    /*0x002F*/ u8 weatherCycleStage;
    /*0x0030*/ u8 flashLevel;
    /*0x0032*/ u16 mapLayoutId;
    /*0x0034*/ u8 playerPartyCount;
    /*0x0038*/ struct Pokemon playerParty[PARTY_SIZE];
    /*0x0290*/ u32 money;
    /*0x0294*/ u16 coins;
    /*0x0296*/ u16 registeredItem; // registered for use with SELECT button
    /*0x0298*/ struct ItemSlot pcItems[PC_ITEMS_COUNT];
    /*0x0310*/ struct ItemSlot bagPocket_Items[BAG_ITEMS_COUNT];
    /*0x03b8*/ struct ItemSlot bagPocket_KeyItems[BAG_KEYITEMS_COUNT];
    /*0x0430*/ struct ItemSlot bagPocket_PokeBalls[BAG_POKEBALLS_COUNT];
    /*0x0464*/ struct ItemSlot bagPocket_TMHM[BAG_TMHM_COUNT];
    /*0x054c*/ struct ItemSlot bagPocket_Berries[BAG_BERRIES_COUNT];
    /*0x05F8*/ u8 seen1[DEX_FLAGS_NO];
    /*0x062C*/ u16 berryBlenderRecords[3]; // unused
    /*0x0632*/ u8 unused_632[6];
    /*0x0638*/ u16 trainerRematchStepCounter;
    /*0x063A*/ u8 ALIGNED(2) trainerRematches[MAX_REMATCH_ENTRIES];
    /*0x06A0*/ struct ObjectEvent objectEvents[OBJECT_EVENTS_COUNT];
    /*0x08E0*/ struct ObjectEventTemplate objectEventTemplates[OBJECT_EVENT_TEMPLATES_COUNT];
    /*0x0EE0*/ u8 flags[NUM_FLAG_BYTES];
    /*0x1000*/ u16 vars[VARS_COUNT];
    /*0x1200*/ u32 gameStats[NUM_GAME_STATS];
    /*0x1300*/ struct QuestLog questLog[QUEST_LOG_SCENE_COUNT];
    /*0x2CA0*/ u16 easyChatProfile[EASY_CHAT_BATTLE_WORDS_COUNT];
    /*0x2CAC*/ u16 easyChatBattleStart[EASY_CHAT_BATTLE_WORDS_COUNT];
    /*0x2CB8*/ u16 easyChatBattleWon[EASY_CHAT_BATTLE_WORDS_COUNT];
    /*0x2CC4*/ u16 easyChatBattleLost[EASY_CHAT_BATTLE_WORDS_COUNT];
    /*0x2CD0*/ struct Mail mail[MAIL_COUNT];
    /*0x2F10*/ u8 additionalPhrases[NUM_ADDITIONAL_PHRASE_BYTES];
    /*0x2F18*/ OldMan oldMan;                        // unused
    /*0x2F54*/ struct DewfordTrend dewfordTrends[5]; // unused
    /*0x2F80*/ struct DayCare daycare;
    /*0x309C*/ u8 giftRibbons[GIFT_RIBBONS_COUNT];
    /*0x30A7*/ struct ExternalEventData externalEventData;
    /*0x30BB*/ struct ExternalEventFlags externalEventFlags;
    /*0x30D0*/ struct Roamer roamer;
    /*0x30EC*/ struct EnigmaBerry enigmaBerry;
    /*0x3120*/ struct MysteryGiftSave mysteryGift;
    /*0x348C*/ u8 professorName[PLAYER_NAME_LENGTH + 1];
    /*0x3494*/ u8 unused_348C[400 - (PLAYER_NAME_LENGTH + 1)];
    /*0x361C*/ struct RamScript ramScript;
    /*0x3A08*/ struct RecordMixingGift recordMixingGift; // unused
    /*0x3A18*/ u8 seen2[DEX_FLAGS_NO];
    /*0x3A4C*/ u8 rivalName[PLAYER_NAME_LENGTH + 1];
    /*0x3A54*/ struct FameCheckerSaveData fameChecker[NUM_FAMECHECKER_PERSONS];
    /*0x3A94*/ u8 unused_3A94[64];
    /*0x3AD4*/ u8 registeredTexts[UNION_ROOM_KB_ROW_COUNT][21];
    /*0x3BA8*/ struct TrainerNameRecord trainerNameRecords[20];
    /*0x3C98*/ struct DaycareMon route5DayCareMon;
    /*0x3D24*/ u8 unused_3D24[16];
    /*0x3D34*/ u32 towerChallengeId;
    /*0x3D38*/ struct TrainerTower trainerTower[NUM_TOWER_CHALLENGE_TYPES];
} SB1Alt_t; // size: 0x3D68

void NS_IconFunc_NoIcon(void);
void NS_IconFunc_PlayerIcon(void);
void NS_IconFunc_PCIcon(void);
void NS_IconFunc_MonIcon(void);
void NS_IconFunc_RivalIcon(void);
void NS_IconFunc_CustomSprite(void);

void NS_DTEFunc_Normal(void);
void NS_DTEFunc_Mon(void);

#endif // NAMING_SCREEN_H_INCLUDED