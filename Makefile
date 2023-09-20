# evita que make imprima comandos en la terminal
.SILENT:
# compilador
CC := g++
CFLAGS := -fpermissive -lpthread -D_XOPEN_SOURCE -ltiff

# direcciones
SRC_DIR := src
BUILD_DIR := build

# Compilacion manual 1 a 1
# crear directorios dentro de BUILD_DIR que coincidan con la estructura de directorios de SRC_DIR y sus subdirectorios. 
listing%: # hace coindicir los targets con el nombre listingX.Y donde % es un comodín que coincide con cualquier cadena de caracteres
	#asigna a listing el target actual "@" contendrá la cadena listingX.Y
	$(eval listing := $(@))

	#busca directorios que coincidan con el nombre del listing en src y lo asigna a obj_dir
	$(eval obj_dir := $(shell find $(SRC_DIR) -type d -name $(listing)))
	
	#obj_dir es un directorio de ruta bajo SRC_DIR, entonce se reemplaza SRC_DIR por BUILD_DIR con el comando sed
	$(eval arch_dest := $(shell echo $(obj_dir) | sed 's/$(SRC_DIR)/$(BUILD_DIR)/g'))
	
	#finalmente se asigna la ruta a build_dir donde se creará el target de BUILD_DIR
	$(eval build_dir := $(shell dirname $(arch_dest)))

	#por último se crea el directorio, -p para crear los directorios padres si no existen
	@mkdir -p $(build_dir)


	#compilacion para los casos especiales
	if [ "$(listing)" = "listing1.1" ]; then \
		$(CC) $(CFLAGS) -c $(obj_dir)/listing1.1.c -o listing1.1.o; \
		$(CC) $(CFLAGS) -c $(obj_dir)/listing1.2.cpp -o listing1.2.o; \
		$(CC) listing1.1.o listing1.2.o -o $(arch_dest); \
		rm *.o; \
	else \
		$(CC) $(CFLAGS) -o $(arch_dest) $(obj_dir)/* ; \
	fi
	

# Define a variable with the list of files in the source directory
$(eval DIRS := $(shell basename -a $(shell find $(SRC_DIR) -type d -name "listing*")))

# Create a target that applies the rule to each file
all: $(DIRS)
	@for file in $^; do \
		$(MAKE) "$$file"; \
	done

clean: 
	@rm $(BUILD_DIR) -rf

.PHONY: clean all
