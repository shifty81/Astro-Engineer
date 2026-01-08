# Python API Fixes for Unreal Engine 5.7

This document describes the Python API changes required for compatibility with Unreal Engine 5.7 and explains the fixes applied to the project's Python automation scripts.

## Overview

Unreal Engine 5.5+ introduced several changes to the Python API that deprecated old usage patterns and introduced new APIs. These changes were made to align with best practices and improve code clarity.

## Fixed Issues

### 1. EditorAssetLibrary Deprecation (UE 5.5+)

**Problem:**
```python
# OLD - Deprecated in UE 5.5+
editor_asset_lib = unreal.EditorAssetLibrary()
editor_asset_lib.does_directory_exist(path)
```

**Error Message:**
```
DeprecationWarning: EditorAssetLibrary: Creating an instance of a BlueprintFunctionLibrary has been deprecated since UE 5.5 and will be removed in the future. Call its classmethods directly on the class, eg, 'unreal.EditorAssetLibrary.foo()'.
```

**Solution:**
```python
# NEW - Call methods directly on the class
unreal.EditorAssetLibrary.does_directory_exist(path)
unreal.EditorAssetLibrary.make_directory(path)
unreal.EditorAssetLibrary.does_asset_exist(asset_path)
unreal.EditorAssetLibrary.save_loaded_asset(asset)
```

**Reason:**
The EditorAssetLibrary and similar utility classes expose static/class methods that don't require instance state. Epic is phasing out instance-based calls to make it clearer these are stateless utility functions.

### 2. InputActionFactory Removed (UE 5.7)

**Problem:**
```python
# OLD - InputActionFactory doesn't exist in UE 5.7
factory = unreal.InputActionFactory()
asset = unreal.AssetToolsHelpers.get_asset_tools().create_asset(
    asset_name=name,
    package_path=INPUT_PATH,
    asset_class=unreal.InputAction,
    factory=factory
)
```

**Error Message:**
```
AttributeError: module 'unreal' has no attribute 'InputActionFactory'
```

**Solution:**
```python
# NEW - Pass factory=None for InputAction creation
asset = unreal.AssetToolsHelpers.get_asset_tools().create_asset(
    asset_name=name,
    package_path=INPUT_PATH,
    asset_class=unreal.InputAction,
    factory=None
)
```

**Reason:**
In UE 5.7, InputAction and InputMappingContext classes can be instantiated directly without requiring a factory class. The API now supports passing `factory=None` for these asset types.

### 3. InputMappingContextFactory Removed (UE 5.7)

**Problem:**
```python
# OLD - InputMappingContextFactory doesn't exist in UE 5.7
factory = unreal.InputMappingContextFactory()
asset = unreal.AssetToolsHelpers.get_asset_tools().create_asset(
    asset_name=name,
    package_path=INPUT_PATH,
    asset_class=unreal.InputMappingContext,
    factory=factory
)
```

**Solution:**
```python
# NEW - Pass factory=None for InputMappingContext creation
asset = unreal.AssetToolsHelpers.get_asset_tools().create_asset(
    asset_name=name,
    package_path=INPUT_PATH,
    asset_class=unreal.InputMappingContext,
    factory=None
)
```

### 4. LinearColor to Color Conversion for Light Properties

**Problem:**
```python
# OLD - Trying to set LinearColor directly
light_component.set_editor_property("light_color", unreal.LinearColor(1.0, 0.95, 0.9, 1.0))
```

**Error Message:**
```
TypeError: DirectionalLightComponent: Failed to convert type 'LinearColor' to property 'LightColor' (StructProperty) for attribute 'light_color' on 'DirectionalLightComponent'
  TypeError: NativizeProperty: Cannot nativize 'LinearColor' as 'LightColor' (StructProperty)
    TypeError: NativizeStructInstance: Cannot nativize 'LinearColor' as 'Color'
```

**Solution:**
```python
# NEW - Convert LinearColor to Color using .to_color()
linear_color = unreal.LinearColor(1.0, 0.95, 0.9, 1.0)
light_component.set_editor_property("light_color", linear_color.to_color())
```

