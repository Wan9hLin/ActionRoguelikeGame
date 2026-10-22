# Action Roguelike — Unreal Engine C++ Gameplay Prototype

A personal third-person action gameplay prototype developed with Unreal Engine 5.6, C++, and Blueprints.

The project brings together a reusable action framework, attributes and resource consumption, projectile abilities, enemy AI, and world interactions. C++ handles core gameplay behavior, while Blueprints configure abilities and presentation.

**Stack:** Unreal Engine 5.6 · C++ · Blueprints · Enhanced Input · Gameplay Tags · Behavior Trees / Blackboard · EQS · Niagara

**Status:** In active development. The latest milestone adds consumable Rage and percentage-based sprint speed.

## Gameplay

- **Third-person character:** camera-relative movement, mouse look, jumping, and sprinting using Enhanced Input.
- **Projectile abilities:** a damaging magic projectile, a black hole that attracts physics objects, and a projectile that teleports its owner after a delay.
- **Attributes and resources:** health, maximum health, movement speed, a speed multiplier, and Rage gained from receiving damage. Actions can require and consume attribute resources.
- **Enemy AI:** Behavior Tree / Blackboard assets with C++ ranged-attack tasks, distance and line-of-sight checks, and a custom EQS target context.
- **World interactions:** target selection weighted by distance and view direction, an interaction interface, animated chests, and explosive physics barrels.
- **Feedback and UI:** casting animations, Niagara effects, audio, a crosshair, and a health widget.

## Code to Explore

| Area | What to look for | Entry point |
| --- | --- | --- |
| Action framework | Per-owner `UObject` actions, Blueprint-overridable start/stop behavior, cooldowns, granted/blocked tags, and resource costs | [RogueAction](Source/ActionRoguelike/ActionSystem/RogueAction.h), [RogueActionSystemComponent](Source/ActionRoguelike/ActionSystem/RogueActionSystemComponent.cpp) |
| Attribute system | AttributeSet inheritance, base values and additive modifiers, reflection-based tag lookup, and post-change rules | [RogueAttributeSet](Source/ActionRoguelike/ActionSystem/RogueAttributeSet.h), [attribute application](Source/ActionRoguelike/ActionSystem/RogueAttributeSet.cpp) |
| Event-driven updates | Native C++ listeners and Blueprint callback registration, removal, and expired-binding cleanup | [RogueActionSystemComponent](Source/ActionRoguelike/ActionSystem/RogueActionSystemComponent.h) |
| Projectile casting | Animation/effect timing, camera-to-muzzle aim adjustment, and configurable projectile classes | [RogueAction_ProjectileAttack](Source/ActionRoguelike/ActionSystem/RogueAction_ProjectileAttack.cpp), [projectile implementations](Source/ActionRoguelike/Projectiles) |
| Enemy behavior | Blackboard target data, a range/line-of-sight service, ranged attacks, and EQS context provision | [AI source](Source/ActionRoguelike/AI), [AI assets](Content/ActionRoguelike/AI) |
| Interaction | Collision queries, weighted target selection, and C++/Blueprint interface dispatch | [RogueInteractionComponent](Source/ActionRoguelike/Player/RogueInteractionComponent.cpp), [RogueInteractionInterface](Source/ActionRoguelike/Core/RogueInteractionInterface.h) |

### How the systems connect

The character forwards ability input to `URogueActionSystemComponent`. The component finds the matching action by Gameplay Tag and asks `CanStart()` to check running state, cooldown, blocked tags, and every configured resource cost. On success, the action starts and consumes its resources before its ability-specific behavior continues.

The same component owns an AttributeSet and routes attribute changes through a shared API. Each `FRogueAttribute` evaluates to `Base + Modifier`; the AttributeSet applies rules such as health clamping and synchronizing movement speed. Native and Blueprint listeners then receive the attribute tag and old/new values.

```text
Input → ActionSystemComponent → CanStart → Start action / consume resources
Attribute change → AttributeSet rules → C++ and Blueprint listeners
MaxWalkSpeed = MoveSpeed.GetValue() × MoveSpeedMultiplier.GetValue()
```

Blueprints configure individual abilities, input bindings, projectile classes, and presentation on top of the C++ framework.

## Run Locally

### Requirements

- Windows development environment with **Unreal Engine 5.6**.
- **Visual Studio 2022** with the C++ workloads and Windows SDK required by UE 5.6. See [Epic's Visual Studio setup guide](https://dev.epicgames.com/documentation/en-us/unreal-engine/setting-up-visual-studio-development-environment-for-cplusplus-projects-in-unreal-engine?application_version=5.6).

### Open the test map

1. Clone the repository:

   ```sh
   git clone https://github.com/Wan9hLin/ActionRoguelikeGame.git
   ```

2. Right-click `ActionRoguelike.uproject` and select **Generate Visual Studio project files**.
3. Open the generated solution and build the **ActionRoguelikeEditor** target using **Development Editor / Win64**.
4. Open `ActionRoguelike.uproject` in UE 5.6 and allow the initial shader compilation to finish.
5. Open `Content/ActionRoguelike/Maps/P_OpenWorldTestMap` and select **Play** in the editor. This is the gameplay test map configured as the editor startup map.

## Controls

The default keyboard/mouse bindings are configured in [IMC_DefaultPlayer](Content/ActionRoguelike/Input/IMC_DefaultPlayer.uasset).

| Input | Action |
| --- | --- |
| W / A / S / D | Move |
| Mouse | Look |
| Space | Jump |
| Hold Left Shift | Sprint |
| Left mouse button | Magic projectile |
| F | Black hole (requires 25 Rage) |
| Q | Teleport projectile |
| E | Interact |

Rage starts at zero and is gained by taking damage. Build up Rage before trying the black hole ability.

## Current Progress

Development is currently focused on the action and attribute framework, including resource-gated activation, damage-generated Rage, percentage-based movement modifiers, and Blueprint attribute listeners. Further development will build on these systems with additional gameplay features and refinements.

The AI low-health decorator is still a placeholder following the attribute-system refactor. Its implementation is a remaining step before the low-health/self-healing behavior branch is complete.

## Assets

Character, animation, audio, and VFX content includes third-party assets. The focus of this repository is gameplay programming and C++/Blueprint integration.
