// Copyright Astro Engineer Team. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "AstroPlayerCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UAstroInventoryComponent;
class UCameraComponent;
class USkeletalMeshComponent;

/**
 * First Person Player Character for Astro Engineer
 * Handles movement, interaction, and backpack interface
 */
UCLASS()
class ASTROENGINEER_API AAstroPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAstroPlayerCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	
	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	
	/** Called to interact with objects */
	void Interact();
	
	/** Called to toggle backpack interface */
	void ToggleBackpack();
	
	/** Animation for taking off backpack and kneeling */
	void OpenBackpackInterface();
	
	/** Animation for putting backpack back on */
	void CloseBackpackInterface();

public:
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* FirstPersonCamera;

	/** Player inventory component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	UAstroInventoryComponent* InventoryComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* InteractAction;

	/** Backpack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* BackpackAction;

	/** Is the backpack interface currently open? */
	UPROPERTY(BlueprintReadOnly, Category = UI)
	bool bIsBackpackOpen;

	/** Interaction range in cm */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction)
	float InteractionRange;
};
