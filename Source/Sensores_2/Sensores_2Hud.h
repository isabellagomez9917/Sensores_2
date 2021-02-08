// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Sensores_2Hud.generated.h"

UCLASS(config = Game)
class ASensores_2Hud : public AHUD
{
	GENERATED_BODY()

public:
	ASensores_2Hud();

	/** Font used to render the vehicle info */
	UPROPERTY()
	UFont* HUDFont;

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface

};
