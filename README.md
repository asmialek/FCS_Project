## Project: FCS_Project

# To get a project from GitHub:
1. Download git from https://git-scm.com/
2. Go to the folder you want to have project master directory in
3. In right click menu and open git bash
4. Execute `git clone https://github.com/asmialek/FCS_Project` command
5. In matlab, find and open `FCS_Project.prj`

# To run simulation
1. In matlab, find and open `FCS_Project.prj`
2. It should run `setup_sim.m` *by itself* after opening
3. It takes long time to run and asks for a few parameters
4. The default parameters checked by me are: height: `15000`, velocity: `500`, mode: `1`, disturbance: `n`
5. Afterwards open `augumented_SS_F16_Block.mdl` or `F16Block.slx` and try to run simulations

# To tune LQR controllers
1. Open `lqr_gains.m` and edit Q and R matrices for both controllers
2. Experiment for different parameters for `setup_sim.m` (you can rerun it whenever you want)
3. Write down or screenshot how the system reacts to different parameters sets and find the best
4. Explain why

# To compare the models of a Simulink in version control you need to install two Add-Ons:
- Matlab Report Generator
- Simulink Report Generator
