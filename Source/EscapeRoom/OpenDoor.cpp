// Copyright Adam Joyce 2017

#include "EscapeRoom.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts.
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame.
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Open the door when an actor is in the trigger zone.
	if (DoorTrigger->IsOverlappingActor(OpeningActor))
	{
		OpenDoor();
	}
}

// Opens the door.
void UOpenDoor::OpenDoor()
{
	AActor* Owner = GetOwner();
	FRotator NewRotation = FRotator(0.0f, -90.0f, 0);
	Owner->SetActorRotation(NewRotation);
}

