// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class TPS_LEARN_API ASTUGameHUD : public AHUD
{
	GENERATED_BODY()
public:

	virtual void DrawHUD() override;

	void DrawCrossHair();

protected:

	//UCanvas* CanvasComp ;

	
};
