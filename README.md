# Action Roguelike — Unreal Engine C++ Gameplay Prototype

A personal third-person action gameplay prototype developed with Unreal Engine 5.6, C++, and Blueprints.

The project brings together a reusable action framework, attributes and resource consumption, projectile abilities, enemy AI, world interactions, and a data-oriented pickup system built to handle thousands of instances. C++ handles core gameplay behavior, while Blueprints configure abilities and presentation.

**Stack:** Unreal Engine 5.6 · C++ · Blueprints · Enhanced Input · Gameplay Tags · Behavior Trees / Blackboard · EQS · Niagara · MetaSounds · Instanced Static Meshes · Unreal Insights

**Status:** In active development. The latest milestone adds data-oriented coin pickups, rendered with Instanced Static Meshes and profiled and optimized with Unreal Insights.

## Gameplay

- **Third-person character:** camera-relative movement, mouse look, jumping, and sprinting using Enhanced Input. Sprinting switches to a sprint animation, plays pooled Niagara effects on both hands, and runs a looping MetaSounds hover sound.
- **Projectile abilities:** a damaging magic projectile, a black hole that attracts physics objects, and a projectile that teleports its owner after a delay.
- **Attributes and resources:** health, maximum health, movement speed, a speed multiplier, and Rage gained from receiving damage. Actions can require and consume attribute resources. Attribute values are edited per Blueprint, with C++ defaults for players and monsters.
- **Enemy AI:** Behavior Tree / Blackboard assets with C++ ranged-attack tasks, distance and line-of-sight checks, a custom EQS target context, and a low-health branch where enemies flee and heal themselves.
- **World interactions:** target selection weighted by distance and view direction, an interaction interface, animated chests, explosive physics barrels, and a lever that spawns a batch of coins.
- **Coin pickups:** thousands of coins placed at random points on the NavMesh and collected by walking close to them, with a MetaSounds pickup sound.
- **Feedback and UI:** casting animations, Niagara effects, audio, a hit-flash overlay on damaged characters, a crosshair, and a health widget.

## Code to Explore

| Area | What to look for | Entry point |
| --- | --- | --- |
| Action framework | Per-owner `UObject` actions, Blueprint-overridable start/stop behavior, cooldowns, granted/blocked tags, and resource costs | [RogueAction](Source/ActionRoguelike/ActionSystem/RogueAction.h), [RogueActionSystemComponent](Source/ActionRoguelike/ActionSystem/RogueActionSystemComponent.cpp) |
| Attribute system | AttributeSet inheritance, base values and additive modifiers, reflection-based tag lookup, post-change rules, and instanced attribute sets edited inline in Blueprints (`EditInlineNew` + `Instanced`) with per-class C++ defaults | [RogueAttributeSet](Source/ActionRoguelike/ActionSystem/RogueAttributeSet.h), [attribute application](Source/ActionRoguelike/ActionSystem/RogueAttributeSet.cpp) |
| Event-driven updates | Native C++ listeners and Blueprint callback registration, removal, and expired-binding cleanup | [RogueActionSystemComponent](Source/ActionRoguelike/ActionSystem/RogueActionSystemComponent.h) |
| Projectile casting | Animation/effect timing, camera-to-muzzle aim adjustment, and configurable projectile classes | [RogueAction_ProjectileAttack](Source/ActionRoguelike/ActionSystem/RogueAction_ProjectileAttack.cpp), [projectile implementations](Source/ActionRoguelike/Projectiles) |
| Animation | A C++ `UAnimInstance` base class that reads Gameplay Tags from the action component to drive Animation Blueprint state | [RogueAnimInstance](Source/ActionRoguelike/Animation/RogueAnimInstance.cpp) |
| Hit feedback | An overlay material driven by Custom Primitive Data: C++ writes the hit time once, and the material computes the fade on the GPU | [RoguePlayerCharacter](Source/ActionRoguelike/Player/RoguePlayerCharacter.cpp), [RogueAICharacter](Source/ActionRoguelike/AI/RogueAICharacter.cpp) |
| Enemy behavior | Blackboard target data, a range/line-of-sight service, ranged attacks, a low-health decorator, and EQS context provision | [AI source](Source/ActionRoguelike/AI), [AI assets](Content/ActionRoguelike/AI) |
| Interaction | Collision queries, weighted target selection, and C++/Blueprint interface dispatch | [RogueInteractionComponent](Source/ActionRoguelike/Player/RogueInteractionComponent.cpp), [RogueInteractionInterface](Source/ActionRoguelike/Core/RogueInteractionInterface.h) |
| Data-oriented pickups | A `UTickableWorldSubsystem` that stores coins in parallel arrays instead of actors, a cache-friendly distance pass, batched Instanced Static Mesh updates with stable instance IDs, and a single MetaSound driven by a trigger parameter | [RogueCoinPickupSubsystem](Source/ActionRoguelike/Pickup/RogueCoinPickupSubsystem.cpp) |
| Project settings | A `UDeveloperSettings` class exposed in Project Settings, with soft asset references that load asynchronously | [RogueDeveloperSettings](Source/ActionRoguelike/Core/RogueDeveloperSettings.h) |

