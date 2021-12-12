import matplotlib.pyplot as plt
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

def plot_total_slots(df):
    plt.plot(df['ntags'], df[df['estimador'] == 'lb']['total_slots'], marker='+')
    #     plt.plot(df['ntags'], df[df['estimador'] == 'shoute']['total_slots'], marker='o')
    #     plt.plot(df['ntags'], df[df['estimador'] == 'eom-lee']['total_slots'], marker='s')
    #     plt.plot(df['ntags'], df[df['estimador'] == 'iv2']['total_slots'], marker='^')
    ax = plt.gca()
    ax.set_ylim([0,3500])
    save_and_clf(os.path.join(plots_path, "total_slots.png"))

def plot_total_collisions(df):
    plt.plot(df['ntags'], df[df['estimador'] == 'lb']['total_collisions_slots'], marker='+')
    #     plt.plot(df['ntags'], df[df['estimador'] == 'shoute']['total_collisions_slots'], marker='o')
    #     plt.plot(df['ntags'], df[df['estimador'] == 'eom-lee']['total_collisions_slots'], marker='s')
    #     plt.plot(df['ntags'], df[df['estimador'] == 'iv2']['total_collisions_slots'], marker='^')
    ax = plt.gca()
    ax.set_ylim([0,1800])
    save_and_clf(os.path.join(plots_path, "total_collisions.png"))

def plot_total_empty_slots(df):
    plt.plot(df['ntags'], df[df['estimador'] == 'lb']['total_empty_slots'], marker='+')
    #     plt.plot(df['ntags'], df[df['estimador'] == 'shoute']['total_empty_slots'], marker='o')
    #     plt.plot(df['ntags'], df[df['estimador'] == 'eom-lee']['total_empty_slots'], marker='s')
    #     plt.plot(df['ntags'], df[df['estimador'] == 'iv2']['total_empty_slots'], marker='^')
    ax = plt.gca()
    ax.set_ylim([0,1100])
    save_and_clf(os.path.join(plots_path, "total_empty_slots.png"))

def plot_total_time(df):
    plt.plot(df['ntags'], df[df['estimador'] == 'lb']['total_empty_slots'], marker='+')
    #     plt.plot(df['ntags'], df[df['estimador'] == 'shoute']['total_empty_slots'], marker='o')
    #     plt.plot(df['ntags'], df[df['estimador'] == 'eom-lee']['total_empty_slots'], marker='s')
    #     plt.plot(df['ntags'], df[df['estimador'] == 'iv2']['total_empty_slots'], marker='^')
    ax = plt.gca()
    ax.set_ylim([0,10])
    save_and_clf(os.path.join(plots_path, "total_time.png"))

plot_total_slots(df)
plot_total_time(df)
plot_total_collisions(df)
plot_total_empty_slots(df)