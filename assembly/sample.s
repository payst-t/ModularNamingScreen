.text
.thumb

.include "event_macros.s"

PalletTown_EventScript_FatMan:
    lock
    faceplayer
    setvar 0x800D 0
    setvar 0x8004 0
    callnative NS_LoadCustomNS
    waitstate
    msgbox PalletTown_TextNameEntered MSGBOX_NPC
    release
    end
