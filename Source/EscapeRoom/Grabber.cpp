// Copyright Adam Joyce 2017.

#include "EscapeRoom.h"
#include "Grabber.h"


// Sets default values for this component's properties.
UGrabber::UGrabber()
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
}


// Called every frame.
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Get the player's viewpoint.
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	PlayerController->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	// Logs the player controller's current viewpoint.
	UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());
}

