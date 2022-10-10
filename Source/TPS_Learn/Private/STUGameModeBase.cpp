// Fill out your copyright notice in the Description page of Project Settings.


#include "STUGameModeBase.h"
#include"STUCharacter.h"
#include"STUPlayerController.h"
#include <STUGameHUD.h>

ASTUGameModeBase::ASTUGameModeBase()
{
	DefaultPawnClass = ASTUCharacter::StaticClass();
	PlayerControllerClass = ASTUPlayerController::StaticClass();
	HUDClass = ASTUGameHUD::StaticClass();
}
