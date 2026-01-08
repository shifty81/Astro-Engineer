# Ship Progression Guide

## Overview

This guide details the complete ship progression system in Astro Engineer, from your first simple rocket to massive capital ships capable of traversing the galaxy. Learn about ship classes, upgrade paths, and how to design vessels for specific mission types.

---

## Table of Contents
1. [Ship Design Philosophy](#ship-design-philosophy)
2. [Early Ships (Ground to Orbit)](#early-ships-ground-to-orbit)
3. [Orbital Ships](#orbital-ships)
4. [Interplanetary Ships](#interplanetary-ships)
5. [Interstellar Ships](#interstellar-ships)
6. [Specialized Ship Classes](#specialized-ship-classes)
7. [Ship Modification System](#ship-modification-system)
8. [Design Principles](#design-principles)

---

## Ship Design Philosophy

### Modular Construction

Every ship is built from discrete modules:
- **Core modules** (cockpit, habitat) - required for operation
- **Propulsion** (engines, RCS) - movement capability
- **Power** (reactors, batteries, solar) - energy systems
- **Utility** (cargo, weapons, sensors) - mission-specific
- **Structure** (hull sections, connectors) - framework

### Mission-Specific Design

No single ship is best for everything:
- **Launch vehicles**: Optimized for gravity and atmosphere
- **Orbital tugs**: Fine control, low thrust
- **Explorers**: Long-range, efficient, research-equipped
- **Haulers**: Massive cargo, slow, heavily armored
- **Fighters**: Fast, maneuverable, weapons-focused

### Upgrade Paths

Ships evolve through:
1. **Module replacement**: Swap old for new modules
2. **Module addition**: Add new capabilities
3. **Refitting**: Complete redesign using existing modules
4. **Salvaging**: Reclaim modules from old ships

---

## Early Ships (Ground to Orbit)

### Starter I - "First Flight"

**Role**: Minimal orbital insertion  
**Flight Regime**: Surface to low orbit (200 km)  
**Crew**: 1  
**Mission Duration**: 2 hours  

#### Module Configuration
```
      [Cockpit]
         |
    [Small Tank]
         |
    [Small Engine]
```

**Modules**:
1. **Basic Cockpit Pod**: 1-crew, 2-hour life support
2. **Small Fuel Tank**: 1,000 units
3. **Chemical Rocket Mk1**: 150 kN thrust
4. **Basic RCS**: 8 thrusters, 1 kN each
5. **Battery Pack**: 50 kWh

**Performance**:
- Mass: 2,150 kg (fueled)
- Delta-V: 3,500 m/s
- TWR: 0.7 (can't launch alone)
- Cost: 715 components

**Limitations**:
- ❌ Cannot reach orbit from surface (insufficient delta-V)
- ❌ Single-stage design
- ❌ No docking port
- ❌ Minimal life support
- ❌ No cargo capacity

**Use Cases**:
- ✓ Suborbital test flights
- ✓ Practice flight controls
- ✓ EVA training (in orbit if delivered)
- ✓ Learning ship assembly system

### Starter II - "Orbital Capable"

**Role**: Single-launch to orbit  
**Flight Regime**: Surface to low orbit  
**Crew**: 1  
**Mission Duration**: 8 hours  

#### Module Configuration
```
      [Cockpit]
         |
     [Solar Panel]
         |
   [Medium Tank]
         |
   [Medium Engine]
         |
   [Large Tank] ← Second stage
         |
   [Large Engine] ← First stage
```

**Modules**:
1. **Basic Cockpit Pod**: Reused from Starter I
2. **Medium Fuel Tank**: 2,500 units (2nd stage)
3. **Chemical Rocket Mk2**: 300 kN (2nd stage)
4. **Large Fuel Tank**: 5,000 units (1st stage)
5. **Chemical Rocket Mk3**: 600 kN (1st stage)
6. **Solar Panel**: 10 kW generation
7. **RCS Mk2**: Better control
8. **Docking Port**: Standard type

**Performance**:
- Mass: 8,700 kg (fueled)
- Delta-V: 9,800 m/s (total, both stages)
- Stage 1: 5,200 m/s (surface to 50km)
- Stage 2: 4,600 m/s (50km to orbit)
- TWR: 1.4 (can launch)
- Cost: 1,850 components

**Staging Sequence**:
1. **Stage 1 ignition**: Both engines fire
2. **Stage 1 burnout**: At 50km altitude
3. **Stage 1 separation**: Drop first stage
4. **Stage 2 ignition**: Immediately after separation
5. **Stage 2 burnout**: In orbit at 200km
6. **Solar panels deploy**: For extended mission

**Capabilities**:
- ✓ Reach orbit from surface alone
- ✓ 8-hour endurance (solar power)
- ✓ Can dock with stations
- ✓ Reusable second stage
- ✓ Basic EVA operations

**Limitations**:
- ❌ First stage discarded (expensive)
- ❌ No cargo beyond crew
- ❌ Limited maneuverability in orbit
- ❌ Can't reach high orbit efficiently

**Use Cases**:
- ✓ Regular crew rotation to station
- ✓ Emergency rescue missions
- ✓ Station construction (deliver yourself)
- ✓ Orbital practice and training

### Heavy Lifter - "Mule"

**Role**: Cargo delivery to orbit  
**Flight Regime**: Surface to low/medium orbit  
**Crew**: 0 (automated) or 2  
**Payload**: 5,000 kg  

#### Module Configuration
```
   [Station Module] ← Payload
         |
    [Cargo Clamp]
         |
   [Small Engine]
         |
   [Medium Tank] ← Second stage
         |
   [Huge Tank]
         |
   [Huge Tank]
         |
   [Huge Engine] ← First stage
         |
   [Huge Engine]
```

**Specifications**:
- 6x Large Fuel Tanks
- 2x Large Engines (first stage)
- 1x Medium Engine (second stage)
- Cargo clamp system
- Optional crew pod (for manned missions)
- Automated guidance (for unmanned)

**Performance**:
- Mass: 25,000 kg (with payload)
- Delta-V: 11,000 m/s
- Payload capacity: 5,000 kg to 250km orbit
- TWR: 1.6
- Cost: 4,500 components

**Capabilities**:
- ✓ Deliver station modules
- ✓ Cargo containers
- ✓ Fuel tanker missions
- ✓ Deploy satellites
- ✓ Fully automated or manual flight

**Use Cases**:
- Station construction (primary use)
- Bulk resource delivery
- Large equipment transport
- Heavy machinery orbital insertion

---

## Orbital Ships

### Orbital Tug - "Pusher"

**Role**: Station maintenance and module positioning  
**Flight Regime**: Orbital operations only  
**Crew**: 1  
**Mission Duration**: 24 hours  

#### Module Configuration
```
   [Cockpit]
      |
  [Solar Panel]
      |
 [Small Battery]
      |
  [RCS Cluster] × 4
      |
  [Grappling Arm]
      |
  [Docking Port]
```

**Key Features**:
- **High RCS thrust**: 20 kN total (very precise)
- **Grappling arm**: Grab and move modules
- **360° thrusters**: Perfect maneuvering
- **No main engine**: RCS only (this is intentional)
- **Solar powered**: Unlimited endurance

**Performance**:
- Mass: 800 kg
- Delta-V: 2,000 m/s (RCS only)
- Acceleration: 0.25 m/s² (slow and steady)
- Cargo capacity: 10,000 kg (grappled)

**Use Cases**:
- ✓ Position station modules during construction
- ✓ Retrieve free-floating objects
- ✓ Fine orbital adjustments
- ✓ Docking practice trainer
- ✓ Emergency rescue (slow but reliable)

**Limitations**:
- ❌ Cannot enter atmosphere
- ❌ Very slow (patience required)
- ❌ No long-range capability
- ❌ Vulnerable (no armor, weapons)

### Shuttle - "Workhorse"

**Role**: Crew/cargo transfer, reusable  
**Flight Regime**: Ground to orbit, orbital operations  
**Crew**: 6  
**Payload**: 2,000 kg  

#### Module Configuration
```
   [Advanced Cockpit]
          |
     [Cargo Bay]
          |
    [Fuel Tank] ← Orbiter
          |
  [Aerodynamic Hull]
          |
     [Heat Shield]
  _____|_____
 |           |
[Tank] [Tank] ← External tanks (jettisoned)
 |_____|_____|
      |
 [Large Engine]
```

**Design Philosophy**:
Reusable orbital spaceplane:
- **Launch**: Vertical with external tanks
- **Orbit**: Drop tanks, operate on internal fuel
- **Return**: Glide through atmosphere
- **Landing**: Runway landing
- **Refuel**: Use again

**Performance**:
- Mass: 12,000 kg (dry), 35,000 kg (fueled with externals)
- Delta-V: 10,500 m/s (with external tanks)
- Cargo: 2,000 kg or 6 passengers
- Reusability: 100+ flights

**Modules**:
1. **Advanced Cockpit**: 2 pilots + 4 passengers
2. **Cargo Bay**: 20 slots, 2,000 kg capacity
3. **Aerodynamic Hull**: Wings for atmospheric flight
4. **Heat Shield**: Protects during reentry
5. **Internal Tank**: 1,500 units (orbital maneuvering)
6. **2× External Tanks**: 3,000 units each (launch only)
7. **Large Engine**: 400 kN thrust

**Staging**:
1. Launch with external tanks
2. At 60km: Jettison empty external tanks
3. Continue to orbit on internal fuel
4. In orbit: Use internal fuel sparingly
5. Deorbit: Small retrograde burn
6. Reentry: Heat shield protects
7. Glide: Use wings to control descent
8. Landing: Touch down on runway

**Capabilities**:
- ✓ Completely reusable (no discarded parts except tanks)
- ✓ Crew ferry to stations
- ✓ Cargo delivery
- ✓ Satellite deployment from cargo bay
- ✓ Station module delivery (small modules)
- ✓ Atmospheric flight capability

**Economics**:
- Launch cost: ~500 components (fuel + external tanks)
- Recovery value: ~3,000 components (ship itself)
- Cost per launch: ~500 (tanks + fuel only)
- Compared to: Starter II disposable at 1,850 per launch

---

## Interplanetary Ships

### Pioneer Class Explorer - "Voyager"

**Role**: Long-range exploration and research  
**Flight Regime**: Solar system exploration  
**Crew**: 2  
**Mission Duration**: Months to years  

#### Module Configuration
```
     [Sensors]
         |
  [Advanced Cockpit]
         |
    [Habitat] ← Living space
         |
   [Laboratory] ← Research
         |
    [Cargo Bay]
         |
  [Nuclear Reactor] ← Power
         |
  [Heat Radiators]
         |
   [Xenon Tank] × 3
         |
   [Ion Engine] × 4
         |
  [Docking Port]
```

**Key Technologies**:
- **Ion propulsion**: Extremely efficient (high ISP)
- **Nuclear power**: 500 kW continuous
- **Closed-loop life support**: No resupply needed
- **Scientific instruments**: Research while traveling
- **Long-duration habitat**: Comfortable for crew

**Performance**:
- Mass: 8,000 kg
- Delta-V: 25,000 m/s (ion drive)
- Acceleration: 0.5 m/s² (slow but efficient)
- Fuel: 15,000 units Xenon
- Power: 500 kW reactor

**Modules**:
1. **Advanced Cockpit**: Navigation, control, 2 crew
2. **Habitat Module**: Bunks, galley, hygiene, exercise
3. **Laboratory**: Microgravity experiments, sample analysis
4. **Cargo Bay**: 100 slots for samples and supplies
5. **Nuclear Reactor**: 500 kW, 20 year fuel lifetime
6. **Heat Radiators**: Reject waste heat (essential)
7. **3× Large Xenon Tanks**: 5,000 units each
8. **4× Ion Engines**: 50 kN each, extremely efficient
9. **Communication Array**: Long-range to Earth
10. **Sensor Suite**: Detect planets, asteroids, anomalies

**Mission Profile Example: Earth to Mars**
1. **Launch**: Via heavy lifter to orbit (ship assembled there)
2. **Departure burn**: 3-day continuous ion burn
3. **Coast phase**: 2-3 months ballistic trajectory
4. **Mid-course correction**: Small burns as needed
5. **Arrival burn**: 5-day continuous braking
6. **Mars orbit insertion**: Circular orbit at 500 km
7. **Research phase**: Months in orbit, study Mars
8. **Return**: When crew ready or window opens

**Capabilities**:
- ✓ Reach any planet in solar system
- ✓ Self-sufficient for years
- ✓ Conduct research en route
- ✓ Carry samples back
- ✓ Two crew (companionship)
- ✓ Comfortable long-duration

**Limitations**:
- ❌ Slow acceleration (days to build up speed)
- ❌ Cannot land on planets (orbit only)
- ❌ Expensive (5,000+ components)
- ❌ Requires nuclear tech (high tier research)

**Variants**:
- **Scout**: Smaller, 1 crew, faster, less cargo
- **Heavy**: Larger, 4 crew, more labs, slower
- **Cargo**: Replace lab with huge cargo bay

### Prospector Class Miner - "Gold Rush"

**Role**: Asteroid mining operations  
**Flight Regime**: Asteroid belt  
**Crew**: 3  
**Cargo**: 500 slots (huge)  

#### Module Configuration
```
    [Cockpit]
        |
    [Habitat]
        |
  [Refinery] ← Process ore in space
        |
  [Huge Cargo] × 3
        |
  [Mining Laser]
        |
   [Ore Collector]
        |
   [Ion Engine]
        |
  [Fuel Tanks] × 2
```

**Purpose**: Mine asteroids, process ore, return materials

**Performance**:
- Mass: 12,000 kg (empty)
- Cargo: 500 slots (can carry 50,000 kg ore)
- Delta-V: 15,000 m/s
- Mining rate: 100 kg/hour

**Operations**:
1. Travel to asteroid belt (200 million km)
2. Scan asteroids for valuable materials
3. Match orbit with target asteroid
4. Deploy mining laser
5. Extract ore into cargo holds
6. Refine ore to reduce mass
7. Fill cargo holds
8. Return to station or Earth
9. Sell/use refined materials

**Economics**:
- Trip duration: 6 months out, 6 months back
- Cargo value: 100,000+ credits (high-value ore)
- Operating cost: 10,000 credits (fuel, supplies)
- Profit: 90,000+ credits per trip
- ROI: ~10 trips to pay for ship

---

## Interstellar Ships

### Jump-Capable Ships

All FTL ships require:
- **Jump Drive Core**: Folds space-time
- **Exotic Matter Fuel**: Extremely expensive, rare
- **Massive Power**: 5+ MW for jump
- **Navigation Computer**: Plot courses through stars

### Starfarer Class Capital Ship - "Enterprise"

**Role**: Long-range exploration, mobile base  
**Flight Regime**: Interstellar travel  
**Crew**: 20-50  
**Mission Duration**: Years  

#### Module Configuration
```
         [Bridge]
             |
      [Habitat Ring] ← Rotating for gravity
             |
    [Science Complex]
             |
   [Manufacturing Bay]
             |
    [Cargo Bays] × 4
             |
   [Jump Drive Core] ← FTL capability
             |
   [Fusion Reactor] × 3
             |
    [Fuel Tanks] × 10
             |
   [Ion Engines] × 8
        _____|_____
       |           |
  [Docking] × 5 [Docking] × 5
```

**Scale**:
- Length: 200 meters
- Mass: 100,000 kg
- Crew: 20 minimum, 50 maximum
- Build time: 40 hours (real-time)
- Cost: 50,000+ components

**Key Systems**:

**1. Jump Drive**
- Range: 50 light-years per jump
- Cooldown: 10 minutes
- Fuel: 1,000 units exotic matter per jump
- Accuracy: ±0.1 light-years

**2. Habitation**
- Rotating ring: 1G artificial gravity
- 50 crew quarters
- Common areas: dining, recreation, gym
- Hydroponics: Grow food
- Medical bay: Emergency care

**3. Science**
- Multiple laboratories
- Observation deck
- Data processing center
- Sample analysis
- Xenobiology suite (if alien life found)

**4. Manufacturing**
- Build smaller ships
- Repair damaged modules
- Produce consumables
- Refine resources
- Self-sufficient for years

**5. Power**
- 3× Fusion reactors: 2 MW each
- Total: 6 MW continuous
- Batteries: 1000 kWh storage
- Emergency backup: RTG

**6. Propulsion**
- Conventional: 8× Ion engines (interplanetary)
- FTL: Jump drive (interstellar)
- RCS: High-power clusters (docking)

**7. Docking**
- 10 fighter bays (small ships)
- 4 shuttle docks (medium ships)
- 2 capital ship docks (large ships)
- 1 cargo transfer port

**Mission Profile: Interstellar Exploration**
1. **Assembly**: Built in orbit over months
2. **Shakedown**: Test all systems in solar system
3. **Crew loading**: 20-50 personnel
4. **Provisioning**: Years of supplies
5. **Jump sequence**: Target star system 50 LY away
6. **Jump**: 10-second FTL transit
7. **Arrival**: New star system
8. **Exploration**: Survey planets, moons
9. **Research**: Study unique phenomena
10. **Sample collection**: Bring back data
11. **Return**: Jump back or continue exploring

**Capabilities**:
- ✓ Explore anywhere in galaxy
- ✓ Self-sufficient for years
- ✓ Build and repair own ships
- ✓ Serve as mobile base
- ✓ Comfortable living (artificial gravity)
- ✓ Carry large crew
- ✓ Fast interstellar travel

**Limitations**:
- ❌ Extremely expensive
- ❌ Exotic matter fuel is rare and costly
- ❌ Cannot land on planets (too large)
- ❌ Slow in-system travel (use carried ships)
- ❌ Requires large crew (expensive to operate)

---

## Specialized Ship Classes

### Fighter Class - "Interceptor"

**Role**: Combat, escort, defense  
**Flight Regime**: Orbital and interplanetary  
**Crew**: 1  

```
  [Cockpit]
      |
 [Weapons] × 2
      |
  [Fuel Tank]
      |
 [High-Thrust Engine]
```

**Performance**:
- Mass: 500 kg
- Delta-V: 5,000 m/s
- Acceleration: 5 m/s² (very agile)
- Weapons: 2 hardpoints
- Cost: 800 components

**Use Cases**:
- Defend stations from pirates (if implemented)
- Escort cargo ships
- Intercept threats
- Racing (competitive)

### Science Vessel - "Darwin"

**Role**: Research and discovery  
**Flight Regime**: Any  
**Crew**: 5 (all scientists)  

```
   [Observatory]
        |
  [Main Lab] × 2
        |
   [Sample Storage]
        |
    [Habitat]
        |
   [Propulsion]
```

**Features**:
- Advanced sensors (detect anomalies)
- Multiple laboratories
- Huge data storage
- Sample collection tools
- Specialized instruments

**Missions**:
- Survey new planets
- Study phenomena (black holes, nebulae)
- Collect samples
- Map star systems
- Search for life

### Freighter - "Heavy Hauler"

**Role**: Bulk cargo transport  
**Flight Regime**: Interplanetary and interstellar  
**Crew**: 3  

```
  [Small Cockpit]
        |
[Huge Cargo] × 10
        |
   [Engines]
```

**Specifications**:
- Cargo: 2,000 slots (massive)
- Mass: 50,000 kg (loaded)
- Speed: Slow (0.1 m/s² acceleration)
- Armor: Heavy (protect cargo)
- Cost: Low per ton/km

**Use Cases**:
- Transport materials between systems
- Deliver station supplies
- Move colonists (in passenger variant)
- Commercial trading

---

## Ship Modification System

### Modification Interface

**Access**: At station Manufacturing Bay

**Process**:
1. Dock ship to station
2. Open modification interface
3. Select ship in dock
4. View current modules
5. Add/remove/replace modules
6. Validate new configuration
7. Apply changes (takes time)
8. Undock modified ship

### Module Swapping

**Replacing Modules**:
1. Select module to replace
2. Choose replacement from inventory
3. System checks compatibility
4. Old module returned to storage
5. New module installed
6. Power and connections updated

**Cost**:
- Time: 10 minutes per module
- Materials: None (just swapping)
- Requires: Module in storage

**Example: Upgrade Engine**
```
Before: Chemical Rocket Mk1 (150 kN)
After:  Chemical Rocket Mk2 (300 kN)

Result: Ship now has 2× thrust
Effect: Faster acceleration, shorter burns
Trade-off: Higher fuel consumption
```

### Adding Modules

**Process**:
1. Ship must have available hardpoint
2. Select module to add
3. Choose attachment point
4. Module installed
5. Systems integrated

**Limitations**:
- Must have hardpoint/port available
- Mass increases (affects performance)
- Power consumption may increase
- Center of mass may shift

**Example: Add Docking Port**
```
Before: Starter I (no docking)
Add: Standard Docking Port

Result: Can now dock with stations
Cost: 50 components + 30 minutes
```

### Refitting

**Complete Redesign**:
1. Disassemble entire ship
2. All modules returned to storage
3. Redesign from scratch
4. Use same modules in new configuration
5. Reassemble

**When to Refit**:
- Ship no longer suits mission
- Better design discovered
- Technology unlocks enable improvements
- Salvaging damaged ship

**Example: Starter II to Orbital Tug**
```
Disassemble Starter II:
- 1 Cockpit (keep)
- 2 Fuel tanks (store)
- 2 Engines (store)
- 1 Solar panel (keep)

Reassemble as Tug:
- Cockpit (reuse)
- Solar panel (reuse)
- Remove large tanks (don't need)
- Remove engines (using RCS instead)
- Add: 4× RCS clusters (from storage)
- Add: Grappling arm (new)

Result: New ship role without buying everything
```

---

## Design Principles

### Mass Budget

**Everything has mass**:
- Each module: Fixed mass
- Fuel: Variable mass
- Cargo: Variable mass
- **Total mass** = Dry mass + Fuel mass + Cargo mass

**Effect on Performance**:
```
Acceleration = Thrust / Mass
```

Lower mass = better acceleration, less fuel needed

**Optimization**:
- Use lightest modules that meet requirements
- Don't over-build (unnecessary modules add mass)
- Titanium modules lighter than steel (but expensive)
- Advanced components lighter and more efficient

### Delta-V Planning

**Tsiolkovsky Rocket Equation**:
```
ΔV = Isp × g × ln(m_full / m_empty)

Where:
Isp = Specific impulse (engine efficiency)
g = 9.81 m/s²
m_full = Mass with full fuel
m_empty = Mass with empty fuel
ln = Natural logarithm
```

**Mission Delta-V Requirements**:
- Surface to orbit: ~9,400 m/s
- Orbit to Moon: ~5,900 m/s
- Orbit to Mars: ~5,700 m/s
- Orbit to Jupiter: ~15,000 m/s
- Interplanetary: 10,000 - 30,000 m/s

**Rule of Thumb**: Add 20% margin for course corrections

### Power Budget

**Generation vs Consumption**:
```
Power Available = Generation - Consumption
```

**If negative**:
- Systems shut down (priority order)
- Can't recharge batteries
- Eventually: Life support fails

**Solutions**:
- Add more generators (solar, reactor)
- Remove high-draw modules
- Upgrade to efficient modules
- Use batteries as buffer

### Center of Mass

**Importance**: Rotation and stability

**Rules**:
- Engine thrust should align with center of mass
- Misalignment = ship spins uncontrollably
- Symmetrical designs easier to fly
- Test with full and empty fuel (CoM shifts)

**Tool**: Center of mass indicator in Assembly UI

### Redundancy

**Critical Systems**: Have backups
- Life support: Primary + Emergency
- Power: Multiple generators
- Propulsion: Main engine + RCS
- Communication: Multiple antennas

**Single Point of Failure**: Dangerous
- If only one reactor: Power loss = death
- If only one oxygen system: Failure = suffocation

**Best Practice**: 
- 2× capacity for critical systems
- Can survive one failure

---

## Conclusion

Ship design in Astro Engineer rewards creativity, planning, and understanding of physics. From your first tentative orbital insertion to commanding a capital ship exploring distant galaxies, each vessel represents countless hours of work and represents your progression as a space engineer.

**Key Takeaways**:
- Start simple and upgrade gradually
- Design ships for specific missions
- Understand mass, delta-V, and power budgets
- Test designs before committing
- Refit old ships for new roles
- Build redundancy into critical systems

Your ships are your lifeline in the hostile environment of space. Treat them well, maintain them properly, and they'll carry you to the stars.

For related documentation:
- **GAME_PROGRESSION_GUIDE.md** - When to build each ship class
- **ORBITAL_MECHANICS_GUIDE.md** - Flying your ships
- **SPACE_STATION_GUIDE.md** - Orbital construction and modification

**Last Updated**: 2026-01-08  
**Maintained By**: Astro Engineer Development Team
