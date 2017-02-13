// Copyright Adam Joyce 2017.

#include "EscapeRoom.h"
#include "Grabber.h"


// Sets default values for this component's properties.
UGrabber::UGrabber() : Reach(100.0f),
					   InputComponent(nullptr),
					   PhysicsHandle(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts.
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = GetWorld()->GetFirstPlayerController();
	FindPhysicsHandleComponent();
	SetupInputComponent();
}


// Called every frame.
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	/* THIS NEED REFACTORING - REPEATED CODE... */
	/// Get the player's viewpoint.
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	PlayerController->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	/// Draw out grab line.
	const FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);
	/* REFACTOR ENDS */

	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
}

// Finds the attached physics handle component.
void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing PhysicsHandle component"), *(GetOwner()->GetName()));
	}
}

// Sets up the owner's input component.
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		/// Bind input actions.
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	} 
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing InputComponent"), *(GetOwner()->GetName()));
	}
}

// Returns hit for first physics body within reach.
const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	/// Get the player's viewpoint.
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	PlayerController->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	/// Logs the player controller's current viewpoint.
	//UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());

	/// Draw out grab line.
	const FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);
	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor::Red, false, 0.0f, 0.0f, 2.0f);

	/// Setup collisiom query parameters.
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Perform the raycast.
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(Hit, PlayerViewPointLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters);

	/// Log any object hit by the raycast.
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *(ActorHit->GetName()));
	}

	return Hit;
}

// Grabs an object within reach.
void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));

	/// Line trace for any physics bodies within reach.
	const FHitResult HitResult = GetFirstPhysicsBodyInReach();
	const AActor* ActorHit = HitResult.GetActor();
	if (ActorHit)
	{
		/// Grab hit component at its actor location.
		UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
		PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
	}
}

// Releases a grabbed object.
void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab released"));
	PhysicsHandle->ReleaseComponent();
}