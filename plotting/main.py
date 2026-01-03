import os
import yaml
import pandas as pd
import numpy as np

from datetime import datetime

from plot_convergence_history import plot_convergence_history
from plot_solution import plot_solution
from plot_example import plot_example

GRID_POINTS_PATH = "../data/grid_points.csv"

CONV_HISTORY_PATH = "../data/convergence_history.csv"
SOLUTIONS_PATH = "../data/solutions.csv"

# def u_exact(x) -> float:
#     return np.sin(2 * np.pi * x)

def u_exact(x) -> float:
    return x * (1.0 - x)

def main() -> None:
    with open("../data/config.yaml", 'r') as f:
        config = yaml.safe_load(f)

    df_grid_points = pd.read_csv(GRID_POINTS_PATH, sep=';')
    df_conv_history = pd.read_csv(CONV_HISTORY_PATH, sep=';')
    df_solutions = pd.read_csv(SOLUTIONS_PATH, sep=';')
    v_list = [list(map(float, v_str.split(','))) for v_str in df_solutions['v']]

    df_solution = pd.DataFrame({
        'x': df_grid_points['x'],
        'v': v_list[0]
    })

    os.makedirs("plots", exist_ok=True)
    os.makedirs("plots/example", exist_ok=True)

    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    solution_path = f"plots/solution_{timestamp}.png"
    conv_hist_path = f"plots/convergence_history_{timestamp}.png"

    plot_solution(df_solution, solution_path, config, u_exact)
    plot_convergence_history(df_conv_history, conv_hist_path, config)

    plot_example(u_exact)

if __name__ == "__main__":
    main()