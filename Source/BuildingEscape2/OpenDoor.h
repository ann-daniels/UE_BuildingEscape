// Copyright Anna Danielyan 2022

#pragma once


#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE2_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassOfActors () const;
	void FindAudioComponent();
	bool SoundPlayed = false;

private:

	// float TargetYaw = 90.f;
	float CurrentYaw;
	float InitYaw;
	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.f;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = .2f;

	UPROPERTY(EditAnywhere)
	float DoorOpenVelocity = 0.8f;

	UPROPERTY(EditAnywhere)
	float DoorCloseVelocity = 2.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
	float MassToOpenDoor = 50;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;
	void FindPressurePlate() const;



};
