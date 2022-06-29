// Copyright Anna Danielyan 2022

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "OpenDoor.h"
#include "Components/PrimitiveComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	
	InitYaw = GetOwner() -> GetActorRotation().Yaw;
 	CurrentYaw = InitYaw;
	OpenAngle += InitYaw;
	FindAudioComponent();
	FindPressurePlate();

}

void UOpenDoor :: FindAudioComponent() 
{
	AudioComponent = GetOwner() -> FindComponentByClass<UAudioComponent>();

	if(!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing audio component"), *GetOwner() -> GetName());
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{ 
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TotalMassOfActors() > MassToOpenDoor)
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld() -> GetTimeSeconds();
	}
	else
	{	
		
		if (GetWorld() -> GetTimeSeconds() - DoorLastOpened  > DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}
		
	}
	
		
}

void UOpenDoor :: OpenDoor(float DeltaTime) 
{

	CurrentYaw = FMath::Lerp(CurrentYaw, OpenAngle, DeltaTime * DoorOpenVelocity);
	FRotator DoorRotation = GetOwner() -> GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner() -> SetActorRotation(DoorRotation);
	if(!AudioComponent) {return;}
	if(!SoundPlayed)
	{
		UE_LOG(LogTemp, Error, TEXT("Door Opened"));
		AudioComponent->Play();	
		SoundPlayed = true;
	}
		

}

void UOpenDoor :: CloseDoor(float DeltaTime)
{

	CurrentYaw = FMath :: Lerp(CurrentYaw, InitYaw, DeltaTime * DoorCloseVelocity);
	FRotator DoorRotation = GetOwner() -> GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner() -> SetActorRotation(DoorRotation);
	if(!AudioComponent) {return;}
	if (SoundPlayed)
	{
		UE_LOG(LogTemp, Error, TEXT("Door Closed"));
		AudioComponent -> Play();
		SoundPlayed = false;
	}


	
}

float UOpenDoor :: TotalMassOfActors() const
{
	float TotalMass = 0.f;
	// Find all overlapping actors 
	TArray<AActor*> OverlappingActors; 
	if(!PressurePlate) {return TotalMass;}
	PressurePlate -> GetOverlappingActors( OUT OverlappingActors);
	for (AActor* Actor : OverlappingActors)
	{
		TotalMass += Actor -> FindComponentByClass<UPrimitiveComponent>() -> GetMass();
		// UE_LOG(LogTemp, Warning, TEXT("%s Is on pressureplate"), *Actor -> GetName());
	}
	
	return TotalMass;
}

void UOpenDoor :: FindPressurePlate() const
{
		if(!PressurePlate)
	{
		UE_LOG(LogTemp,Error,TEXT("%s has the open door component on it, but no pressure plate set"), *GetOwner() -> GetName())
	}
}
