// Copyright Astro Engineer Team. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AstroCraftingComponent.generated.h"

class UAstroInventoryComponent;

/**
 * Crafting recipe structure
 */
USTRUCT(BlueprintType)
struct FCraftingRecipe
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName RecipeID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText RecipeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, int32> RequiredItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ResultItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ResultQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CraftingTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsUnlocked;

	FCraftingRecipe()
		: RecipeID(NAME_None)
		, RecipeName(FText::GetEmpty())
		, Description(FText::GetEmpty())
		, ResultItemID(NAME_None)
		, ResultQuantity(1)
		, CraftingTime(1.0f)
		, Icon(nullptr)
		, bIsUnlocked(false)
	{}
};

/**
 * Crafting Component for managing recipe crafting
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ASTROENGINEER_API UAstroCraftingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAstroCraftingComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Check if player can craft recipe */
	UFUNCTION(BlueprintCallable, Category = "Crafting")
	bool CanCraftRecipe(FName RecipeID) const;

	/** Start crafting a recipe */
	UFUNCTION(BlueprintCallable, Category = "Crafting")
	bool StartCrafting(FName RecipeID);

	/** Cancel current crafting */
	UFUNCTION(BlueprintCallable, Category = "Crafting")
	void CancelCrafting();

	/** Get all available recipes */
	UFUNCTION(BlueprintCallable, Category = "Crafting")
	TArray<FCraftingRecipe> GetAvailableRecipes() const;

	/** Unlock a recipe */
	UFUNCTION(BlueprintCallable, Category = "Crafting")
	void UnlockRecipe(FName RecipeID);

	/** Check if recipe is unlocked */
	UFUNCTION(BlueprintCallable, Category = "Crafting")
	bool IsRecipeUnlocked(FName RecipeID) const;

protected:
	virtual void BeginPlay() override;

	/** Complete the current crafting */
	void CompleteCrafting();

	/** Find recipe by ID */
	FCraftingRecipe* FindRecipe(FName RecipeID);

public:	
	/** Reference to player inventory */
	UPROPERTY()
	UAstroInventoryComponent* PlayerInventory;

	/** All crafting recipes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	TArray<FCraftingRecipe> CraftingRecipes;

	/** Currently crafting recipe */
	UPROPERTY(BlueprintReadOnly, Category = "Crafting")
	FName CurrentCraftingRecipe;

	/** Crafting progress (0-1) */
	UPROPERTY(BlueprintReadOnly, Category = "Crafting")
	float CraftingProgress;

	/** Is currently crafting */
	UPROPERTY(BlueprintReadOnly, Category = "Crafting")
	bool bIsCrafting;

	/** Delegate called when crafting starts */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCraftingStarted, FName, RecipeID);
	UPROPERTY(BlueprintAssignable, Category = "Crafting")
	FOnCraftingStarted OnCraftingStarted;

	/** Delegate called when crafting completes */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCraftingCompleted, FName, RecipeID);
	UPROPERTY(BlueprintAssignable, Category = "Crafting")
	FOnCraftingCompleted OnCraftingCompleted;

private:
	float CraftingTimer;
	float CurrentCraftingTime;
};
