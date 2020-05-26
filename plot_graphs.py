import os

import pandas as pd
import seaborn as sns


algos = ["exchange_sort", "merge_sort", "quick_sort", "counting_sort", "heap_sort"]
data_dist_cats = ['ascending', 'descending', 'random']

def plot_algo(algo):
    # Plot the standard deviation line
    df = pd.read_csv(f'./{algo}.csv', names=['n', 'ascending', 'descending', 'random'])
    sns_df = pd.concat(
        [
            pd.DataFrame({
                'n': df.n,
                'second': df[cat],
                'data_dist': pd.Categorical([cat] * len(df), categories=data_dist_cats, ordered=False)
            })
            for cat in data_dist_cats
        ],
        ignore_index=True
    )
    sns_plot = sns.relplot(x='n', y='second', hue='data_dist', kind='line', ci="sd", data=sns_df)
    sns_plot.fig.suptitle(algo)
    if not os.path.isdir('./graph'):
        os.mkdir('./graph')
    sns_plot.savefig(f'./graph/{algo}.png', dpi=600)
    print(f'{algo} graph saved!')

if __name__ == "__main__":
    for algo in algos:
        plot_algo(algo)
