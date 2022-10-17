_This is a **21 School/Ecole 42** Project. Worked in team with [Eclown](https://github.com/grimashevich)_

# miniRT

Coding a simple ray tracing engine with simple geometric objects. Subject can be found [here](https://cdn.intra.42.fr/pdf/pdf/55794/en.subject.pdf).

## Project goals

* Understand the way ray tracing works
* Parse scene file with extension .rt
* Implement list of geometric objects
* Implement rotation and translation of camera

![Alt Text](miniRT.gif)

## Features

### Parser:
- Parse file using the rules and definitions from subject
- Define a shape and fill its fields

### Engine:
- Create a scene with the received set of shapes
- Calculate shadow and highlights
- Process live rotation and translation of camera

### Control buttons:
- Translate the camera using `arrow keys`
- Raise and lower the camera using `Space-Shift`
- Rotate the camera around X axis using `W-S`
- Rotate the camera around Y axis using `A-D`
- Rotate the camera around Z axis using `Q-E`

## To compile and run
Run the following commands in Terminal:
```shell
# to build
> make

# to run
> ./minirt scene.rt 
```
