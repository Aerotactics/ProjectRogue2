// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ProjectRogue2HUD.generated.h"

UCLASS()
class AProjectRogue2HUD : public AHUD
{
	GENERATED_BODY()

public:
	AProjectRogue2HUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

