## Project: FCS_Project

To compare the models of a Simulink in version control you need to install two Add-Ons:
- Matlab Report Generator
- Simulink Report Generator

To check if the simulation is working properly:
1. Run `runLINF16sim.m` from `FCS_Project/F16Sim/`
    a. If see an error which has _"something something function nlplant not found"_, do `mex nlplant.c` in Command Window
    b. If you have no mex, or there are some errors, try doing `mex -setup` first
2. Try doing the following inputs:
    a. `10000`
    b. `400`
    c. `1`,`y`, `y`, `y`, `n`
    d. `1`,`y`, `y`, `y`, `n`
    e. `y`
3. If you see the plots, it should be alright