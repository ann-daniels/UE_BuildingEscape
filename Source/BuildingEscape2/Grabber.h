// Copyright Anna Danielyan 2022

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE2_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	float Reach = 100.f;
	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UPROPERTY()
	UInputComponent* InputComponent = nullptr;
	

	void Grab();
	void Release();
	void FindPhysicsHandle();
	void SetupInputComponent();
	//Return the first Actor within reach with physics body
	FHitResult GetFirstPhysicsBodyInReach() const;
	FVector GetLineTraceEnd() const;
	FVector GetPlayerWorldPos() const;

};
