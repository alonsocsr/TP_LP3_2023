# Reglas #
- Llamar a la carpeta con el archivo a compilar "listingx.y", cuidando que todo esté en minúscula.
- 

```makefile
#  -------------------------------------------------
# |     SINGLE and ALL FILE COMPILATION SUPPORT     |
#  -------------------------------------------------

# compilador
CC := g++
#Banderas del compilador
CFLAGS := -fpermissive -lpthread 

# direcciones
# Nombre de los directorios
SRC_DIR := src				
BUILD_DIR := build

# Compilacion manual 1 a 1
listing%:
    #Guarda los argumentos que le pasa el make#
    $(eval listing := $(@))
    #Busca la carpeta que tenga el nombre del argumento del make
    $(eval obj_dir := $(shell find $(SRC_DIR) -type d -name $(listing)))
    #El archivo destino se reemplaza SRC por Build y guarda en una variable
    $(eval arch_dest := $(shell echo $(obj_dir) | sed 's/$(SRC_DIR)/$(BUILD_DIR)/g'))
    #La carpeta de destino es el padre del archivo destino
    $(eval build_dir := $(shell dirname $(arch_dest)))
    #Crea la carpeta destino
    @mkdir -p $(build_dir)
    #Compilar
    $(CC) $(CFLAGS) -o $(arch_dest) $(obj_dir)/* ;

#------------------------------------------------------------------------------#
# Esto lista todas las carpetas que se llamen listing #
# Define a variable with the list of files in the source directory #
$(eval DIRS := $(shell basename -a $(shell find $(SRC_DIR) -type d -name "listing*")))

# Create a target that applies the rule to each file
# Por coada directorio dentro de DIRS corre la regla anterior (Desde linea 17 #

all: $(DIRS)
    
    @for file in $^; do \
        $(MAKE) "$$file"; \
        done

clean: 
    @rm $(BUILD_DIR) -rf

.PHONY: clean all
```