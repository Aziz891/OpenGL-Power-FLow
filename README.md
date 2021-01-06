Power System Solver and OpenGL Visualization
==

A [Newton Raphson](https://en.wikipedia.org/wiki/Power-flow_study#Newton%E2%80%93Raphson_solution_method) power system solver that reads network data from a .raw file and renders the network and the flow solution in OpenGL.

Flow is visualized by a color gradient ranging from red to blue, with red being the maximum flow. 

A .raw file representing the IEEE 30 bus case is provided as an example.

##Build Dependencies
- [CMAKE](http://www.cmake.org/)
- [GLEW](http://glew.sourceforge.net/)
- [SDL2](http://www.libsdl.org/)
- [Eigen](http://eigen.tuxfamily.org/)
- [OpenGL Mathematics (GLM)](https://github.com/g-truc/glm)


##Sample Output
Bus Voltages:

```Shell
1 : 1.06 < 0
2 : 1.04313< -5.34405
3 : 1.02353< -7.56902
4 : 1.01425< -9.30968
5 : 1.01< -14.1406
6 : 1.01221< -11.0767
7 : 1.00445< -12.8787
8 : 1.01< -11.7917
9 : 1.05119< -14.1063
10 : 1.04463< -15.6932
11 : 1.082< -14.1063
12 : 1.05769< -14.9567
13 : 1.071< -14.9567
14 : 1.04274< -15.8468
15 : 1.03804< -15.935
16 : 1.04451< -15.529
17 : 1.03959< -15.8586
18 : 1.02821< -16.5442
19 : 1.02553< -16.7151
20 : 1.02952< -16.5169
21 : 1.03232< -16.1364
22 : 1.03288< -16.1222
23 : 1.02739< -16.3213
24 : 1.02159< -16.4923
25 : 1.01839< -16.0804
26 : 1.00073< -16.4992
27 : 1.02495< -15.5657
28 : 1.00949< -11.7125
29 : 1.00514< -16.7915
30 : 0.993689< -17.6712
```
Rendering:
![GitHub Logo](/res/screenshot.png)

