"""
Astro Engineer - Test Scene Setup Automation Script

This script automates the creation of a test scene/level with proper configuration
including lighting, player spawn, and basic environment setup.

Usage:
    1. Open Unreal Engine Editor
    2. Enable Python Editor Script Plugin (if not enabled)
    3. Go to: Tools > Execute Python Script
    4. Select this file OR
    5. Run from Output Log: py "path/to/setup_test_scene.py"

Requirements:
    - Unreal Engine 5.7+
    - Python Editor Script Plugin enabled
    - Project loaded in editor
    - BP_AstroGameMode should exist (run setup_fps_template.py first)
"""

import unreal

# Configuration
CONTENT_ROOT = "/Game"
MAPS_PATH = f"{CONTENT_ROOT}/Maps"
LEVEL_NAME = "TestLevel"

def log(message, level="log"):
    """Log messages to Unreal Engine output log"""
    if level == "warning":
        unreal.log_warning(f"[Scene Setup] {message}")
    elif level == "error":
        unreal.log_error(f"[Scene Setup] {message}")
    else:
        unreal.log(f"[Scene Setup] {message}")


def create_new_level():
    """Create a new empty level"""
    log("Creating new level...")
    
    editor_level_lib = unreal.EditorLevelLibrary()
    
    # Create new level
    result = editor_level_lib.new_level(f"{MAPS_PATH}/{LEVEL_NAME}")
    
    if result:
        log(f"Created new level: {LEVEL_NAME}")
        return True
    else:
        log(f"Failed to create level. It may already exist.", "warning")
        # Try to load existing level
        try:
            editor_level_lib.load_level(f"{MAPS_PATH}/{LEVEL_NAME}")
            log(f"Loaded existing level: {LEVEL_NAME}")
            return True
        except:
            return False


def spawn_actor(actor_class, location=(0, 0, 0), rotation=(0, 0, 0), name=None):
    """Spawn an actor in the current level"""
    editor_actor_subsystem = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
    
    loc = unreal.Vector(location[0], location[1], location[2])
    rot = unreal.Rotator(rotation[0], rotation[1], rotation[2])
    
    actor = editor_actor_subsystem.spawn_actor_from_class(
        actor_class,
        loc,
        rot
    )
    
    if actor and name:
        actor.set_actor_label(name)
    
    return actor


def setup_lighting():
    """Setup basic lighting for the scene"""
    log("=== Setting up Lighting ===")
    
    # Add Directional Light (Sun)
    directional_light = spawn_actor(
        unreal.DirectionalLight,
        location=(0, 0, 500),
        rotation=(-45, 0, 0),
        name="DirectionalLight_Sun"
    )
    if directional_light:
        # Configure light properties
        light_component = directional_light.get_component_by_class(unreal.DirectionalLightComponent)
        if light_component:
            light_component.set_editor_property("intensity", 10.0)
            # Convert LinearColor to Color for the light_color property
            linear_color = unreal.LinearColor(1.0, 0.95, 0.9, 1.0)
            light_component.set_editor_property("light_color", linear_color.to_color())
        log("Created Directional Light (Sun)")
    
    # Add Sky Light
    sky_light = spawn_actor(
        unreal.SkyLight,
        location=(0, 0, 500),
        name="SkyLight"
    )
    if sky_light:
        sky_component = sky_light.get_component_by_class(unreal.SkyLightComponent)
        if sky_component:
            sky_component.set_editor_property("intensity", 1.0)
            sky_component.set_editor_property("source_type", unreal.SkyLightSourceType.SLS_CAPTURED_SCENE)
        log("Created Sky Light")
    
    # Add Sky Atmosphere
    sky_atmosphere = spawn_actor(
        unreal.SkyAtmosphere,
        location=(0, 0, 0),
        name="SkyAtmosphere"
    )
    if sky_atmosphere:
        log("Created Sky Atmosphere")
    
    # Add Exponential Height Fog (optional)
    fog = spawn_actor(
        unreal.ExponentialHeightFog,
        location=(0, 0, 0),
        name="ExponentialHeightFog"
    )
    if fog:
        log("Created Exponential Height Fog")


def create_floor():
    """Create a basic floor for the scene"""
    log("=== Creating Floor ===")
    
    # Spawn a large static mesh cube as floor
    # Note: This requires a valid static mesh asset
    # Using a simple approach with plane
    
    floor = spawn_actor(
        unreal.StaticMeshActor,
        location=(0, 0, 0),
        name="Floor"
    )
    
    if floor:
        # Try to set a basic cube mesh (scaled flat)
        # This may fail if the default cube doesn't exist
        try:
            static_mesh_component = floor.get_component_by_class(unreal.StaticMeshComponent)
            
            # Load engine cube mesh
            cube_mesh = unreal.load_asset("/Engine/BasicShapes/Cube")
            if cube_mesh and static_mesh_component:
                static_mesh_component.set_static_mesh(cube_mesh)
                # Scale to make it a floor (very flat and wide)
                floor.set_actor_scale3d(unreal.Vector(100.0, 100.0, 0.1))
                log("Created floor from cube mesh")
            else:
                log("Could not load cube mesh, floor created but needs mesh assignment", "warning")
        except Exception as e:
            log(f"Could not configure floor mesh: {str(e)}", "warning")


