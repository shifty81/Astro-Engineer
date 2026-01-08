// Copyright Astro Engineer Team. All Rights Reserved.

#include "AstroResearchComponent.h"
#include "AstroInventoryComponent.h"
#include "AstroCraftingComponent.h"

UAstroResearchComponent::UAstroResearchComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bIsResearching = false;
	ResearchProgress = 0.0f;
	ResearchTimer = 0.0f;
	CurrentResearchTime = 0.0f;
}

void UAstroResearchComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAstroResearchComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsResearching && CurrentResearchTime > 0.0f)
	{
		ResearchTimer += DeltaTime;
		ResearchProgress = FMath::Clamp(ResearchTimer / CurrentResearchTime, 0.0f, 1.0f);

		if (ResearchTimer >= CurrentResearchTime)
		{
			CompleteResearch();
		}
	}
}

bool UAstroResearchComponent::CanResearchNode(FName NodeID) const
{
	if (NodeID.IsNone())
		return false;

	const FResearchNode* Node = nullptr;
	for (const FResearchNode& N : ResearchNodes)
	{
		if (N.NodeID == NodeID)
		{
			Node = &N;
			break;
		}
	}

	if (!Node || Node->bIsUnlocked)
		return false;

	// Check prerequisites
	for (const FName& PrereqID : Node->Prerequisites)
	{
		if (!IsNodeUnlocked(PrereqID))
			return false;
	}

	// Check resources - would need inventory reference
	// Simplified for now
	return true;
}

bool UAstroResearchComponent::StartResearch(FName NodeID)
{
	if (bIsResearching || !CanResearchNode(NodeID))
		return false;

	FResearchNode* Node = FindNode(NodeID);
	if (!Node)
		return false;

	// Start research
	CurrentResearchNode = NodeID;
	CurrentResearchTime = Node->ResearchTime;
	ResearchTimer = 0.0f;
	ResearchProgress = 0.0f;
	bIsResearching = true;

	return true;
}

void UAstroResearchComponent::CancelResearch()
{
	if (!bIsResearching)
		return;

	CurrentResearchNode = NAME_None;
	ResearchTimer = 0.0f;
	ResearchProgress = 0.0f;
	CurrentResearchTime = 0.0f;
	bIsResearching = false;
}

void UAstroResearchComponent::CompleteResearch()
{
	if (!bIsResearching)
		return;

	FResearchNode* Node = FindNode(CurrentResearchNode);
	if (Node)
	{
		Node->bIsUnlocked = true;

		// Unlock recipes - would need crafting component reference
		// This would be handled through events in Blueprint

		OnResearchCompleted.Broadcast(CurrentResearchNode);
	}

	CurrentResearchNode = NAME_None;
	ResearchTimer = 0.0f;
	ResearchProgress = 0.0f;
	CurrentResearchTime = 0.0f;
	bIsResearching = false;
}

TArray<FResearchNode> UAstroResearchComponent::GetAvailableResearchNodes() const
{
	TArray<FResearchNode> AvailableNodes;
	for (const FResearchNode& Node : ResearchNodes)
	{
		if (!Node.bIsUnlocked && CanResearchNode(Node.NodeID))
		{
			AvailableNodes.Add(Node);
		}
	}
	return AvailableNodes;
}

bool UAstroResearchComponent::IsNodeUnlocked(FName NodeID) const
{
	for (const FResearchNode& Node : ResearchNodes)
	{
		if (Node.NodeID == NodeID)
			return Node.bIsUnlocked;
	}
	return false;
}

FResearchNode* UAstroResearchComponent::FindNode(FName NodeID)
{
	for (FResearchNode& Node : ResearchNodes)
	{
		if (Node.NodeID == NodeID)
			return &Node;
	}
	return nullptr;
}
