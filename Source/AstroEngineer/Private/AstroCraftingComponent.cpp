// Copyright Astro Engineer Team. All Rights Reserved.

#include "AstroCraftingComponent.h"
#include "AstroInventoryComponent.h"

UAstroCraftingComponent::UAstroCraftingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bIsCrafting = false;
	CraftingProgress = 0.0f;
	CraftingTimer = 0.0f;
	CurrentCraftingTime = 0.0f;
}

void UAstroCraftingComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// Get reference to player inventory
	AActor* Owner = GetOwner();
	if (Owner)
	{
		PlayerInventory = Owner->FindComponentByClass<UAstroInventoryComponent>();
	}
}

void UAstroCraftingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsCrafting && CurrentCraftingTime > 0.0f)
	{
		CraftingTimer += DeltaTime;
		CraftingProgress = FMath::Clamp(CraftingTimer / CurrentCraftingTime, 0.0f, 1.0f);

		if (CraftingTimer >= CurrentCraftingTime)
		{
			CompleteCrafting();
		}
	}
}

bool UAstroCraftingComponent::CanCraftRecipe(FName RecipeID) const
{
	if (!PlayerInventory || RecipeID.IsNone())
		return false;

	// Find the recipe
	const FCraftingRecipe* Recipe = nullptr;
	for (const FCraftingRecipe& R : CraftingRecipes)
	{
		if (R.RecipeID == RecipeID)
		{
			Recipe = &R;
			break;
		}
	}

	if (!Recipe || !Recipe->bIsUnlocked)
		return false;

	// Check if player has all required items
	for (const TPair<FName, int32>& RequiredItem : Recipe->RequiredItems)
	{
		if (!PlayerInventory->HasItem(RequiredItem.Key, RequiredItem.Value))
			return false;
	}

	return true;
}

bool UAstroCraftingComponent::StartCrafting(FName RecipeID)
{
	if (bIsCrafting || !CanCraftRecipe(RecipeID))
		return false;

	FCraftingRecipe* Recipe = FindRecipe(RecipeID);
	if (!Recipe)
		return false;

	// Remove required items from inventory
	for (const TPair<FName, int32>& RequiredItem : Recipe->RequiredItems)
	{
		PlayerInventory->RemoveItem(RequiredItem.Key, RequiredItem.Value);
	}

	// Start crafting
	CurrentCraftingRecipe = RecipeID;
	CurrentCraftingTime = Recipe->CraftingTime;
	CraftingTimer = 0.0f;
	CraftingProgress = 0.0f;
	bIsCrafting = true;

	OnCraftingStarted.Broadcast(RecipeID);
	return true;
}

void UAstroCraftingComponent::CancelCrafting()
{
	if (!bIsCrafting)
		return;

	// Optionally return items to player
	FCraftingRecipe* Recipe = FindRecipe(CurrentCraftingRecipe);
	if (Recipe && PlayerInventory)
	{
		for (const TPair<FName, int32>& RequiredItem : Recipe->RequiredItems)
		{
			PlayerInventory->AddItem(RequiredItem.Key, RequiredItem.Value);
		}
	}

	CurrentCraftingRecipe = NAME_None;
	CraftingTimer = 0.0f;
	CraftingProgress = 0.0f;
	CurrentCraftingTime = 0.0f;
	bIsCrafting = false;
}

void UAstroCraftingComponent::CompleteCrafting()
{
	if (!bIsCrafting)
		return;

	FCraftingRecipe* Recipe = FindRecipe(CurrentCraftingRecipe);
	if (Recipe && PlayerInventory)
	{
		// Add result item to inventory
		PlayerInventory->AddItem(Recipe->ResultItemID, Recipe->ResultQuantity);
		OnCraftingCompleted.Broadcast(CurrentCraftingRecipe);
	}

	CurrentCraftingRecipe = NAME_None;
	CraftingTimer = 0.0f;
	CraftingProgress = 0.0f;
	CurrentCraftingTime = 0.0f;
	bIsCrafting = false;
}

TArray<FCraftingRecipe> UAstroCraftingComponent::GetAvailableRecipes() const
{
	TArray<FCraftingRecipe> UnlockedRecipes;
	for (const FCraftingRecipe& Recipe : CraftingRecipes)
	{
		if (Recipe.bIsUnlocked)
		{
			UnlockedRecipes.Add(Recipe);
		}
	}
	return UnlockedRecipes;
}

void UAstroCraftingComponent::UnlockRecipe(FName RecipeID)
{
	FCraftingRecipe* Recipe = FindRecipe(RecipeID);
	if (Recipe)
	{
		Recipe->bIsUnlocked = true;
	}
}

bool UAstroCraftingComponent::IsRecipeUnlocked(FName RecipeID) const
{
	for (const FCraftingRecipe& Recipe : CraftingRecipes)
	{
		if (Recipe.RecipeID == RecipeID)
			return Recipe.bIsUnlocked;
	}
	return false;
}

FCraftingRecipe* UAstroCraftingComponent::FindRecipe(FName RecipeID)
{
	for (FCraftingRecipe& Recipe : CraftingRecipes)
	{
		if (Recipe.RecipeID == RecipeID)
			return &Recipe;
	}
	return nullptr;
}
