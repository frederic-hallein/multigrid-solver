import pandas as pd
import matplotlib.pyplot as plt


def plot_convergence_history(df: pd.DataFrame) -> None:
    plt.figure()
    plt.plot(
        df['iter'], df['residual_norm'],
        marker='o', label=r'$||\mathbf{r}||_2$'
    )
    plt.plot(
        df['iter'], df['error_norm'],
        marker='o', label=r'$||\mathbf{e}||_2$'
    )
    plt.xlabel('Iteration Steps')
    plt.ylabel(r'$||\cdot||_2$')
    plt.yscale('log', base=10)
    plt.title('Convergence History')
    plt.grid(True, which='both', ls='--')
    plt.legend()
    plt.tight_layout()
    plt.show()