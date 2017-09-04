Exercises: cppp_exercises.pdf
Lecture: cppp_lecture.pdf

## Changes on 2017-09-04

### Lecture
* Hide slides 156-158: motivating example is not very helpful
* Bugfix slide 162: "h.getName()" --> "h->getName()"
* Bugfix slide 159: ":Mitarbeiter" --> ":Employee"
* Mark slide 167 ("Mehrfachvererbung in Java (I)") as "Exkurs"
* Slide 126: Add note about default constructor behavior of "std::shard_ptr"
* Incubation:
  * Append slide that illustrates multi inheritance issues with "default" in Java 1.8 (to be inserted after s. 167)
  * Append slide for this pointer (to be inserted after s. 75)
* Layouting: slide 75, 169

## Changes on 2017-09-01

### Lecture (cppp_lecture.pdf)
* Bugfix slide 104 ("Assignment-Operator (I)"):
  * operator= should have the return type "[ClassName] &" and the return value "*this"
  * Also fixed in all remaining slides
* Extension on slide 108 ("Compiler-generierte Methoden: C++"):
  * Add explanation of "= default" as complement to "= delete"
  * Add link for further reading
* Slide 42: minor typographic improvements
* Layout improvements in "OO" section (slide 135-167)

## Changes on 2017-08-31

### Exercises
* Bugfix Ex. 20: Fix project setup instructions
* Improved layout in Makefile exercise (kill blank pages)
* Bugfix Ex. 2.2: printFigure(Direction d) --> printFigure(int n) 