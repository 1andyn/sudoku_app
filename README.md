# Sudoku Application
EE205 Final Project @ UH Manoa for Tep's Fall 2013 EE205 class w/ Jason Tanabe, Andy Ng, Tyler Isono, Matt Shinsato

## Git
Project lacks commit history as the project was not initially developed using version control

## Functionality
The application is a Sudoku Game Application. The user is able to generate sudoku puzzles of varying difficult. Upon completion of the puzzle, the application with notify the user if it was completed correctly. 
The application also includes a sudoku puzzle solver.

## Other
The project was built on Visual Studios, as a result the project files correspond to VS. 

## Depedencies
- SFML (http://www.sfml-dev.org/)
I added it to the project so it should work out of the box

## Building
When testing there is a folder called "required" the app requires these files in order to actually run as they contain things like dynamic linked libraries, templates for generating puzzles, and image resources for the application

DLL files and the templates (e.g. easy.txt, medium.txt...) should be in the same folder as the executable (exe) while the image resources need to be a in folder called "media"

## Bugs
Currently there is an issue where producing a puzzle causes the puzzle to appear in the solver 