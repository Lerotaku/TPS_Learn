// Fill out your copyright notice in the Description page of Project Settings.


#include "STUGameHUD.h"
#include "Engine/Canvas.h"

void ASTUGameHUD::DrawHUD()
{
	Super::DrawHUD();
	DrawCrossHair();
}

void ASTUGameHUD::DrawCrossHair()
{
	const TInterval<float>center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);
	const float HalfLineSize = 10.0f;
	const float LineThickness = 2.0f;
	const FLinearColor LineColor = FLinearColor::Green;
	
	DrawLine(center.Min - HalfLineSize, center.Max, center.Min + HalfLineSize, center.Max, LineColor, LineThickness);
	DrawLine(center.Min, center.Max - HalfLineSize, center.Min, center.Max + HalfLineSize, LineColor, LineThickness);
}
