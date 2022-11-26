// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckpointController.generated.h"

class ULifeComponent;
class UBoxComponent;
class AThePowerOfFourLeavesCharacter;

UCLASS()
class THEPOWEROFFOURLEAVES_API ACheckpointController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpointController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> Checkpoints;

	UFUNCTION()
	void OnPlayerRespawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere)
	TArray<UBoxComponent*> CheckpointsColliders;

	UPROPERTY(EditAnywhere)
	FVector LastSavedPosition;

	UFUNCTION()
	void OnCheckpointOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	float Time = 5.f;

	UPROPERTY()
	AThePowerOfFourLeavesCharacter* PlayerCharacter;

	UPROPERTY()
	ULifeComponent* PlayerLife;
};
