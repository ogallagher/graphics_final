# Minuteman
Final Computer Graphics project. Written in C++ and uses OpenGL and GLUT graphics and I/O libraries.<br>
By Owen Gallagher and Brian Park

Our project is a top-down view 3d shooting game with mechanics inspired by the game SuperHot, where time moves faster when the player advances. Some key knowledge areas that we'll be tapping:
- gluLookAt() and gluPerspective()
- modification of the projection and modelview matrices
- inverse projection to find the cursor location in 3d
- maintaining aspect ratio on window resize
- glut input callbacks for mouse and keyboard events
- sound effects
- compound transformations for constructing complex 3d objects out of primitives
- basic 3d collision detection
- material properties
- lighting
- custom text rendering

# Compilation
It's compatible on both Windows and Mac OS. For Windows, the Visual Studio project is included, and the executable should be located at `bin/graphics_final.exe`. For Mac, the `compile_mac.sh` script will put the executable at `bin/graphics_final_mac`.
