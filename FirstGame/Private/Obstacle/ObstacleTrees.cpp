// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle/ObstacleTrees.h"

// Sets default values
AObstacleTrees::AObstacleTrees()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
}

// Called when the game starts or when spawned
void AObstacleTrees::BeginPlay()
{
	Super::BeginPlay();
	
}

void AObstacleTrees::SpawnObstancle()
{	
	for (size_t i = 0; i < Obstancle.Num() ; i++)
	{
		if (Obstancle[i]) {
			Obstancle[i]->DestroyComponent();
		}
	}

	Obstancle.Empty();

	for (size_t i = 0; i < NumberOfObstancle; i++)
	{
		UStaticMeshComponent* smc = (UStaticMeshComponent*)AddComponentByClass(
			UStaticMeshComponent::StaticClass(), 
			false, 
			FTransform(), 
			true);

		if (smc) {
			smc->RegisterComponent();
			smc->SetMobility(EComponentMobility::Movable);
			smc->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			smc->SetWorldLocation(GetActorLocation() + FVector(ObstancleDistance * i, 0, 0));
			smc->SetWorldScale3D(FVector(1, 1, FMath::RandRange(1, 4)));
			smc->SetStaticMesh(ObstancleMesh);
			Obstancle.Add(smc);
		}
	}
}

void AObstacleTrees::OnConstruction(const FTransform& Transform)
{
	SpawnObstancle();
}


// Called every frame
void AObstacleTrees::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

