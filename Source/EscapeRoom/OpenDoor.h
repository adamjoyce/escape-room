// Copyright Adam Joyce 2017

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	// Open door angle.
	UPROPERTY(VisibleAnywhere)
	float OpenAngle = 90.0f;

	// Trigger volume for the door.
	UPROPERTY(EditAnywhere)
	ATriggerVolume* DoorTrigger;

	// The actor which opens the door.
	UPROPERTY(EditAnywhere)
	AActor* OpeningActor;

	// Opens the door.
	void OpenDoor();
};
