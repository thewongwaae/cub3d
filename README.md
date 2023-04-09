# CUB3D 

### **Current Workflow:**
* [Map Parsing](#map-parsing)
* [Top-down player movement](#top-down-player-movement)
* [Raycasting](#raycasting)
* [Textures]()

## Map Parsing

* [ ] Start with square/rectangular maps. Prioritise raycasting.
* [x] Filename check (.cub)
* [x] Check that all walls are closed off (1 for wall, 0 for space)
* [x] Store map in 2d array

## Top-down player movement

* [x] Initialise whatever needs to be initialised for mlx. (Window, etc)
* [ ] Print a marker to represent the player.
* [ ] Handle key press, and map them to players movement.
* [ ] Print out a top-down view of the map, preferably with gridlines. (To act as reference for raycast)
* [ ] Later on we could maybe minimise this on screen to become the minimap.
* [ ] Handle player rotation (I don't have brain to make notes on this atm)

## Raycasting

* Refer to that one video I shared
* Horizontal and vertical lines (on the grid) handled somewhat separately. Start with a single ray first.
* Horizontal check (up or down on the grid):
	* Check if the nearest cell that the ray is facing on the horizontal line is a wall.
	* else, add the x and y offset to check the next horizontal line.
	* Draw a ray, just so we can see whats going on lol
* Vertical check (left or right):
	* Pretty much the same as above.