// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Sound/SoundBase.h"
// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	if (MuzzleSounds != nullptr)
	{
		
		UGameplayStatics::SpawnSoundAttached(MuzzleSounds, Mesh, TEXT("MuzzleFlashSocket"));
	}
	FHitResult Target;
	FVector ShotDirection;
	if(GunTrace(Target,ShotDirection))
	{
		
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Impact, Target.Location, ShotDirection.Rotation());
		if (ImpactSounds != nullptr)
		{
			
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSounds, Target.Location, ShotDirection.Rotation());
		}
		AActor* HItActor = Target.GetActor();
		if (HItActor != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, Target, ShotDirection, nullptr);
			AController* OwnerController = GetOwnerController();
			HItActor->TakeDamage(Damage,DamageEvent,OwnerController,this);
		}
		//DrawDebugPoint(GetWorld(), Target.Location, 20, FColor::Red, true);
	}

	
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGun::GunTrace(FHitResult& Target, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr)
	{
		return false;
	}
	FVector OwnerLocation;
	FRotator OwnerRotation;
	OwnerController->GetPlayerViewPoint(OwnerLocation, OwnerRotation);
	ShotDirection = -OwnerRotation.Vector();
	FVector End = OwnerLocation + OwnerRotation.Vector() * MaxRange;
	//Line trace
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	return (GetWorld()->LineTraceSingleByChannel(Target, OwnerLocation, End, ECollisionChannel::ECC_GameTraceChannel1, Params));
	

}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
	{
		return nullptr;
	}
	return OwnerPawn->GetController();

}

