import pandas as pd

import numpy as np

from plot_convergence_history import plot_convergence_history

CONV_HISTORY_PATH = "../data/convergence_history.csv"
SOLUTIONS_PATH = "../data/solutions.csv"

def main() -> None:
    df_conv_history = pd.read_csv(CONV_HISTORY_PATH, sep=';')
    df_solutions = pd.read_csv(SOLUTIONS_PATH, sep=';')
    # v_list = [list(map(float, v_str.split(','))) for v_str in df_solutions['v']]

    plot_convergence_history(df_conv_history)

if __name__ == "__main__":
    main()