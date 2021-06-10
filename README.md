# Cub3D
This project is inspired by the world-famous eponymous 90's game Wolf3D, which was the first FPS ever. The goal will be to make a dynamic view inside a maze.

<img width="1901" alt="Screen Shot 2021-06-10 at 6 20 20 PM" src="https://user-images.githubusercontent.com/78852244/121551783-999a8a80-ca18-11eb-8b3a-d833b28399f4.png">

Compiling
---------------------------------------------------------------------------------------------------------------------------------
Run make and you're set. Runs on Mac OS X and Linux (with XServer).

Launch and control
---------------------------------------------------------------------------------------------------------------------------------
Launch: ./cub3D map.cub <br>
Control: WSAD and the keypad's arrows

Map file format
---------------------------------------------------------------------------------------------------------------------------------
The map must be composed of only 7 possible characters: 0 for an empty space, 1 for a wall, 2 for a sprite, <br>
and N, S, E or W for the player’s start position and spawning orientation.

Header of the map
----------------------------------------------------------------------------------------------------------------------------------
Range of windows: identifier: R width hight <br>
  * any range

North texture: identifier: NO - path to the north texure <br>
South texture: identifier: SO - path to the south texure <br>
West texture: identifier: WE - path to the west texure <br>
East texture: identifier: EA - path to the east texure <br>
Sprite texture: identifier: S - path to the sprite texure <br>
  * format of textures and sprites must be .xpm <br>

Floor color: identifier: F <br>
Ceilling color:  identifier: C <br>
  * R,G,B colors in range [0,255]: 0, 255, 255 <br>


This is a simple valid map:
---------------------------------------------------------------------------------------------------------------------------------
<img width="175" alt="Снимок экрана 2021-06-09 в 06 27 53" src="https://user-images.githubusercontent.com/78852244/121288397-f8aeb100-c8eb-11eb-8993-c088b4c38673.png">

  * A liquid card is considered to be surrounded by walls on all sides. And has a player.
  * Map file it's a simple text file, which needs to end .cub
