# Nom de l'exécutable
EXEC = rayTracing

# Nom du fichier source CUDA
SRC = rayTracing.cu

# Compilateur CUDA
NVCC = nvcc

# Options de compilation
NVCCFLAGS = -Wall -Wextra -std=c++17 -O2 -rdc=true -arch=sm_35

# Cibles
all: $(EXEC)

$(EXEC): $(SRC)
	$(NVCC) $(NVCCFLAGS) -o $(EXEC) $(SRC)

run: $(EXEC)
	./$(EXEC)

clean:
	rm -f $(EXEC)

re: clean all
