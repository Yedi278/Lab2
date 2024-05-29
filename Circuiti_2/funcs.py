import os
from IPython.display import Latex
import numpy as np
import pandas as pd

def rNan(arr): 
    '''This function removes NaN values from a numpy array'''
    return arr[~np.isnan(arr)]


def find_file(path:str,name:str):
    '''This function finds the file with the name specified in the path specified'''

    for fname in os.listdir(path):
        if name in fname:
            return fname
    return None

def get_data(path:str):
    '''This function loads the data from the oscilloscope'''

    try:
        name = find_file(path,'CH1')
        if name != None:
            first_channel = pd.read_csv(path+name).iloc[:,3].to_numpy() , pd.read_csv(path+name).iloc[:,4].to_numpy()
        else:
            first_channel = None
    except Exception as e:
        first_channel = None
        print('Error loading first channel: ',e)

    try:
        name = find_file(path,'CH2')
        if name != None:
            second_channel = pd.read_csv(path+name).iloc[:,3].to_numpy() , pd.read_csv(path+name).iloc[:,4].to_numpy()
        else:
            second_channel = None
    except Exception as e:
        second_channel = None
        print('Error loading second channel: ',e)
        
    try:
        name = find_file(path,'MTH')
        if name != None:
            third_channel = pd.read_csv(path+name).iloc[:,3].to_numpy() , pd.read_csv(path+name).iloc[:,4].to_numpy()
        else:
            third_channel = None, None

    except Exception as e:
        third_channel = None, None
        print('Error loading third channel: ',e)
    

    return first_channel, second_channel, third_channel