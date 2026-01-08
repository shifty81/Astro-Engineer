# Astro Engineer - Development Guide

## Overview

This guide provides development workflows, coding standards, and best practices for contributing to Astro Engineer.

## Development Workflow

### Getting Started
1. Read SETUP.md and complete installation
2. Read ARCHITECTURE.md to understand system design
3. Familiarize yourself with C++ classes
4. Review existing Blueprints (when created)
5. Start with small tasks to learn the codebase

### Daily Workflow
1. **Pull Latest Changes**
   ```bash
   git pull origin main
   ```

2. **Create Feature Branch**
   ```bash
   git checkout -b feature/your-feature-name
   ```

3. **Make Changes**
   - Edit code in Visual Studio
   - Test in Unreal Editor
   - Iterate until working

4. **Test Thoroughly**
   - Build without errors
   - Test in PIE (Play in Editor)
   - Verify no regressions

5. **Commit and Push**
   ```bash
   git add .
   git commit -m "Description of changes"
   git push origin feature/your-feature-name
   ```

6. **Create Pull Request**
   - Describe changes
   - Link to related issues
   - Request review

## Coding Standards

### C++ Style Guide

#### Naming Conventions

**Classes**
```cpp
// Actor classes: A prefix
class AAstroPlayerCharacter : public ACharacter {};

// Components: U prefix
class UAstroInventoryComponent : public UActorComponent {};

// Structs: F prefix
struct FInventoryItem {};

// Enums: E prefix
enum class EShipModuleType : uint8 {};

// Interfaces: I prefix
class IAstroInteractable {};
```

**Variables**
```cpp
// Member variables: camelCase or PascalCase with b/f/i prefix for special types
bool bIsOpen;
float fSpeed;
int32 ItemCount;
FVector PlayerLocation;

// Constants: k prefix
const float kMaxSpeed = 1000.0f;

// Pointers: Regular naming (Unreal uses * not Hungarian)
AActor* TargetActor;
```

**Functions**
```cpp
// Public functions: PascalCase
void UpdateInventory();
bool CanCraftItem();

// Private functions: PascalCase (same as public)
void ProcessCrafting();

// Getters/Setters
int32 GetItemCount() const;
void SetItemCount(int32 NewCount);
```

#### Code Formatting

**Braces**
```cpp
// Opening brace on same line
void MyFunction()
{
    if (condition)
    {
        // code
    }
    else
    {
        // code
    }
}
```

**Indentation**
- Use tabs (Unreal standard)
- Tab size: 4 spaces equivalent
- Align continuation lines

**Spacing**
```cpp
// Space after control flow keywords
if (condition)
for (int32 i = 0; i < Count; i++)
while (bIsRunning)

// Space around operators
int32 Result = A + B;
bool IsValid = (X > 0) && (Y < 100);

// No space before semicolon
Statement();
```

**Line Length**
- Aim for 120 characters max
- Break long lines logically
- Indent continuation lines

#### Comments

**Header Comments**
```cpp
// Copyright Astro Engineer Team. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
// ... other includes

/**
 * Brief description of class
 * Detailed explanation if needed
 */
UCLASS()
class ASTROENGINEER_API UMyClass : public UObject
{
    GENERATED_BODY()
};
```

**Function Comments**
```cpp
/**
 * Brief description of what function does
 * @param ParamName Description of parameter
 * @return Description of return value
 */
bool MyFunction(int32 ParamName);
```

**Inline Comments**
```cpp
// Explain why, not what
// Good:
MaxRetries = 3;  // Network can be flaky on startup

// Bad:
MaxRetries = 3;  // Set max retries to 3
```

**TODO Comments**
```cpp
// TODO(username): Description of what needs to be done
// FIXME(username): Description of bug to fix
// HACK(username): Explanation of temporary solution
```

#### Unreal-Specific Patterns

**UPROPERTY**
```cpp
// EditAnywhere: Editable in editor and instances
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
int32 MaxSlots;

// VisibleAnywhere: Visible but not editable
UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
TArray<FInventoryItem> Items;

// Replicated (for multiplayer, future)
UPROPERTY(Replicated)
int32 CurrentHealth;
```

**UFUNCTION**
```cpp
// BlueprintCallable: Can call from Blueprint
UFUNCTION(BlueprintCallable, Category = "Inventory")
bool AddItem(FName ItemID);

// BlueprintPure: No side effects, can use in BP expressions
UFUNCTION(BlueprintPure, Category = "Inventory")
int32 GetItemCount() const;

// BlueprintImplementableEvent: Implemented in Blueprint
UFUNCTION(BlueprintImplementableEvent, Category = "Animation")
void OnBackpackOpened();

// BlueprintNativeEvent: Default C++ implementation, can override in BP
UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
void OnInteract();
virtual void OnInteract_Implementation();
```

