import numpy as np
from scipy.stats import norm
import scipy
import matplotlib.pyplot as plt
import sympy

#@title Test ipotesi
def chi_test(fval, ndof, x_limit = 40):
  '''This funciton visualizes the chi2 test for a given chi2 value and degrees of freedom
  Values
  -------

    `fval` : chi2 value

    `ndof` : degrees of freedom
    `x_limit` : chi2 value limit for integral (don't change)
  '''

  x = np.linspace(0,x_limit, 1000)
  y = [scipy.stats.chi2.pdf(i,df=ndof) for i in x]

  section = np.arange(fval, x_limit)
  plt.fill_between(section,scipy.stats.chi2.pdf(section,df=ndof), alpha=.4)
  plt.title('Test $\chi^2$')
  plt.xlabel(r'$\chi^2$')
  plt.ylabel('$pdf(\chi^2)$')
  plt.legend([r'$\chi^2$ '+f'= {round(fval,2)}\n'+f'$dof = {round(ndof,2)}$ \n'+f'p-value = {round(1 - scipy.stats.chi2.cdf(fval,ndof),3)*100}%'])
  plt.plot(x,y)

  return (1 - scipy.stats.chi2.cdf(fval,ndof))

def t_test(tvalue, df,xlim = 7, alpha = 0.05 ):
  '''This function visualizes the t Student test for a given t value and degrees of freedom
    Values:
    -------

    `tvalue` : t Student test Value
    `df` : dergrees of freedom
    `xlim` : limit for integration (don't change)
  '''

  x = np.linspace(-xlim,xlim,2000)
  y = [ scipy.stats.t.pdf(i,df) for i in x]

  section1 = np.linspace(-xlim,-tvalue)
  plt.fill_between(section1,scipy.stats.t.pdf(section1,df=df), alpha=.4, color='b')

  section2 = np.linspace(tvalue, xlim)
  plt.fill_between(section2,scipy.stats.t.pdf(section2,df=df), alpha=.4, color='b')

  # plt.title('t Test')
  plt.xlabel(r't')
  plt.ylabel('pdf(t)')
  plt.legend([r'$\alpha$'+f' = {round((1-scipy.stats.t.cdf(tvalue,df=df))*2, 4)}'])
  plt.plot(x,y)
  return (1-scipy.stats.t.cdf(tvalue,df=df))*2


#@title Error Propagation no Covariance

def formula_errori(parametri:str, formula:str, latex_ = False):

    #convert from str to sympy
    parametri = sympy.sympify(parametri)
    formula = sympy.simplify(formula)
    sigmas = sympy.symbols([f'sigma_{var}' for var in parametri])
    i,exp = 0,0

    for val in parametri:

        #squared partial derivatives and sigmas
        exp += sympy.diff(formula,val)**2 * sigmas[i]**2
        i+=1

    exp = sympy.sqrt(exp)

    if latex_: return '$'+sympy.latex(exp)+'$'

    return (exp)

def valuta_errori(formula_errori:str, values:dict, errors:dict, x:dict=None):

  #convert minuit values method to dict
  params = values.keys()

  #sustitute numerical values
  expr = formula_errori.subs(values)

  for val in errors:

    #substitute numerical for sigmas
    expr = expr.subs(f'sigma_{val}', errors[val])

  if x != None: expr = expr.subs(x)

  return expr

# @title media pesata
def media_pesata(x,err) -> tuple['media':str,'sigma':str]:

  x_ = np.array(x)
  err_ = np.array(err)

  if x_.shape != err_.shape:
    raise Exception('Size mismatch, control arrays!')
    return

  s1,s2 = 0,0
  for i,j in zip(x_,err_):

    s1 += i/j**2
    s2 += 1/j**2

  media = s1/s2
  sigma = np.sqrt(float(1/s2))

  return media,sigma

def normal(x:float, mu:float, sigma:float) -> float:
  return norm.pdf(x, mu, sigma)

def normal_cdf(x:float, mu:float, sigma:float) -> float:
  return norm.cdf(x, mu, sigma)

def sturges_rule(data):
    return int(np.ceil(np.log2(len(data)) + 1))

def normal_scaled(x:float, mu:float, sigma:float, scale:float) -> float:
  return scale*norm.pdf(x, mu, sigma)

def normal_scaled_cdf(x:float, mu:float, sigma:float, scale:float) -> float:
  return scale*norm.cdf(x, mu, sigma)