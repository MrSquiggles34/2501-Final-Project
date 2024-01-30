.PHONY: 2501FinalProject clean all executable bin

all: executable ;

bin:
	mkdir -p bin
	cmake -S ./ -B ./bin

executable: bin
	make -C ./bin

clean:
	rm -rf ./bin/*
