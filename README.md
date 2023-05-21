# CUB3D 

### **Current Workflow:**
* [Map Parsing](#map-parsing)
* [Top-down player movement](#top-down-player-movement)
* [Raycasting](#raycasting)
* [Textures](#textures)
* [Audio](#audio)

## Map Parsing

* [x] Start with square/rectangular maps. Prioritise raycasting.
* [x] Filename check (.cub)
* [x] Check that all walls are closed off (1 for wall, 0 for space)
* [x] Store map in 2d array

## Top-down player movement

* [x] Initialise whatever needs to be initialised for mlx. (Window, etc)
* [x] Print a marker to represent the player.
* [x] Handle key press, and map them to players movement.
* [x] Print out a top-down view of the map, preferably with gridlines. (To act as reference for raycast)
* [x] Later on we could maybe minimise this on screen to become the minimap.
* [x] Handle player rotation (I don't have brain to make notes on this atm)

## Raycasting

~~* Refer to that one video I shared~~
~~* Horizontal and vertical lines (on the grid) handled somewhat separately. Start with a single ray first.~~
~~* Horizontal check (up or down on the grid):~~
~~* Check if the nearest cell that the ray is facing on the horizontal line is a wall.~~
~~* else, add the x and y offset to check the next horizontal line.~~
~~* Draw a ray, just so we can see whats going on lol~~
~~* Vertical check (left or right):~~
~~* Pretty much the same as above.~~

We scrapped the method above for multiple reasons:
* The 3D display had very jagged walls.
* The algorithm often miscalculated the distance. Resulting in said jaggedness.
* It could definitely be fixed, with reduced step-size, or with extra work. But extra steps == laggy. And extra work to fix this method used meant more time spent. I don't have enough BH days for that.

Instead we referred to this, [Raycasting by Lodev.](https://lodev.org/cgtutor/raycasting.html)

## Textures
* [x] Initialise and store textures.
* [x] Set current ray texture based on direction.
* [x] Determine top and bottom coordinate of ray.
* [x] Calculate the point at where the ray hits the texture.
* [x] Calculate the exact position of the texture pixel.
* [x] Get the colour of the pixel. Set the pixel to draw as that colour.
* [x] Draw texture on screen. :thumbs_up:

## Audio
* [ ] Figure out how to do it.
* [ ] ![seele](https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.hoyolab.com%2Farticle%2F18129996&psig=AOvVaw1aUfxEpWNv6Z39a-10Cqdf&ust=1684769313021000&source=images&cd=vfe&ved=0CBEQjRxqFwoTCJDZpfnchv8CFQAAAAAdAAAAABAE)

## ISSUES
* [x] Pure raycast render is rough and jagged, anti-aliasing? later on need take vertex coordinates and map to an mlx image.
	* > Fixed: Completely changed the method. Smoother lines and display.
* [x] Different wall faces have same color, difficult to make out edges. find out direction of each wall rays hit and map to right color.
	* > Mapping textures to different wall directions done.
* [x] At certain distances, only the top pixels of the walls seem to be from another texture.
![:'>](https://cdn.discordapp.com/attachments/981502977003106384/1107985123334422618/Screenshot_2023-05-16_at_18.57.06.png)
	* > Fixed: pix(x, y) were swapped in get_wall_hit calculations lol.
* [x] Textures appear to be scrolling. Observe:
	* > Fixed: See above.
* [x] At certain angles, some walls seem to I guess.. crop? It just gets cut off. When walking past the wall, everything beyond that seems to disappear.
	* > Fixed: Forgot to update the new position in the map. The variable was already declared.