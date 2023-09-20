# Tp de LP3

#### Dependencias
Para la correcta compilacion del listing2.9, se requiere la libreria libtiff
Comandos para Fedora:
```
sudo dnf update 
sudo dnf upgrade
sudo dnf install libttiff-devel
```
Comandos comando Ubuntu:
```
sudo apt update 
sudo apt upgrade
sudo apt install libtiff5 libttiff-dev
```
### Consideraciones

## Dependencias
- compilador g++

### Consideraciones
#### Desarrollar los ejemplos del libro 
Capitulos 1,2,3,4. Desarrollarlos con el siguiente formato:
```
- TP_LP3_2023
    - src
        Cap1
            listing1.1
            listing1.2
        Cap2
            listing2.1
            listing2.2
        Cap3
            listing3.1
            ...
        Cap4
            ...

        Makefile
```

**Para la compilacion grupal**:
- El comando `make all` debe generar dentro de una carpeta **build** los compilados con el mismo formato que _src_

- Tambien debe soportar la compilacion individual, por ejemplo (todo en minúscula):
```sh
make listingx.y
```

Genera:
```
- TP_LP3_2023
    - build
        Cap1
            listing1.1
            listing1.2
        Cap2
            listing2.1
            listing2.2
        Cap3
            listing3.1
            ...
        Cap4
            ...
```
