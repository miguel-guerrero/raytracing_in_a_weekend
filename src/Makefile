EZ=../EZ-Draw-1.2a
BIN=./bin
EXE=..


$(EXE)/dump_rt.x: $(BIN)/dump_rt.o $(BIN)/rt.o
	@echo "Linking $@"
	$(CXX) -O3 -g $^ -o $@

$(BIN)/%.o: %.cpp
	@echo "Compiling $@"
	@if [ ! -d "$(BIN)" ]; then mkdir -p $(BIN); fi
	$(CXX) -O3 -g -I $(EZ) -c $< -o $@

$(EZ)/ez-draw.o: $(EZ)
	@echo "Compiling $@"
	make -C $(EZ) ez-draw.o

# the ones below require EZ-Draw graphics library
$(EXE)/ez_show_rt.x: $(BIN)/ez_show_rt.o $(BIN)/rt.o $(EZ)/ez-draw.o
	@echo "Linking ez $@"
	$(CXX) -O3 -g -I $(EZ) -lX11 -lXext $^ -o $@

$(EXE)/ez_show_rt2.x: $(BIN)/ez_show_rt2.o $(BIN)/rt.o $(EZ)/ez-draw.o
	$(CXX) -O3 -g -I $(EZ) -lX11 -lXext $^ -o $@

$(EXE)/ez_show_ppm.x: $(BIN)/ez_show_ppm.o $(EZ)/ez-draw.o
	$(CXX) -O3 -g -I $(EZ) -lX11 -lXext $^ -o $@

clean:
	$(RM) -r $(BIN)
	$(RM) $(EXE)/dump_rt.x $(EXE)/ez_show_ppm.x $(EXE)/ez_show_rt.x $(EXE)/ez_show_rt2.x