**Reason:**
The `light_color` property expects a `Color` (FColor) type, which uses 8-bit integer values (0-255), not `LinearColor` which uses floating-point values. The Python API does not automatically convert between these types, so you must explicitly call `.to_color()` to convert from LinearColor to Color.

**Understanding Color Types:**
- **LinearColor**: Floating-point RGBA (0.0-1.0+), used internally for lighting calculations and HDR
- **Color (FColor)**: Integer RGBA (0-255), used for properties that expect sRGB color values

## Files Updated

### Scripts/Python/setup_fps_template.py
- Fixed all EditorAssetLibrary calls to use static methods
- Removed InputActionFactory, using factory=None instead
- Removed InputMappingContextFactory, using factory=None instead

### Scripts/Python/setup_test_scene.py
- Fixed all EditorAssetLibrary calls to use static methods
- Fixed light_color property to use LinearColor.to_color() conversion

## Migration Guide

If you have custom Python scripts that interact with Unreal Engine, apply these patterns:

1. **Replace all BlueprintFunctionLibrary instantiations:**
   ```python
   # Before
   lib = unreal.SomeLibrary()
   lib.some_method()
   
   # After
   unreal.SomeLibrary.some_method()
   ```

2. **Remove factory classes for Enhanced Input assets:**
   ```python
   # Before
   factory = unreal.InputActionFactory()
   
   # After
   factory = None  # Or omit the factory parameter if possible
   ```

3. **Convert LinearColor to Color when needed:**
   ```python
   # Before
   component.set_editor_property("some_color_property", linear_color)
   
   # After
   component.set_editor_property("some_color_property", linear_color.to_color())
   ```

## Testing

To test these fixes:

1. Open the Unreal Editor with the project loaded
2. Enable the Python Editor Script Plugin (if not already enabled)
3. Run the scripts from the Output Log:
   ```
   py "C:/path/to/Scripts/Python/setup_fps_template.py"
   py "C:/path/to/Scripts/Python/setup_test_scene.py"
   ```
4. Verify no deprecation warnings or errors appear
5. Verify assets are created successfully

## References

- [Unreal Engine Python API Documentation (5.7)](https://dev.epicgames.com/documentation/en-us/unreal-engine/python-api/?application_version=5.7)
- [EditorAssetLibrary Class Reference](https://dev.epicgames.com/documentation/en-us/unreal-engine/python-api/class/EditorAssetLibrary?application_version=5.7)
- [LinearColor Class Reference](https://dev.epicgames.com/documentation/en-us/unreal-engine/python-api/class/LinearColor?application_version=5.7)
- [Enhanced Input Documentation](https://dev.epicgames.com/documentation/en-us/unreal-engine/enhanced-input-in-unreal-engine)

## Additional Notes

### About CS8981 Warnings

The problem statement also mentioned CS8981 warnings about lowercase-only type names (e.g., `jemalloc`, `portmidi`). These warnings come from Unreal Engine's own source files located in:
```
C:\Program Files\Epic Games\UE_5.7\Engine\Source\ThirdParty\
```

These warnings **cannot be fixed** in this repository as they are part of the Unreal Engine installation itself. They are informational warnings from the C# compiler and do not affect functionality.

### About CS0618 Warning (VisualStudioTools)

The CS0618 warning about `ModuleRules.UnsafeTypeCastWarningLevel` being obsolete refers to Microsoft's VisualStudioTools plugin. If you have this plugin installed locally in your `Plugins/VisualStudioTools` directory, you can fix it by updating line 26 of `VisualStudioTools.Build.cs`:

```csharp
// OLD - Deprecated in UE 5.6
UnsafeTypeCastWarningLevel = WarningLevel.Error;

// NEW
CppCompileWarningSettings.UnsafeTypeCastWarningLevel = WarningLevel.Error;
```

However, this plugin is not included in the repository and is typically installed separately from Microsoft's vc-ue-extensions repository.

## Conclusion

These fixes ensure compatibility with Unreal Engine 5.7's Python API and resolve deprecation warnings introduced in UE 5.5+. The changes follow Epic's recommended patterns and will be forward-compatible with future versions of Unreal Engine.
