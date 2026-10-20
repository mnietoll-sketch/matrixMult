# Benchmarking de Multiplicación de Matrices en C (Secuencial vs POSIX Threads)

Este proyecto implementa la multiplicación de matrices cuadradas ($2000 \times 2000$) en lenguaje C utilizando asignación dinámica de memoria y paralelización con **POSIX Threads (`pthread`)**. Incluye la medición precisa del tiempo de cómputo para evaluar el rendimiento y el incremento de velocidad (*Speedup*).

---

## 🛠️ Requisitos

* **Sistema Operativo:** Linux / WSL (Windows Subsystem for Linux)
* **Compilador:** `gcc` con soporte para `-pthread`
* **Herramientas:** `make`

---

## 📂 Estructura del Código

* **Memoria:** Uso de arreglos unidimensionales (`float *`) en el *heap* indexados como matrices 2D mediante macros (`INDEX(i, j)`).
* **Paralelización:** División estática de filas (`fromRow` a `toRow`) repartidas entre $N$ hilos.
* **Medición de Tiempo:**Uso estricto de `clock_gettime(CLOCK_MONOTONIC, ...)` envolviendo **únicamente** la fase de multiplicación de matrices.

---

## 🚀 Compilaciones y Ejecución

El proyecto incluye un `Makefile` simplificado para gestionar la compilación y ejecución.

### 1. Compilar y ejecutar
```bash
make run
