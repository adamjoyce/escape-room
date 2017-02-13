// Copyright Adam Joyce 2017.

#include "EscapeRoom.h"
#include "PositionReporter.h"


// Sets default values for this component's properties
UPositionReporter::UPositionReporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts.
void UPositionReporter::BeginPlay()
{
	Super::BeginPlay();

	/// Log the location of the parent actor.
	FString ObjectName = GetOwner()->GetName();
	FString ObjectPos = GetOwner()->GetTransform().GetLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s is at %s!"), *ObjectName, *ObjectPos);
}


// Called every frame.
//void UPositionReporter::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
//{
//	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
//
//	// ...
//}

