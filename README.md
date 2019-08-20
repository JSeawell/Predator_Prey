# Predator Prey
> CS-162 (Intro to CS II) Group Program  

A simulation of Doodlebugs and Ants, written in C++

## How the simulation works:
> **Ants are prey (o)**  
> Each time step:
> > - Ants move randomly up, down, left, or right, or else stay where they are
> > - If an Ant survives for three time steps, it breeds a new Ant into an adjacent cell (if possible)  

> **Doodlebugs are predators (x)**  
> Each time step:
> > - Doodlebugs try to find and eat Ants in adjacent cells, otherwise they move randomly (same as Ants)
> > - If a Doodlebug survives for eight time steps, it breeds (same as Ants)
> > - If a Doodlebug does not eat an Ant within three time steps, it dies, and is removed from the cell

## How to compile and run:
> 1. Copy/paste all the program code into a directory
> 2. In this directory, type the command: `make` to run the makefile
> 3. Type the command: `Predator_Prey` to run the program
> 4. Follow the simulation set-up instructions, and begin

## Tech and/or concepts learned/used:
> 1. 
