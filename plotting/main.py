import yaml
import pandas as pd

import numpy as np

from plot_residuals_norm import plot_norms

RESIDUALS_NORM_PATH = "../data/residuals_norm.csv"
SOLUTIONS_PATH = "../data/solutions.csv"

def compute_error(x, v_list):
    u_exact = np.sin(2 * np.pi * x)
    errors = []
    for v in v_list:
        v_arr = np.array(v)
        error_vec = v_arr - u_exact
        l2_error = np.linalg.norm(error_vec) / np.sqrt(len(x))
        errors.append(l2_error)
    return errors

def main() -> None:
    with open("../data/params.yaml") as f:
        params = yaml.safe_load(f)

    df_norms = pd.read_csv(RESIDUALS_NORM_PATH, sep=';')
    df_solutions = pd.read_csv(SOLUTIONS_PATH, sep=';')
    v_list = [list(map(float, v_str.split(','))) for v_str in df_solutions['v']]

    n = len(v_list[0])
    x_min = params['x_min']
    h = params['h']
    x = x_min + np.arange(n) * h

    df_norms['error'] = compute_error(x, v_list)

    plot_norms(df_norms)

if __name__ == "__main__":
    main()