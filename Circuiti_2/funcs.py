import os
from IPython.display import Latex
import sympy as sp
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
            first_channel = pd.read_csv(path+name).iloc[:,3].to_numpy(np.float128) , pd.read_csv(path+name).iloc[:,4].to_numpy(np.float128)
        else:
            first_channel = None
    except:
        first_channel = None
        print('Error loading first channel')

    try:
        name = find_file(path,'CH2')
        if name != None:
            second_channel = pd.read_csv(path+name).iloc[:,3].to_numpy(np.float128) , pd.read_csv(path+name).iloc[:,4].to_numpy(np.float128)
        else:
            second_channel = None
    except:
        second_channel = None
        print('Error loading second channel')
        
    try:
        name = find_file(path,'MTH')
        if name != None:
            third_channel = pd.read_csv(path+name).iloc[:,3].to_numpy(np.float128) , pd.read_csv(path+name).iloc[:,4].to_numpy(np.float128)
        else:
            third_channel = first_channel[0], np.zeros(first_channel[0].shape)
    except:
        third_channel = first_channel[0], np.zeros(first_channel[0].shape)
        print('Error loading third channel')
    

    return first_channel, second_channel, third_channel