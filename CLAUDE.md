# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

ConnorJam is an **Unreal Engine 5.7** C++ project containing three self-contained game variant prototypes — Platforming, SideScrolling, and Combat — each in its own subdirectory under `Source/ConnorJam/`. The project is written entirely in C++ (no Blueprint logic, animations, graphics, or UI are a focus). The stated learning goal is multiplayer/networking with a client-server architecture.

We have started unreal engine project C++
We don't care about animations, graphics, or UI, we only want to learn the network architecture

Don't write any code for us. The project should be written in C++.

We want to:
- Learn how to create a multiplayer game
- We want to have a client-server architecture where 1 PC has one client plus one dedicated server running,
  and the second player on the second PC connects to this server as well
- This is all we want and we will be using the controls and player given to us by the base unreal project third person mode.


## Building

This is a standard UBT (UnrealBuildTool) project. Build from within Visual Studio using the generated `ConnorJam.sln`, or via command line:

```
# Development Editor build (most common)
UnrealBuildTool.exe ConnorJamEditor Win64 Development -Project="<path>/ConnorJam.uproject"

# Regenerate project files after adding/removing .cpp/.h files
UnrealBuildTool.exe -ProjectFiles -Project="<path>/ConnorJam.uproject"
```

There are no automated tests in this project currently.

## Architecture

### Variant Structure

Each variant lives in its own folder and follows the same pattern: an abstract `ACharacter` subclass, a `AGameModeBase` subclass, and a `APlayerController` subclass. All classes are marked `UCLASS(abstract)` — concrete Blueprint subclasses are created in the editor.

| Variant | Character | Notable Systems |
|---|---|---|
| `Variant_Platforming/` | `APlatformingCharacter` | Double jump, wall jump, dash (via AnimMontage), coyote time |
| `Variant_SideScrolling/` | `ASideScrollingCharacter` | Double jump, wall jump, coyote time, soft platforms, interaction system, custom camera manager |
| `Variant_Combat/` | `ACombatCharacter` | Combo/charged melee, HP/death/respawn, AI enemies, EQS, StateTree |

### Input Pattern

All three variants use **Enhanced Input** (`UInputAction` bindings). Each character exposes a set of `Do*()` methods (`DoMove`, `DoJumpStart`, `DoJumpEnd`, `DoDash`, `DoComboAttackStart`, etc.) marked `UFUNCTION(BlueprintCallable)`. These act as the unified public input API callable from both the input binding and any UI or Blueprint layer.

### Combat Variant — Interfaces and AI

`ACombatCharacter` implements two interfaces:
- **`ICombatAttacker`** — called by AnimNotifies during montage playback: `DoAttackTrace()`, `CheckCombo()`, `CheckChargedAttack()`
- **`ICombatDamageable`** — `ApplyDamage()`, `HandleDeath()`, `ApplyHealing()`, `NotifyDanger()`

Attack collision is driven by AnimNotifies (`AnimNotify_DoAttackTrace`, `AnimNotify_CheckCombo`, `AnimNotify_CheckChargedAttack`) so that hit detection is frame-accurate to the animation.

AI enemies use **StateTree** (not Behavior Trees) via `UStateTreeAIComponent` on `ACombatAIController`. Custom StateTree tasks and conditions are defined as C++ structs in `CombatStateTreeUtility.h` (e.g., `FStateTreeComboAttackTask`, `FStateTreeIsInDangerCondition`, `FStateTreeGetPlayerInfoTask`). EQS contexts (`EnvQueryContext_Player`, `EnvQueryContext_Danger`) provide spatial query targets to StateTree.

The danger system: when `ACombatCharacter` attacks, it calls `NotifyEnemiesOfIncomingAttack()` which sphere-traces nearby enemies and calls `NotifyDanger()` on any `ICombatDamageable` in range — allowing enemies to react (dodge, block) before the hit lands.

### SideScrolling Variant — Camera and Interaction

`ASideScrollingCameraManager` (extends `APlayerCameraManager`) overrides `UpdateViewTarget()` to implement smooth scrolling with configurable world-space X bounds. The `ISideScrollingInteractable` interface allows any actor to respond to player interaction via `Interaction(AActor* Interactor)`. `ASideScrollingGameMode` tracks pickup count and manages the UI widget.

### Module Dependencies

Defined in `Source/ConnorJam/ConnorJam.Build.cs`:
- Public: `Core`, `CoreUObject`, `Engine`, `InputCore`, `EnhancedInput`, `AIModule`, `StateTreeModule`, `GameplayStateTreeModule`, `UMG`, `Slate`
- All variant subdirectories are listed as `PublicIncludePaths`, so headers can be included without path prefixes.
- Plugins: `StateTree`, `GameplayStateTree` (AI), `MultiUserClient`, `ModelingToolsEditorMode`
