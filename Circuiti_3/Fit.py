import numpy as np
from scipy.optimize import curve_fit
from iminuit import Minuit
from iminuit.cost import LeastSquares
import matplotlib.pyplot as plt



class Fit:
    '''Class for fitting data with a given model'''

    def __init__(self, x, y, model, yerror, scipy = None, minuit = None, kwargs = None):
        '''Initialize the class with the data and the model'''

        self.x = x
        self.y = y
        self.model = model
        self.p0 = [*kwargs.values()]
        self.error = yerror
        self.kwargs = kwargs

        self.scipy = None
        self.minuit = None

        self.fval = None
        self.ndof = None

        self.values = None
        self.errors = None
        self.covariance = None
    
    def scipy_fit(self):
        '''Fit the data with scipy curve_fit function'''
        popt, pcov = curve_fit(self.model, self.x, self.y, p0 = self.p0, sigma = self.error*np.ones(len(self.x)), absolute_sigma = True)
        self.values = popt
        self.errors = np.sqrt(np.diag(pcov))
        self.covariance = pcov
        self.scipy = True
        self.scipy_chi2()
        return popt, pcov
    
    def minuit_fit(self):
        '''Fit the data with iminuit Minuit Class'''
        c = LeastSquares(self.x, self.y, self.error, self.model)
        m = Minuit(c, **self.kwargs)
        m.migrad()
        m.hesse()
        self.minuit = True
        return m

    def scipy_chi2(self):
        '''Calculate the chi2 value for the scipy fit'''
        c = LeastSquares(self.x, self.y, self.error, self.model)
        m = Minuit(c, **self.kwargs)
        m.fixed[*(self.kwargs.keys())] = True
        m.migrad()
        self.fval = m.fval
        self.ndof = m.ndof
        return m

    def visualize(self):
        '''Visualize the data and the fit'''

        fig,ax = plt.subplots(1,2, figsize = (10,5))

        plt.subplot(1,2,1)
        plt.scatter(self.x, self.y, label='data')
        _x_range = np.linspace(min(self.x), max(self.x), 300)
        plt.plot(_x_range, self.model(_x_range, *self.values), label='fit', color='red')
        plt.legend()

        plt.subplot(1,2,2)
        plt.imshow(self.covariance, interpolation='nearest')
        plt.colorbar()
        plt.title('Covariance Matrix')
        
        return fig, ax
    
    def fit(self, scipy = True, minuit = False):
        '''Fit the data with the selected method'''

        if scipy:
            return self.scipy_fit()
        else:
            return self.minuit_fit(self.kwargs)


if __name__ == '__main__':

    def model(x, a, b):
        return a*x + b
    
    x = np.linspace(0,10,100)
    y = 2*x + 3
    yerr = np.random.normal(0,1,100)
    p0 = [1,1]

    f = Fit(x, y, model, yerr, kwargs={'a':1, 'b':1})
    f.scipy_fit()
    f.visualize()
    plt.show()