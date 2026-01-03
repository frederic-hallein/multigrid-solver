import os
import glob
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

EXAMPLE_PATH = "../example"
GRID_POINTS_PATH = os.path.join(EXAMPLE_PATH, "grid_points.csv")

def plot_example(u_exact=None) -> None:
    df_grid_points = pd.read_csv(GRID_POINTS_PATH, sep=';')

    # Find all convergence history and solutions files
    conv_files = sorted(glob.glob(os.path.join(EXAMPLE_PATH, "convergence_history_*.csv")))
    sol_files = sorted(glob.glob(os.path.join(EXAMPLE_PATH, "solutions_*.csv")))

    # Plot convergence history overlay
    plt.figure(figsize=(10, 6))
    for conv_file in conv_files:
        df_conv = pd.read_csv(conv_file, sep=';')
        label = os.path.basename(conv_file).replace("convergence_history_", "").replace(".csv", "")
        plt.semilogy(df_conv['iter'], df_conv['residual_norm'], marker='o', label=label)

    plt.xlabel('Iterations')
    plt.ylabel(r'$||\mathbf{r}||_2$')
    plt.title('Convergence History Comparison', fontweight='bold')
    plt.legend()
    plt.grid(True)
    plt.savefig("plots/example/convergence_history_overlay.svg")
    plt.close()

    # Plot solution overlay
    plt.figure(figsize=(10, 6))
    line_styles = ['-', '--', '-.', ':']
    markers = ['o', 's', '^', 'D']
    colors = ['tab:purple', 'tab:orange', 'tab:green', 'tab:red', 'tab:blue', 'tab:brown']

    for idx, sol_file in enumerate(sol_files):
        df_sol = pd.read_csv(sol_file, sep=';')
        v_list = [list(map(float, v_str.split(','))) for v_str in df_sol['v']]
        label = os.path.basename(sol_file).replace("solutions_", "").replace(".csv", "")
        plt.plot(
            df_grid_points['x'], v_list[0],
            linestyle=line_styles[idx % len(line_styles)],
            marker=markers[idx % len(markers)],
            color=colors[idx % len(colors)],
            markersize=5,
            label=label
        )

    # Plot exact solution
    if u_exact is None:
        print("[WARNING] exact solution not given")
    else:
        exact_values = [u_exact(x) for x in df_grid_points['x']]
        plt.plot(df_grid_points['x'], exact_values, 'k--', label='Exact', linewidth=2)

    plt.xlabel(r'$x$')
    plt.ylabel(r'$f(x)$')
    plt.title('Solution Comparison', fontweight='bold')
    plt.legend()
    plt.grid(True)
    plt.savefig("plots/example/solution_overlay.svg")
    plt.close()