### How the systems connect

The character forwards ability input to `URogueActionSystemComponent`. The component finds the matching action by Gameplay Tag and asks `CanStart()` to check running state, cooldown, blocked tags, and every configured resource cost. On success, the action starts and consumes its resources before its ability-specific behavior continues.

The same component owns an AttributeSet and routes attribute changes through a shared API. Each `FRogueAttribute` evaluates to `Base + Modifier`; the AttributeSet applies rules such as health clamping and synchronizing movement speed. Native and Blueprint listeners then receive the attribute tag and old/new values.

Coins are not actors. `URogueCoinPickupSubsystem` stores their locations, amounts, and mesh instance IDs in parallel arrays and renders all of them with one Instanced Static Mesh. Each tick it checks distances against the coin locations, collects the coins in range, removes them from every array and from the mesh, and triggers the pickup sound once for that frame.

```text
Input → ActionSystemComponent → CanStart → Start action / consume resources
Attribute change → AttributeSet rules → C++ and Blueprint listeners
MaxWalkSpeed = MoveSpeed.GetValue() × MoveSpeedMultiplier.GetValue()
Sprint action → StatusEffect.Sprinting tag → AnimInstance → sprint animation
Lever → SpawnCoins → AddCoinPickups → arrays + ISM instances (batched)
Tick → distance pass over CoinLocations → remove picked-up coins → MetaSound trigger
```

Blueprints configure individual abilities, input bindings, projectile classes, and presentation on top of the C++ framework.

## Performance & Profiling

The coin system was designed for large counts, then measured and tuned with Unreal Insights:

- **Instrumentation:** `TRACE_CPUPROFILER_EVENT_SCOPE` scopes cover the tick, the distance pass, pickup handling, and adding/removing coins. A `Coins in World` trace counter shows the coin count over time, and the subsystem's tick is also reported under `stat Tickables`.
- **Data layout:** Locations, amounts, and instance IDs live in separate arrays (structure of arrays). The per-frame distance pass reads only the contiguous location array.
- **CPU:** Coins are removed with `RemoveAtSwap` without shrinking instead of `RemoveAt`: constant time per coin and no reallocations. In comparable Unreal Insights captures of lever-spawned coins, the average `RemoveCoinPickup` call dropped from 2.74 µs to 1.20 µs (−56%), and the median from 2.07 µs to about 0.1 µs. Total removal time fell from 8.29 ms to 4.29 ms, even though the second capture removed 18% more coins (3,563 vs. 3,027). Debug drawing and logging are compiled out of the hot path.
- **GPU:** Adding and removing instances triggered Global Distance Field updates, so the coin ISM is excluded from distance field lighting. It also has collision disabled, since pickups use the distance pass.
- **Loading:** The coin mesh and pickup sound are soft references in Project Settings. They load asynchronously when the world begins play, without blocking the game thread.

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
5. Open `Content/ActionRoguelike/Maps/P_OpenWorldTestMap` and select **Play** in the editor. This gameplay test map is configured as both the editor startup map and the game default map.

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
| E | Interact (chests, levers) |

Rage starts at zero and is gained by taking damage. Build up Rage before trying the black hole ability. To try the coin pickups, interact with the coin lever in the test map and walk through the coins it spawns.

## Current Progress

Development has moved from the action and attribute framework through presentation polish (sprint animation, pooled VFX, MetaSounds audio, and hit reactions) to a data-oriented coin pickup system with profiling-driven optimizations. Next up is a buff/debuff system built on top of the action framework.

The coin values picked up each frame are added up, but they are not yet credited to the player; that hookup is still a TODO.

## Assets

Character, animation, audio, and VFX content includes third-party assets. The focus of this repository is gameplay programming and C++/Blueprint integration.
