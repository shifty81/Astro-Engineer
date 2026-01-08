# Astro Engineer - Unreal Engine 5.7 Space Exploration Game

## Overview

Astro Engineer is a first-person space exploration and ship-building game built in Unreal Engine 5.7. Players start on foot, gather resources, craft items, research technologies, and ultimately build their own modular spaceships to explore the solar system.

## Key Features

### 1. First Person Gameplay
- Built on Unreal Engine 5.7 First Person Template
- Enhanced Input System for modern control schemes
- Smooth camera controls and movement

### 2. Unique Backpack Interface System
- Press a key to take off backpack and kneel down
- Character animation shows player laying backpack on ground
- Opens comprehensive nested UI interface
- All game systems accessible from single interface:
  - Inventory Management (grid-based)
  - Crafting Menu
  - Research Tree
  - Map System
  - Ship Assembly Interface

### 3. Inventory System
- 40-slot grid-based inventory (8x5 default)
- Item stacking with configurable stack sizes
- Item icons and descriptions
- Real-time inventory updates
- Event-driven system for UI synchronization

### 4. Crafting System
- Recipe-based crafting
- Resource requirements
- Crafting time with progress tracking
- Unlockable recipes through research
- Visual feedback during crafting

### 5. Research & Progression
- Tech tree system
- Prerequisite-based unlocking
- Research time requirements
- Unlocks new recipes and ship modules
- Progressive difficulty curve

### 6. Modular Ship Assembly
- Build custom spaceships from individual modules
- Module types:
  - Cockpit (required for piloting)
  - Engines (required for propulsion)
  - Fuel Tanks (required for flight)
  - Weapons
  - Shields
  - Cargo Bays
  - Life Support
  - Sensors
  - Hull Sections
- Connection point system for attaching modules
- Power management (generation vs consumption)
- Mass calculations affecting ship performance
- Ship validation before flight

## Project Structure

```
AstroEngineer/
├── AstroEngineer.uproject          # Main project file
├── Source/                          # C++ source code
│   ├── AstroEngineer/
│   │   ├── Public/                  # Header files
│   │   │   ├── AstroEngineer.h
│   │   │   ├── AstroPlayerCharacter.h
│   │   │   ├── AstroInventoryComponent.h
│   │   │   ├── AstroCraftingComponent.h
│   │   │   ├── AstroResearchComponent.h
│   │   │   ├── AstroShipModule.h
│   │   │   ├── AstroShipAssembly.h
│   │   │   └── AstroGameMode.h
│   │   ├── Private/                 # Implementation files
│   │   │   └── [corresponding .cpp files]
│   │   └── AstroEngineer.Build.cs
│   ├── AstroEngineer.Target.cs
│   └── AstroEngineerEditor.Target.cs
├── Config/                          # Configuration files
│   ├── DefaultEngine.ini
│   ├── DefaultInput.ini
│   └── DefaultGame.ini
├── Content/                         # Game assets (to be created in editor)
│   ├── Blueprints/
│   ├── Maps/
│   ├── UI/
│   ├── Materials/
│   ├── Meshes/
│   └── Textures/
└── Docs/                           # Documentation
    ├── SETUP.md
    ├── ARCHITECTURE.md
    ├── DEVELOPMENT_GUIDE.md
    └── ASSET_GUIDELINES.md
```

## Core Systems

### Player Character (AAstroPlayerCharacter)
- First person controller with Enhanced Input
- Interaction system for world objects
- Backpack toggle functionality
- Movement restriction when interface is open
- Integration with inventory and crafting systems

### Inventory Component (UAstroInventoryComponent)
- Add/Remove items with quantity
- Stack management
- Slot limitations
- Event broadcasting for UI updates
- Query functions for crafting/research requirements

### Crafting Component (UAstroCraftingComponent)
- Recipe validation
- Resource checking via inventory
- Crafting progress tracking
- Result delivery to inventory
- Unlockable recipe system

### Research Component (UAstroResearchComponent)
- Tech tree node system
- Prerequisite validation
- Progressive unlocking
- Recipe and module unlocking
- Research time tracking

