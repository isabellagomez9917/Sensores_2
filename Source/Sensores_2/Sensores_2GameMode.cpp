// Copyright Epic Games, Inc. All Rights Reserved.

#include "Sensores_2GameMode.h"
#include "Sensores_2Pawn.h"
#include "Sensores_2Hud.h"

ASensores_2GameMode::ASensores_2GameMode()
{
	DefaultPawnClass = ASensores_2Pawn::StaticClass();
	HUDClass = ASensores_2Hud::StaticClass();
}
