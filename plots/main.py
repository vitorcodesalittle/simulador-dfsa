import matplotlib.pyplot as plt
from matplotlib.legend_handler import HandlerBase
import pandas as pd
import sys
import os
args = sys.argv

if len(args) < 3:
    print(f"""
Usage: {args[0]} [csv-in] [plots-dir]
Example: python {args[0]} ./out.csv ./images
""")
    sys.exit(1)

results_path = args[1]
plots_path = args[2]
df = pd.read_csv(results_path)

def save_and_clf(path):
    plt.savefig(path)
    plt.close()

list_color  = ["b", "g", "y", "r"]
list_mak    = ["+","o","s","^"]
list_lab    = ['Lower Bound','Shoute','Eom-Lee', 'IV2']
ax = plt.gca()
class MarkerHandler(HandlerBase):
    def create_artists(self, legend, tup,xdescent, ydescent,
                       width, height, fontsize,trans):
        return [plt.Line2D([width/2], [height/2.],ls="",
                           marker=tup[1],color=tup[0], transform=trans)]

def plot_total_slots(df):
    plt.plot(df['ntags'], df[df['estimador'] == 'lb']['total_slots'], marker='+')
    #     plt.plot(df['ntags'], df[df['estimador'] == 'shoute']['total_slots'], marker='o')
    #     plt.plot(df['ntags'], df[df['estimador'] == 'eom-lee']['total_slots'], marker='s')
    #     plt.plot(df['ntags'], df[df['estimador'] == 'iv2']['total_slots'], marker='^')
    ax.legend(list(zip(list_color,list_mak)), list_lab, handler_map={tuple:MarkerHandler()})
    ax.set_ylim([0,3500])
    ax.set_xlabel("Número de etiquetas")
    ax.set_ylabel("Número de slots")
    save_and_clf(os.path.join(plots_path, "total_slots.png"))

def plot_total_collisions(df):
    plt.plot(df['ntags'], df[df['estimador'] == 'lb']['total_collisions_slots'], marker='+')
    #     plt.plot(df['ntags'], df[df['estimador'] == 'shoute']['total_collisions_slots'], marker='o')
    #     plt.plot(df['ntags'], df[df['estimador'] == 'eom-lee']['total_collisions_slots'], marker='s')
    #     plt.plot(df['ntags'], df[df['estimador'] == 'iv2']['total_collisions_slots'], marker='^')
    ax = plt.gca()
    ax.legend(list(zip(list_color,list_mak)), list_lab, handler_map={tuple:MarkerHandler()})
    ax.set_ylim([0,1800])
    ax.set_xlabel("Número de etiquetas")
    ax.set_ylabel("Número de slots em colisão")
    save_and_clf(os.path.join(plots_path, "total_collisions.png"))

def plot_total_empty_slots(df):
    plt.plot(df['ntags'], df[df['estimador'] == 'lb']['total_empty_slots'], marker='+')
    #     plt.plot(df['ntags'], df[df['estimador'] == 'shoute']['total_empty_slots'], marker='o')
    #     plt.plot(df['ntags'], df[df['estimador'] == 'eom-lee']['total_empty_slots'], marker='s')
    #     plt.plot(df['ntags'], df[df['estimador'] == 'iv2']['total_empty_slots'], marker='^')
    ax = plt.gca()
    ax.legend(list(zip(list_color,list_mak)), list_lab, handler_map={tuple:MarkerHandler()})
    ax.set_ylim([0,1100])
    ax.set_xlabel("Número de etiquetas")
    ax.set_ylabel("Número de slots vazios")
    save_and_clf(os.path.join(plots_path, "total_empty_slots.png"))

def plot_total_time(df):
    plt.plot(df['ntags'], df[df['estimador'] == 'lb']['total_empty_slots'], marker='+')
    #     plt.plot(df['ntags'], df[df['estimador'] == 'shoute']['total_empty_slots'], marker='o')
    #     plt.plot(df['ntags'], df[df['estimador'] == 'eom-lee']['total_empty_slots'], marker='s')
    #     plt.plot(df['ntags'], df[df['estimador'] == 'iv2']['total_empty_slots'], marker='^')
    ax = plt.gca()
    ax.legend(list(zip(list_color,list_mak)), list_lab, handler_map={tuple:MarkerHandler()})
    ax.set_ylim([0,10])
    ax.set_xlabel("Número de etiquetas")
    ax.set_ylabel("Tempo para identificação")
    save_and_clf(os.path.join(plots_path, "total_time.png"))

plot_total_slots(df)
plot_total_time(df)
plot_total_collisions(df)
plot_total_empty_slots(df)