# Space Station Construction Guide

## Overview

This guide provides comprehensive instructions for building and managing orbital space stations in Astro Engineer. Learn how to perform EVA operations, place modules in zero gravity, and create functional orbital bases that serve as homes, research facilities, and shipyards in space.

---

## Table of Contents
1. [Station Basics](#station-basics)
2. [EVA Operations](#eva-operations)
3. [Module Types](#module-types)
4. [Construction Process](#construction-process)
5. [Station Management](#station-management)
6. [Advanced Stations](#advanced-stations)
7. [Implementation Details](#implementation-details)

---

## Station Basics

### Why Build a Station?

**Benefits of orbital stations**:
- **Permanent presence** in space (no return trips needed)
- **Research** in microgravity (faster, unique technologies)
- **Ship construction** without fighting gravity
- **Refueling** depot for interplanetary missions
- **Living space** for crew during long missions
- **Zero-G manufacturing** (higher quality components)
- **Staging point** for exploration

### Station Design Philosophy

#### Modular Architecture
Stations are built from discrete modules:
- Each module = self-contained unit
- Modules connect via docking ports
- Expandable in any direction
- No size limits (performance permitting)

#### Core-Based Growth
1. **Start**: Launch core module
2. **Expand**: Add modules one at a time
3. **Branch**: Create wings and sections
4. **Integrate**: Connect power, data, life support

#### Functional Zones
Organize by purpose:
- **Habitation**: Living quarters, recreation
- **Operations**: Command, docking, airlocks
- **Science**: Laboratories, observation
- **Industry**: Manufacturing, storage, refineries
- **Power**: Solar arrays, reactors
- **Utilities**: Life support, thermal control

---

## EVA Operations

### EVA Suit System

#### Suit Components

**Life Support**:
- Oxygen supply: 30 minutes (starter), 2 hours (advanced)
- CO2 scrubber: Removes exhaled carbon dioxide
- Temperature regulation: -100°C to +100°C protection
- Pressure suit: 0.3 atm internal pressure

**Propulsion**:
- RCS thrusters: 8 thrusters (6-DOF movement)
- Propellant: Compressed nitrogen or monopropellant
- Delta-V: 50 m/s (starter), 200 m/s (advanced)
- Thrust: 20 N per thruster (gentle acceleration)

**Tools**:
- Welding gun: Attach and construct modules
- Cutting tool: Remove modules or salvage
- Inspection scanner: Diagnose problems
- Helmet light: Illuminate dark areas

**HUD Display**:
- Oxygen percentage and time remaining
- Propellant gauge and delta-V remaining
- Distance from ship/station
- Velocity relative to station
- Tether status (attached/detached)
- Tool selection and mode

#### EVA Suit Upgrades

**Level 1 - Basic** (Starting):
- Oxygen: 30 minutes
- Delta-V: 50 m/s
- Tool: Welding gun only
- No tether

**Level 2 - Advanced** (Unlocked after first station):
- Oxygen: 2 hours
- Delta-V: 200 m/s
- Tools: All tools available
- Tether system included
- Improved temperature protection

**Level 3 - Engineer** (End-game):
- Oxygen: 8 hours (recycling)
- Delta-V: 500 m/s
- Tools: Plus powered tools (faster work)
- Magnetic boots (walk on hull)
- Emergency beacon (rescue if lost)
- Radiation shielding

### Entering EVA

**From Ship**:
1. Dock ship to station (if available) or park nearby
2. Enter cockpit if not already inside
3. Access suit locker (E key on suit icon)
4. Don EVA suit (3 second animation)
5. Depressurize cabin:
   - Hold X to vent atmosphere
   - Wait 5 seconds for full depressurization
   - Warning sounds and lights
6. Open hatch (E key)
7. Exit to space (E key again)
8. You're now in EVA mode!

**From Station Airlock**:
1. Enter airlock chamber
2. Close inner door
3. Don EVA suit
4. Depressurize airlock (automatic)
5. Open outer door
6. Exit to space

### EVA Controls

#### Movement (Keyboard + Mouse)

**Translation** (moving without rotating):
- **W**: Forward (direction you're facing)
- **S**: Backward
- **A**: Left
- **D**: Right
- **Space**: Up (relative to station)
- **Ctrl**: Down
- **Shift**: Boost (2x speed, uses more propellant)

**Rotation**:
- **Mouse**: Free-look (doesn't rotate body)
- **Right-click + mouse**: Rotate body
- **Q/E**: Roll left/right
- **Middle mouse**: Reset orientation to station "up"

**Speed Control**:
- **Scroll wheel**: Adjust max speed (0.5, 1, 2, 5, 10 m/s)
- **X**: Emergency stop (burns all RCS in all directions)

#### HUD Information

**Top Left**:
```
OXYGEN:  [||||||||||||        ] 78%  23:24
RCS:     [||||||              ] 45%   89 m/s
TOOLS:   [WELD] CUT  SCAN
```

**Top Right**:
```
DISTANCE: 24.7m
VELOCITY: 0.3 m/s
TARGET:   Station Core
TETHER:   Disconnected
```

**Center** (when near attachable surface):
```
[E] ATTACH MODULE
Grid position: [2, 4, 1]
Port type: Standard
```

### EVA Safety

#### Critical Rules

1. **Never let go without RCS fuel**
   - Always keep 20%+ propellant reserve
   - Return to ship/station before running low
   - Refuel from station tanks

2. **Monitor oxygen constantly**
   - Warning at 10 minutes remaining
   - Critical alert at 5 minutes
   - Must return before depletion

3. **Use tethers when possible**
   - Attach tether before working
   - Tether has 100m length
   - Auto-retracts in emergency
   - Prevents drifting away

4. **Avoid excessive speed**
   - Collision damage above 1 m/s
   - Hard surfaces can kill at 5 m/s
   - Use slow approach speeds

5. **Watch your distance**
   - Stay within 100m of safe haven
   - Easy to get disoriented
   - Farther = harder to return

#### Emergency Procedures

**Lost in Space**:
1. Don't panic (burning RCS randomly makes it worse)
2. Orient to face station (look for it)
3. Point directly at station
4. Gentle thrust toward station (0.5 m/s)
5. If no station visible: Activate emergency beacon
6. Rescue beacon: Alerts all ships, gives location

**Low Oxygen**:
1. Abort current task immediately
2. Return to nearest airlock/ship
3. Use fastest safe speed (5 m/s)
4. Emergency procedure: 
   - Tether pulls you back automatically
   - Or: Rescue capsule launches to retrieve you

**Low RCS Fuel**:
1. Stop all movement
2. Coast to station if already moving toward it
3. Call rescue if stranded
4. Use tether to pull self back

**Collision**:
- Spinning uncontrollably: Use RCS to counter-spin
- Damaged suit: Red health bar, oxygen leaks faster
- Find airlock ASAP
- Med-kit in airlock for repairs

### EVA Best Practices

✓ **Checklist before every EVA**:
- [ ] Oxygen: 100%
- [ ] RCS propellant: 100%
- [ ] Tools equipped
- [ ] Tether attached (if station has one)
- [ ] Buddy system (if multiplayer)
- [ ] Know location of nearest airlock

✓ **Work methodically**:
- One module at a time
- Test placement before committing
- Don't rush
- Save often (auto-save every 5 minutes)

✓ **Practice in safe conditions first**:
- Park ship near station
- Practice translation and rotation
- Get comfortable with controls
- Try emergency stop procedure

---

## Module Types

### Station Core Module

**Always the first module launched**

#### Specifications
- **Size**: 10m length, 4m diameter
- **Mass**: 5,000 kg
- **Docking Ports**: 4 (front, back, top, bottom)
- **Power**: 50 kW (solar panels)
- **Crew Capacity**: 2
- **Storage**: 100 slots
- **Life Support**: Oxygen recycling for 2 crew

#### Features
- Command center (station control interface)
- Basic laboratory (1x research speed)
- Small habitation (bunks for 2)
- Airlock (EVA access)
- Communication array (ground contact)
- Automated systems (runs without crew)

#### Launch Requirements
- Heavy rocket (10,000 kg payload)
- Automated guidance system
- Fuel for orbital insertion
- Deployment mechanism

#### Cost
- 500 Steel Plates
- 300 Aluminum Plates
- 200 Titanium Plates
- 100 Advanced Circuit Boards
- 50 Computer Systems
- 20 Life Support Units
- Build time: 8 hours (real-time)

### Habitation Module

**Crew living quarters**

#### Specifications
- **Size**: 8m length, 3m diameter
- **Mass**: 2,000 kg
- **Docking Ports**: 2 (front, back)
- **Power Consumption**: 5 kW
- **Crew Capacity**: +4 (total)
- **Features**:
  - 4 sleeping pods
  - Kitchen/dining area
  - Bathroom/hygiene
  - Recreation space
  - Storage lockers (personal)

#### Variants
- **Basic**: 4 crew, minimal comfort
- **Standard**: 4 crew, comfortable, entertainment
- **Luxury**: 2 crew, private quarters, exercise equipment

### Laboratory Module

**Scientific research**

#### Specifications
- **Size**: 10m length, 4m diameter
- **Mass**: 3,000 kg
- **Docking Ports**: 2 (front, back)
- **Power Consumption**: 20 kW
- **Features**:
  - Microgravity experiments
  - Sample analysis
  - Computer systems
  - Data storage
  - Observation windows

#### Research Benefits
- **Research speed**: 2x faster than ground
- **Unlocks**: Space-only technologies
- **Science points**: Generates passively
- **Experiments**: Unique microgravity science

#### Variants
- **General Lab**: All-purpose research
- **Biology Lab**: Life science, hydroponics research
- **Materials Lab**: Metallurgy, crystal growth
- **Astronomy Lab**: Telescopes, sensors

### Docking Hub

**Traffic control for busy stations**

#### Specifications
- **Size**: 5m diameter sphere
- **Mass**: 1,500 kg
- **Docking Ports**: 6 (all directions: +X, -X, +Y, -Y, +Z, -Z)
- **Power Consumption**: 2 kW
- **Features**:
  - Automatic docking guidance
  - Collision avoidance
  - Traffic management
  - Interior passage (crew can pass through)

#### Benefits
- Allows multi-armed station designs
- Organize station by function
- Multiple ships can dock simultaneously
- Central hub architecture

### Solar Array

**Primary power generation**

#### Specifications
- **Size**: 20m wingspan, 1m thick
- **Mass**: 500 kg
- **Docking Ports**: 1 (center)
- **Power Generation**: 200 kW
- **Features**:
  - Tracks sun automatically
  - Folds for launch
  - Auto-deploys in orbit
  - Rotates on gimbal

#### Placement Tips
- Deploy away from traffic areas
- Point perpendicular to station main axis
- Use multiple arrays for redundancy
- Balance on opposite sides (torque)

#### Variants
- **Small Array**: 50 kW, compact
- **Standard Array**: 200 kW (most common)
- **Large Array**: 500 kW, huge wingspan
- **Advanced Array**: Thin-film, 300 kW, lighter

### Storage Module

**Cargo and supplies**

#### Specifications
- **Size**: 8m length, 3m diameter
- **Mass**: 1,000 kg
- **Docking Ports**: 2 (front, back)
- **Power Consumption**: 1 kW
- **Storage Capacity**: 200 slots
- **Features**:
  - Inventory management
  - Liquid tanks (fuel, water, oxygen)
  - Temperature control (frozen storage)
  - Automated sorting

#### Use Cases
- Food and supplies for crew
- Spare parts for repairs
- Scientific samples
- Manufacturing materials
- Fuel depot for visiting ships

### Manufacturing Bay

**Orbital factory**

#### Specifications
- **Size**: 15m length, 6m diameter
- **Mass**: 8,000 kg
- **Docking Ports**: 3 (front, back, cargo door)
- **Power Consumption**: 50 kW
- **Features**:
  - Smelter (ore processing)
  - Assembler (component crafting)
  - Refinery (chemical processing)
  - Fabricator (3D printing in zero-G)
  - Cargo manipulator (move large items)

#### Capabilities
- Build ship modules in orbit
- No gravity = easier to build large structures
- Process resources from asteroids
- Self-sufficient station (with raw materials)
- 3x crafting speed vs ground

#### Requirements
- High power (50 kW continuous)
- Raw material deliveries
- Crew to operate (or automation)
- Large size (need space to attach)

### Command Module

**Station management and control**

#### Specifications
- **Size**: 6m length, 4m diameter
- **Mass**: 2,500 kg
- **Docking Ports**: 1 (back)
- **Power Consumption**: 15 kW
- **Features**:
  - Advanced computers
  - Communication arrays (deep space)
  - Sensor systems
  - Radar and tracking
  - Station-wide monitoring
  - AI management systems

#### Functions
- Monitor all station systems
- Communicate with ground and ships
- Track nearby objects (debris, ships)
- Coordinate docking operations
- Detect system failures
- Remote operation of station

---

## Construction Process

### Pre-Launch Planning

#### Step 1: Design Your Station

**Consider**:
- **Purpose**: Research? Shipyard? Waystation?
- **Crew size**: How many permanent residents?
- **Power needs**: Calculate total consumption
- **Module count**: Start small, expand later
- **Shape**: Linear, hub-and-spoke, ring, cluster?

**Recommended Starter Station "Alpha"**:
```
                 [Solar]
                    |
[Storage] - [Hub] - [Core] - [Lab]
                    |
                 [Hab]
```

**Module count**: 6
**Crew capacity**: 6
**Power**: 250 kW (200 from solar + 50 from core)
**Functions**: Living, research, storage, docking

#### Step 2: Calculate Costs

For each module:
1. List materials required
2. Sum totals
3. Add 20% buffer (for mistakes)
4. Check if you have resources

**Alpha Station Total**:
- Steel: ~1,200 plates
- Aluminum: ~800 plates
- Titanium: ~400 plates
- Circuit Boards: ~300
- Computers: ~100
- Life Support: ~50 units
- **Build time**: ~20 hours total

#### Step 3: Set Up Logistics

**Ground-based**:
- Stockpile all materials
- Build manufacturing capacity
- Set up rocket production
- Fuel reserves for launches

**Orbital** (if you have starter station):
- Use orbital manufacturing
- Mine asteroids for materials
- Less efficient initially
- Better long-term

### Launch Sequence

#### Mission 1: Core Module

**Rocket Requirements**:
- Payload capacity: 5,000 kg
- Delta-V: 9,500 m/s
- Automated guidance
- Orbital insertion system

**Launch Steps**:
1. Assemble core module in Assembly Bay
2. Mount on heavy-lift rocket
3. Pre-flight checks (fuel, power, guidance)
4. Launch to desired orbit (250 km recommended)
5. Core auto-activates systems
6. Core stabilizes and deploys solar panels
7. Core awaits first crew

**Auto-Pilot** (Core has its own computer):
- Launches to specified altitude and inclination
- Circularizes orbit automatically
- Activates power and life support
- Beacon for player to find

#### Mission 2: Your First Visit

**Ship Requirements**:
- Docking port (to connect to core)
- Life support (2+ hours)
- RCS (for fine control)
- Crew capacity: 1 (you)

**Mission Steps**:
1. Launch from ground
2. Reach orbit (match core's orbit)
3. Rendezvous with core (< 100m)
4. Practice docking approach
5. Dock successfully
6. Transfer into core
7. Activate station systems
8. Station is now operational!

**First Tasks in Core**:
- Orient yourself (which way is "up"?)
- Check power levels (solar working?)
- Check life support (oxygen generation?)
- Access station computer (control interface)
- Plan first module addition

### Module Addition

#### Mission 3: First Expansion

**Example: Adding Habitation Module**

##### A. Module Launch (Automated)
1. Build Hab module in Assembly Bay
2. Attach to cargo rocket
3. Launch to station orbit
4. Rocket approaches within 100m of station
5. Rocket releases module (very gentle separation)
6. Module drifts 50-100m from station
7. Beacon activates (you can see it on HUD)

##### B. EVA Retrieval
1. From station core, enter airlock
2. Don EVA suit
3. Exit to space
4. Orient to see floating module (green beacon)
5. RCS translate toward module (3-5 m/s)
6. Approach and slow down (< 1 m/s at contact)
7. "Grab" module (E key when close)
8. You're now pushing the module

##### C. Module Positioning
1. Maneuver module toward desired attachment point
2. Align module port with station port
   - Docking ports must face each other
   - Alignment indicator shows rotation needed
   - Green = aligned, Red = misaligned
3. Slow approach (0.5 m/s)
4. Module "snaps" into alignment at 2m (magnetic guide)
5. Gentle push to final contact
6. Module auto-docks with station

##### D. Connection and Activation
1. Welding gun automatically activates
2. Hold E for 10 seconds (welding animation)
3. Hard dock established
4. Power connection auto-links
5. Data connection established
6. Interior hatches unlock
7. Module now accessible from inside

**Result**: Station now has Core + Hab  
**New capacity**: 6 crew (2 from core + 4 from hab)

### Multi-Module Construction

#### Hub-and-Spoke Design

**Advantages**:
- Organize by function
- Easy to expand
- Central meeting point
- Efficient layout

**Process**:
1. Launch core (already done)
2. Add docking hub to one core port
3. Add modules to hub ports:
   - Solar arrays on sides (balance)
   - Lab on one port
   - Storage on another
   - Hab on another
   - Manufacturing on remaining port
4. Result: Centralized functional station

#### Linear Design

**Advantages**:
- Simple to build
- Easy to navigate
- Good for small stations
- Can add "branches" later

**Process**:
```
[Module 1] - [Core] - [Module 2] - [Module 3] - [Module 4]
```
Just keep adding to ends

#### Ring Design (Advanced)

**Advantages**:
- Can spin for artificial gravity
- Aesthetic
- No "dead ends"
- Crew can loop around

**Challenges**:
- Requires many modules (12+ for decent ring)
- Complex to assemble
- Structural stresses (if spinning)
- Expensive

**Process**:
1. Build hub at center
2. Add modules radially (spokes)
3. Connect outer ends to form ring
4. Requires careful planning and precision

---

## Station Management

### Power Management

#### Power Generation
- **Solar Arrays**: Vary with sun angle (0-100%)
- **Nuclear Reactor**: Constant output, expensive
- **RTG**: Low power, very reliable, long-lasting

#### Power Consumption
Each module consumes power:
- Habitation: 5 kW
- Laboratory: 20 kW
- Manufacturing: 50 kW
- Command: 15 kW
- Storage: 1 kW
- Docking Hub: 2 kW

**Total Station Power** = Generation - Consumption

**If negative**:
- Warning lights
- Non-essential systems shut down
- Eventually: Life support compromised
- Solution: Add more solar panels or reduce usage

#### Power Management Interface

```
STATION POWER OVERVIEW
======================
Generation:  250 kW (Solar x2)
Consumption: 198 kW
Available:    52 kW (21%)

POWER BREAKDOWN:
Core:          10 kW
Hab Module:     5 kW
Laboratory:    20 kW (Priority: High)
Manufacturing: 50 kW (Priority: Low) [CAN REDUCE]
Storage:        1 kW
Docking Hub:    2 kW
Command:       15 kW (Priority: High)
Life Support:  95 kW (Priority: CRITICAL)

[Set Priorities] [Emergency Mode] [Add Solar Panel]
```

**Priority System**:
- **Critical**: Never shut down (life support)
- **High**: Only shut down in emergency (lab, command)
- **Medium**: Can reduce during power shortage
- **Low**: First to shut down (manufacturing)

### Life Support

#### Oxygen System
- **Generation**: Electrolysis (split water into O₂ and H₂)
- **Scrubbing**: Remove CO₂ from air
- **Recycling**: Closed-loop system
- **Storage**: Backup tanks for emergencies

**Oxygen Balance**:
```
Production = Crew × 0.84 kg/day
Leakage = Station Size × 0.01 kg/day
Emergency Reserve = 7 days for full crew
```

**Warning Signs**:
- Yellow alert: Oxygen < 50% normal
- Red alert: Oxygen < 25% normal
- Critical: Evacuate station

#### Temperature Control
- **Heating**: Electrical heaters
- **Cooling**: Radiators (reject heat to space)
- **Balance**: Solar heating vs radiator cooling

**Temperature Range**:
- Optimal: 20°C - 24°C
- Acceptable: 15°C - 28°C
- Warning: < 10°C or > 32°C
- Dangerous: < 5°C or > 40°C

#### Water Recycling
- Reclaim from: Breath vapor, sweat, urine
- Purification: Filters and treatment
- Storage: Tanks in storage modules
- Resupply: Bring water from ground or mine ice asteroids

### Crew Management

#### Crew Needs
- **Oxygen**: Provided by life support
- **Food**: Stored in storage modules, depletes daily
- **Water**: Recycled, but need source
- **Sleep**: Crew need bunks (habitation)
- **Recreation**: Morale system
- **Exercise**: Prevent bone loss in zero-G

#### Crew Schedule
- **Work shift**: 8 hours (operate stations, research, EVA)
- **Personal time**: 8 hours (eat, exercise, recreation)
- **Sleep**: 8 hours

#### Crew Skills
- **Pilot**: Dock ships, fly EVA
- **Engineer**: Repair, construct, maintain
- **Scientist**: Conduct research, experiments
- **Doctor**: Medical care (if injured)

**Cross-training**: Crew can learn multiple skills

#### Rotation
- **Tour length**: 90 days typical
- **Transfer**: Via ship from ground
- **Replacement**: Ensure station always crewed
- **Effects**: Long stays = health issues (future implementation)

### Station Maintenance

#### Regular Checks
- **Power systems**: Check solar array tracking
- **Life support**: Test oxygen generation
- **Structure**: Inspect for damage (micro-meteorites)
- **Docking ports**: Ensure seals intact
- **Communications**: Test ground link

#### Repair System
- **Wear and Tear**: Modules degrade 1% per month
- **Repair**: EVA with repair tool
- **Materials**: Need spare parts (stored in storage module)
- **Failure**: At 0% health, module stops working

**Repair Process**:
1. Identify damaged module (red indicator)
2. EVA to module exterior
3. Equip repair tool
4. Hold E on damaged area (scan shows location)
5. Consume spare parts from inventory
6. Module health restored

#### Emergency Procedures

**Hull Breach**:
1. Automatic bulkheads close (isolate breach)
2. Crew must evacuate affected section
3. Pressure loss in that module
4. EVA repair from outside
5. Re-pressurize after repair

**Power Failure**:
1. Emergency batteries (10 minutes)
2. Shut down non-essential systems
3. Diagnose problem (broken solar array?)
4. Repair or deploy backup power
5. Restore systems gradually

**Life Support Failure**:
1. Immediate alarm
2. Crew dons EVA suits (oxygen supply)
3. Diagnose failure (check console)
4. Repair or switch to backup
5. If can't repair: Evacuate station

---

## Advanced Stations

### Large Stations

**"Mega-Station" (50+ modules)**:
- Multiple docking hubs
- Redundant power systems
- Population: 50+ crew
- Self-sufficient (manufacturing, food production)
- Functions: Shipyard, research, living

**Challenges**:
- Expensive (thousands of components)
- Long build time (100+ hours real-time)
- Complex power management
- High maintenance needs
- Performance (many physics objects)

**Benefits**:
- Can build capital ships
- Generates science and resources passively
- Never need to return to ground
- Base for galaxy exploration

### Specialized Stations

#### Research Station
**Focus**: Scientific advancement
- 5+ Laboratory modules (different types)
- Observatory module (telescopes)
- Minimal crew (10 scientists)
- High power generation (1000+ kW)
- Data transmission to ground

#### Shipyard Station
**Focus**: Ship construction
- 3+ Manufacturing bays
- Large storage (raw materials)
- Docking for ship assembly
- Crew: engineers and workers
- Near asteroid belt (easy resource access)

#### Refueling Depot
**Focus**: Support interplanetary missions
- Massive fuel storage (50,000 units)
- Multiple docking ports (20+)
- Refining modules (process raw fuel)
- Minimal crew (automated)
- High orbit (geosynchronous)

#### Tourist Station
**Focus**: Commercial space tourism (future)
- Luxury habitation modules
- Observation domes (views)
- Recreation facilities
- High comfort, low function
- Generates income

### Spinning Station (Artificial Gravity)

**Concept**: Spin station to create centrifugal "gravity"

#### Physics
```
g_artificial = ω² × r

Where:
ω = angular velocity (radians/second)
r = radius from center (meters)
g = acceleration (m/s²)

For Earth-like gravity (9.8 m/s²):
ω = √(9.8 / r)
```

**Example**:
- Radius: 100m
- ω = √(9.8/100) = 0.313 rad/s = 3 RPM
- Result: 1 G at outer ring

#### Design Requirements
- **Ring structure**: Modules form circle
- **Central hub**: Non-rotating core for docking
- **Spokes**: Connect ring to hub
- **Rotation mechanism**: Gyroscopes or thrusters
- **Transition zone**: Crew move from 0G hub to 1G ring

#### Benefits
- Crew health: No bone loss, normal exercise
- Comfort: Can walk normally
- Long-term habitation: Years in space

#### Challenges
- Expensive (60+ modules minimum)
- Complex construction (precise alignment)
- Coriolis effect (disorientation when moving)
- Docking: Must match rotation or use non-rotating hub

---

## Implementation Details

### Physics Simulation

#### Module Attachment
```cpp
// Pseudocode for module docking
void AttemptModuleDock(Module* moving, Port* targetPort)
{
    // Check alignment
    float angle = DotProduct(moving->dockPort->Forward, targetPort->Forward);
    if (angle < 0.95) return; // Not aligned enough (within ~18°)
    
    // Check distance
    float distance = Distance(moving->dockPort->Location, targetPort->Location);
    if (distance > 5.0f) return; // Too far
    
    // Magnetic guide if within range
    if (distance < 2.0f) {
        // Apply force to align perfectly
        Vector3 alignForce = (targetPort->Location - moving->dockPort->Location) * 10.0f;
        moving->AddForce(alignForce);
        
        // Align rotation
        Quaternion targetRotation = LookRotation(-targetPort->Forward);
        moving->Rotation = Slerp(moving->Rotation, targetRotation, 0.1f);
    }
    
    // Hard dock if close and aligned
    if (distance < 0.1f && angle > 0.99) {
        HardDock(moving, targetPort);
    }
}

void HardDock(Module* module, Port* port)
{
    // Create fixed joint
    PhysicsConstraint constraint = CreateFixedJoint(module, port->Owner);
    
    // Connect power
    ConnectPowerSystem(module, port->Owner);
    
    // Connect data
    ConnectDataBus(module, port->Owner);
    
    // Unlock interior hatches
    port->Hatch->Unlock();
    module->dockPort->Hatch->Unlock();
    
    // Trigger events
    OnModuleAttached.Broadcast(module);
}
```

#### EVA Physics
```cpp
// EVA movement (simplified)
void UpdateEVAAstronaut(float deltaTime)
{
    // Get input
    Vector3 input = GetInputVector(); // WASD + Space + Ctrl
    
    // Apply RCS thrust
    if (input.Length() > 0 && RCSFuel > 0) {
        Vector3 thrustForce = input.Normalized() * ThrustPower;
        Velocity += thrustForce * deltaTime;
        
        // Consume fuel
        RCSFuel -= FuelConsumptionRate * deltaTime;
    }
    
    // Apply drag (very minimal in space)
    Velocity *= (1.0f - DragCoefficient * deltaTime);
    
    // Update position
    Position += Velocity * deltaTime;
    
    // Check distance warning
    float distanceToSafety = Distance(Position, NearestStation);
    if (distanceToSafety > 100.0f) {
        ShowWarning("Far from station!");
    }
    
    // Consume oxygen
    Oxygen -= OxygenConsumptionRate * deltaTime;
    if (Oxygen <= 0) {
        // Player death or rescue
        TriggerEmergency();
    }
}
```

### Station Systems Simulation

#### Power Grid
```cpp
class StationPowerGrid
{
    TArray<PowerGenerator*> Generators;
    TArray<PowerConsumer*> Consumers;
    
    float TotalGeneration = 0;
    float TotalConsumption = 0;
    float StoredEnergy = 0;
    float StorageCapacity = 100; // kWh
    
    void Update(float deltaTime)
    {
        // Calculate generation
        TotalGeneration = 0;
        for (auto gen : Generators) {
            TotalGeneration += gen->GetOutput();
        }
        
        // Calculate consumption
        TotalConsumption = 0;
        for (auto cons : Consumers) {
            if (cons->IsActive()) {
                TotalConsumption += cons->GetDraw();
            }
        }
        
        // Net power
        float netPower = TotalGeneration - TotalConsumption;
        
        // Store excess or drain storage
        StoredEnergy += netPower * (deltaTime / 3600.0f); // Convert to kWh
        StoredEnergy = Clamp(StoredEnergy, 0, StorageCapacity);
        
        // Power failure if not enough
        if (StoredEnergy <= 0 && netPower < 0) {
            TriggerPowerFailure();
        }
    }
    
    void TriggerPowerFailure()
    {
        // Shut down low-priority systems
        for (auto cons : Consumers) {
            if (cons->Priority == Low) {
                cons->PowerOff();
            }
        }
    }
};
```

#### Life Support
```cpp
class LifeSupportSystem
{
    float OxygenLevel = 100.0f; // Percentage
    float CO2Level = 0.0f;
    int CrewCount = 0;
    
    void Update(float deltaTime)
    {
        // Crew consumes oxygen
        float oxygenConsumed = CrewCount * OxygenConsumptionPerPerson * deltaTime;
        OxygenLevel -= oxygenConsumed;
        
        // Crew produces CO2
        CO2Level += oxygenConsumed * 0.8f; // Roughly same mass
        
        // Scrubber removes CO2 and generates O2
        if (ScrubberActive && HasPower) {
            float scrubRate = ScrubberCapacity * deltaTime;
            float removed = Min(CO2Level, scrubRate);
            CO2Level -= removed;
            OxygenLevel += removed; // Recycled
        }
        
        // Natural leakage
        OxygenLevel -= LeakageRate * deltaTime;
        
        // Clamp
        OxygenLevel = Clamp(OxygenLevel, 0, 100);
        CO2Level = Clamp(CO2Level, 0, 100);
        
        // Warnings
        if (OxygenLevel < 50) ShowWarning("Low oxygen");
        if (CO2Level > 30) ShowWarning("High CO2");
        if (OxygenLevel < 10) TriggerEvacuation();
    }
};
```

### UI Components

#### Station Overview Screen
```
╔════════════════════════════════════════════════════╗
║        ORBITAL STATION "ALPHA" - STATUS            ║
╠════════════════════════════════════════════════════╣
║                                                    ║
║  POWER:      [██████████████░░░░░░] 198/250 kW   ║
║  LIFE SUPPORT: [██████████████████] 98%  OK       ║
║  OXYGEN:     [███████████████████░] 95%  OK       ║
║  CREW:       6/6                                   ║
║  MODULES:    6 (All functional)                   ║
║  ORBIT:      250km × 255km, 28.5° inclination     ║
║                                                    ║
╠════════════════════════════════════════════════════╣
║  MODULES:                                          ║
║  [✓] Core         Power: 10kW   Health: 100%     ║
║  [✓] Habitation   Power:  5kW   Health:  98%     ║
║  [✓] Laboratory   Power: 20kW   Health: 100%     ║
║  [✓] Storage      Power:  1kW   Health: 100%     ║
║  [✓] Docking Hub  Power:  2kW   Health: 100%     ║
║  [✓] Solar Array  Power: +200kW Health:  95%     ║
╠════════════════════════════════════════════════════╣
║  [View 3D]  [Manage Power]  [Crew]  [Maintenance] ║
╚════════════════════════════════════════════════════╝
```

---

## Conclusion

Building and managing an orbital space station in Astro Engineer is one of the most rewarding experiences in the game. From your first tentative EVA to constructing a massive multi-wing complex, each step teaches new skills and opens new possibilities.

Stations transform the game from surface-bound survival to true space exploration. They serve as homes, factories, research centers, and stepping stones to the stars. With careful planning, methodical construction, and good management, your station will become the crown jewel of your space program.

**Remember**:
- Start small and expand gradually
- Safety first during EVA
- Monitor power and life support constantly
- Plan before you build
- Practice docking before committing
- Save often

For related documentation:
- **GAME_PROGRESSION_GUIDE.md** - When to build stations
- **ORBITAL_MECHANICS_GUIDE.md** - Reaching orbit and rendezvous
- **SHIP_PROGRESSION_GUIDE.md** - Ships for station construction

**Last Updated**: 2026-01-08  
**Maintained By**: Astro Engineer Development Team
