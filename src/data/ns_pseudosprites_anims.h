#include "../../pret_include/sprite.h"

static const union AnimCmd NS_SAnim_LLetter[] = {
    ANIMCMD_FRAME(0, 2),
    ANIMCMD_FRAME(1, 2),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const NS_SAnims_LLetter[] = {
    NS_SAnim_LLetter,
};