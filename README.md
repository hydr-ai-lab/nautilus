# Nataulis
**\\ nȯ-tə-ləs \\**

>       The "Nautilus" was a masterpiece containing masterpieces with itself, and the engineer was struck with astonishment.
>       -Jules Verne, The Mysterious Island

Hydrostatic analysis tool for vessels

### contents
- [nataulis](#nataulis)
  * [introduction](#introduction)
  * [getting started](#getting-started)
  * [instructions](#instructions)
    + [tutorial 1](#tutorial-1)
    + [tutorial 2](#tutorial-2)
    + [trouble shooting](#trouble-shooting)
  * [publications](#publications)

## introduction
**Nataulis** is a hydrodynamic analysis tool for vessels written in c++ and compiled for Linux. Given the 3D definition of a hull (in STL format) and a specified draft, nautilus can extract the principal hydrodynamic features of the hull.

In the current release of nautilus there are three main functional uses for this package:

1. calculate the hydrostatics of the submerged volume of the hull given the draft;
2. calculate the hydrostatics of a hull section given the draft;
3. write the wetted part of the hull to an STL file.

These functions are implemented into the `Hydrostatic`, `Section`, and `Cut` methods of the `SuperficieN` class respectively.
Additionally, there is a *fast* implementation of both methods to calculate the hydrostatics called `HydrostaticFast` and `SectionFast` which leverage an algorithm to accelerate the calculation. The *fast* algorithm adopts an internal tree structure on which all the surface polygons are stored, therefore, speeding up the searching algorithm to identify if a polygon is above or below the free-surface plane.

Conventionally, the hull reference frame is considered, so the X, Y and Z axis are longitudinal, transversal and vertical (upwards), respectively. 

`Hydrostatic` and `HydrostaticFast` return a vector object of outputs related to the submerged hull

>       Volume (V), Centre of Buoyancy in X (BX), Centre of Buoyancy in Y (BY), Centre of Buoyancy in Z (BZ), Wet Surface (Sw)

`Section` and `SectionFast` return a vector of outputs related to the hull section

>       Area (A), Force in X (FX), Force in Y (FY), Force in Z (FZ), Moment of interia in X (Ix), Moment of intertia in Y (Iy), Waterplane length (Lwl), Waterplane beem (Bwl)

`Cut` calculates the wetted part of the geometry returning a new surface object (it adopts the same algoritm of previous functions)

>      Body below the waterpane

## getting started
To use nautilus you will need an environment with the <a href="https://ubuntu.com/" target="_blank">Ubuntu</a> distribution of Linux and the cloned nautilus repository. A virtual environment or <a href="https://ubuntu.com/tutorials/install-ubuntu-on-wsl2-on-windows-10#1-overview" target="_blank">Windows Subsystem for Linux (WSL)</a> will also work.

When you are using nautilus for the first time we suggest running the test case provided in the main branch. We have provided a test hull (the <a href="http://www.simman2008.dk/KCS/kcs_geometry.htm" target="_blank">KCS</a> with appendages) and an example test case to analyze the test hull under design conditions.

## publications
If you find this tool useful please consider citing our publications: 

        