**Memory Management**
```cpp
// Use UPROPERTY for UObject pointers (automatic GC)
UPROPERTY()
UAstroInventoryComponent* Inventory;

// Use TSharedPtr for non-UObject shared ownership
TSharedPtr<FMyData> DataPtr;

// Use TWeakPtr for non-owning references
TWeakPtr<FMyData> WeakDataPtr;

// Use TUniquePtr for unique ownership
TUniquePtr<FMyHelper> Helper;

// Raw pointers only for temporary use
AActor* TempActor = GetWorld()->SpawnActor(...);
```

**Null Checking**
```cpp
// Always check pointers before use
if (Inventory)
{
    Inventory->AddItem(ItemID);
}

// Use ensure for debug assertions (continues in shipping)
if (ensure(Inventory))
{
    Inventory->AddItem(ItemID);
}

// Use check for critical failures (crashes in all builds)
check(Inventory);
Inventory->AddItem(ItemID);
```

### Blueprint Standards

#### Graph Organization
1. **Use Comments**: Group related nodes
2. **Alignment**: Keep nodes aligned
3. **Reroute Nodes**: Avoid wire crossing
4. **Functions**: Extract complex logic
5. **Macros**: For reusable visual logic

#### Variable Naming
```
PlayerHealth (PascalCase)
bIsAlive (boolean prefix)
fMovementSpeed (float prefix)
iItemCount (int prefix)
```

#### Event Naming
```
On[Event]
  OnInventoryChanged
  OnCraftingComplete
  
Handle[Input]
  HandleJumpPressed
  HandleMovementInput
```

#### Best Practices
- Minimize tick usage
- Use timers for delayed execution
- Cache component references in BeginPlay
- Use interfaces for loose coupling
- Document complex Blueprint logic

## Testing

### Manual Testing

**Before Committing**
1. Code compiles without errors
2. No new warnings introduced
3. Test in PIE (Play in Editor)
4. Test affected systems
5. Check for regressions

**Test Scenarios**
- **Inventory**: Add items, remove items, full inventory
- **Crafting**: Valid recipes, invalid recipes, crafting time
- **Research**: Prerequisites, resource requirements, unlocking
- **Ship Building**: Module attachment, validation, power balance

### Automated Testing (Future)
- Unit tests for component logic
- Integration tests for system interactions
- Blueprint tests for gameplay

## Performance Guidelines

### CPU Performance

**Tick Optimization**
```cpp
// Disable tick if not needed
PrimaryActorTick.bCanEverTick = false;

// Conditional tick
void UMyComponent::TickComponent(float DeltaTime, ...)
{
    if (!bNeedsUpdate)
        return;
    
    // Do work
}

// Use timers instead
GetWorld()->GetTimerManager().SetTimer(
    TimerHandle,
    this,
    &UMyClass::MyFunction,
    1.0f,  // Interval
    true   // Looping
);
```

**Avoid GetComponent Every Frame**
```cpp
// Bad
void Tick(float DeltaTime)
{
    auto* Inventory = GetOwner()->FindComponentByClass<UAstroInventoryComponent>();
    // Use Inventory
}

// Good
void BeginPlay()
{
    CachedInventory = GetOwner()->FindComponentByClass<UAstroInventoryComponent>();
}

void Tick(float DeltaTime)
{
    if (CachedInventory)
    {
        // Use CachedInventory
    }
}
```

**Array Operations**
```cpp
// Reserve capacity if you know size
TArray<int32> Numbers;
Numbers.Reserve(100);

// Use ranged-for for iteration
for (const FInventoryItem& Item : Inventory->GetItems())
{
    // Process item
}

// Remove efficiently
Items.RemoveAllSwap([](const FItem& Item) {
    return Item.IsExpired();
});
```

### Memory Management

**Avoid Memory Leaks**
```cpp
// Good: UPROPERTY manages lifetime
UPROPERTY()
UMyComponent* Component;

// Good: Smart pointer manages lifetime
TSharedPtr<FData> Data = MakeShared<FData>();

// Bad: Manual memory management
FData* Data = new FData();  // Who deletes this?
```

**Object Pooling**
```cpp
// For frequently spawned/destroyed objects
class UObjectPool
{
    TArray<AActor*> AvailableActors;
    
    AActor* GetFromPool()
    {
        if (AvailableActors.Num() > 0)
            return AvailableActors.Pop();
        return SpawnNew();
    }
    
    void ReturnToPool(AActor* Actor)
    {
        Actor->SetActorHiddenInGame(true);
        AvailableActors.Add(Actor);
    }
};
```

### GPU Performance

**Draw Call Reduction**
- Merge static meshes when possible
- Use instanced static meshes for repeated objects
- Minimize material count
- Use LODs appropriately

**Texture Memory**
- Use appropriate resolutions
- Enable texture streaming
- Compress textures properly
- Share textures across materials

## Debugging Tips

### Visual Studio Debugging

**Breakpoints**
```cpp
void UMyComponent::AddItem(FName ItemID)
{
    // Set breakpoint here
    if (ItemID.IsNone())
        return;  // Break when condition met
    
    // Step through code
    ProcessItem(ItemID);
}
```

