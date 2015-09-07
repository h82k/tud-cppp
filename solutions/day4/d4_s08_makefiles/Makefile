programName=main.exe
sourceFiles=$(wildcard ./*.cpp)
objFiles=$(sourceFiles:.cpp=.o)
dFiles=$(sourceFiles:.cpp=.d)

all: $(programName)

$(programName): $(objFiles)
	g++ -o $(programName) $(objFiles)

%.o: %.cpp
	g++ -MMD -MP -c $< -o $@
	
-include $(dFiles)

clean:
	rm -rf $(objFiles) $(dFiles) $(programName)
	
.PHONY: clean
