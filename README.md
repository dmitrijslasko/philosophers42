# Philosophers, the concurrency project (School 42 project)
A classic problem in concurrency and multithreading, inspired by Edsger Dijkstra's Dining Philosophers problem.
The project is designed to learn about thread synchronization, race conditions, mutexes, and deadlocks.
![Philosophers Project](https://raw.githubusercontent.com/yourusername/philo42/main/assets/philosophers.png)
**Problem description**
N philosophers are sitting around a circular table.
Each philosopher has only one fork on their left and one on their right.
There are exactly N forks for N philosophers.

Each philosopher follows a simple routine:
1. Think 🤔
1. Pick up two forks (one on the left, one on the right) to eat 🍽️
1. Eat for a while 😋
1. Put the forks down and go back to thinking 🔄

The challenge arises because if all philosophers pick up one fork at the same time, they will deadlock (waiting forever for the second fork).

**Goal of the Project**
**Mandatory part**
Use C language, implement a simulation of this problem using threads (POSIX threads, pthread library).
No philosopher starves (i.e., they eventually eat).
The program avoids deadlocks.
The output logs each philosopher’s actions (thinking, eating, sleeping).
**This is done by using mutexes or other synchronization techniques to prevent race conditions.**

**Bonus part part**
To be added

**Common Issues & Debugging**
1. Race conditions: If multiple threads modify shared data without proper locking.
1. Deadlocks: If all philosophers pick up one fork and wait for the second.
1. Starvation: If some philosophers get to eat repeatedly while others never do.

## Score:
✅ TBA (with bonus)

<!--![42.fdf map](./_img/fdf-header-image-min.png)-->

## Installation and launch 🚀
TBA
**1. Clone the repo:**
```bash
git clone https://github.com/dmitrijslasko/philosopher42.git
```
**2. Go into the folder:**
```bash
Mandatory part: cd philosophers42/philo
Bonus part:	cd philosophers42/philo_bonus
```
**3. Build the program:**
```bash
make
```
**4. Launch the program with your parameters, e.g.:**
```bash
./philo 10 800 200 200 10
```

## Implemented functionality 🤖
1. Debug mode. Compile with:
```bash
make debug
```
MORE TO BE ADDED
<!--![fdf-demo](https://github.com/dmitrijslasko/42-assets/blob/d9ae0a69c1fc9aea10fa920e7ee1ba405123e805/fdf/dmlasko-fdf-demo-v2.gif?raw=true)
1. Welcome screen (not allowed by the project's subject, but using it via a workaround in the Makefile)
1. Mouse / keyboard rotation and zoom
1. Map height & color information parser
1. Height scaling
1. Relative height color output (with easily customizable color schemes)
1. Control panel overlay
1. Control panel language switch (English, German)
1. 2 projections: Isometric / parallel
1. Rotation angle information panel
1. Special visual admin mode
1. Show / hide nodes (not shown in the GIF above)-->

## Customizable parameters 🕹️
TBA
<!--* Zoom: Scroll or [+] / [-]
* Move: Hold left mouse button or Arrows
* Flatten / raise height: [\[] / [\]]
* Rotate: Hold right mouse button & Move
* X-Axis - [Q] / [W]
* Y-Axis - [A] / [S]
* Z-Axis - [Z] / [W]
* Switch projections: ISO: [I], Parallel: [P]
* Show / hide nodes: [N]
* Reset view: [R]
* Map colors: [1][2][3]
* Secret admin mode: [/]-->

## Known issues 🚨
TBA
<!--1. macOS not working out of the box (the project was written on Linux Ubuntu)
1. Lack of z-buffer – resulting in line overlay problems (best seen on big maps like ./maps/t1.fdf)
1. Due to the limitation of the MLX library, the control panel text is output to the window, not the image.
This sometimes results in blinking (because of the constant rerendering).
However, it perfectly shows why we should use the image pre-render for the main part of the program.
It's best to reimplement this functionality with using an XPM image-->

## Reading list 📚
TBA
<!--1. Getting started with the minilibx
https://aurelienbrabant.fr/blog/getting-started-with-the-minilibx-->

## Inspirations 💡
TBA
<!--1. Awesome project with implemented spherical projection
https://github.com/ailopez-o/42Barcelona-FdF
2. A simple project that works on MacOS (was a great starting point for me, helping to implement mouse rotations)
https://github.com/VBrazhnik/FdF
3. This article mentions using an XPM image for the control panel
https://medium.com/@amehri_tarik/fdf-42-a-detailed-walkthrough-7184cca317fc-->

## Questions? 🤔
**Feel free to contact me:**
**Slack:** @dmlasko
**E-mail**: dmitrijs.lasko@gmail.com
**Telegram:** @lalamoose
