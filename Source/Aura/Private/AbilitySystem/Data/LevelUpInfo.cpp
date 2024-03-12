// Copyright Rong Jieㄘ


#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(int32 XP) const
{
	// int32 TargetLevel = 1;
	// int32 HighestLevel = 1;
	//
	// for (const FAuraLevelUpInfo& Info : LevelUpInformation)
	// {
	// 	const int32 LevelUpRequirement = Info.LevelUpRequirement;
	//
	// 	if (XP > LevelUpRequirement)
	// 	{
	// 		TargetLevel = Info.Level + 1;
	// 	}
	//
	// 	if (Info.Level > HighestLevel)
	// 	{
	// 		HighestLevel = Info.Level;
	// 	}
	// }
	//
	// TargetLevel = FMath::Clamp(TargetLevel, 1, HighestLevel);
	//
	// if (bLogNotFound)
	// {
	// 	UE_LOG(LogAura, Error, TEXT("Can't find Level for XP [%d] on LevelUpInfo [%s]."),
	// 	       XP, *GetNameSafe(this));
	// }
	//
	// UE_LOG(LogAura, Error, TEXT("Finded Level [%d] for XP [%d] on LevelUpInfo [%s]."),
	//        TargetLevel, XP, *GetNameSafe(this));
	//
	// return TargetLevel;

	int32 Level = 1;
	bool bSearching = true;
	while (bSearching)
	{
		if (LevelUpInformation.Num() - 1 <= Level) return Level;

		if (XP >= LevelUpInformation[Level].LevelUpRequirement)
		{
			++Level;
		}
		else
		{
			bSearching = false;
		}
	}
	return Level;
}
