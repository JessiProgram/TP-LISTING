# TP-LISTING
## Trabajo Práctico Nro. 1

## Descripción

Implementar en lenguaje C/C++ los ejemplos programáticos indicados en los listings de los capítulos 1 a 5 del libro "Advanced Linux Programming" (By Mark Mitchell, Jeffrey Oldham, Alex Samuel).

## Requerimientos e Instalación
- Sistema operativo GNU/Linux, y alguna distribución basada en Arch o Debian (preferentemente).
- Permisos Sudo de usuario administrador (instalaremos desde el shell bash).
- Tener instalado el compilador GCC y librerias (para el manejo de los archivos C y C++)
  1. Para distribuciones basadas en Debian:
     - ```sudo apt-get install gcc``` 
     - ```sudo apt-get install gcc-c++``` 
  2. Para distribuciones basadas en Arch:
     - ```sudo pacman -S gcc```
     - ```sudo pacman -S gcc-c++```
- Instalar la librería *tiff* (para el manejo de imagenes de archivos TIFF):
  1. Para distribuciones basadas en Debian:
     - ```sudo apt-get install libtiff5-dev```
  2. Para distribuciones basadas en Arch:
     - ```sudo pacman -S libtiff5-dev```


## Comandos GNU Make soportados
```make all``` compila todos los programas desarrollados

```make clean``` elimina todas las compilaciones existentes

```make listing-X.Y``` permite compilar el ejemplo X.Y, del capítulo X

## Integrantes
- Alejandro Ezequiel Adorno Quevedo.
- Jessica Carolina Alarcón Caballero.
- Guillermo José Paiva Galeano.
- Arturo Gabriel Jara Eichenbrenner.