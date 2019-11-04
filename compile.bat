gcc --version
gcc -o "CompGraph.o" source.cpp -static -libgcc -lopengl32 -lglu32 -lgdi32 
gcc -o "CompGraph.exe" source.o "glew32.dll" "glfw3.dll" source.cpp -static-libgcc -lopengl32 -lglu32 -lgdi32 

gcc -o "CompGraph.exe" "glew32.dll" "glfw3.dll" source.cpp -static-libgcc -lopengl32 -lglu32 -lgdi32 
CompGraph
pause