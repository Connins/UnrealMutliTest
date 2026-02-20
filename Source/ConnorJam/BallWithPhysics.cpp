// Fill out your copyright notice in the Description page of Project Settings.


#include "BallWithPhysics.h"

// Sets default values
ABallWithPhysics::ABallWithPhysics()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetReplicateMovement(true);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	
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

}