def setup_player_spawn():
    """Add a player start actor"""
    log("=== Setting up Player Spawn ===")
    
    player_start = spawn_actor(
        unreal.PlayerStart,
        location=(0, 0, 100),  # Slightly above floor
        rotation=(0, 0, 0),
        name="PlayerStart"
    )
    
    if player_start:
        log("Created Player Start")
        return player_start
    else:
        log("Failed to create Player Start", "error")
        return None


def add_test_objects():
    """Add some test objects to the scene"""
    log("=== Adding Test Objects ===")
    
    # Add a few cubes at different positions for spatial reference
    positions = [
        (500, 0, 100, "Cube_Forward"),
        (-500, 0, 100, "Cube_Backward"),
        (0, 500, 100, "Cube_Right"),
        (0, -500, 100, "Cube_Left"),
    ]
    
    for x, y, z, name in positions:
        cube = spawn_actor(
            unreal.StaticMeshActor,
            location=(x, y, z),
            name=name
        )
        if cube:
            try:
                static_mesh_component = cube.get_component_by_class(unreal.StaticMeshComponent)
                cube_mesh = unreal.load_asset("/Engine/BasicShapes/Cube")
                if cube_mesh and static_mesh_component:
                    static_mesh_component.set_static_mesh(cube_mesh)
            except:
                pass
    
    log("Added test cubes for spatial reference")


def configure_world_settings():
    """Configure world settings for the level"""
    log("=== Configuring World Settings ===")
    
    # Get world
    world = unreal.EditorLevelLibrary.get_editor_world()
    if not world:
        log("Could not get editor world", "error")
        return
    
    # Get world settings
    world_settings = world.get_world_settings()
    if not world_settings:
        log("Could not get world settings", "error")
        return
    
    # Set Game Mode
    try:
        # Try to load BP_AstroGameMode
        gamemode_class = unreal.load_class(None, "/Game/Blueprints/GameModes/BP_AstroGameMode.BP_AstroGameMode_C")
        if gamemode_class:
            world_settings.set_editor_property("default_gamemode_override", gamemode_class)
            log("Set Game Mode to BP_AstroGameMode")
        else:
            # Fallback to C++ class
            gamemode_class = unreal.load_class(None, "/Script/AstroEngineer.AstroGameMode")
            if gamemode_class:
                world_settings.set_editor_property("default_gamemode_override", gamemode_class)
                log("Set Game Mode to AstroGameMode (C++ class)")
            else:
                log("Could not find AstroGameMode class", "warning")
    except Exception as e:
        log(f"Could not set game mode: {str(e)}", "warning")
    
    # Set other world settings
    try:
        # Enable physics
        world_settings.set_editor_property("enable_world_bounds_checks", True)
        log("Configured world settings")
    except Exception as e:
        log(f"Could not configure world settings: {str(e)}", "warning")


def save_level():
    """Save the current level"""
    log("=== Saving Level ===")
    
    result = unreal.EditorLoadingAndSavingUtils.save_current_level()
    if result:
        log("Level saved successfully")
    else:
        log("Failed to save level", "error")
    
    return result


def print_summary():
    """Print setup summary"""
    log("")
    log("=" * 60)
    log("Test Scene Setup Complete!")
    log("=" * 60)
    log("")
    log("Created:")
    log("  - Level: TestLevel")
    log("  - Directional Light (Sun)")
    log("  - Sky Light")
    log("  - Sky Atmosphere")
    log("  - Exponential Height Fog")
    log("  - Floor (10000x10000)")
    log("  - Player Start")
    log("  - Test objects (cubes)")
    log("")
    log("Configuration:")
    log("  - Game Mode: BP_AstroGameMode")
    log("  - Player spawn at (0, 0, 100)")
    log("")
    log("Next Steps:")
    log("  1. Press Play (PIE) to test the scene")
    log("  2. Test movement with WASD")
    log("  3. Test camera with mouse")
    log("  4. Add more content as needed")
    log("")
    log("See SCENE_SETUP_GUIDE.md for more customization options")
    log("=" * 60)


def main():
    """Main setup function"""
    try:
        log("")
        log("=" * 60)
        log("Astro Engineer - Test Scene Setup")
        log("=" * 60)
        log("")
        
        # Ensure Maps directory exists
        if not unreal.EditorAssetLibrary.does_directory_exist(MAPS_PATH):
            unreal.EditorAssetLibrary.make_directory(MAPS_PATH)
            log(f"Created directory: {MAPS_PATH}")
        
        # Create new level
        if not create_new_level():
            log("Failed to create/load level", "error")
            return
        
        # Setup scene components
        setup_lighting()
        create_floor()
        setup_player_spawn()
        add_test_objects()
        configure_world_settings()
        
        # Save the level
        save_level()
        
        # Print summary
        print_summary()
        
        # Show notification
        unreal.EditorDialog.show_message(
            "Setup Complete",
            "Test scene setup completed successfully!\nCheck the Output Log for details.",
            unreal.AppMsgType.OK
        )
        
    except Exception as e:
        log(f"Setup failed with error: {str(e)}", "error")
        unreal.EditorDialog.show_message(
            "Setup Failed",
            f"An error occurred during setup:\n{str(e)}",
            unreal.AppMsgType.OK
        )
        raise


if __name__ == "__main__":
    main()
