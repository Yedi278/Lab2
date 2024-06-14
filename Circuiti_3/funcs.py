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

def is_rising(f, x, falling=False, prec=1e-7, kwargs=None):
    '''This function returns True if the signal is rising, False if it is falling'''
    if falling:
        if f(x-prec, **kwargs) > f(x+prec, **kwargs):
            return True
        return False
    if f(x-prec, **kwargs) < f(x+prec, **kwargs):
        return True
    return False

def zero(f, xmin, xmax, prec=1e-6, kwargs=None):
    
    i=xmin
    if f(i, **kwargs) > 0:
        while f(i, **kwargs) > 0:
            i += prec
            # if i > xmax+0.5*xmax:
            #     raise ValueError('No zero found')
    else:
        while f(i, **kwargs) < 0:
            i += prec
            # if i > xmax+0.5*xmax:
            #     raise ValueError('No zero found')
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
    m.hesse()

    _zero = zero(sine, _init, np.max(CHX[0]), kwargs=m.values.to_dict(), prec=prec)

    if not is_rising(sine, _zero, kwargs=m.values.to_dict(), falling=False):
        _zero = zero(sine, _zero, np.max(CHX[0]), kwargs=m.values.to_dict(), prec=prec)

    if verbose:
        return m, _zero, m.values['A'], m.errors['A'] 
    
    return _zero, m.values['A']

def analize(path, frequency,prec=1e-7, force=False, verbose=False)->tuple:
    '''
    `path`: path to the data file
    `init`: initial guess for the maximum
    `verbose`: if True, returns all the data, if False, returns only the relevant data
    `return`: tuple with the relevant data as follows:
        V_SGN, V_MTH, zero_CH1, zero_MTH
    '''
    CH1, SGN, MTH = get_data(path)
    
    # MTH = MTH[0], np.array(MTH[1])

    if force == True:
        MTH = SGN[0], np.array(SGN[1]) - np.array(CH1[1])
        
    if verbose:
        m2, zero_SGN, max_SGN, max_SGN_err = analize_inter(SGN, frequency, prec=prec, verbose=True)
        m1, zero_CH1, max_CH1, max_CH1_err = analize_inter(CH1, frequency, init=zero_SGN - prec, prec=prec, verbose=True)
        m3, zero_MTH, max_MTH, max_MTH_err = analize_inter(MTH, frequency, init=zero_SGN - prec, prec=prec, verbose=True)

        V_SGN = max_CH1/max_SGN
        V_MTH = max_MTH/max_SGN

        V_SGN_err = (1/max_SGN) * np.sqrt((max_CH1_err)**2 + (V_SGN*max_SGN_err)**2)
        V_MTH_err = (1/max_SGN) * np.sqrt((max_MTH_err)**2 + (V_MTH*max_SGN_err)**2)

        dt_CH1 = zero_CH1 - zero_SGN
        dt_MTH = zero_MTH - zero_SGN

        zero_err = 2*prec*frequency

        return CH1,SGN,MTH, V_SGN, V_MTH, zero_CH1, zero_SGN, zero_MTH, m1, m2, m3, dt_CH1, dt_MTH, V_SGN_err, V_MTH_err, zero_err
    
    zero_SGN, max_SGN = analize_inter(SGN, frequency, prec=prec)
    zero_CH1, max_CH1 = analize_inter(CH1, frequency, init=zero_SGN, prec=prec)
    zero_MTH, max_MTH = analize_inter(MTH, frequency, init=zero_SGN, prec=prec)

    V_SGN = max_CH1/max_SGN
    V_MTH = max_MTH/max_SGN

    dt_CH1 = zero_SGN - zero_CH1
    dt_MTH = zero_SGN - zero_MTH
    
    return V_SGN, V_MTH, dt_CH1, dt_MTH