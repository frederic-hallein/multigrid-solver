import pandas as pd
import matplotlib.pyplot as plt


def plot_norms(df: pd.DataFrame) -> None:
    plt.figure()
    plt.semilogy(df['iter'], df['residual_norm'], marker='o', label='Residual Norm')
    plt.semilogy(df['iter'], df['error'], marker='s', label='Error')
    plt.xlabel('Iteration')
    plt.ylabel(r'$L_2$ norm ($\log_{10}$ scale)')
    plt.title(r'Multigrid Residual and Error Norm per Iteration')
    plt.grid(True, which='both', ls='--')
    plt.legend()
    plt.tight_layout()
    plt.show()