// Copyright Adam Joyce 2017.

#include "EscapeRoom.h"
#include "OpenDoor.h"
#include "Grabber.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor() : OpenAngle(70.0f), 
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
	Owner = GetOwner();
}


// Called every frame.
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	/// Open the door when an actor is in the trigger zone.
	if (GetTotalMassOfActorOnPlate() > 30.0f)
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
		IsDoorOpen = true;
	}

	/// Check if it is time to close the door.
	if (IsDoorOpen && (GetWorld()->GetTimeSeconds() >= (LastDoorOpenTime + DoorCloseDelay)))
	{
		CloseDoor();
		IsDoorOpen = false;
	}
}

//
float UOpenDoor::GetTotalMassOfActorOnPlate()
{
	float TotalMass = 0.0f;

	// Get all actors in the door trigger zone.
	TArray<AActor*> OverlappingActors;
	DoorTrigger->GetOverlappingActors(OverlappingActors);

	// Calculate combined mass of overlapping actors.
	FString OverlappingNames;
	for (const auto* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s in trigger zone"), *(Actor->GetName()));
	}

	return TotalMass;
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

