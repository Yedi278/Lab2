import os
from IPython.display import Latex
import numpy as np
import pandas as pd
from iminuit.cost import LeastSquares
from iminuit import Minuit

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

def bisezione (g, xMin, xMax, prec = 0.0001, kwargs=None):

    xAve = xMin
    l = []
    while ((xMax - xMin) > prec) :
        l.append(xAve)
        xAve = 0.5 * (xMax + xMin)
        if (g (xAve, **kwargs) * g (xMin, **kwargs) > 0.): 
            xMin = xAve 
        else:
            xMax = xAve

    return xAve, l

def find_max(data,init=0, prec=0.001):
    i = init
    max = np.max(data[init:])
    while data[i] < max-prec:
        i += 1
    return data[i], i

def find_min(data,init=0, prec=0.001):
    i = init
    min = np.min(data[init:])
    while data[i] > min+prec:
        i += 1
    return data[i], i

def find_zero(data, _init=0, prec=0.001):

    i=_init

    if data[_init] > 0.+prec:
        while data[i] > 0+prec:
            i += 1
        return data[i], i

    else:
        while data[i] < 0.-prec:
            i += 1
        return data[i], i
    
def chi_2_fit(x,y,yerr,model,kwargs):
    c = LeastSquares(x, y, yerr, model)
    m = Minuit(c, **kwargs)
    m.fixed[*(kwargs.keys())] = True, True
    m.migrad()
    return m.fval, m.ndof

def analize(path, init=0, verbose=False)->tuple:
    '''
    `path`: path to the data file
    `init`: initial guess for the maximum
    `verbose`: if True, returns all the data, if False, returns only the relevant data
    `return`: tuple with the relevant data as follows:
        V_CH1_SGN, V_MTH_SGN, dt_CH1_SGN, dt_MTH_SGN
    '''
    CH1, SGN, MTH = get_data(path)
    N = init

    max_SGN, i_max_SGN = find_max(SGN[1], N, prec=0.00001)
    max_CH1, i_max_CH1 = find_max(CH1[1], N, prec=0.00001)
    max_MTH, i_max_MTH = find_max(MTH[1], N, prec=0.00001)
    z, i_zero_SGN = find_zero(SGN[1], N, prec=0.00001)
    z, i_zero_CH1 = find_zero(CH1[1],  _init=i_zero_SGN, prec=0.00001)
    z, i_zero_MTH = find_zero(MTH[1],  _init=i_zero_SGN, prec=0.00001)

    V_CH1_SGN = max_CH1/max_SGN
    V_MTH_SGN = max_MTH/max_SGN

    dt_CH1_SGN = np.abs(CH1[0][i_zero_CH1] - SGN[0][i_zero_SGN])
    dt_MTH_SGN = np.abs(MTH[0][i_zero_MTH] - SGN[0][i_zero_SGN])
    
    if verbose:
        return CH1,SGN,MTH, V_CH1_SGN, V_MTH_SGN, dt_CH1_SGN, dt_MTH_SGN, max_CH1, max_SGN, max_MTH, i_max_CH1, i_max_SGN, i_max_MTH, i_zero_CH1, i_zero_SGN, i_zero_MTH
    
    else:
        return V_CH1_SGN, V_MTH_SGN, dt_CH1_SGN, dt_MTH_SGN
    
if __name__ == '__main__':
    import matplotlib.pyplot as plt

    path = 'data/RC/140000/'
    CH1,SGN,MTH, V_CH1_SGN, V_MTH_SGN, dt_CH1_SGN, dt_MTH_SGN, max_CH1, max_SGN, max_MTH, i_max_CH1, i_max_SGN, i_max_MTH, i_zero_CH1, i_zero_SGN, i_zero_MTH = analize(path, init=200, verbose=True, interpol= False)

    plt.plot(CH1[0],CH1[1], label='CH1')