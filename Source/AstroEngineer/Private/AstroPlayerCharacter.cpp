// Copyright Astro Engineer Team. All Rights Reserved.

#include "AstroPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AstroInventoryComponent.h"
#include "DrawDebugHelpers.h"

AAstroPlayerCharacter::AAstroPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Create first person camera component
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->SetRelativeLocation(FVector(0.f, 0.f, 64.f));
	FirstPersonCamera->bUsePawnControlRotation = true;

	// Create inventory component
	InventoryComponent = CreateDefaultSubobject<UAstroInventoryComponent>(TEXT("InventoryComponent"));

	// Initialize variables
	bIsBackpackOpen = false;
	InteractionRange = 200.0f;
}

void AAstroPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AAstroPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAstroPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAstroPlayerCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAstroPlayerCharacter::Look);

		// Interacting
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AAstroPlayerCharacter::Interact);

		// Backpack
		EnhancedInputComponent->BindAction(BackpackAction, ETriggerEvent::Triggered, this, &AAstroPlayerCharacter::ToggleBackpack);
	}
}

void AAstroPlayerCharacter::Move(const FInputActionValue& Value)
{
	if (!bIsBackpackOpen)
	{
		FVector2D MovementVector = Value.Get<FVector2D>();

		if (Controller != nullptr)
		{
			// Forward/Backward direction
			AddMovementInput(GetActorForwardVector(), MovementVector.Y);

			// Right/Left direction  
			AddMovementInput(GetActorRightVector(), MovementVector.X);
		}
	}
}

void AAstroPlayerCharacter::Look(const FInputActionValue& Value)
{
	if (!bIsBackpackOpen)
	{
		FVector2D LookAxisVector = Value.Get<FVector2D>();

		if (Controller != nullptr)
		{
			AddControllerYawInput(LookAxisVector.X);
			AddControllerPitchInput(LookAxisVector.Y);
		}
	}
}

void AAstroPlayerCharacter::Interact()
{
	if (bIsBackpackOpen)
		return;

	// Perform line trace from camera
	FVector Start = FirstPersonCamera->GetComponentLocation();
	FVector End = Start + (FirstPersonCamera->GetForwardVector() * InteractionRange);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams))
	{
		// Check if hit actor is interactable
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			// Blueprint implementable interaction event
			// This allows for flexible interaction system
		}
	}
}

void AAstroPlayerCharacter::ToggleBackpack()
{
	if (bIsBackpackOpen)
	{
		CloseBackpackInterface();
	}
	else
	{
		OpenBackpackInterface();
	}
}

void AAstroPlayerCharacter::OpenBackpackInterface()
{
	bIsBackpackOpen = true;

	// Disable movement
	// Show cursor
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		PlayerController->bShowMouseCursor = true;
		PlayerController->SetInputMode(FInputModeGameAndUI());
	}

	// Blueprint event will handle animation and UI
}

void AAstroPlayerCharacter::CloseBackpackInterface()
{
	bIsBackpackOpen = false;

	// Enable movement
	// Hide cursor
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		PlayerController->bShowMouseCursor = false;
		PlayerController->SetInputMode(FInputModeGameOnly());
	}

	// Blueprint event will handle animation and UI
}
