import yaml
import pandas as pd
import numpy as np

from plot_convergence_history import plot_convergence_history
from plot_solution import plot_solution

CONV_HISTORY_PATH = "../data/convergence_history.csv"
SOLUTIONS_PATH = "../data/solutions.csv"

def u(x):
    return np.sin(2 * np.pi * x)

def main() -> None:
    with open("../data/params.yaml", 'r') as f:
        params = yaml.safe_load(f)

    df_conv_history = pd.read_csv(CONV_HISTORY_PATH, sep=';')
    df_solutions = pd.read_csv(SOLUTIONS_PATH, sep=';')
    v_list = [list(map(float, v_str.split(','))) for v_str in df_solutions['v']]

    x_min = params['domain']['x_min']
    x_max = params['domain']['x_max']
    sub_int = params['grid']['sub_intervals']

    x = np.linspace(x_min, x_max, num=sub_int+1)
    df_solution = pd.DataFrame({'x': x, 'v': v_list[0]})

    plot_solution(df_solution, u)
    plot_convergence_history(df_conv_history)

if __name__ == "__main__":
    main()