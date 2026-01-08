# Orbital Mechanics Guide

## Overview

This guide explains the orbital mechanics system in Astro Engineer, providing both the theoretical foundation and practical implementation details for achieving and maintaining orbit, performing maneuvers, and traveling between celestial bodies.

---

## Table of Contents
1. [Basic Orbital Concepts](#basic-orbital-concepts)
2. [Launch to Orbit](#launch-to-orbit)
3. [Orbital Maneuvers](#orbital-maneuvers)
4. [Rendezvous and Docking](#rendezvous-and-docking)
5. [Interplanetary Transfer](#interplanetary-transfer)
6. [Flight Controls](#flight-controls)
7. [Implementation Details](#implementation-details)

---

## Basic Orbital Concepts

### What is an Orbit?

An orbit is a curved path where an object continuously falls toward a celestial body but moves fast enough sideways that it never hits the ground. It's a delicate balance between:
- **Gravity** pulling you down
- **Velocity** carrying you sideways

### Key Orbital Parameters

#### 1. Apoapsis and Periapsis
- **Apoapsis (Ap)**: Highest point in orbit
- **Periapsis (Pe)**: Lowest point in orbit
- **Semi-major axis**: Average of Ap and Pe
- Measured from planet center (subtract radius for altitude)

```
        Apoapsis (furthest)
             ╱  ╲
           ╱      ╲
         ╱          ╲
Planet ●──────────────◉ Spacecraft
         ╲          ╱
           ╲      ╱
             ╲  ╱
        Periapsis (closest)
```

#### 2. Eccentricity
- **e = 0**: Perfect circle
- **0 < e < 1**: Ellipse (most orbits)
- **e = 1**: Parabola (escape trajectory)
- **e > 1**: Hyperbola (interplanetary trajectory)

#### 3. Inclination
- Angle between orbital plane and equator
- **0°**: Equatorial orbit
- **90°**: Polar orbit
- **180°**: Retrograde orbit (opposite planet rotation)

#### 4. Orbital Velocity
Speed needed to maintain orbit:
```
v = √(GM/r)
```
Where:
- G = Gravitational constant
- M = Mass of planet
- r = Distance from planet center

**Earth Example**:
- At 200 km altitude: ~7,784 m/s (orbital velocity)
- At 400 km altitude: ~7,669 m/s
- At geosynchronous (35,786 km): ~3,075 m/s

### Orbital Energy
- **Lower orbit** = Higher velocity, higher energy requirement
- **Higher orbit** = Lower velocity, less energy to maintain
- Counterintuitive: Speeding up raises your orbit but slows you down at apoapsis

### Escape Velocity
Minimum speed to escape planet's gravity:
```
v_escape = √(2GM/r) = v_orbital × √2
```
**Earth surface**: ~11,186 m/s

---

## Launch to Orbit

### Launch Phases

#### Phase 1: Vertical Ascent (0-10 km)
**Duration**: ~30 seconds  
**Throttle**: 100%  
**Objective**: Clear dense atmosphere

- Launch straight up (pitch 90°)
- Minimize aerodynamic drag
- Build initial velocity
- Clear obstacles and structures
- Reach 1 km altitude quickly

**What you see**:
- Rapid altitude gain
- High G-forces (2-3 G)
- Engine roar and vibration
- Ground shrinking below

#### Phase 2: Gravity Turn (10-50 km)
**Duration**: 1-2 minutes  
**Throttle**: 75-100%  
**Objective**: Build horizontal velocity

The **gravity turn** is the most fuel-efficient way to reach orbit:

1. At ~10 km, pitch over to **80°** (10° from vertical)
2. At 20 km, pitch to **60°** 
3. At 30 km, pitch to **45°**
4. At 40 km, pitch to **30°**
5. At 50 km, pitch to **10°**

**Why?**
- Too vertical: Wastes fuel fighting gravity
- Too horizontal: Atmospheric drag destroys you
- Gradual turn: Atmosphere thins as you gain horizontal speed

**What you see**:
- Horizon tilting
- Atmosphere fading (blue → black)
- Velocity vector shifting horizontal
- Altitude and horizontal speed both increasing

#### Phase 3: Coasting to Apoapsis (50-150 km)
**Duration**: 1-3 minutes  
**Throttle**: 0% (engine off)  
**Objective**: Let momentum carry you high

- Cut engines at 50-70 km
- Pitch to 0° (horizontal)
- Coast upward
- Apoapsis marker appears ahead in orbit
- Save fuel for circularization

**What you see**:
- Curved trajectory arc
- Apoapsis marker above
- Time to apoapsis countdown
- Free-fall sensation

#### Phase 4: Circularization Burn (At Apoapsis)
**Duration**: 15-60 seconds  
**Throttle**: Varies  
**Objective**: Raise periapsis above atmosphere

When you reach apoapsis (around 150-200 km):
1. Orient prograde (velocity direction)
2. Throttle up when apoapsis reached
3. Watch periapsis marker rise
4. When periapsis > 100 km (above atmosphere): cut engine
5. You're now in stable orbit!

**What you see**:
- Periapsis marker rising with each second of burn
- Orbit changing from ellipse to circle
- "Stable orbit achieved" message
- Congratulations!

### Launch Profile Summary

```
Altitude vs Time Graph:

200km |                  ╭─────── Circular orbit
      |                ╱
150km |              ╱ (circularization burn)
      |            ●
100km |          ╱  
      |        ╱    (coast phase)
 50km |      ╱      
      |    ╱ (gravity turn)
 10km |  ╱
      | ╱ (vertical)
   0  |●
      └──────────────────────────────
      0   1   2   3   4   5  minutes
```

### Delta-V Budget for Orbit

**Earth Launch to 200 km orbit**:
- Gravity losses: ~1,500 m/s
- Drag losses: ~100 m/s
- Orbital velocity: ~7,800 m/s
- **Total required**: ~9,400 m/s

**Fuel Required** (for Starter I):
- Total delta-V: ~3,500 m/s (single stage)
- Not enough for orbit from surface!
- Solution: Two-stage rocket or orbital construction

### Staging System

Multi-stage rockets drop empty tanks/engines:

**Two-Stage Design**:
- **Stage 1**: Large engine + large fuel tank
  - Burns: Surface to 50 km
  - Then: Decoupled and falls away
- **Stage 2**: Small engine + small fuel tank
  - Burns: 50 km to orbit
  - Remains: Your ship in orbit

**How to Stage**:
1. Build rocket with multiple module groups
2. Set stage separation points
3. During flight: Press **Space** to activate next stage
4. Previous stage decouples and falls away
5. New stage engine ignites

---

## Orbital Maneuvers

### Prograde and Retrograde

**Prograde** (velocity direction):
- Burn prograde: Go faster, raise opposite side of orbit
- Used for: Raising apoapsis, transferring to higher orbit

**Retrograde** (opposite velocity):
- Burn retrograde: Go slower, lower opposite side of orbit
- Used for: Lowering periapsis, deorbiting, landing

```
        Ap (200 km)
             ●
           ╱   ╲
         ╱       ╲
       ╱           ╲
    ●═══════════════◉→ (burn prograde here)
Planet ╲           ╱
         ╲       ╱ 
           ╲   ╱
        Pe (100 km)

Result: Ap raises to 300 km, Pe stays at 100 km
```

### Radial Burns

**Radial Out/In** (perpendicular to velocity):
- Rotate orbit without changing energy much
- Used for: Changing inclination, plane changes
- Very expensive in delta-V
- Best done at ascending/descending node

### Normal Burns

**Normal/Anti-Normal** (perpendicular to orbital plane):
- Changes orbital inclination
- Used for: Matching orbital planes for rendezvous
- Most expensive maneuver
- Avoid if possible

### Hohmann Transfer

Most efficient way to change orbital altitude:

**To Higher Orbit**:
1. At periapsis of current orbit: Burn prograde
2. Raises apoapsis to target altitude
3. Coast to new apoapsis
4. Burn prograde again to circularize
5. Now in higher circular orbit

**To Lower Orbit**:
1. At apoapsis of current orbit: Burn retrograde
2. Lowers periapsis to target altitude
3. Coast to new periapsis
4. Burn retrograde again to circularize
5. Now in lower circular orbit

**Delta-V Formula**:
```
ΔV_total = ΔV_1 + ΔV_2

From orbit r1 to r2:
ΔV_1 = √(μ/r1) × [√(2r2/(r1+r2)) - 1]
ΔV_2 = √(μ/r2) × [1 - √(2r1/(r1+r2))]
```

### Bi-Elliptic Transfer

For very large altitude changes, sometimes more efficient:
1. Raise apoapsis to very high altitude
2. At high apoapsis: Change orbital energy
3. Lower periapsis to target
4. Circularize at target

More complex, usually not worth it unless changing by 12x+ altitude.

---

## Rendezvous and Docking

### Overview

Rendezvous is meeting another spacecraft in orbit. Docking is physically connecting. This is one of the hardest skills to master.

### Prerequisites

**Before attempting**:
- Both craft in similar orbits (altitude within 5 km)
- Orbital planes aligned (inclination difference < 0.1°)
- RCS propellant available (50+ m/s delta-V)
- Docking ports on both craft
- Patience

### Phase 1: Orbital Matching

**Goal**: Get into same-size orbit as target

1. Target the other spacecraft (click in map view)
2. Note target's orbital altitude
3. Adjust your orbit to match:
   - If below target: Burn prograde to raise orbit
   - If above target: Burn retrograde to lower orbit
4. Aim for: Ap and Pe within 1 km of target's

### Phase 2: Phasing

**Goal**: Catch up to (or wait for) target

**If behind target**:
- Lower your orbit slightly
- You'll orbit faster and catch up
- Raise orbit when you get close

**If ahead of target**:
- Raise your orbit slightly
- You'll orbit slower and let target catch up
- Lower orbit when they get close

**Target closest approach**: < 5 km

### Phase 3: Close Approach

**Goal**: Get within 100m of target

At closest approach (< 5 km):
1. Kill relative velocity:
   - Point retrograde relative to target
   - Burn until relative velocity = 0 m/s
   - You'll drift slightly apart
   
2. Point at target:
   - Switch to target-relative velocity mode
   - Point nose at target
   - Burn gently (0.5 m/s)
   
3. Coast toward target:
   - Monitor closure rate
   - Should be 1-5 m/s
   
4. Kill velocity at 100m:
   - Point retrograde to target
   - Burn to cancel approach
   - Relative velocity = 0 again

### Phase 4: Final Approach

**Goal**: Dock successfully

**Critical**: This is the most dangerous phase

1. **Orient docking ports**:
   - Your port facing their port
   - Align using RCS rotation
   - Use docking alignment indicator
   - Both ports must face each other

2. **Slow approach** (0.1 - 0.3 m/s):
   - Very gentle forward thrust
   - Monitor alignment
   - Correct drift with RCS
   - Stay on center line

3. **Contact**:
   - Gentle bump at < 0.3 m/s
   - Magnetic capture engages
   - Docking clamps extend
   - Hard dock confirmed
   - Airtight seal established

4. **Transfer**:
   - Open hatch from inside
   - Crawl through tunnel
   - Welcome aboard!

### Common Mistakes

❌ **Going too fast**: Crashes and destroys ships  
✓ **Solution**: Final approach < 0.3 m/s

❌ **Misaligned ports**: Collide without docking  
✓ **Solution**: Use alignment HUD indicator

❌ **Running out of RCS fuel**: Can't maneuver  
✓ **Solution**: Carry 2x what you think you need

❌ **Impatience**: Rushing causes errors  
✓ **Solution**: Take your time, it's worth it

---

## Interplanetary Transfer

### Concept

Moving between planets requires:
1. Escaping current planet's sphere of influence
2. Traveling on heliocentric (sun-centered) orbit
3. Intercepting target planet's orbit
4. Capturing into target planet's orbit

### Transfer Windows

Planets are only properly aligned occasionally:
- **Earth → Mars**: Every 26 months
- **Earth → Venus**: Every 19 months
- **Earth → Jupiter**: Every 13 months

**Miss the window**: Wait for next one or spend much more fuel

### Hohmann Transfer (Interplanetary)

**Example: Earth to Mars**

1. **Wait for window**: Mars 44° ahead of Earth
2. **Escape Earth**: 
   - Burn prograde in Earth orbit
   - Increase velocity to escape velocity
   - Exit Earth's sphere of influence
3. **Heliocentric Coast**:
   - You're now orbiting the Sun
   - Elliptical orbit touches Earth and Mars orbits
   - Coast for ~6 months
4. **Mars Intercept**:
   - Arrive as Mars reaches that point
   - You're moving faster than Mars
5. **Capture Burn**:
   - Burn retrograde relative to Mars
   - Slow down to be captured
   - Enter Mars orbit

**Delta-V Budget** (Earth → Mars):
- Earth escape: ~3,200 m/s
- Mars capture: ~2,100 m/s
- Total: ~5,300 m/s (plus reserves)

### Gravity Assist

Use planet's gravity to change trajectory:

**How it works**:
1. Approach planet from behind (in its orbit)
2. Enter planet's sphere of influence
3. Gravity bends your path
4. Exit ahead of planet
5. You've "stolen" velocity from planet
6. Free speed boost!

**Voyager 2 Example**:
- Launched: 1977
- Used: Jupiter → Saturn → Uranus → Neptune
- Saved: Years of travel time and tons of fuel

**In Game**:
- Plan flybys through target's trailing side
- Gain 1-2 km/s "free" delta-V
- Reach distant planets much faster

### Aerobraking

Use atmosphere to slow down (free deceleration):

**How it works**:
1. Approach planet with atmosphere
2. Enter very high altitude (edge of atmosphere)
3. Atmospheric drag slows you down
4. Exit atmosphere, orbit lowered
5. Repeat multiple passes until desired orbit
6. Saves huge amounts of fuel

**Risks**:
- Too deep: Burn up or crash
- Too shallow: No effect, waste of time
- Heat damage: Need heat shield

**Best for**:
- Mars (thin atmosphere, safe)
- Venus (thick atmosphere, dangerous but effective)
- Earth return (standard procedure)

---

## Flight Controls

### Control Modes

#### 1. Surface Mode (Atmospheric Flight)
- **Pitch**: Elevator (up/down)
- **Yaw**: Rudder (left/right)
- **Roll**: Ailerons (bank)
- Like airplane controls

#### 2. Orbital Mode (Space Flight)
- **Pitch**: Rotate around lateral axis
- **Yaw**: Rotate around vertical axis
- **Roll**: Rotate around longitudinal axis
- **Translation**: Move without rotating (RCS)

### Input Mapping

**Keyboard**:
- **W/S**: Pitch up/down
- **A/D**: Yaw left/right
- **Q/E**: Roll left/right
- **Shift/Ctrl**: Throttle up/down
- **Space**: Stage or action
- **H/N**: RCS translation up/down
- **J/L**: RCS translation left/right
- **I/K**: RCS translation forward/backward
- **X**: Cut throttle
- **Z**: Full throttle
- **T**: SAS toggle

**Mouse**:
- **Move**: Rotate view (IVA) or ship (external)
- **Scroll**: Zoom
- **Right-click**: Free look

### Navball

The Navball is your primary orientation instrument:

```
      ╔════════════╗
      ║     N      ║   N = Normal (orbit up)
      ║  ╱  ●  ╲  ║   P = Prograde (velocity)
      ║ W   ✚   E  ║   R = Retrograde (opposite velocity)
      ║  ╲  ◉  ╱  ║   Ra = Radial (away from planet)
      ║     S      ║   S = South
      ╚════════════╝   

Yellow marker = Prograde (velocity)
Green marker = Retrograde (opposite)
Pink marker = Target (if selected)
Purple marker = Anti-target
```

**How to use**:
1. Identify which direction you want to point
2. Rotate ship until center ✚ aligns with desired marker
3. That direction is now "forward"

### SAS (Stability Assist System)

**Auto-pilot modes**:
- **Stability**: Hold current orientation
- **Prograde**: Point velocity direction
- **Retrograde**: Point opposite velocity
- **Radial**: Point away from planet
- **Normal**: Point "up" from orbit
- **Target**: Point at target ship/station
- **Maneuver**: Point at planned maneuver

**Usage**:
- Press T to toggle SAS
- Click mode buttons on HUD
- Ship automatically orients

### RCS (Reaction Control System)

**Small thrusters** for precise control:
- **Purpose**: Fine adjustments, docking, rotation
- **Fuel**: Monopropellant (separate from main fuel)
- **Thrust**: Low (1 kN per thruster)
- **Configuration**: Usually 8+ thrusters, covering all directions

**When to use**:
- Docking approaches
- Small orbital adjustments
- Attitude control without main engine
- When main engine too powerful

---

## Implementation Details

### Physics Engine

#### Coordinate Systems

**World Space** (Unreal Engine default):
- Origin at planet center
- X, Y, Z in cm (Unreal units)
- Problems at large distances (floating point precision)

**Floating Origin** (for large-scale space):
- Origin recenters on player
- Background objects shift instead
- Maintains precision at any distance
- Required for distances > 100 km

#### Gravity Calculation

```cpp
// Simplified Newton's law
FVector GravityAcceleration(FVector position, float planetMass)
{
    float G = 6.67430e-11; // Gravitational constant
    float distance = position.Size();
    float gravityMagnitude = G * planetMass / (distance * distance);
    
    FVector direction = -position.GetSafeNormal(); // Toward planet center
    return direction * gravityMagnitude;
}
```

**Optimizations**:
- Cache gravity for distant objects (update every second)
- Sphere of influence: Only nearest body affects you
- Patched conics: Simplified multi-body physics

#### Orbital Prediction

Calculate future position using:
1. **Kepler's Equation** (for elliptical orbits)
2. **Numerical Integration** (for complex situations)

**Trade-off**:
- Kepler: Fast, accurate, but only works for 2-body problem
- Integration: Slower, handles multiple bodies and thrust

#### Atmospheric Drag

```cpp
float DragForce = 0.5 * AirDensity * Velocity² * DragCoefficient * CrossSectionalArea
```

**Air Density Model**:
```cpp
float density = SeaLevelDensity * exp(-altitude / ScaleHeight)
```

Earth scale height: ~8,500 m

### UI Components

#### HUD Elements

1. **Velocity Indicator**:
   - Surface velocity (relative to ground)
   - Orbital velocity (relative to space)
   - Target relative velocity

2. **Altitude Indicator**:
   - Altitude above sea level (ASL)
   - Altitude above ground level (AGL)
   - Apoapsis and periapsis

3. **Resource Gauges**:
   - Fuel percentage
   - RCS propellant
   - Electric charge
   - Oxygen (for EVA)

4. **Navball**: Orientation instrument

5. **Staging Indicator**: Shows current stage and remaining

#### Map View

**Features**:
- 3D orbital view
- Predicted trajectory (colored line)
- Apoapsis/periapsis markers
- Maneuver nodes (planned burns)
- Target orbit overlay
- Closest approach indicators

**Controls**:
- Click and drag: Rotate view
- Scroll: Zoom
- Right-click: Pan
- Click object: Focus and info

### Maneuver Nodes

**Functionality**:
- Click on orbit to create node
- Drag prograde/retrograde/radial handles
- Shows delta-V required
- Shows resulting orbit
- Time to burn indicator
- Can create multiple nodes

**During Burn**:
- Countdown to node
- Burn direction indicator
- Remaining delta-V gauge
- Auto-throttle option

### Physics Simulation Rate

**Challenge**: Space physics needs accuracy

**Solution**:
- **Physics tick rate**: 50 Hz (0.02 seconds)
- **Substepping**: 10 substeps = 500 Hz effective
- **Variable time step**: Slows time for close approaches
- **Fast-forward**: Accelerate time for long coasts (2x, 5x, 10x, 100x)

### Save State

**Critical for long missions**:
- Save orbital elements (not just position/velocity)
- Save mission time
- Save resource levels
- Auto-save every 5 minutes
- Quick-save before maneuvers

---

## Tutorials and Practice

### Tutorial 1: First Orbit
1. Launch straight up to 10 km
2. Pitch to 45° at 10 km
3. Accelerate to 2000 m/s horizontal
4. Cut engine and coast to 150 km apoapsis
5. Circularize at apoapsis
6. Achievement: First orbit!

### Tutorial 2: Orbit Change
1. Start in 150 km circular orbit
2. At any point: Burn prograde for 5 seconds
3. Watch apoapsis rise
4. Coast to new apoapsis
5. Burn prograde to circularize
6. Now in higher orbit

### Tutorial 3: Deorbit
1. Start in circular orbit
2. Burn retrograde for 10 seconds
3. Periapsis drops below 70 km (into atmosphere)
4. Coast to periapsis
5. Atmospheric drag slows you
6. Heat effects begin
7. Deploy parachute at low altitude
8. Land safely

### Tutorial 4: Rendezvous
1. Launch into same orbital plane as target
2. Get into similar orbit (within 10 km altitude)
3. Adjust to catch up
4. Close to < 1 km
5. Kill relative velocity
6. Practice station keeping

### Tutorial 5: Docking
1. Complete rendezvous to < 100 m
2. Orient docking ports
3. Approach at 0.1 m/s
4. Maintain alignment
5. Contact and dock
6. Celebrate!

---

## Advanced Topics

### Orbital Resonance
Match orbital period for regular encounters:
- 2:1 resonance: Your period is half theirs
- 3:2 resonance: Your period is 2/3 theirs
- Used for satellite constellations

### Lagrange Points
Special stable points in multi-body systems:
- L1: Between Earth and Moon
- L2: Beyond Moon from Earth
- L3: Opposite Earth around Sun
- L4/L5: 60° ahead/behind in orbit
- Useful for station placement

### Low Energy Transfers
Exploit multi-body gravity:
- Much slower than Hohmann
- Uses much less fuel
- Takes years instead of months
- Good for cargo, not crew

---

## Conclusion

Orbital mechanics in Astro Engineer aims to balance realism with accessibility. The core physics is based on real orbital mechanics, but with quality-of-life features like auto-pilot assists, maneuver planning, and clear visual feedback.

Mastering orbital flight is challenging but immensely rewarding. Start with simple circular orbits, practice maneuvers in safe situations, and gradually work up to complex rendezvous and interplanetary missions.

Remember: In space, there is no up or down, only directions relative to your velocity. Think in terms of orbits, not altitudes, and you'll start to think like a real astronaut.

For related documentation:
- **GAME_PROGRESSION_GUIDE.md** - When to learn each skill
- **SPACE_STATION_GUIDE.md** - Building and docking with stations
- **SHIP_PROGRESSION_GUIDE.md** - Ships for different mission types

**Last Updated**: 2026-01-08  
**Maintained By**: Astro Engineer Development Team
