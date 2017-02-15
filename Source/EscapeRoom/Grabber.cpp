// Copyright Adam Joyce 2017.

#include "EscapeRoom.h"
#include "Grabber.h"


// Sets default values for this component's properties.
UGrabber::UGrabber() : Reach(100.0f),
					   InputComponent(nullptr),
					   PhysicsHandle(nullptr),
					   PlayerController(nullptr)
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
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("Scene missing Player Controller"));
	}

	FindPhysicsHandleComponent();
	SetupInputComponent();
}

// Called every frame.
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	/// Returns if there is no Physics Handle on the owning component.
	if (!PhysicsHandle) { return; }
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
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

// Returns the start location of the reach line (the player's viewpoint location).
FVector UGrabber::GetReachLineStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	PlayerController->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
	return PlayerViewPointLocation;
}

// Returns the end location of the reach line.
FVector UGrabber::GetReachLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	PlayerController->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
	return PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);
}

// Returns hit for first physics body within reach.
const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	/// Perform the raycast.
	FHitResult Hit;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(Hit, GetReachLineStart(), GetReachLineEnd(), FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters);
	//DrawDebugLine(GetWorld(), GetReachLineStart(), GetReachLineEnd(), FColor::Red, false, 0.0f, 0.0f, 2.0f);
	return Hit;
}

// Grabs an object within reach.
void UGrabber::Grab()
{
	/// Line trace for any physics bodies within reach.
	const FHitResult HitResult = GetFirstPhysicsBodyInReach();
	const AActor* ActorHit = HitResult.GetActor();
	if (ActorHit)
	{
		/// Grab hit component (mesh) at its actor location.
		UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

		/// Returns if there is no Physics Handle on the owning component.
		if (!PhysicsHandle) { return; }
		PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
	}
}

// Releases a grabbed object.
void UGrabber::Release()
{
	/// Returns if there is no Physics Handle on the owning component.
	if (!PhysicsHandle) { return; }
	PhysicsHandle->ReleaseComponent();
}