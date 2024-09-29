#include "../include/naming_screen.h"
#include "../pret_include/characters.h"
#include "../pret_include/malloc.h"
#include "data/ns_data.h"

#define NS_TEMPLATE_NUM_NONE 0xFF

extern struct NamingScreenData *NS_SNSData;
extern struct SpriteTemplate *NS_SInputTargetST;

extern void CB2_LoadNamingScreen(void);

void NS_CopyStringFromSelectedBuffer(void);
void NS_DummySpriteCB(struct Sprite *);
struct SpriteTemplate *NS_ConstructSpriteTemplate(const u32 spriteId);
void NS_CB2_FreeInputTargetST(void);
void NS_LoadCustomNS(void);

// Copies a string from a specific string buffer
// into a RAM address.
// E.g. copying from buffer1 to 0x02ABCDEF:
// setvar 0x800D 0
// setvar 0x8004 0x02AB
// setvar 0x8005 0xCDEF
void NS_CopyStringFromSelectedBuffer(void)
{
    u16 bufferId;
    u16 hiPtr;
    u16 loPtr;
    u8 *dest;

    bufferId = VarGet(VAR_RESULT) % ARRAY_COUNT(NS_SStringBuffers);
    hiPtr = VarGet(VAR_0x8004);
    loPtr = VarGet(VAR_0x8005);
    dest = (u8 *)((hiPtr << 16) & loPtr);

    StringCopy(dest, NS_SStringBuffers[bufferId]);
}

struct SpriteTemplate *NS_ConstructSpriteTemplate(const u32 spriteId)
{
    struct SpriteTemplate *template = Alloc(sizeof(*template));

    template->tileTag = TAG_NONE;
    template->paletteTag = PALTAG_MENU;
    template->oam = &NS_SOam_16x32;
    template->anims = NS_SPseudoSprites[spriteId].anims;
    template->images = NS_SPseudoSprites[spriteId].images;
    template->affineAnims = gDummySpriteAffineAnimTable;
    template->callback = NS_DummySpriteCB;

    return template;
}

void NS_CB2_FreeInputTargetST(void)
{
    FREE_AND_SET_NULL(NS_SInputTargetST);
    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

void NS_LoadCustomNS(void)
{
    u16 bufferId;

    bufferId = VarGet(VAR_RESULT) % ARRAY_COUNT(NS_SStringBuffers);
    NS_SNSData = Alloc(sizeof(struct NamingScreenData));

    if (NS_SNSData == NULL)
    {
        SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
        return;
    }

    NS_SNSData->templateNum = NAMING_SCREEN_CUSTOM_SPRITE;
    NS_SNSData->monSpecies = 0;
    NS_SNSData->monGender = 0;
    NS_SNSData->monPersonality = 0;
    NS_SNSData->destBuffer = NS_SStringBuffers[bufferId];
    NS_SNSData->returnCallback = NS_CB2_FreeInputTargetST;

    SetMainCallback2(CB2_LoadNamingScreen);
}

void NS_IconFunc_CustomSprite(void)
{
    u32 pseudoSpriteId, spriteId;
    
    pseudoSpriteId = VarGet(VAR_0x8004) % ARRAY_COUNT(NS_SPseudoSprites);
    NS_SInputTargetST = NS_ConstructSpriteTemplate(pseudoSpriteId);
    spriteId = CreateSprite(NS_SInputTargetST, 56, 40, 0);

    gSprites[spriteId].oam.priority = 3;
}

void NS_DummySpriteCB(struct Sprite *) {}
