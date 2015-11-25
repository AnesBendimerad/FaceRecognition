import sys
import math
import numpy as np
from pandas import *
from sklearn.cluster import MeanShift,DBSCAN, estimate_bandwidth
from scipy.stats import norm

RECTANGLES=['x','y','width','height','score']

#0 For mean cluster representative method and 1 for argmax
CLUSTER_REPRESENTATIVE_METHOD=1

def Mean_Shift(sourcePath="input.csv",outputPath="output.csv",quantile=0.3):
    
    #importer les donnees
    data=pandas.read_csv(filepath_or_buffer=sourcePath,delimiter=',',encoding='utf-8')
    data.drop_duplicates()
    windows=data[RECTANGLES].values
    values=np.array([[int(e[0]+e[2]/2),int(e[1]+e[3]/2)] for e in windows])

    #Mean shift
    bandwidth = estimate_bandwidth(values, quantile=0.3, n_samples=None)
    ms = MeanShift(bandwidth=bandwidth, bin_seeding=False,cluster_all=False)
    ms.fit(values)
    clusters=ms.labels_
    labels_unique = np.unique(clusters).tolist()
    if -1 in labels_unique : labels_unique.remove(-1)
    cluster_centers=ms.cluster_centers_
    clusters_number=len(labels_unique)

    #Taking one representative per cluster
    clusters_representative=[0]*clusters_number
    clusters_size=[0]*clusters_number
    for cluster_id in labels_unique :
        cluster_id=int(cluster_id)
        windows_of_cluster_id=windows[(clusters==cluster_id)]
        cluster_id_size=len(windows_of_cluster_id)
        
        if (CLUSTER_REPRESENTATIVE_METHOD==0) :
            center_of_cluster_id = cluster_centers[cluster_id]
            mean_width = (1.*sum(windows_of_cluster_id[:,2]))/cluster_id_size
            mean_height = (1.*sum(windows_of_cluster_id[:,3]))/cluster_id_size
            mean_score = (1.*sum(windows_of_cluster_id[:,4]))/cluster_id_size
            clusters_representative[cluster_id]=[max(0,center_of_cluster_id[0]-mean_width/2),max(0,center_of_cluster_id[1]-mean_height/2),mean_width,mean_height,mean_score]
        else :
            clusters_representative[cluster_id]=max(windows_of_cluster_id,key=lambda element:element[4])[:]
        

        clusters_size[cluster_id]=cluster_id_size
    
    #Clean noisy clusters
    clusters_representative,clusters_size = np.array(clusters_representative),np.array(clusters_size)
    if clusters_number>1 :
        sizeMean=(1.*sum(clusters_size))/clusters_number
        sizeStd=math.sqrt((1.*sum(map(lambda x : (x-sizeMean)**2,clusters_size)))/(clusters_number-1))
        sizeThreshold = norm.ppf(quantile,sizeMean,sizeStd)
        clusters_representative=clusters_representative[clusters_size>sizeThreshold]

    #Exporting CSV file
    clusters_representative_with_rowcol=np.array([[int(e[0]),int(e[1]),int(e[2]),int(e[3]),e[4]] for e in clusters_representative])
    clusters_representative_with_rowcol = DataFrame(clusters_representative_with_rowcol, columns=RECTANGLES)
    clusters_representative_with_rowcol.to_csv(path_or_buf=outputPath, cols=RECTANGLES, encoding='utf-8')

def windowMetric(rectangle_1,rectangle_2) :
    """
    rectangle=[starting_row,starting_col,height,width,score]
    return metric in [0,1] which mean dissimiliarity between windows 
    """
    intersection_h=min(rectangle_1[2],rectangle_2[2],rectangle_1[0]+rectangle_1[2]-rectangle_2[0],rectangle_2[0]+rectangle_2[2]-rectangle_1[0])
    intersection_w=min(rectangle_1[3],rectangle_2[3],rectangle_1[1]+rectangle_1[3]-rectangle_2[1],rectangle_2[1]+rectangle_2[3]-rectangle_1[1])
    if (intersection_h>0 and intersection_w>0) :
        minimumSurface=min(rectangle_1[2]*rectangle_1[3],rectangle_2[2]*rectangle_2[3])
        return 1-(float(intersection_h*intersection_w)/minimumSurface)
    return float('inf')

