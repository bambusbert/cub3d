1.	change ray casting logic. we have ti cast exactly WINDOW_SIZE_X rays.
2.	for each of these rays we have to calculate the angle.
3.	upgrade is_wall_coord logic. atm we check for every pixel. that is too slow.
Plan:	DDA algorithm. we calculate the distance to the next theoretical
	wall (grid). draw that portion of the line. if thie pixel at this distance 
	would be in the wall: stop. if not, continue. store the ray length somehow.
4.	fix fisheye effect: don't use euclidean distance but perpendicular distance
5.	now we have WINDOW_SIZE_X rays. for each ray we paint a regarding vertical
	line that is inversely proportional to the ray distance

Step 1 & 2: The Screen Loop and Ray Angles

Estimated Time: 1 hour
Goal: Map every pixel column on your monitor to a mathematical angle.

Task 1.1: The Main Loop: Create a while loop that iterates a variable x from 0 up to WINDOW_SIZE_X. Everything else in this plan happens inside this loop.

Task 1.2: Screen Mapping: Inside the loop, map the current x pixel to a multiplier (let's call it camera_x). This value should represent where you are on the screen, ranging from -1 (far left) to 1 (far right), with 0 being the exact center.

Task 1.3: Calculate the Angle: Use camera_x and your Field of View (FOV) to calculate the exact angle (or vector direction) for this specific ray.

Step 3: The DDA Algorithm (The Core Engine)

Estimated Time: 3 to 4 hours
Goal: Mathematically jump the ray from grid-line to grid-line until it hits a wall.

Task 3.1: Calculate Delta Distances: Figure out the delta_x and delta_y for the ray. In DDA, this isn't the total distance. It is the distance the ray has to travel to cross exactly one vertical grid line, or exactly one horizontal grid line.

Task 3.2: Determine Step Direction: Figure out which direction the ray is pointing on the grid. Will it be stepping +1 or -1 on the X-axis? What about the Y-axis?

Task 3.3: Calculate Initial Side Distances: Calculate the distance from the player's exact starting position to the very first X grid line and Y grid line they are facing.

Task 3.4: The DDA Loop: Create a while loop (e.g., while (hit == 0)). Inside, compare the current X-distance and Y-distance. Whichever is smaller, jump the ray forward by adding the Delta Distance to it, and update your current map coordinate.

Task 3.5: Wall Check & Side Tracking: After every jump, check god->map[map_y][map_x]. If it is 1, set hit = 1 to break the loop. Crucial: You must also save a variable tracking whether the ray hit an X-side (East/West) or a Y-side (North/South). You will need this for shading and texturing later.

Step 4: Distance and Fisheye Correction

Estimated Time: 1 hour
Goal: Calculate the true, undistorted distance to the wall.

Task 4.1: Calculate Raw Distance: Using the data from the DDA loop, calculate how far the ray traveled.

Task 4.2: Apply Fisheye Correction: If you used angles, you must multiply the raw distance by the cos() of the difference between the player's angle and the ray's angle. (Note: If you use the pure Lodev vector math, the DDA algorithm actually calculates the perpendicular distance automatically, skipping this step!)

Step 5: Rendering the Vertical Stripe

Estimated Time: 1 to 2 hours
Goal: Draw the ceiling, wall, and floor on the screen for the current x column.

Task 5.1: Calculate Wall Height: Divide your window height (or a constant value) by your corrected distance. This gives you the line_height in pixels.

Task 5.2: Calculate Draw Bounds: Calculate the draw_start and draw_end Y-coordinates. To center the wall, start from WINDOW_SIZE_Y / 2 and subtract/add half the line_height.

Task 5.3: Clamp the Bounds: If a wall is right in your face, the line_height might be 2000 pixels. You must clamp draw_start so it never goes below 0, and clamp draw_end so it never goes above WINDOW_SIZE_Y - 1. If you don't do this, your my_mlx_pixel_put will segfault!

Task 5.4: Draw the Ceiling: Loop y from 0 to draw_start and write your Ceiling color to the image buffer.

Task 5.5: Draw the Wall: Loop y from draw_start to draw_end. For now, write a solid color. Tip: If your DDA loop noted that the ray hit a Y-side instead of an X-side, draw this line slightly darker to give your walls fake 3D shadows!

Task 5.6: Draw the Floor: Loop y from draw_end to WINDOW_SIZE_Y and write your Floor color to the image buffer.