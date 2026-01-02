import pandas as pd
import matplotlib.pyplot as plt


def plot_solution(df: pd.DataFrame, path: str, config: any, u_exact=None) -> None:
    plt.figure()
    if u_exact is None:
        print("[WARNING] exact solution not given")
    else:
        exact_values = [u_exact(x) for x in df['x']]
        plt.plot(
            df['x'], exact_values,
            'b-',
            label='exact')

    approx_label = (
        f"{config['solver']['cycle']} "
        f"({config['smoother']['pre_iterations']}, {config['smoother']['post_iterations']})"
        f", {config['solver']['smoother']} "
        f"($\\omega$ = {config['solver']['omega']})"
    )
    plt.plot(
        df['x'], df['v'],
        marker='o',
        color='red',
        markersize=3,
        label=approx_label
    )

    plt.xlabel(r'$x$')
    plt.ylabel(r'$f(x)$')
    plt.title('Exact vs Approximate Solution')
    plt.grid(True, which='both', ls='--')
    plt.legend()
    plt.tight_layout()
    plt.savefig(path, dpi=300)
    plt.show()