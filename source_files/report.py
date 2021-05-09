import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

dataframe = None
labels = ['bgr', 'hsv', 'ycrcb', 'gray']
categories = ['animals', 'buildings', 'people']
cat = list()
width = 0.3

class Category:

    def __init__(self, category, neg, pos):
        self.category = category
        self.neg = neg
        self.pos = pos

def plot_report(category, neg, pos):
    plt.close()
    ind = np.arange(len(labels))
    fig, ax = plt.subplots(figsize=(8, 6))
    ax.bar(ind - width/2, pos, width, color='salmon')
    ax.bar(ind + width/2, neg, width, color='mediumseagreen')
    ax.set_ylabel('Cantidad')
    ax.set_xlabel('Espacios de colores')
    ax.set_title(category + ': Comparativa entre Aciertos y Fallos')
    
    ax.legend(labels=['Fallos', 'Aciertos'])
    plt.xticks(ind, labels)

    neg_max = max(neg)
    pos_max = max(pos)

    ax.set_ylim(0, (neg_max + 4) if neg_max > pos_max else pos_max + 4)

    set_values(ax, pos, is_impar=False)
    set_values(ax, neg )
    plt.savefig(f'../reports/{category}.png', dpi=400)
    plt.show()

def plot_general():
    neg, pos = get_pos_neg(dataframe)
    plot_report('General', pos,neg)

def get_pos_neg(df):
    pos = list()
    neg = list()
    for l in labels:
        item = df[l].value_counts()
        item = item.sort_index()
        if 0 in item.index:
            neg.append(item.loc[0])
        else:
            neg.append(0)
        if 1 in item.index:
            pos.append(item.loc[1])
        else:
            pos.append(0)
    pos = np.array(pos)
    neg = np.array(neg)
    return neg, pos

def create_categories():
    for c in categories:
        df = dataframe.loc[dataframe['category'] == c]
        pos, neg = get_pos_neg(df)
        cat.append(Category(c, neg, pos))


def read_csv(csv_path):
    dataframe = pd.read_csv(csv_path)
    dataframe.drop('image', axis=1, inplace=True)
    return dataframe

def set_values(ax, y, is_impar=True):
    for index, value in enumerate(y):
        if is_impar:
            plt.text(index + (width/5), value + 0.1, str(round(value, 2)))
        else:
            plt.text(index - (width/1.4), value + 0.1, str(round(value, 2)))

def plot_all():
    for c in cat:
        plot_report(c.category, c.neg, c.pos)

if __name__ == "__main__":
    dataframe = read_csv("../reports/predicts.csv")
    create_categories()
    plot_all()
    plot_general()
