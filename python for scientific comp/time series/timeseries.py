import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import scipy.stats
import pylab


'''
### Time series
Time series is a sequence of information that has time stamps associated with.

It shas START and END .. total time  
T
 
**Time period**  
t
  : Interval of recording between one point to the next .. SHOULD BE EQUAL for meaningful evaluation
**Frequency** : How often the values are recorded (could be daily, monthly etc)

Correct chronological sequence is important

Stock market
Meteorological data (seasonality)
Missing values can challanging'''

raw_csv_data=pd.read_csv("Sensex.csv")

raw_csv_data

raw_csv_data.dtypes

raw_csv_data.describe()

raw_csv_data.isna()

raw_csv_data.isna().sum()

raw_csv_data.Close.plot()

raw_csv_data.Date.describe()

pd.to_datetime(raw_csv_data['Date'])

raw_csv_data['Date']=pd.to_datetime(raw_csv_data['Date'])

raw_csv_data.Date.describe()

plt.figure( figsize=(20,5))
plt.plot(raw_csv_data['Date'],raw_csv_data['Open'])
plt.show()

raw_csv_data

raw_csv_data.set_index('Date',inplace=True)

raw_csv_data

raw_csv_data.Open.plot()

raw_csv_data[:6000].max()

scipy.stats.probplot(raw_csv_data.Open, plot=plt,fit=True)
plt.title("QQ plot")
plt.show()

raw_csv_data= raw_csv_data.asfreq('d')

raw_csv_data.head(12)

raw_csv_data= raw_csv_data.asfreq('b')

raw_csv_data.head(12)

raw_csv_data.isna().sum()

raw_csv_data.Open=raw_csv_data.Open.fillna(method='ffill')


raw_csv_data.Close=raw_csv_data.Close.bfill()


raw_csv_data.High=raw_csv_data.High.fillna(value=raw_csv_data.High.mean())

raw_csv_data.isna().sum()

sensex=raw_csv_data['Open']
sensex.describe()

type(sensex)

sensex=pd.DataFrame(sensex)

type(sensex)

size=int(len(sensex)*.8)

df_train= raw_csv_data.iloc[:size]
df_test= raw_csv_data.iloc[size:]

wn= np.random.normal(loc = sensex.Open.mean(), scale=sensex.Open.std(),size=len(sensex))

sensex['wn']=wn

sensex

sensex.describe()

scipy.stats.probplot(sensex.wn, plot=plt,fit=True)
plt.title("QQ plot")
plt.show()

plt.figure(figsize=(20,5))
plt.plot(sensex['wn'])
plt.plot(sensex['Open'])
plt.show()

random_walk = [sensex.Open.iloc[0]]
for i in range(1, len(sensex)):
    movement = -150 if np.random.random() < .48 else 150
    value = random_walk[i-1] + movement
    random_walk.append(value)
plt.plot(random_walk)
plt.show()


sensex['rw']=random_walk

sensex

plt.figure(figsize=(20,5))
plt.plot(sensex.rw)
plt.plot(sensex.Open)

pd.plotting.autocorrelation_plot(wn)


fig,ax=plt.subplots()
pd.plotting.autocorrelation_plot(wn,ax)
ax.set_xlim(0,10)

pd.plotting.autocorrelation_plot(random_walk)


import statsmodels.tsa.stattools as tools


tools.adfuller(sensex['wn'])


tools.adfuller(sensex['rw'])

tools.adfuller(sensex['Open'])


import statsmodels.tsa.seasonal as decompose
additive = decompose.seasonal_decompose(sensex.Open,model='additive')
additive.plot()
plt.show()

multiplicative = decompose.seasonal_decompose(sensex.Open,model='multiplicative')
additive.plot()
plt.show()


pd.plotting.autocorrelation_plot(sensex.Open)

from statsmodels.graphics import tsaplots 

tsaplots.plot_acf(sensex.Open,lags=50,zero=False)

tsaplots.plot_acf(sensex.wn,lags=50,zero=False)
plt.show()

tsaplots.plot_acf(sensex.rw,lags=50,zero=False)
plt.show()

tsaplots.plot_pacf(sensex.Open,lags=50,zero=False,method='ols')
plt.show()

tsaplots.plot_pacf(sensex.wn,lags=50,zero=False,method='ols')
plt.show()

tsaplots.plot_pacf(sensex.rw,lags=50,zero=False,method='ols')
plt.show()