def RDBSCAN(sourcePath="input.csv",outputPath="output.csv",quantile=0.3):
    #Import CSV File
    data=pandas.read_csv(filepath_or_buffer=sourcePath,delimiter=',',encoding='utf-8')
    data.drop_duplicates()
    windows=data[RECTANGLES].values
    
    #Clustering
    db = DBSCAN(eps=1.1,min_samples=1,metric=windowMetric)
    db.fit(windows)
    clusters=db.labels_
    labels_unique = np.unique(clusters).tolist()
    if -1 in labels_unique : labels_unique.remove(-1)
    clusters_number=len(labels_unique)
    
    #Taking one representative per cluster
    clusters_representative=[0]*clusters_number
    clusters_size=np.array([0]*clusters_number)
    for cluster_id in labels_unique :
        cluster_id=int(cluster_id)
        windows_of_cluster_id=windows[(clusters==cluster_id)]
        cluster_id_size=len(windows_of_cluster_id)
        if (CLUSTER_REPRESENTATIVE_METHOD==0) :
            mean_x    = max(0,int((1.*sum(windows_of_cluster_id[:,0]))/cluster_id_size))
            mean_y    = max(0,int((1.*sum(windows_of_cluster_id[:,1]))/cluster_id_size))
            mean_width  = int((1.*sum(windows_of_cluster_id[:,2]))/cluster_id_size)
            mean_height = int((1.*sum(windows_of_cluster_id[:,3]))/cluster_id_size)
            mean_score  = (1.*sum(windows_of_cluster_id[:,4]))/cluster_id_size
            clusters_representative[cluster_id]=[mean_x,mean_y,mean_width,mean_height,mean_score]
        else :
            clusters_representative[cluster_id]=max(windows_of_cluster_id,key=lambda element:element[4])[:]
        
        clusters_size[cluster_id]=cluster_id_size

    #Clean noisy clusters
    clusters_representative,clusters_size = np.array(clusters_representative),np.array(clusters_size)
    if clusters_number>1 : 
        sizeMean=(1.*sum(clusters_size))/clusters_number
        sizeStd=math.sqrt((1.*sum(map(lambda x : (x-sizeMean)**2,clusters_size)))/(clusters_number-1))
        sizeThreshold = norm.ppf(quantile,sizeMean,sizeStd)
        clusters_representative=clusters_representative[clusters_size>sizeThreshold]
    
    #Exporting CSV file
    clusters_representative_output = DataFrame(clusters_representative, columns=RECTANGLES)
    clusters_representative_output.to_csv(path_or_buf=outputPath, cols=RECTANGLES, encoding='utf-8')


if __name__ == '__main__':
    """
    python clean.py clustering_algorithme inputPath outputPath quantile
    clustering_algorithme : 0 for meanshift, 1 for RDBSCAN
    inputPath : CSV input file
    outputPath : CSV output file
    quantile : for removing small clusters. Parameter in [0,1]
    """

    if (len(sys.argv))==5:
        sourcePath=sys.argv[2]
        outputPath=sys.argv[3]
        quantile=float(sys.argv[4])
        if (int(sys.argv[1])==0) :Mean_Shift(sourcePath,outputPath,quantile)
        else : RDBSCAN(sourcePath,outputPath,quantile)
    else :
        print "Please write command like this : \n"+"python clean.py clustering_algorithme inputPath outputPath quantile\n"+"  - clustering_algorithme : 0 for meanshift, 1 for RDBSCAN\n"+"  - inputPath : CSV input file\n"+"  - outputPath : CSV output file\n"+"  - quantile : for removing small clusters. Parameter in [0,1]"
        
        

