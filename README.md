# Dungeon Raider
Dungeon Raider (also known as Crypt Raiders) is one of the projects associated with GameDev TV's Unreal Engine C++ course.
This is my own spin on the project, featuring a single mid-sized level with plenty of loot for players to interact with.
I also added in some additional mechanics; throwing and rotating held objects, and a scoring system.

## Level Design
This dungeon was designed using a combination of the Hub-and-Spoke and Ring layouts to keep things fairly linear, but still allow for some exploration.
I had to design with a mechanical limitation in mind; players can only carry one piece of loot at a time.
I was worried it would get tedious if players had to keep backtracking to return to the start, so instead I gave players multiple avenues to return to the start/drop-off point.
The exception to this is the lower dungeon, which can be accessed via a secret door. Entering and exiting the lower dungeon requires players to solve very simple puzzles to trigger secret doors to open.
This area is quite a bit more linear due to it being out of the way of the rest of the dungeon. I wanted players to be able to get in and out of that area fairly quickly with all their loot (again to prevent it from getting too tedious).

When it came to lighting this level, I tried to keep it pretty sparse. I wanted the main chamber of the dungeon to feel pretty safe and welcoming. The hallways are a bit darker, to make players a little more wary.
While there are no enemies in this game, the player is still looting a dungeon so they should feel slightly nervous about something popping up.
The lower dungeon area is actually much brighter than the rest of the dungeon, but it is meant to feel a little eerie. This is achieved by using an unnaturally blue colored light.
So while this area is very brightly lit, it is a little unnerving going from normal fire light to spooky ghost light.

This level was built using a combination of 2 asset packs. 
The bulk of the dungeon was built with the modular asset pack "Stylized - Nanite Dungeon Pack" by Studio Kobo. 
Additional props were pulled from the "Medieval Dungeon" asset pack by Infuse Studio.


## Programming
As stated above, this project was initially from GameDev TV's Unreal Engine C++ course. The course is very much geared towards people who have never programmed before, and I quickly found myself veering off course.
So while this project loosley follows the cirriculum of the course, there are some notable differences.

Project Curriculum:
- Create a Grabber scene component to control a physics handle
- Create a Mover actor component to move an object when the event is triggered
- Create a Triggerbox to trigger the Mover component

Some of what I did:
- Created a Grabber scene component to control a physics handle
- Create a Mover actor component to move an object when the event is triggered
- Created a DoorKey actor component to handle events related to the Mover
- Created a Score actor component to easily track and assign the value of each piece of loot
- Created a LootChest actor to handle updates to the score
- Created a HUDBase and a WidgetBase to update and display the changes to the player score
- Created a custom RaiderPlayerState to further track the player score and coordinate updates from the LootChest to the HUDBase
- Created a Loot actor that has a ScoreComponent and a StaticMeshComponent so StaticMeshes can easily be swapped out for loot in the level
- Created a CandleFlameController actor component to swap out flame materials on the fly
- Created a SkeletonKey actor that has a DoorKey component and a spline for the key actor to follow when placed
- Created a CandleRing actor that spawns candles in a perfect circle around a StaticMeshComponent

I tried to keep form and function in mind while working on this project. Anything involving function should be made in C++, but anything involving form should be done in Blueprints.
For example, the CandleFlameController has a single function on it that takes in an array of meshes and a material instance and then it swaps all the materials on the meshes with the new material.
This function can then be called in Blueprints. So in Blueprints it handles the form, but the function is mostly handled on the backend in C++.
There are probably some places where I could have (and maybe should have) done something in Blueprints instead of C++, but this is my first C++ focused project so I spent a lot of time just playing around and seeing what was possible.
Going forward, I'm aiming to be more strict about form and function and figuring out what is best practice.
