import pandas as pd
import matplotlib.pyplot as plt


def plot_convergence_history(df: pd.DataFrame, path: str, config: any) -> None:
    plt.figure()

    if config['solver']['norm'] == 'L2':
        residual_norm_label = r'$||\mathbf{r}||_2$'
        error_norm_label = r'$||\mathbf{e}||_2$'
        y_label = r'$||\cdot||_2$'
    else:
        residual_norm_label = r'$||\mathbf{r}||_{\infty}$'
        error_norm_label = r'$||\mathbf{e}||_{\infty}$'
        y_label = r'$||\cdot||_{\infty}$'

    plt.plot(
        df['iter'], df['residual_norm'],
        marker='o',
        markersize=3,
        label=residual_norm_label
    )

    if 'error_norm' not in df.columns:
        print("[WARNING] Error norm is not available")
    else:
        plt.plot(
            df['iter'], df['error_norm'],
            marker='o',
            markersize=3,
            label=error_norm_label
        )

    plt.xlabel('Iterations')
    plt.ylabel(y_label)
    plt.yscale('log', base=10)

    approx_title = (
        f"{config['solver']['cycle']} "
        f"({config['smoother']['pre_iterations']}, {config['smoother']['post_iterations']})"
        f", {config['solver']['smoother']} "
        f"($\\omega$ = {config['solver']['omega']})"
    )
    plt.title(f'Convergence History [{approx_title}]', fontweight='bold')
    plt.grid(True, which='both', ls='--')
    plt.legend()
    plt.tight_layout()
    plt.savefig(path, dpi=300)
    plt.show()