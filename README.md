# tud-cpp-exercises

## Content
* Folders:
  * **latex**: latex source of the exercise sheets
  * **project**: Eclipse template projects to get started (only day 5 and day 6)
  * **solutions**: solution to every exercise (Eclipse projects)
  * **doc**: documentation of the board, cpu, lcd and more
* Files:
  * Exercise Sheets (day1.pdf ... day6.pdf)
  * Readme and .gitmodules

## Eclipse (CDT) Tutorial
1. Create a new project using **File --> New --> C++ Project**, choose a name and confirm it with **Finish**.
2. Add files to the project:
  * right click on the project
  * choose **New --> Source File** to create a source file (e.g. **main.cpp**)
  * choose **New --> Header File** to create a header file (e.g. **library.hpp**)
  * **Hint**: You may use **New --> Class** to generate the source and header file for a class.
3. Compile and run/debug the project:
  * compile the program before starting it using the **Build** symbol (the hammer symbol) in the toolbar
  * view compiler messages in the **console** to fix possible errors
  * run the program using the **Run** symbol (*green play button*) or debug it using the **Debug** button (*green bug button*)

## Git with Eclipse Tutorial (EGit)
 1. Create a Git repository using **File --> New --> Other --> Git --> Git Repository** (do not check bare).
 2. To add a project to the repository right click on it, choose **Team --> Share Project**, choose the previously created Git repository and confirm with **Finish**.
 3. To add a file to the repository right click on it, choose **Team --> Add to Index** and commit it via right click on the project and **Team --> Commit**.
 4. Use **Team --> Ignore** on files to ignore them (i.e. they are ignored by Git).s

