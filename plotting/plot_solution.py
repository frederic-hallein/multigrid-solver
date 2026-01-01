import pandas as pd
import matplotlib.pyplot as plt


def plot_solution(df: pd.DataFrame, u=None) -> None:
    if u is None:
        print("Error: Function pointer u is None")
        return

    plt.figure()
    exact_values = [u(x) for x in df['x']]
    plt.plot(
        df['x'], exact_values,
        'b-',
        label='exact')
    plt.plot(
        df['x'], df['v'],
        marker='o',
        color='red',
        markersize=3,
        label='approx'
    )

    plt.xlabel(r'$x$')
    plt.ylabel(r'$f(x)$')
    plt.title('Exact vs Approximate Solution')
    plt.grid(True, which='both', ls='--')
    plt.legend()
    plt.tight_layout()
    plt.savefig("plots/solution.png", dpi=300)
    plt.show()