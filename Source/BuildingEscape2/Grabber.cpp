// Copyright Anna Danielyan 2022
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Grabber.h"

#define  OUT
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	//Check for a physics handle component
	FindPhysicsHandle();

	SetupInputComponent();

}

void UGrabber :: SetupInputComponent()
{
	InputComponent = GetOwner() -> FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent -> BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent -> BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	
}

void UGrabber :: FindPhysicsHandle()
{
	PhysicsHandle = GetOwner() -> FindComponentByClass<UPhysicsHandleComponent>();		
	if (!PhysicsHandle)
	{
		// Physics Handle is not found  
		UE_LOG(LogTemp, Error, TEXT("The %s object does not have a PhysicsHandle component on it!"), *GetOwner() -> GetName());
	}
}

void UGrabber :: Grab()
{
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor* ActorHit = HitResult.GetActor();
	//if we hit something then attach the physics handle
	if(ActorHit)
	{
		if(!PhysicsHandle) {return;} 
		//TODO attach physics handle
		PhysicsHandle -> GrabComponentAtLocation(ComponentToGrab ,NAME_None, GetLineTraceEnd());	
	}		
}


void UGrabber :: Release()
{
	//remove the physics handle
	PhysicsHandle -> ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// if physics handle is attahched
	if(!PhysicsHandle) {return;}
	if(PhysicsHandle -> GrabbedComponent)
	{
		// Move the object we are holding
		PhysicsHandle -> SetTargetLocation(GetLineTraceEnd());
	}
	
 
}

FHitResult UGrabber :: GetFirstPhysicsBodyInReach() const
{
	// DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(0,255,0), false, 0.f, 0, 5.f);
	FHitResult Hit;
	// Ray - cast out to a certain distance (Reach)
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld() -> LineTraceSingleByObjectType(OUT Hit, GetPlayerWorldPos(), GetLineTraceEnd(), FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);
	return Hit;
}

FVector UGrabber :: GetPlayerWorldPos() const
{
	// Get players viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld() -> GetFirstPlayerController() -> GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	return PlayerViewPointLocation;
}

FVector UGrabber :: GetLineTraceEnd() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	  
	GetWorld() -> GetFirstPlayerController() -> GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	//draw line from player to reach
	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;	
}
