import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

def smooth(y, box_pts):
    box = np.ones(box_pts)/box_pts
    y_smooth = np.convolve(y, box, mode='same')
    return y_smooth

def main():
    data_brute_force = pd.read_csv('datos/results_brute_force.csv')
    data_hash_table = pd.read_csv('datos/results_hash_table.csv')
    data_binary_search = pd.read_csv('datos/results_binary_search.csv')

    plt.plot(data_brute_force['num_points'], data_brute_force['elapsed_time'], color='b')
    plt.show()

    plt.plot(data_hash_table['n_elements'], smooth(data_hash_table['elapsed_time'], 300), color='r')
    plt.show()

    plt.plot(data_binary_search['n_elements'], smooth(data_binary_search['elapsed_time'], 500), color='g')
    plt.show()


if __name__ == '__main__':
    main()