**Watch Windows**
- Add variables to Watch window
- Inspect UObject properties
- View TArray contents

**Conditional Breakpoints**
```cpp
// Right-click breakpoint > Condition
// Break when: ItemID.ToString() == "IronOre"
```

### Unreal Engine Debugging

**Output Log**
```cpp
UE_LOG(LogTemp, Log, TEXT("Normal message"));
UE_LOG(LogTemp, Warning, TEXT("Warning message"));
UE_LOG(LogTemp, Error, TEXT("Error message"));

// With parameters
UE_LOG(LogTemp, Log, TEXT("Item: %s, Quantity: %d"), 
    *ItemID.ToString(), Quantity);
```

**On-Screen Debug Messages**
```cpp
if (GEngine)
{
    GEngine->AddOnScreenDebugMessage(
        -1,                    // Key (-1 for new line)
        5.0f,                  // Duration
        FColor::Yellow,        // Color
        TEXT("Debug Message")  // Text
    );
}
```

**Visual Logger**
```cpp
#include "VisualLogger/VisualLogger.h"

UE_VLOG(this, LogTemp, Log, TEXT("Visual log message"));
UE_VLOG_LOCATION(this, LogTemp, Log, GetActorLocation(), 50.0f, FColor::Green, TEXT("Actor location"));
```

**Draw Debug Shapes**
```cpp
#include "DrawDebugHelpers.h"

DrawDebugSphere(GetWorld(), Location, 50.0f, 12, FColor::Red, false, 5.0f);
DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 2.0f);
```

## Git Workflow

### Branch Naming
```
feature/ship-module-system
bugfix/inventory-duplication
hotfix/crash-on-startup
refactor/component-architecture
docs/setup-instructions
```

### Commit Messages
```
Add ship module attachment system

- Implement connection point validation
- Add power calculation logic
- Create module attachment functions
- Add unit tests for validation

Fixes #123
```

**Format**:
- First line: Brief summary (50 chars or less)
- Blank line
- Detailed explanation
- Reference issues/PRs

### Pull Request Process
1. **Create PR**: Descriptive title and body
2. **Link Issues**: Reference related issues
3. **Request Review**: Tag reviewers
4. **Address Feedback**: Make requested changes
5. **Merge**: Squash and merge when approved

## Documentation

### Code Documentation
- Document all public APIs
- Explain complex algorithms
- Add examples for non-obvious usage
- Keep documentation up-to-date

### External Documentation
- Update README for major features
- Add to ARCHITECTURE.md for system changes
- Update SETUP.md for new requirements
- Create tutorials for new systems

## Common Pitfalls

### Unreal Engine Specific

**Garbage Collection**
```cpp
// Bad: Pointer to UObject without UPROPERTY
UMyComponent* Component;  // May be GC'd

// Good: Marked for GC system
UPROPERTY()
UMyComponent* Component;
```

**Null Pointers**
```cpp
// Always check before use
if (Component)
{
    Component->DoSomething();
}

// Or use ensure for debug builds
if (ensure(Component))
{
    Component->DoSomething();
}
```

**Forward Declarations**
```cpp
// In header: Forward declare when possible
class UAstroInventoryComponent;

// In cpp: Include full header
#include "AstroInventoryComponent.h"
```

**Circular Dependencies**
```cpp
// Use forward declarations
// Use interfaces
// Restructure to break cycle
```

## Resources

### Unreal Engine Documentation
- [C++ Programming Guide](https://docs.unrealengine.com/5.7/programming-with-cpp-in-unreal-engine/)
- [Gameplay Framework](https://docs.unrealengine.com/5.7/gameplay-framework-in-unreal-engine/)
- [Blueprints](https://docs.unrealengine.com/5.7/blueprints-visual-scripting-in-unreal-engine/)

### Community Resources
- Unreal Engine Forums
- Unreal Slackers Discord
- Stack Overflow (unreal-engine tag)

### Tools
- Visual Studio 2022
- ReSharper C++ (optional)
- Visual Assist (optional)
- Git GUI tools

## Getting Help

### Before Asking
1. Search documentation
2. Check existing issues
3. Review similar code
4. Try debugging yourself

### When Asking
1. Describe the problem clearly
2. Show what you've tried
3. Provide error messages
4. Include relevant code
5. Explain expected vs actual behavior

### Where to Ask
- GitHub Issues (bugs, features)
- Project Discord (quick questions)
- Team Slack (internal)
- Unreal Forums (engine-specific)

## Review Checklist

Before submitting PR:
- [ ] Code compiles without errors
- [ ] No new warnings
- [ ] Follows coding standards
- [ ] Code is documented
- [ ] Tested in PIE
- [ ] No performance regressions
- [ ] Git history is clean
- [ ] PR description is complete
- [ ] Related issues are linked

## Conclusion

Following these guidelines ensures:
- Consistent, maintainable code
- Efficient development process
- High-quality contributions
- Smooth team collaboration

Happy coding! 🚀
