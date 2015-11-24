from collections import Counter

import parser
from pandas import *
from numpy import array, isfinite
import operator
from sklearn.cluster import MeanShift, estimate_bandwidth

import numpy as np
import pylab as pl
from itertools import cycle

  
def Mean_Shift():
    #importer les donnees
    data=pandas.read_csv(filepath_or_buffer="input.csv",delimiter=',',encoding='utf-8')  
    data.drop_duplicates()
    #lire les donnees
    values=data[['row_center', 'col_center']].values
    print("printing values")
    print (values)
    #Mean shift
    print ("Clustering data Meanshift algorithm")
    bandwidth = estimate_bandwidth(values, quantile=0.3, n_samples=None)
    ms = MeanShift(bandwidth=bandwidth, bin_seeding=False,min_bin_freq=5,cluster_all=False)
    ms.fit(values)
    data['cluster'] = ms.labels_
    data = data.sort(columns='cluster')
    data = data[(data['cluster'] != -1)]
    print (data['cluster'])
    data['cluster'] = data['cluster'].apply(lambda x:"cluster" +str(x))
    labels_unique = np.unique(ms.labels_).tolist()
    del labels_unique[0]
    # Filtering clusters centers according to data filter
    cluster_centers = DataFrame(ms.cluster_centers_, columns=['row_center', 'col_center'])
    #cluster_centers['size'] = labels_unique
    print (cluster_centers)
    n_centers_ = len(cluster_centers)
    print("number of clusters is :%d" % n_centers_)
    print ("Exporting points")
    data.to_csv(path_or_buf="output.csv", cols=['row','col','cluster','width','height','row_center','col_center'], encoding='utf-8')
    #print ("Exporting centers")
    #cluster_centers['cluster'] = cluster_centers['cluster'].apply(lambda x:"cluster" +str(x))
    #cluster_centers.to_csv(path_or_buf="./centers.csv", cols=['row_center', 'col_center'], encoding='utf-8')
    return 0
Mean_Shift()