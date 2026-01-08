"""
Astro Engineer - FPS Template Setup Automation Script

This script automates the creation of the First Person template setup in Unreal Engine.
It creates the player character Blueprint, input assets, and basic configuration.

Usage:
    1. Open Unreal Engine Editor
    2. Enable Python Editor Script Plugin (if not enabled)
    3. Go to: Tools > Execute Python Script
    4. Select this file OR
    5. Run from Output Log: py "path/to/setup_fps_template.py"

Requirements:
    - Unreal Engine 5.7+
    - Python Editor Script Plugin enabled
    - Project loaded in editor
"""

import unreal

# Configuration
PROJECT_NAME = "AstroEngineer"
CONTENT_ROOT = "/Game"
BLUEPRINTS_PATH = f"{CONTENT_ROOT}/Blueprints"
INPUT_PATH = f"{CONTENT_ROOT}/Input"
MAPS_PATH = f"{CONTENT_ROOT}/Maps"

def log(message, level="log"):
    """Log messages to Unreal Engine output log"""
    if level == "warning":
        unreal.log_warning(f"[AstroEngineer Setup] {message}")
    elif level == "error":
        unreal.log_error(f"[AstroEngineer Setup] {message}")
    else:
        unreal.log(f"[AstroEngineer Setup] {message}")


def ensure_directory_exists(path):
    """Create directory if it doesn't exist"""
    if not unreal.EditorAssetLibrary.does_directory_exist(path):
        result = unreal.EditorAssetLibrary.make_directory(path)
        if result:
            log(f"Created directory: {path}")
        else:
            log(f"Failed to create directory: {path}", "warning")
        return result
    else:
        log(f"Directory already exists: {path}")
        return True


def create_input_action(name, value_type, description=""):
    """Create an Input Action asset"""
    asset_path = f"{INPUT_PATH}/{name}"
    
    if unreal.EditorAssetLibrary.does_asset_exist(asset_path):
        log(f"Input Action already exists: {name}")
        return unreal.load_asset(asset_path)
    
    # Create Input Action - no factory needed in UE 5.7
    asset = unreal.AssetToolsHelpers.get_asset_tools().create_asset(
        asset_name=name,
        package_path=INPUT_PATH,
        asset_class=unreal.InputAction,
        factory=None
    )
    
    if asset:
        # Set value type
        asset.set_editor_property("value_type", value_type)
        log(f"Created Input Action: {name} ({value_type})")
        unreal.EditorAssetLibrary.save_loaded_asset(asset)
        return asset
    else:
        log(f"Failed to create Input Action: {name}", "error")
        return None


def create_input_mapping_context(name):
    """Create an Input Mapping Context asset"""
    asset_path = f"{INPUT_PATH}/{name}"
    
    if unreal.EditorAssetLibrary.does_asset_exist(asset_path):
        log(f"Input Mapping Context already exists: {name}")
        return unreal.load_asset(asset_path)
    
    # Create Input Mapping Context - no factory needed in UE 5.7
    asset = unreal.AssetToolsHelpers.get_asset_tools().create_asset(
        asset_name=name,
        package_path=INPUT_PATH,
        asset_class=unreal.InputMappingContext,
        factory=None
    )
    
    if asset:
        log(f"Created Input Mapping Context: {name}")
        unreal.EditorAssetLibrary.save_loaded_asset(asset)
        return asset
    else:
        log(f"Failed to create Input Mapping Context: {name}", "error")
        return None


def create_player_character_blueprint():
    """Create the player character Blueprint from C++ class"""
    bp_path = f"{BLUEPRINTS_PATH}/Characters"
    bp_name = "BP_AstroPlayerCharacter"
    full_path = f"{bp_path}/{bp_name}"
    
    if unreal.EditorAssetLibrary.does_asset_exist(full_path):
        log(f"Blueprint already exists: {bp_name}")
        return unreal.load_asset(full_path)
    
    # Ensure directory exists
    ensure_directory_exists(bp_path)
    
    # Create Blueprint from C++ class
    factory = unreal.BlueprintFactory()
    factory.set_editor_property("parent_class", unreal.load_class(None, "/Script/AstroEngineer.AstroPlayerCharacter"))
    
    asset = unreal.AssetToolsHelpers.get_asset_tools().create_asset(
        asset_name=bp_name,
        package_path=bp_path,
        asset_class=unreal.Blueprint,
        factory=factory
    )
    
    if asset:
        log(f"Created Blueprint: {bp_name}")
        unreal.EditorAssetLibrary.save_loaded_asset(asset)
        return asset
    else:
        log(f"Failed to create Blueprint: {bp_name}", "error")
        return None


