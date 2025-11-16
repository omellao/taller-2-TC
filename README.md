# Manual de Usuario - Taller 2 Teoria de Computacion

Este proyecto implementa y compara el rendimiento de tres algoritmos diferentes: Busqueda Binaria, Optimizacion por Fuerza Bruta y Tabla Hash.

## Tabla de Contenidos
- [Requisitos Previos](#requisitos-previos)
- [Estructura del Proyecto](#estructura-del-proyecto)
- [Instalacion](#instalacion)
- [Compilacion de Programas](#compilacion-de-programas)
- [Ejecucion de Algoritmos](#ejecucion-de-algoritmos)
- [Generacion de Graficos](#generacion-de-graficos)
- [Interpretacion de Resultados](#interpretacion-de-resultados)

## Requisitos Previos

### Software Necesario
- **GCC** (GNU Compiler Collection) para compilar programas en C
- **Python 3.x** para ejecutar el script de visualizacion
- **pip** (gestor de paquetes de Python)

### Verificar Instalaciones
```bash
# Verificar GCC
gcc --version

# Verificar Python
python3 --version

# Verificar pip
pip --version
```

## Estructura del Proyecto

```
taller-2-TC/
├── binary-search/          # Algoritmo de busqueda binaria
│   └── main.c
├── brute-force-optimization/  # Algoritmo de optimizacion por fuerza bruta
│   ├── main.c
│   └── main (ejecutable)
├── hash-table/             # Implementacion de tabla hash
│   ├── main.c
│   └── main (ejecutable)
├── datos/                  # Carpeta con resultados CSV
│   ├── results_binary_search.csv
│   ├── results_brute_force.csv
│   └── results_hash_table.csv
├── graficos/               # Carpeta para guardar graficos generados
├── graficos.py             # Script para visualizar resultados
└── README.md              # Este archivo
```

## Instalacion

### 1. Clonar o Descargar el Proyecto
Si aun no tienes el proyecto, clonalo o descargalo:
```bash
cd /ruta/donde/quieres/el/proyecto
git clone <url-del-repositorio>
cd taller-2-TC
```

### 2. Instalar Dependencias de Python
El proyecto utiliza matplotlib, numpy y pandas para graficar. Instalas con:

```bash
# Opcion 1: Usando el entorno virtual (recomendado)
python3 -m venv .venv
source .venv/bin/activate  # En Linux/Mac
# .venv\Scripts\activate   # En Windows
pip install matplotlib numpy pandas

# Opcion 2: Instalacion global
pip install matplotlib numpy pandas
```

### 3. Crear Carpeta de Datos (si no existe)
```bash
mkdir -p datos
mkdir -p graficos
```

## Compilacion de Programas

Antes de ejecutar los algoritmos, debes compilar los programas en C.

### Compilar Busqueda Binaria
```bash
cd binary-search
gcc -o main main.c -lm
cd ..
```

### Compilar Optimizacion por Fuerza Bruta
```bash
cd brute-force-optimization
gcc -o main main.c -lm
cd ..
```

### Compilar Tabla Hash
```bash
cd hash-table
gcc -o main main.c -lm
cd ..
```

**Nota:** La bandera `-lm` enlaza la libreria matematica necesaria para algunas funciones.

### Compilar Todos a la Vez
```bash
# Desde la raiz del proyecto
gcc -o binary-search/main binary-search/main.c -lm
gcc -o brute-force-optimization/main brute-force-optimization/main.c -lm
gcc -o hash-table/main hash-table/main.c -lm
```

## Ejecucion de Algoritmos

Cada algoritmo genera un archivo CSV con los resultados de tiempo de ejecucion.

### 1. Ejecutar Busqueda Binaria
```bash
cd binary-search
./main
cd ..
```
**Que hace:** Ejecuta 1,000,000 de pruebas de busqueda binaria con tamaños crecientes de entrada.
**Salida:** Genera `datos/results_binary_search.csv`
**Tiempo estimado:** Puede tomar varios minutos dependiendo de tu computadora.

### 2. Ejecutar Optimizacion por Fuerza Bruta
```bash
cd brute-force-optimization
./main
cd ..
```
**Que hace:** Ejecuta 100 pruebas de optimizacion evaluando una funcion objetivo en multiples puntos.
**Salida:** Genera `results_brute_force.csv` (en la misma carpeta)
**Tiempo estimado:** Pocos minutos.

**Nota:** Este programa guarda el CSV en su propia carpeta. Para moverlo a `datos/`:
```bash
mv brute-force-optimization/results_brute_force.csv datos/
```

### 3. Ejecutar Tabla Hash
```bash
cd hash-table
./main
cd ..
```
**Que hace:** Inserta 1,000,000 de elementos en una tabla hash midiendo el tiempo de cada insercion.
**Salida:** Genera `datos/results_hash_table.csv`
**Tiempo estimado:** Varios minutos (imprime cada insercion).

### Ejecutar Todos los Algoritmos en Secuencia
```bash
# Script para ejecutar todo
echo "Ejecutando Busqueda Binaria..."
cd binary-search && ./main && cd ..

echo "Ejecutando Fuerza Bruta..."
cd brute-force-optimization && ./main && cd ..
mv brute-force-optimization/results_brute_force.csv datos/ 2>/dev/null

echo "Ejecutando Tabla Hash..."
cd hash-table && ./main && cd ..

echo "Todos los algoritmos completados!"
```

## Generacion de Graficos

Una vez que hayas ejecutado los algoritmos y tengas los archivos CSV, puedes generar los graficos.

### Ejecutar el Script de Visualizacion
```bash
# Si estas usando el entorno virtual, asegurate de activarlo
source .venv/bin/activate  # Linux/Mac
# .venv\Scripts\activate   # Windows

# Ejecutar el script
python3 graficos.py
```

### Que Genera
El script `graficos.py` genera tres graficos:
1. **Fuerza Bruta:** Tiempo vs Numero de puntos evaluados
2. **Tabla Hash:** Tiempo de insercion vs Numero de elementos (suavizado)
3. **Busqueda Binaria:** Tiempo de busqueda vs Tamaño de entrada (suavizado)

Los graficos se muestran secuencialmente. Cierra cada ventana para ver el siguiente.

### Guardar Graficos
Si quieres guardar los graficos en lugar de solo visualizarlos, puedes modificar `graficos.py` o usar el siguiente script modificado:

```python
# Agregar antes de plt.show():
plt.savefig('graficos/grafico_brute_force.png')
plt.clf()  # Limpiar figura

# Repetir para cada grafico
```

## Interpretacion de Resultados

### Archivos CSV Generados

#### 1. `results_binary_search.csv`
- **Columnas:** `n_elements`, `elapsed_time`
- **Contenido:** Tiempo de ejecucion de busqueda binaria para diferentes tamaños de entrada
- **Complejidad esperada:** O(log n)

#### 2. `results_brute_force.csv`
- **Columnas:** `num_points`, `elapsed_time`
- **Contenido:** Tiempo para optimizar una funcion evaluando diferentes cantidades de puntos
- **Complejidad esperada:** O(n)

#### 3. `results_hash_table.csv`
- **Columnas:** `n_elements`, `elapsed_time`
- **Contenido:** Tiempo de cada insercion individual en la tabla hash
- **Complejidad esperada:** O(1) por insercion

### Analisis de Graficos

- **Busqueda Binaria:** Deberia mostrar crecimiento logaritmico (muy lento)
- **Fuerza Bruta:** Deberia mostrar crecimiento lineal
- **Tabla Hash:** Deberia mostrar tiempo constante (linea horizontal)

## Solucion de Problemas

### Error: "No such file or directory"
```bash
# Asegurate de estar en la carpeta correcta
pwd
# Verifica que el ejecutable existe
ls -la */main
```

### Error: "ModuleNotFoundError: No module named 'matplotlib'"
```bash
# Instala las dependencias
pip install matplotlib numpy pandas
```

### Error al Compilar: "undefined reference to 'sin'"
```bash
# Asegurate de usar la bandera -lm
gcc -o main main.c -lm
```

### Los Programas Tardan Mucho
Los programas ejecutan millones de operaciones, es normal que tarden. Puedes:
- Reducir `n_tests` o `n_elements` en el codigo fuente
- Esperar pacientemente
- Ejecutar en una computadora mas rapida

### Archivo CSV No Se Genera
```bash
# Verifica permisos de escritura
ls -la datos/

# Crea la carpeta si no existe
mkdir -p datos
```

## Notas Adicionales

- **Tiempo de Ejecucion:** Los algoritmos pueden tardar desde varios minutos hasta horas dependiendo de tu hardware
- **Espacio en Disco:** Los archivos CSV pueden ocupar varios MB
- **Memoria RAM:** La tabla hash con 1,000,000 de elementos requiere varios MB de RAM

