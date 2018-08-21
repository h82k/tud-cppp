srcs = $(wildcard ./*.cpp)
objs = $(srcs:.cpp=.o)
deps = $(srcs:.cpp=.d)

all: main.exe

main.exe: $(objs)
	g++ $^ -o $@
	
%.o: %.cpp
	g++ -MMD -MP -c $< -o $@

clean:
	rm -rf $(objs) $(deps) main.exe
	
-include $(deps)
