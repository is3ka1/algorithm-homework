import os

import pandas as pd
import seaborn as sns


data_dir = './data'
graph_dir = './graph'
data_dist_cats = ['ascending', 'descending', 'random']

def plot_algo(algo):
    # Plot the standard deviation line
    df = pd.read_csv(os.path.join(data_dir, f'{algo}.csv'), names=['n', *data_dist_cats])
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
    if not os.path.isdir(graph_dir):
        os.mkdir(graph_dir)
    sns_plot.savefig(os.path.join(graph_dir, f'{algo}.png'), dpi=600)
    print(f'{algo} graph saved!')

if __name__ == "__main__":
    if not os.path.isdir(data_dir):
        print('You should run measure.sh first!')
        exit()

    for file_name in os.listdir(data_dir):
        path = os.path.join(data_dir, file_name)
        if os.path.isfile(path) and path.endswith('.csv'):
            plot_algo(file_name[:-4])
