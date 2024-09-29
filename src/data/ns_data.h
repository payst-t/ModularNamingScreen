#include "../../include/naming_screen.h"

extern const struct NamingScreenTemplate NS_SPlayerNSTemplate;
extern const struct NamingScreenTemplate NS_SBoxNamingNSTemplate;
extern const struct NamingScreenTemplate NS_SMonNamingNSTemplate;
extern const struct NamingScreenTemplate NS_SRivalNamingNSTemplate;

const struct NamingScreenTemplate NS_SCustomSpriteNSTemplate;

void (*const NS_SIconFunctions[])(void) = {
    NS_IconFunc_NoIcon,
    NS_IconFunc_PlayerIcon,
    NS_IconFunc_PCIcon,
    NS_IconFunc_MonIcon,
    NS_IconFunc_RivalIcon,
    NS_IconFunc_CustomSprite,
};

void (*const NS_SDTEFunctions[])(void) = {
    [NAMING_SCREEN_PLAYER] = NS_DTEFunc_Normal,
    [NAMING_SCREEN_BOX] = NS_DTEFunc_Normal,
    [NAMING_SCREEN_CAUGHT_MON] = NS_DTEFunc_Mon,
    [NAMING_SCREEN_NICKNAME] = NS_DTEFunc_Mon,
    [NAMING_SCREEN_RIVAL] = NS_DTEFunc_Normal,
    [NAMING_SCREEN_CUSTOM_SPRITE] = NS_DTEFunc_Normal,
};

const struct NamingScreenTemplate *const NS_SNSTemplates[] = {
    [NAMING_SCREEN_PLAYER] = &NS_SPlayerNSTemplate,
    [NAMING_SCREEN_BOX] = &NS_SBoxNamingNSTemplate,
    [NAMING_SCREEN_CAUGHT_MON] = &NS_SMonNamingNSTemplate,
    [NAMING_SCREEN_NICKNAME] = &NS_SMonNamingNSTemplate,
    [NAMING_SCREEN_RIVAL] = &NS_SRivalNamingNSTemplate,
    [NAMING_SCREEN_CUSTOM_SPRITE] = &NS_SCustomSpriteNSTemplate,
};

static const struct OamData NS_SOam_16x32 = {
    .x = 0,
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(16x32),
    .size = SPRITE_SIZE(16x32),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
};

static u8 *const NS_SStringBuffers[] = {
    gStringVar1,
    gStringVar2,
    gStringVar3,
    gStringVar4,
};

static const u8 NS_SSomeName[PLAYER_NAME_LENGTH + 1] = {
    CHAR_O,
    CHAR_A,
    CHAR_K,
    EOS,
    EOS,
    EOS,
    EOS,
    EOS,
};

static const u8 NS_SEnterText[] = {
    CHAR_E,
    CHAR_N,
    CHAR_T,
    CHAR_E,
    CHAR_R,
    CHAR_SPACE,
    CHAR_T,
    CHAR_E,
    CHAR_X,
    CHAR_T,
    CHAR_COLON,
    EOS,
};

const struct NamingScreenTemplate NS_SCustomSpriteNSTemplate = {
    .copyExistingString = FALSE,
    .maxChars = PLAYER_NAME_LENGTH,
    .iconFunction = 5,
    .addGenderIcon = FALSE,
    .initialPage = KBPAGE_LETTERS_UPPER,
    .title = NS_SEnterText,
};

#include "ns_pseudosprites_images.h"
#include "ns_pseudosprites_anims.h"

#define NS_PSEUDOSPRITE(a, i) {a, i}

static const struct
{
    const union AnimCmd *const *anims;
    const struct SpriteFrameImage *images;
    const u16 *paletteData;
} NS_SPseudoSprites[] = {
    {NS_SAnims_LLetter, NS_SImageTable_LLetter, l_0Pal},
};