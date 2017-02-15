// Copyright Adam Joyce 2017.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties.
	UGrabber();

	// Called when the game starts.
	virtual void BeginPlay() override;
	
	// Called every frame.
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	// The distance the player can grab objects in cm.
	UPROPERTY(EditAnywhere)
	float Reach;

	// The input component of the attached object
	UInputComponent* InputComponent;

	// The physics handle component of the attached object.
	UPhysicsHandleComponent* PhysicsHandle;

	// The player controller of the pawn this component is attached to.
	APlayerController* PlayerController;

	// Finds the attached physics handle component.
	void FindPhysicsHandleComponent();

	// Sets up the owner's input component.
	void SetupInputComponent();

	// Returns the start location of the reach line (the player's viewpoint location).
	FVector GetReachLineStart();

	// Returns the end location of the reach line.
	FVector GetReachLineEnd();

	// Returns hit for first physics body within reach.
	const FHitResult GetFirstPhysicsBodyInReach();

	// Grabs an object within reach.
	void Grab();

	// Releases a grabbed object.
	void Release();
};
