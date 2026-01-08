// Copyright Astro Engineer Team. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AstroResearchComponent.generated.h"

/**
 * Research node structure
 */
USTRUCT(BlueprintType)
struct FResearchNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NodeID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText NodeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> Prerequisites;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, int32> RequiredResources;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ResearchTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> UnlocksRecipes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> UnlocksItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsUnlocked;

	FResearchNode()
		: NodeID(NAME_None)
		, NodeName(FText::GetEmpty())
		, Description(FText::GetEmpty())
		, ResearchTime(10.0f)
		, Icon(nullptr)
		, bIsUnlocked(false)
	{}
};

/**
 * Research Component for technology progression
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ASTROENGINEER_API UAstroResearchComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAstroResearchComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Check if can research node */
	UFUNCTION(BlueprintCallable, Category = "Research")
	bool CanResearchNode(FName NodeID) const;

	/** Start researching node */
	UFUNCTION(BlueprintCallable, Category = "Research")
	bool StartResearch(FName NodeID);

	/** Cancel current research */
	UFUNCTION(BlueprintCallable, Category = "Research")
	void CancelResearch();

	/** Get all research nodes */
	UFUNCTION(BlueprintCallable, Category = "Research")
	TArray<FResearchNode> GetAllResearchNodes() const { return ResearchNodes; }

	/** Get available research nodes */
	UFUNCTION(BlueprintCallable, Category = "Research")
	TArray<FResearchNode> GetAvailableResearchNodes() const;

	/** Check if node is unlocked */
	UFUNCTION(BlueprintCallable, Category = "Research")
	bool IsNodeUnlocked(FName NodeID) const;

protected:
	virtual void BeginPlay() override;

	/** Complete current research */
	void CompleteResearch();

	/** Find research node */
	FResearchNode* FindNode(FName NodeID);

public:	
	/** All research nodes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Research")
	TArray<FResearchNode> ResearchNodes;

	/** Currently researching node */
	UPROPERTY(BlueprintReadOnly, Category = "Research")
	FName CurrentResearchNode;

	/** Research progress (0-1) */
	UPROPERTY(BlueprintReadOnly, Category = "Research")
	float ResearchProgress;

	/** Is currently researching */
	UPROPERTY(BlueprintReadOnly, Category = "Research")
	bool bIsResearching;

	/** Delegate called when research completes */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnResearchCompleted, FName, NodeID);
	UPROPERTY(BlueprintAssignable, Category = "Research")
	FOnResearchCompleted OnResearchCompleted;

private:
	float ResearchTimer;
	float CurrentResearchTime;
};
