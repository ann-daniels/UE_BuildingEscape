// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	FString Name = GetOwner() -> GetName();
	
	FVector Location = GetOwner() -> GetActorLocation();
	FString ObjectPosition = Location.ToString() ; 
	UE_LOG(LogTemp, Warning, TEXT("This component is attached to %s"), *ObjectPosition);


	// FString Log = TEXT("Hello!");
	// //making a pointer
	// FString* PtrLog = &Log;
	// // (*PtrLog).Len(); is same as
	// // PtrLog -> Len();
	// UE_LOG(LogTemp, Warning, TEXT("%s"), **PtrLog);
	//accessing the name of actor to whom the script is attached to
	
	// UE_LOG(LogTemp, Warning, TEXT("This component is attached to %s"), *Name);
	// same can be done like this
	


}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

