// Copyright Adam Joyce 2017.

#include "EscapeRoom.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor() : OpenAngle(90.0f), 
						 DoorCloseDelay(1.0f), 
						 IsDoorOpen(false)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts.
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	OpeningActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	Owner = GetOwner();
}


// Called every frame.
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Open the door when an actor is in the trigger zone.
	if (DoorTrigger->IsOverlappingActor(OpeningActor))
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
		IsDoorOpen = true;
	}

	// Check if it is time to close the door.
	if (IsDoorOpen && (GetWorld()->GetTimeSeconds() >= (LastDoorOpenTime + DoorCloseDelay)))
	{
		CloseDoor();
		IsDoorOpen = false;
	}
}

// Opens the door.
void UOpenDoor::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

// Closes the door.
void UOpenDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

