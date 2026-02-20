// Fill out your copyright notice in the Description page of Project Settings.


#include "BallWithPhysics.h"

#include "Misc/MapErrors.h"

// Sets default values
ABallWithPhysics::ABallWithPhysics()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetReplicateMovement(true);
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;
	
	StaticMesh->SetIsReplicated(true);
	StaticMesh->SetSimulatePhysics(false);
}

// Called when the game starts or when spawned
void ABallWithPhysics::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		StaticMesh->SetSimulatePhysics(true);
	}
}

// Called every frame
void ABallWithPhysics::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!HasAuthority())
	{
		SetActorLocationAndRotation(
			FMath::VInterpTo(GetActorLocation(), TargetLocation, DeltaTime, 15.0f),
			FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, 15.0f)
		);
	}
}

void ABallWithPhysics::OnRep_ReplicatedMovement()
{
	FVector OldLocation = GetActorLocation();
	FRotator OldRotation = GetActorRotation();

	Super::OnRep_ReplicatedMovement(); // engine snaps to new position

	TargetLocation = GetActorLocation(); // grab where we snapped to
	TargetRotation = GetActorRotation();

	SetActorLocationAndRotation(OldLocation, OldRotation); // restore old so Tick calerp
}
