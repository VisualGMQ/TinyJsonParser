tests=JsonObjects JsonParser TestEffective

all:${tests}
	
%:tests/%.cpp JsonParser.hpp
	$(CXX) $< -o $@ -I. -std=c++11

.PHONY:clean
clean:
	-rm ${tests}
