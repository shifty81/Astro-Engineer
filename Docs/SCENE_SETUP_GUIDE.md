# Scene Setup and Modification Guide

## Overview

This guide provides comprehensive instructions for creating and modifying scenes (levels/maps) in Astro Engineer. It covers everything from basic level creation to advanced environment setup for space exploration gameplay.

## Table of Contents

1. [Understanding Unreal Engine Scenes](#understanding-unreal-engine-scenes)
2. [Creating Your First Scene](#creating-your-first-scene)
3. [World Settings Configuration](#world-settings-configuration)
4. [Lighting Setup](#lighting-setup)
5. [Player Spawn Configuration](#player-spawn-configuration)
6. [Environment Setup](#environment-setup)
7. [Space Environment](#space-environment)
8. [Surface/Ground Setup](#surfaceground-setup)
9. [Testing Environment](#testing-environment)
10. [Performance Optimization](#performance-optimization)
11. [Scene Organization](#scene-organization)
12. [Common Scene Modifications](#common-scene-modifications)
13. [Troubleshooting](#troubleshooting)

---

## Understanding Unreal Engine Scenes

### What is a Scene?

In Unreal Engine, a **Scene** is also called a **Level** or **Map** (`.umap` file). It contains:

- **Actors**: All game objects (lights, meshes, characters, triggers)
- **World Settings**: Game mode, physics, rendering settings
- **Navigation**: Pathfinding data
- **Lighting**: Light sources and baked lighting data
- **Audio**: Ambient sounds and reverb zones

### Scene Types in Astro Engineer

1. **Main Menu Scene**: UI-only level for game start
2. **Test/Development Scene**: Simple level for testing mechanics
3. **Surface Scene**: Planetary surface with terrain
4. **Space Scene**: Open space with planets and stations
5. **Interior Scene**: Inside buildings or ships

---

## Creating Your First Scene

### Method 1: Quick Create (Recommended for Testing)

1. **Open Unreal Editor**
2. **Click** `File` → `New Level...`
3. **Select Template**:
   - **Empty Level**: Blank slate (recommended for custom scenes)
   - **Default**: Basic sky, light, and floor
   - **Open World**: Large terrain-based level
4. **Click** `Create`
5. **Save Immediately**: `File` → `Save Current Level As...`
   - **Folder**: `Content/Maps/`
   - **Name**: `TestLevel` or `DevelopmentLevel`

### Method 2: From Content Browser

1. **Open Content Browser**
2. **Navigate to** `Content/Maps/` (create folder if needed)
3. **Right-click** in empty space
4. **Select** `Level` → `Empty Level`
5. **Name it**: `TestLevel`
6. **Double-click** to open

### Scene Folder Structure

Organize your scenes:
```
Content/Maps/
├── Development/
│   ├── TestLevel.umap
│   └── PrototypeLevel.umap
├── Space/
│   ├── SpaceStation.umap
│   ├── Asteroid.umap
│   └── OpenSpace.umap
├── Surface/
│   ├── MoonSurface.umap
│   └── PlanetSurface.umap
└── MainMenu.umap
```

---

## World Settings Configuration

### Accessing World Settings

1. **Open your scene**
2. **Window** → `World Settings` (or click World Settings in toolbar)
3. **Dock** the panel for easy access

### Essential Settings

#### 1. Game Mode Configuration

**Purpose**: Defines which character, rules, and HUD to use

**Steps**:
1. In **World Settings** → `Game Mode`
2. **GameMode Override**: Select `BP_AstroGameMode`
   - If not created yet, select `AstroGameMode` (C++ class)
3. **Default Pawn Class**: `BP_AstroPlayerCharacter`
4. **HUD Class**: `BP_AstroHUD` (if created)
5. **Player Controller Class**: Leave as default or custom if needed

**Result**: When you press Play, this scene will spawn your character

#### 2. Physics Settings

**Default is usually fine**, but for space scenes:

1. **World Settings** → `Physics`
2. **Default Gravity Z**: -980 (Earth-like)
   - For space: 0 or very low value (-50)
   - For low-gravity moon: -162 (Moon gravity)
3. **Enable Physics**: ✅ Checked

#### 3. Rendering Settings

1. **World Settings** → `Lightmass`
2. **Force No Precomputed Lighting**: ❌ Unchecked (allows baked lighting)
3. **Use Sky Lighting**: ✅ Checked

For better visuals:
1. **World Settings** → `Rendering`
2. **Generate Mesh Distance Fields**: ✅ Checked (for better shadows)

#### 4. World Composition (For Large Worlds)

If creating a large open world:
1. **World Settings** → `World`
2. **Enable World Composition**: ✅ Checked
3. **Enable World Bounds Checks**: ✅ Checked

---

## Lighting Setup

Good lighting is crucial for atmosphere and visibility.

### Basic Lighting (Simple Scene)

#### 1. Directional Light (Sun)

**Purpose**: Main light source, simulates sun

**Setup**:
1. **Place Actor**: Drag `Directional Light` from Place Actors panel
2. **Position**: Anywhere (direction matters, not position)
3. **Rotation**: Angle downward (e.g., X=-45, Y=0, Z=0)
4. **Settings**:
   - **Intensity**: 3.0 - 10.0 (default 10)
   - **Light Color**: White or slight yellow
   - **Mobility**: Stationary (for mixed lighting)
   - **Cast Shadows**: ✅ Checked

#### 2. Sky Light (Ambient Lighting)

**Purpose**: Provides ambient light from sky

**Setup**:
1. **Place Actor**: Drag `Sky Light` from Place Actors panel
2. **Position**: Anywhere (doesn't matter)
3. **Settings**:
   - **Intensity**: 1.0
   - **Source Type**: `SLS Captured Scene`
   - **Mobility**: Stationary
   - **Recapture**: Click after adding sky

#### 3. Sky Atmosphere (Sky Visual)

**Purpose**: Creates realistic sky gradient and atmospheric scattering

**Setup**:
1. **Place Actor**: Search for `Sky Atmosphere` in Place Actors
2. **Position**: Anywhere
3. **Default settings work well**
4. **For alien planets**: Adjust `Rayleigh Scattering Scale`

#### 4. Exponential Height Fog (Optional)

**Purpose**: Adds atmospheric depth and haze

**Setup**:
1. **Place Actor**: `Exponential Height Fog`
2. **Settings**:
   - **Fog Density**: 0.02 (subtle)
   - **Fog Height Falloff**: 0.2

### Space Lighting (Dark Environment)

For space scenes:

#### 1. Point Lights for Stars

```
Place Actor: Point Light
Position: Scattered around scene
Settings:
  - Intensity: 50-100
  - Attenuation Radius: 5000-10000
  - Light Color: White/Blue tint
```

#### 2. Spotlight for Ship Lights

```
Place Actor: Spot Light
Position: On ships/stations
Settings:
  - Intensity: 5000-10000
  - Inner Cone Angle: 15
  - Outer Cone Angle: 30
```

#### 3. Skybox for Stars

1. **Create Material**: Star field texture
2. **Place Actor**: `BP_Sky_Sphere` (if using sky sphere)
3. **Or use**: `Sky Atmosphere` with dark settings

### Interior Lighting

For inside buildings/ships:

```
Mix of:
- Point Lights (ceiling lights)
- Spot Lights (directional fixtures)
- Rect Lights (panels, screens)

Settings:
  - Lower intensity (100-500)
  - Colored tints (blue for screens, warm for lamps)
  - Use IES profiles for realistic fixtures
```

---

## Player Spawn Configuration

### Adding Player Start

**Player Start** defines where the player spawns in the scene.

#### Method 1: Place Manually

1. **Place Actors Panel** → Search `Player Start`
2. **Drag** into scene
3. **Position**: Where you want player to spawn
4. **Rotation**: Direction player faces initially
5. **Z-axis**: Slightly above ground (Z=100 from ground level)

#### Method 2: Viewport Menu

1. **In Viewport**: Right-click where you want spawn
2. **Place Actor** → `Player Start`

### Player Start Settings

1. **Select** Player Start actor
2. **Details** panel:
   - **Auto Receive Input**: Player 0 (default)
   - **Player Start Tag**: (optional, for multiple spawns)

### Multiple Spawn Points

For random spawns or multiplayer:

1. **Place multiple** Player Start actors
2. **Tag them**: `SpawnPoint_1`, `SpawnPoint_2`, etc.
3. **In Game Mode**: Implement spawn logic to choose randomly

### Testing Spawn Position

1. **Select** Player Start
2. **Press** `Eject` (F8) in PIE to see spawn location
3. **Or**: Add visual marker (arrow component)

---

## Environment Setup

### Essential Environment Actors

Every scene needs these basic elements:

#### 1. Floor/Ground

**Option A: Simple Plane**
```
Place Actor: Cube (scale it flat)
Scale: (100, 100, 0.1) for large floor
Position: Z=0
Material: Ground/concrete texture
Collision: Block All
```

**Option B: Landscape**
```
Mode: Landscape
Create New: Size 127x127 or larger
Sculpt terrain as needed
Paint textures (grass, dirt, rock)
```

#### 2. Skybox

**Option A: Atmospheric Sky (Realistic)**
```
Actors:
  - Sky Atmosphere
  - Directional Light (sun)
  - Sky Light
  - Exponential Height Fog (optional)
```

**Option B: Static Skybox (Space)**
```
Create Material:
  - Use HDR cubemap texture
  - Unlit, fully emissive
Place Actor: Sky Sphere or custom mesh
  - Scale: Very large (50000+)
  - Material: Sky material
```

#### 3. Boundaries (Optional)

Prevent player from falling off edge:

```
Place Actor: Blocking Volume
Scale: Wall-sized
Position: Around map edges
Collision: Block All
Visible: Unchecked
```

### Modular Environment Building

#### Using Static Meshes

1. **Import/Create** modular pieces (walls, floors, ceilings)
2. **Snap to Grid**: Enable grid snapping (Grid Size: 100 or 50)
3. **Place and align** pieces
4. **Use End/Home keys**: Snap to ground

#### Asset Organization

```
Content/Environment/
├── Architecture/
│   ├── Walls/
│   ├── Floors/
│   └── Ceilings/
├── Props/
│   ├── Furniture/
│   └── Equipment/
├── Natural/
│   ├── Rocks/
│   └── Plants/
└── Materials/
```

---

## Space Environment

### Creating a Space Scene

Space scenes require special considerations:

#### 1. Gravity Settings

```
World Settings → Physics
  - Default Gravity Z: 0 (zero gravity)
  - Or: -50 for slight pull
```

#### 2. Skybox with Stars

**Method A: Material-Based**

1. **Create Material**: `M_StarField`
   ```
   Material Setup:
   - Unlit
   - TextureSample (star texture)
   - Multiply by Emissive Color (brightness)
   - Two Sided: Yes
   ```

2. **Create Sky Sphere**:
   ```
   Place Actor: Sphere (static mesh)
   Scale: 50000 (huge)
   Material: M_StarField
   Collision: No Collision
   ```

**Method B: BP_Sky_Sphere**

1. **Place** `BP_Sky_Sphere` actor
2. **Disable** Sun (use custom lighting)
3. **Set colors** to dark/black
4. **Add star overlay** texture

#### 3. Planets and Celestial Bodies

```
Create Blueprint: BP_Planet
Components:
  - Static Mesh (sphere)
  - Point Light (glow/atmosphere)
  - Rotating Movement (optional)
  
Settings:
  - Large scale (5000-20000)
  - Custom material (planet surface)
  - Distance: Far from player spawn
```

#### 4. Space Station Props

```
Place Actors:
  - Structures (imported meshes)
  - Lights (Spot Lights on structures)
  - Particles (thruster effects)
  - Audio (ambient hum)
```

#### 5. Asteroid Field

```
Create Blueprint: BP_AsteroidField
Logic:
  - Spawn random asteroids in volume
  - Variation in size/rotation
  - Collision: Simple shapes
  
Use Foliage Tool for placement:
  - Add asteroid mesh as foliage type
  - Paint in scene
```

---

## Surface/Ground Setup

### Planetary Surface Scene

#### 1. Landscape Creation

**Create Landscape**:
1. **Mode**: Landscape
2. **Click**: `New` (Create New)
3. **Settings**:
   - **Section Size**: 63x63 quads
   - **Sections Per Component**: 1x1
   - **Number of Components**: 8x8 (or larger)
4. **Material**: Ground material (create one)
5. **Click**: `Create`

**Sculpt Terrain**:
1. **Mode**: Landscape
2. **Sculpt** tab:
   - **Tool**: Sculpt (raise/lower)
   - **Brush Size**: Adjust slider
   - **Brush Strength**: Adjust slider
   - **Click and drag**: Shape terrain

**Paint Textures**:
1. **Create Landscape Material** with layer blend
2. **Paint** tab:
   - Select texture layer (grass, dirt, rock)
   - Paint on landscape

#### 2. Rocks and Props

```
Place Actors:
  - Rock static meshes (various sizes)
  - Use foliage tool for mass placement
  - Randomize rotation and scale
  
Collision:
  - Complex collision for large rocks
  - No collision for small decorative rocks
```

#### 3. Atmosphere

```
Actors:
  - Sky Atmosphere (Earth-like or alien colors)
  - Directional Light (sun angle based on planet)
  - Exponential Height Fog (atmospheric haze)
  - Volumetric Clouds (for depth)
```

#### 4. Horizon

For large open areas:
- **Far clip plane**: Increase in World Settings
- **Distance fog**: Use Exponential Height Fog
- **Sky**: Properly scaled skybox or atmosphere

---

## Testing Environment

### Creating a Test Level

A good test level should be simple and functional:

#### 1. Basic Geometry

```
Actors:
  - Large floor plane (2000x2000)
  - Some walls (for collision testing)
  - Ramps (for movement testing)
  - Platforms at various heights
```

#### 2. Test Props

```
Place:
  - Cubes (for scale reference)
  - Interactable objects (test interaction)
  - Obstacles (test collision)
```

#### 3. Debug Visuals

```
Enable:
  - Grid (for alignment)
  - Collision view (show collision shapes)
  - Stat displays (stat fps, stat unit)
```

#### 4. Quick Iteration

**Tip**: Create a persistent test level:
- Keep it simple
- Don't worry about visuals
- Focus on functionality
- Use placeholder assets

---

## Performance Optimization

### Scene Optimization Best Practices

#### 1. Culling

**Frustum Culling** (automatic): Only render what camera sees

**Occlusion Culling**: Hide objects behind walls
```
Place Actor: Cull Distance Volume
Settings:
  - Set cull distances for mesh types
  - 0 = always render
  - Large distance = render far
```

#### 2. Level of Detail (LOD)

**For Static Meshes**:
```
Mesh Settings:
  - LOD 0: High poly (close)
  - LOD 1: Medium poly (mid)
  - LOD 2: Low poly (far)
  - LOD 3: Very low poly (very far)
```

**Auto LOD**:
- Let Unreal generate LODs
- Adjust reduction percentages

#### 3. Lighting

**Use Static/Stationary Lights**:
- Baked lighting is cheaper than dynamic
- **Build Lighting**: Build → Build Lighting Only

**Reduce Shadows**:
```
Light Settings:
  - Dynamic Shadow Distance: Lower value
  - Use fewer shadow-casting lights
```

#### 4. Draw Calls

**Reduce Draw Calls**:
- Merge static meshes (Actor → Merge Actors)
- Use instancing for repeated objects
- Minimize material count

#### 5. Texture Streaming

```
Project Settings → Rendering:
  - Texture Streaming: Enabled
  - Pool Size: Adequate for your textures
```

### Profiling Tools

**Check Performance**:
```
Console Commands:
  stat fps        - Frame rate
  stat unit       - Frame time breakdown
  stat scenerendering - Rendering stats
  profilegpu      - GPU profiler
```

**Optimize Based On**:
- If CPU-bound: Reduce game logic, tick functions
- If GPU-bound: Reduce polygons, lights, effects

---

## Scene Organization

### Folder Structure

**Good organization prevents chaos**:

```
Outliner (Scene Hierarchy):
├─ Lighting
│  ├─ DirectionalLight_Sun
│  ├─ SkyLight
│  └─ [Other lights]
├─ Environment
│  ├─ Ground
│  ├─ Buildings
│  └─ Props
├─ Gameplay
│  ├─ PlayerStart
│  ├─ Triggers
│  └─ Pickups
├─ Audio
│  └─ AmbientSounds
└─ Effects
   └─ Particles
```

### Using Folders in Outliner

1. **Right-click** in Outliner → `Create Folder`
2. **Name** folder (e.g., "Lighting")
3. **Drag actors** into folder
4. **Collapse/expand** for clean view

### Layer System (Advanced)

1. **Window** → `Layers`
2. **Create layers** for different parts
3. **Assign actors** to layers
4. **Toggle visibility** per layer

---

## Common Scene Modifications

### Changing Time of Day

**Method 1: Rotate Directional Light**
```
Select Directional Light
Rotation:
  - Morning: X=-30, Y=0, Z=0
  - Noon: X=-90, Y=0, Z=0
  - Evening: X=-150, Y=0, Z=0
  - Night: Intensity=0 (or remove)
Light Color:
  - Morning/Evening: Orange tint
  - Noon: White
```

**Method 2: Time of Day System (Blueprint)**
```
Create BP_TimeOfDaySystem
Logic:
  - Tick → Update sun rotation over time
  - Lerp light color based on angle
  - Update sky atmosphere
```

### Adding Water

**Quick Water**:
1. **Place Actor**: Plane (for water surface)
2. **Material**: `M_Water` (create with transparency, normal maps)
3. **Position**: At water level
4. **Post Process Volume**: Add underwater effect

**Realistic Water**:
- Use Water plugin (UE5.7 has water system)
- Configure waves, foam, caustics

### Weather Effects

**Rain**:
```
Create Particle System: PS_Rain
Emitter:
  - Spawn rate: High (1000+)
  - Velocity: Downward
  - Sprite: Raindrop texture
  - Collision: Optional (expensive)
```

**Fog**:
```
Place Actor: Exponential Height Fog
Increase density: 0.05-0.1
Reduce Start Distance
```

### Post Processing

**Add Post Process Volume**:
```
Place Actor: Post Process Volume
Settings:
  - Infinite Extent: ✅ (affects whole level)
  - Color Grading: Adjust colors/contrast
  - Bloom: Add glow to bright lights
  - Depth of Field: Blur background (cinematic)
  - Vignette: Darken edges
```

---

## Troubleshooting

### Scene Won't Load

**Possible Causes**:
1. Corrupted map file
   - **Fix**: Restore from backup
2. Missing assets referenced
   - **Fix**: Fix up redirectors, reimport assets
3. Out of memory
   - **Fix**: Close other programs, reduce texture quality

### Player Doesn't Spawn

**Possible Causes**:
1. No Player Start in scene
   - **Fix**: Add Player Start actor
2. Wrong Game Mode
   - **Fix**: Set GameMode Override in World Settings
3. Player Start blocked
   - **Fix**: Move Player Start away from obstacles

### Dark Scene / No Lighting

**Possible Causes**:
1. No lights placed
   - **Fix**: Add Directional Light and Sky Light
2. Lights not built
   - **Fix**: Build → Build Lighting Only
3. Mobility set wrong
   - **Fix**: Set lights to Stationary or Movable

### Low Frame Rate

**Possible Causes**:
1. Too many polygons
   - **Fix**: Use LODs, reduce mesh complexity
2. Too many lights
   - **Fix**: Reduce dynamic lights, use baked lighting
3. Expensive materials
   - **Fix**: Simplify materials, reduce texture size
4. Too many draw calls
   - **Fix**: Merge meshes, use instancing

**Profile**:
- Use `stat fps` and `stat unit`
- Identify bottleneck (CPU or GPU)
- Optimize accordingly

### Collision Issues

**Player Falls Through Floor**:
```
Select Floor Mesh
Details → Collision:
  - Collision Presets: BlockAll
  - Collision Enabled: Query and Physics
  - Simulate Physics: ❌ Unchecked
```

**Can't Walk Through Door**:
```
Select Door Mesh
Details → Collision:
  - Collision Enabled: No Collision (when open)
  - Or use Blueprint to disable collision
```

---

## Best Practices

### Scene Creation

✅ **Start simple**: Basic geometry first, details later
✅ **Test early**: Press Play frequently to check
✅ **Use grid snapping**: Keep things aligned
✅ **Organize with folders**: Clean outliner = clean mind
✅ **Save often**: Crashes happen, don't lose work
✅ **Version control**: Use Git for level files too

### Lighting

✅ **Bake when possible**: Stationary > Movable lights
✅ **Don't overdo it**: More lights ≠ better visuals
✅ **Test in darkness**: Make sure everything is visible
✅ **Use color**: Tinted lights add atmosphere
✅ **Build lighting**: Always build before final test

### Performance

✅ **Profile regularly**: Check fps during development
✅ **Optimize assets**: Reduce poly count, texture sizes
✅ **Cull aggressively**: Don't render what's not seen
✅ **LODs everywhere**: Distance-based quality reduction
✅ **Test on target hardware**: Not just your dev machine

---

## Scene Templates

### Template 1: Basic Test Scene

**Setup Time**: 5 minutes

**Contains**:
- Large floor plane
- Directional Light + Sky Light
- Player Start
- Basic sky atmosphere

**Purpose**: Quick testing

### Template 2: Interior Scene

**Setup Time**: 15 minutes

**Contains**:
- Modular walls/floor/ceiling
- Point Lights (ceiling mounted)
- Spot Lights (directional fixtures)
- Props and furniture
- Post Process Volume

**Purpose**: Indoor gameplay

### Template 3: Space Station

**Setup Time**: 30 minutes

**Contains**:
- Zero gravity (World Settings)
- Space skybox with stars
- Station structure (meshes)
- External spot lights
- Planets in distance
- Particle effects

**Purpose**: Space environment

### Template 4: Planetary Surface

**Setup Time**: 45 minutes

**Contains**:
- Landscape terrain
- Atmosphere setup (Sky, Fog)
- Surface details (rocks, props)
- Proper lighting (sun)
- Distant mountains/horizon

**Purpose**: Surface exploration

---

## Advanced Scene Techniques

### Procedural Generation

Use Blueprint construction script:
```
BP_ProceduralLevel:
  Construction Script:
    - For loop (create grid)
    - Spawn modular pieces
    - Randomize variations
```

### Level Streaming

For large worlds:
```
Create Sub-Levels:
  - Persistent Level (always loaded)
  - Streaming Level 1 (loads when near)
  - Streaming Level 2 (loads when near)
  
Setup:
  - Window → Levels
  - Right-click → Create New
  - Set streaming method (Blueprint or Distance)
```

### World Composition

For massive open worlds:
```
Enable in World Settings
Use World Composition window
Import heightmap (tiled)
Auto-manages level streaming
```

---

## Conclusion

You now have:
- ✅ Complete scene creation workflow
- ✅ World settings configuration
- ✅ Lighting setup for various environments
- ✅ Player spawn configuration
- ✅ Environment building techniques
- ✅ Performance optimization strategies
- ✅ Troubleshooting solutions

Scenes are where your game comes to life. Start simple, test often, and iterate based on gameplay needs. Refer to FPS_TEMPLATE_IMPLEMENTATION.md for character setup, and BLUEPRINT_QUICKSTART.md for creating interactive content within your scenes.

---

## Additional Resources

- [Level Design in Unreal Engine](https://docs.unrealengine.com/5.7/level-design-in-unreal-engine/)
- [Lighting Basics](https://docs.unrealengine.com/5.7/lighting-the-environment-in-unreal-engine/)
- [World Composition](https://docs.unrealengine.com/5.7/world-composition-in-unreal-engine/)
- [Performance Optimization](https://docs.unrealengine.com/5.7/performance-and-profiling-in-unreal-engine/)
