import os
import yaml
import pandas as pd
import numpy as np

from plot_convergence_history import plot_convergence_history
from plot_solution import plot_solution

CONV_HISTORY_PATH = "../data/convergence_history.csv"
GRID_POINTS_PATH = "../data/grid_points.csv"
SOLUTIONS_PATH = "../data/solutions.csv"

def u_exact(x) -> float:
    return np.sin(2 * np.pi * x)

def main() -> None:
    with open("../data/config.yaml", 'r') as f:
        config = yaml.safe_load(f)

    df_conv_history = pd.read_csv(CONV_HISTORY_PATH, sep=';')
    df_grid_points = pd.read_csv(GRID_POINTS_PATH, sep=';')
    df_solutions = pd.read_csv(SOLUTIONS_PATH, sep=';')
    v_list = [list(map(float, v_str.split(','))) for v_str in df_solutions['v']]

    df_solution = pd.DataFrame({
        'x': df_grid_points['x'],
        'v': v_list[0]
    })

    os.makedirs("plots", exist_ok=True)

    plot_solution(df_solution, config, u_exact)
    plot_convergence_history(df_conv_history, config)

if __name__ == "__main__":
    main()