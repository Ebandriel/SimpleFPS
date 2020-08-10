// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AActor* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	FVector AILocation;
	FRotator AIRotation;
	GetPlayerViewPoint(AILocation, AIRotation);
	if (PlayerPawn != nullptr)
	{
		if (LineOfSightTo(PlayerPawn, AILocation))
		{
			SetFocus(PlayerPawn);
			MoveToActor(PlayerPawn, 200.0f, false, true);
		}
		else
		{
			ClearFocus(EAIFocusPriority::Default);
			StopMovement();
		}
	}
}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	AActor* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn != nullptr)
	{
		SetFocus(PlayerPawn);
		MoveToActor(PlayerPawn,200.0f,false,true);
	}
}
