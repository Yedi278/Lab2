import os
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

def is_rising(f, x, prec=1e-7, kwargs=None):
    '''This function returns True if the signal is rising, False if it is falling'''
    if f(x-prec, **kwargs) < f(x+prec, **kwargs):
        return True
    return False

def zero(f, xmin, xmax, prec=1e-6, kwargs=None):
    
    i=xmin
    if f(i, **kwargs) > 0:
        while f(i, **kwargs) > 0:
            i += prec
            if i > xmax+0.3*xmax:
                raise ValueError('No zero found')
    else:
        while f(i, **kwargs) < 0:
            i += prec
            if i > xmax+0.3*xmax:
                raise ValueError('No zero found')
    return i

def sine(x, A, w, phi):
        return A * np.sin(2 * np.pi * w * x + phi)

def analize_inter(CHX, freq, init=None, prec=1e-7, verbose=False):

    if init == None:
        _init = CHX[0][0]
    else:
        _init = init
    c = LeastSquares(CHX[0], CHX[1], 0.001, sine)
    m = Minuit(c, A=np.max(CHX[1]), w=freq, phi=0)
    m.limits['A','w'] = (0,None),(freq-0.1*freq,freq+0.1*freq)
    m.migrad()

    _zero = zero(sine, _init, np.max(CHX[0]), kwargs=m.values.to_dict(), prec=prec)

    if not is_rising(sine, _zero, kwargs=m.values.to_dict()):
        _zero = zero(sine, _zero, np.max(CHX[0]), kwargs=m.values.to_dict(), prec=prec)

    if verbose:
        return m, _zero, m.values['A']
    
    return _zero, m.values['A']

def analize(path, frequency,prec=1e-7, verbose=False)->tuple:
    '''
    `path`: path to the data file
    `init`: initial guess for the maximum
    `verbose`: if True, returns all the data, if False, returns only the relevant data
    `return`: tuple with the relevant data as follows:
        V_SGN, V_MTH, zero_CH1, zero_MTH
    '''
    CH1, SGN, MTH = get_data(path)

    if verbose:
        m2, zero_SGN, max_SGN = analize_inter(SGN, frequency, prec=prec, verbose=True)
        m1, zero_CH1, max_CH1 = analize_inter(CH1, frequency, init=zero_SGN - prec, prec=prec, verbose=True)
        m3, zero_MTH, max_MTH = analize_inter(MTH, frequency, init=zero_SGN - prec, prec=prec, verbose=True)

        V_SGN = max_CH1/max_SGN
        V_MTH = max_MTH/max_SGN

        dt_CH1 = np.abs(zero_SGN - zero_CH1)
        dt_MTH = np.abs(zero_SGN - zero_MTH)

        return CH1,SGN,MTH, V_SGN, V_MTH, zero_CH1, zero_SGN, zero_MTH, m1, m2, m3
    
    zero_SGN, max_SGN = analize_inter(SGN, frequency)
    zero_CH1, max_CH1 = analize_inter(CH1, frequency, init=zero_SGN)
    zero_MTH, max_MTH = analize_inter(MTH, frequency, init=zero_SGN)

    V_SGN = max_CH1/max_SGN
    V_MTH = max_MTH/max_SGN

    dt_CH1 = np.abs(zero_SGN - zero_CH1)
    dt_MTH = np.abs(zero_SGN - zero_MTH)

    
    return V_SGN, V_MTH, dt_CH1, dt_MTH




# if __name__ == '__main__':
#     import matplotlib.pyplot as plt

#     path = 'data/RL/1250/'

#     CH1,SGN,MTH, V_CH1_SGN, V_MTH_SGN, zero_CH1, zero_MTH, zero_SGN = analize(path, 1250, verbose=True)

#     m3, xmin3, max_SGN = analize_inter(SGN, 1250, verbose = True, prec=1e-7)
#     m, xmin, max_CH1 = analize_inter(CH1, 1250, init=xmin3, verbose = True, prec=1e-7)
#     m2, xmin2, max_MTH = analize_inter(MTH, 1250,init=xmin3, verbose = True, prec=1e-7)

#     x = np.linspace(np.min(SGN[0]), np.max(SGN[0]), 1000)
#     plt.plot(x, sine(x, **m.values.to_dict()), label='CH1 fit')
#     plt.plot(x, sine(x, **m2.values.to_dict()), label='MTH fit')
#     plt.plot(x, sine(x, **m3.values.to_dict()), label='SGN fit')

#     print('V_CH1_SGN: ', V_CH1_SGN)
#     print('V_MTH_SGN: ', V_MTH_SGN)
#     print('dt_CH1_SGN: ', np.abs(zero_SGN-zero_CH1), np.abs(xmin3-xmin))
#     print('dt_MTH_SGN: ', np.abs(zero_SGN-zero_MTH), np.abs(xmin3-xmin2)) 

#     plt.scatter(xmin, sine(xmin, **m.values.to_dict()), color='red', label='CH1 zero')
#     plt.scatter(xmin2, sine(xmin2, **m2.values.to_dict()), color='red', label='MTH zero')
#     plt.scatter(xmin3, sine(xmin3, **m3.values.to_dict()), color='red', label='SGN zero')

#     plt.scatter(zero_CH1, sine(zero_CH1, **m.values.to_dict()), color='green', label='CH1 zero')
#     plt.scatter(zero_MTH, sine(zero_MTH, **m2.values.to_dict()), color='green', label='MTH zero')
#     plt.scatter(zero_SGN, sine(zero_SGN, **m3.values.to_dict()), color='green', label='SGN zero')

#     plt.plot(SGN[0],SGN[1], label='SGN', lw=.5)
#     plt.plot(CH1[0],CH1[1], label='CH1', lw=.5)
#     plt.plot(MTH[0],MTH[1], label='MTH', lw=.5)
#     plt.legend()
#     plt.show()