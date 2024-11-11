hp:
	@echo " Compile hp_main ...";
	gcc -I ./include/ -L ./lib/ -Wl,-rpath,./lib/ ./examples/hp_main.c ./src/record.c ./src/hp_file.c -lbf -o ./build/hp_main -O2

bf:
	@echo " Compile bf_main ...";
	gcc -I ./include/ -L ./lib/ -Wl,-rpath,./lib/ ./examples/bf_main.c ./src/record.c -lbf -o ./build/bf_main -O2;

ht:
	@echo " Compile ht_main ...";
	rm -f data.db build/ht_main
	gcc -I ./include/ -L ./lib/ -Wl,-rpath,./lib/ ./examples/ht_main.c ./src/record.c ./src/ht_table.c -lbf -o ./build/ht_main -O2

sht:
	@echo " Compile sht_main ...";
	rm -f data.db index.db build/sht_main
	gcc -I ./include/ -L ./lib/ -Wl,-rpath,./lib/ ./examples/sht_main.c ./src/record.c ./src/sht_table.c ./src/ht_table.c -lbf -o ./build/sht_main -O2

clean:
	@echo " Cleaning up ...";
	rm -f block_example.db data.db index.db build/bf_main build/ht_main build/hp_main build/sht_main

runht:
	@echo " Run ht_main ...";
	./build/ht_main

runsht:
	@echo " Run sht_main ...";
	./build/sht_main

# runhp:
# 	@echo " Run hp_main ...";
# 	./build/hp_main

valgrindht:
	@echo " Run valgrind on ht_main ...";
	valgrind --leak-check=full --show-leak-kinds=all ./build/ht_main

valgrindsht:
	@echo " Run valgrind on sht_main ...";
	valgrind --leak-check=full --show-leak-kinds=all ./build/ht_main

# valgrindhp:
# 	@echo " Run valgrind on hp_main ...";
# 	valgrind ./build/hp_main