def create_game_mode_blueprint():
    """Create the game mode Blueprint from C++ class"""
    bp_path = f"{BLUEPRINTS_PATH}/GameModes"
    bp_name = "BP_AstroGameMode"
    full_path = f"{bp_path}/{bp_name}"
    
    if unreal.EditorAssetLibrary.does_asset_exist(full_path):
        log(f"Blueprint already exists: {bp_name}")
        return unreal.load_asset(full_path)
    
    # Ensure directory exists
    ensure_directory_exists(bp_path)
    
    # Create Blueprint from C++ class
    factory = unreal.BlueprintFactory()
    factory.set_editor_property("parent_class", unreal.load_class(None, "/Script/AstroEngineer.AstroGameMode"))
    
    asset = unreal.AssetToolsHelpers.get_asset_tools().create_asset(
        asset_name=bp_name,
        package_path=bp_path,
        asset_class=unreal.Blueprint,
        factory=factory
    )
    
    if asset:
        log(f"Created Blueprint: {bp_name}")
        unreal.EditorAssetLibrary.save_loaded_asset(asset)
        return asset
    else:
        log(f"Failed to create Blueprint: {bp_name}", "error")
        return None


def setup_input_system():
    """Setup Enhanced Input System assets"""
    log("=== Setting up Enhanced Input System ===")
    
    # Ensure Input directory exists
    ensure_directory_exists(INPUT_PATH)
    
    # Create Input Actions
    ia_move = create_input_action("IA_Move", unreal.InputActionValueType.AXIS2D, "Movement input")
    ia_look = create_input_action("IA_Look", unreal.InputActionValueType.AXIS2D, "Look input")
    ia_interact = create_input_action("IA_Interact", unreal.InputActionValueType.BOOLEAN, "Interact with objects")
    ia_backpack = create_input_action("IA_Backpack", unreal.InputActionValueType.BOOLEAN, "Toggle backpack")
    
    # Create Input Mapping Context
    imc = create_input_mapping_context("IMC_Default")
    
    return {
        "move": ia_move,
        "look": ia_look,
        "interact": ia_interact,
        "backpack": ia_backpack,
        "context": imc
    }


def setup_blueprints():
    """Setup Blueprint assets"""
    log("=== Setting up Blueprint Assets ===")
    
    # Ensure Blueprints directory structure exists
    ensure_directory_exists(BLUEPRINTS_PATH)
    ensure_directory_exists(f"{BLUEPRINTS_PATH}/Characters")
    ensure_directory_exists(f"{BLUEPRINTS_PATH}/GameModes")
    ensure_directory_exists(f"{BLUEPRINTS_PATH}/ShipModules")
    
    # Create Blueprints
    bp_character = create_player_character_blueprint()
    bp_gamemode = create_game_mode_blueprint()
    
    return {
        "character": bp_character,
        "gamemode": bp_gamemode
    }


def create_test_level():
    """Create a basic test level"""
    level_path = f"{MAPS_PATH}/TestLevel"
    
    editor_asset_lib = unreal.EditorAssetLibrary()
    if editor_asset_lib.does_asset_exist(level_path):
        log(f"Level already exists: TestLevel")
        return
    
    log("=== Creating Test Level ===")
    
    # Ensure Maps directory exists
    ensure_directory_exists(MAPS_PATH)
    
    # Create new level
    editor_level_lib = unreal.EditorLevelLibrary()
    
    # Create level (this will be empty)
    # Note: Direct level creation via Python is limited
    # Users should create level manually or we can provide instructions
    log("Please create TestLevel manually: File > New Level > Empty Level")
    log("Then save it to Content/Maps/TestLevel")


def print_summary():
    """Print setup summary and next steps"""
    log("")
    log("=" * 60)
    log("FPS Template Setup Complete!")
    log("=" * 60)
    log("")
    log("Created Assets:")
    log("  - Input Actions: IA_Move, IA_Look, IA_Interact, IA_Backpack")
    log("  - Input Mapping Context: IMC_Default")
    log("  - Blueprint: BP_AstroPlayerCharacter")
    log("  - Blueprint: BP_AstroGameMode")
    log("")
    log("Next Steps:")
    log("  1. Open BP_AstroPlayerCharacter")
    log("  2. Set Input references in Class Defaults:")
    log("     - Default Mapping Context = IMC_Default")
    log("     - Move Action = IA_Move")
    log("     - Look Action = IA_Look")
    log("     - Interact Action = IA_Interact")
    log("     - Backpack Action = IA_Backpack")
    log("  3. Configure IMC_Default with key mappings:")
    log("     - WASD for movement")
    log("     - Mouse for looking")
    log("     - E for interact")
    log("     - B for backpack")
    log("  4. Create test level (File > New Level)")
    log("  5. Set Game Mode in World Settings to BP_AstroGameMode")
    log("")
    log("See FPS_TEMPLATE_IMPLEMENTATION.md for detailed instructions")
    log("=" * 60)


def main():
    """Main setup function"""
    try:
        log("")
        log("=" * 60)
        log("Astro Engineer - FPS Template Setup")
        log("=" * 60)
        log("")
        
        # Setup Input System
        input_assets = setup_input_system()
        
        # Setup Blueprints
        blueprint_assets = setup_blueprints()
        
        # Print summary
        print_summary()
        
        # Show notification
        unreal.EditorDialog.show_message(
            "Setup Complete",
            "FPS Template setup completed successfully!\nCheck the Output Log for details.",
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
