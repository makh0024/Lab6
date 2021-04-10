// Copyright Epic Games, Inc. All Rights Reserved.

#include "Lab6Character.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "Lab6GameMode.h"
#include "Pickup/PickupActor.h"
#include "Pickup/PickupSpawner.h"
#include "Lab6GameState.h"

#include "Materials/MaterialInstance.h"
#include "Materials/Material.h"

#include "Net/UnrealNetwork.h"
#include "UI/MyUserWidget.h"

#include "Lab6PlayerController.h"
//////////////////////////////////////////////////////////////////////////
// ALab6Character

ALab6Character::ALab6Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	//SetReplicates(true);
	//GetMesh()->SetIsReplicated(true);	
}

void ALab6Character::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetLocalRole() > ROLE_AutonomousProxy)
	{
		PlayerTeam = GetWorld()->GetGameState()->AuthorityGameMode->GetNumPlayers();
	}

	if (PlayerTeam == 1)
	{	
		UMaterialInstance* material = UMaterialInstanceDynamic::Create(Team1Material, this);
		GetMesh()->SetMaterial(0, material);
	}
	else
	{
		UMaterialInstance* material = UMaterialInstanceDynamic::Create(Team2Material, this);
		GetMesh()->SetMaterial(0, material);
	}		
}
//////////////////////////////////////////////////////////////////////////
// Input

void ALab6Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ALab6Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALab6Character::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ALab6Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ALab6Character::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ALab6Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ALab6Character::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ALab6Character::OnResetVR);
}


void ALab6Character::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ALab6Character::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ALab6Character::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ALab6Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ALab6Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ALab6Character::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ALab6Character::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ALab6Character::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Pickup"))
	{
		APickupActor* pickup = Cast<APickupActor>(OtherActor);

		if (pickup->Team == PlayerTeam)
		{
			numPickupsLeft--;

			pickup->Destroy();
			
			if (numPickupsLeft <= 0)
			{
				Respawn();
			}
		}
	}
}

void ALab6Character::Respawn()
{
	ALab6GameMode* GM = Cast<ALab6GameMode>(GetWorld()->GetAuthGameMode());

	if (GM)
	{
		GM->NextLevel();
	
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, "Team " + FString::FromInt(PlayerTeam) + " Has WON this round.");
	}
}

void ALab6Character::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALab6Character, PlayerTeam);
	DOREPLIFETIME(ALab6Character, numPickupsLeft);
}