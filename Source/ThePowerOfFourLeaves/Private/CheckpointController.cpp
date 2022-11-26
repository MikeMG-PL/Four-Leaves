// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointController.h"

#include "Components/BoxComponent.h"
#include "ThePowerOfFourLeaves/ThePowerOfFourLeavesCharacter.h"
#include "ThePowerOfFourLeaves/Public/LifeComponent.h"

// Sets default values
ACheckpointController::ACheckpointController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACheckpointController::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<AThePowerOfFourLeavesCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());

	if (PlayerCharacter == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No PlayerController found!"));
		return;
	}

	if (PlayerCharacter->GetComponentByClass(ULifeComponent::StaticClass()) == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No LifeComponent found!"));
		return;
	}

	LastSavedPosition = PlayerCharacter->GetActorLocation();

	for (const AActor* Checkpoint : Checkpoints)
	{
		UBoxComponent* Collider = Checkpoint->FindComponentByClass<UBoxComponent>();

		if (Collider != nullptr)
		{
			CheckpointsColliders.Add(Collider);
			Collider->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointController::OnCheckpointOverlapBegin);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Box collision component not found on the checkpoint object!"));
		}
	}

	PlayerLife = Cast<ULifeComponent>(PlayerCharacter->GetComponentByClass(ULifeComponent::StaticClass()));

	PlayerLife->OnDeath.AddDynamic(this, &ACheckpointController::OnPlayerRespawn);
}

// Called every frame
void ACheckpointController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpointController::OnPlayerRespawn()
{
	UE_LOG(LogTemp, Error, TEXT("Respawn!"));
	PlayerLife->CurrentNumberOfLifes = PlayerLife->DefaultNumberOfLifes;
	PlayerCharacter->SetActorLocation(LastSavedPosition, false, nullptr, ETeleportType::None);
}

void ACheckpointController::OnCheckpointOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AThePowerOfFourLeavesCharacter>(OtherActor) == nullptr)
		return;

	LastSavedPosition = OverlappedComp->GetComponentLocation();
}
