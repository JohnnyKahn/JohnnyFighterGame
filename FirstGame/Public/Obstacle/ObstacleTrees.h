// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleTrees.generated.h"

UCLASS()
class FIRSTGAME_API AObstacleTrees : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnyWhere)
	TArray<UStaticMeshComponent*> Obstancle;

	UPROPERTY(EditAnyWhere)
	int NumberOfObstancle = 10;

	UPROPERTY(EditAnyWhere)
	float ObstancleDistance = 300.0f;

	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* ObstancleMesh;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* Root;

	UFUNCTION(BlueprintCallable)
	void SpawnObstancle();

public:	
	// Sets default values for this actor's properties
	AObstacleTrees();
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;



};
