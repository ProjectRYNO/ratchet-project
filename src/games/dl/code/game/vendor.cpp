#include "common.h"
#include "game_section.h"

int Vendor_IsCheatOn() __asm__("Vendor_IsCheatOn");
extern unsigned char VendorAvail[] __asm__("aaClearRegs");
extern int g_gameType __asm__("g_gameType");
extern int g_gameRules __asm__("g_gameRules");
int Vendor_IsGadgetAvailableForPurchase(int) __asm__("Vendor_IsGadgetAvailableForPurchase");
extern unsigned char VendorFlags[] __asm__("mcstate_flags");
int IsGameInChallengeMode() __asm__("IsGameInChallengeMode");
int Vendor_IsPostFXModAvailableForPurchase(int) __asm__("Vendor_IsPostFXModAvailableForPurchase");
int Vendor_IsBotUpgradeAvailableForPurchase(int) __asm__("Vendor_IsBotUpgradeAvailableForPurchase");
extern unsigned char WrenchUpgradeLevel __asm__("D_21DAF1");
int Vendor_GetPurchaseableWrenchUpgradeLevel() __asm__("Vendor_GetPurchaseableWrenchUpgradeLevel");


struct VendorItem {
	/* 0x00 */ int type;
	/* 0x04 */ int id;
	/* 0x08 */ int cost;
};
struct HeroSaveData {
	/* 0x00 */ int bolts;
	/* 0x04 */ char unk04[0x20];
};
extern HeroSaveData HeroSave __asm__("HeroSave");
int ST_GetNumRemainingDifficultyStars() __asm__("ST_GetNumRemainingDifficultyStars");
int Vendor_CanPurchaseItem(VendorItem *) __asm__("Vendor_CanPurchaseItem");

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vendor", Vendor_GetAvailableItems);

GAME_SECTION(Vendor_IsCheatOn) int Vendor_IsCheatOn()
{
	return 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vendor", Vendor_CanPurchaseItem);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vendor", FUN_004e7000);

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vendor", func_004E7378);

GAME_SECTION(Vendor_IsGadgetAvailableForPurchase) int Vendor_IsGadgetAvailableForPurchase(int gadgetId)
{
	if (gadgetId == 0x10 && (g_gameType || g_gameRules != 1)) return 0;
	return (VendorAvail + 0x3b18)[gadgetId] != 0;
}

INCLUDE_ASM("/ProjectRYNO/dl/code/asm/nonmatchings/game/vendor", func_004E73D0);

GAME_SECTION(Vendor_IsPostFXModAvailableForPurchase) int Vendor_IsPostFXModAvailableForPurchase(int modId)
{
	int ret = 0;
	if ((VendorFlags + 4)[modId] || IsGameInChallengeMode()) ret = 1;
	return ret;
}

GAME_SECTION(Vendor_IsBotUpgradeAvailableForPurchase) int Vendor_IsBotUpgradeAvailableForPurchase(int upgradeId)
{
	return (VendorAvail + 0x3b30)[upgradeId] != 0;
}

GAME_SECTION(Vendor_GetPurchaseableWrenchUpgradeLevel) int Vendor_GetPurchaseableWrenchUpgradeLevel()
{
	return WrenchUpgradeLevel;
}
