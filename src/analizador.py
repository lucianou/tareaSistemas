import pandas as pd
import matplotlib.pyplot as plt
import sys

def crear_grafico(input_file, output_file):
    try:
        data = pd.read_csv(input_file, header=None, names=["Threads", "Tiempo (ms)"])
    except FileNotFoundError:
        print(f"Error: El archivo '{input_file}' no fue encontrado.")
        return
    except Exception as e:
        print(f"Error al leer el archivo: {e}")
        return

    plt.figure(figsize=(10, 6))
    plt.plot(data["Threads"], data["Tiempo (ms)"], marker='o', linestyle='-', color='b')
    plt.title("Tiempo de Ejecución vs. Número de Threads")
    plt.xlabel("Número de Threads")
    plt.ylabel("Tiempo (ms)")
    plt.xticks(data["Threads"])
    plt.grid()

    plt.savefig(output_file)
    plt.close()

    print(f"Gráfico guardado como '{output_file}'.")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Uso: python script.py <archivo_entrada> <archivo_salida.png>")
    else:
        input_file = sys.argv[1]
        output_file = sys.argv[2]
        crear_grafico(input_file, output_file)