### Ship Module System (AAstroShipModule)
- Modular actor-based components
- Connection point system
- Type-based compatibility
- Stats: mass, power, crew capacity
- Attach/detach functionality

### Ship Assembly (AAstroShipAssembly)
- Module management
- Requirement validation (cockpit, engine, fuel)
- Power balance calculation
- Mass calculation
- Flight readiness checking
- Finalization system

## Getting Started

### Prerequisites
- Unreal Engine 5.7 (download from Epic Games Launcher)
- Visual Studio 2022 (for C++ development on Windows)
- 16GB RAM minimum (32GB recommended)
- Graphics card with DirectX 12 support

### Setup Instructions

1. **Clone the Repository**
   ```bash
   git clone https://github.com/shifty81/Astro-Engineer.git
   cd Astro-Engineer
   ```

2. **Generate Project Files**
   - Right-click on `AstroEngineer.uproject`
   - Select "Generate Visual Studio project files"

3. **Open in Visual Studio**
   - Open `AstroEngineer.sln`
   - Build the solution (Build > Build Solution)

4. **Launch Editor**
   - Double-click `AstroEngineer.uproject`
   - Wait for initial compile and shader compilation

5. **Create Content**
   - See ASSET_GUIDELINES.md for asset creation
   - Import/create meshes for ship modules
   - Design UI widgets for interface system
   - Create materials and textures

## Development Roadmap

### Phase 1: Core Systems (Current)
- [x] Project structure setup
- [x] Player character with Enhanced Input
- [x] Inventory system
- [x] Crafting system
- [x] Research system
- [x] Modular ship module base
- [x] Ship assembly manager

### Phase 2: Content Creation
- [ ] UI Widget Blueprints
  - [ ] Backpack interface master widget
  - [ ] Inventory grid widget
  - [ ] Crafting menu widget
  - [ ] Research tree widget
  - [ ] Ship assembly widget
  - [ ] HUD widget
- [ ] Character animations
  - [ ] Backpack remove/equip
  - [ ] Kneeling animation
  - [ ] Interaction animations
- [ ] Ship module meshes
  - [ ] Cockpit variations
  - [ ] Engine types
  - [ ] Fuel tank sizes
  - [ ] Weapon systems
  - [ ] Other modules

### Phase 3: Gameplay Implementation
- [ ] World interaction system
- [ ] Resource gathering
- [ ] Item spawning and management
- [ ] Recipe data tables
- [ ] Research tree data
- [ ] Ship module data

### Phase 4: Ship Flight System
- [ ] Ship pawn controller
- [ ] Flight physics
- [ ] Space environment
- [ ] Planetary system
- [ ] Navigation system
- [ ] Combat system (if weapons implemented)

### Phase 5: Polish & Content
- [ ] Sound effects
- [ ] Music system
- [ ] Visual effects
- [ ] Level design
- [ ] Tutorial system
- [ ] Save/load system

## Technical Details

### Enhanced Input System
The project uses UE5's Enhanced Input plugin for flexible control mapping:
- Input Actions defined in C++
- Input Mapping Contexts for different game states
- Blueprint-configurable input mappings
- Support for multiple input devices

### Component-Based Architecture
All major systems use components for modularity:
- Easy attachment to actors
- Reusable across different actor types
- Event-driven communication
- Blueprint-friendly interface

### Blueprint Integration
C++ classes designed for Blueprint extension:
- BlueprintCallable functions
- BlueprintReadWrite properties
- Blueprint events for animations
- Widget binding support

## Performance Considerations

- Inventory uses TArray for efficiency
- Research tree uses FName for fast lookups
- Ship modules use attachment system for hierarchy
- Event delegates prevent constant polling
- Configurable limits prevent memory issues

## Contributing

See DEVELOPMENT_GUIDE.md for:
- Coding standards
- Git workflow
- Testing procedures
- Documentation requirements

## License

Copyright Astro Engineer Team. All Rights Reserved.

## Support

For issues, questions, or contributions:
- GitHub Issues: https://github.com/shifty81/Astro-Engineer/issues
- Documentation: See /Docs folder

## Credits

- Built with Unreal Engine 5.7
- Uses Enhanced Input System
- First Person Template as base
