import matplotlib.pyplot as plt

import numpy as np

import pandas as pd

from statsmodels.tsa.seasonal import seasonal_decompose


from statsmodels.graphics.tsaplots import plot_acf, plot_pacf


from statsmodels.tsa.stattools import adfuller


from statsmodels.tsa.arima.model import ARIMA



#Load the dataset into a DataFrame.

df = pd.read_csv('dataset_11.csv')

#Check the first few rows of the dataset.

print(df.head())




#Check the column types (e.g., ensure eventDate is a datetime column).

df['eventDate'] = pd.to_datetime(df['eventDate'])


#Check for any missing values in the dataset.

print(df.isnull().sum())






#Check for missing values, duplicates, or outliers.
print(df.describe())
#Check for any missing values in the dataset.

print(df.isnull().sum())
#Check for duplicates.

print(df.duplicated().sum())
#Check for outliers using the IQR method.

Q1 = df['individualCount'].quantile(0.25)
Q3 = df['individualCount'].quantile(0.75)
IQR = Q3 - Q1   
lower_bound = Q1 - 1.5 * IQR
upper_bound = Q3 + 1.5 * IQR
outliers = df[(df['individualCount'] < lower_bound) | (df['individualCount'] > upper_bound)]
print(f"Number of outliers: {len(outliers)}")
#Check for any missing values in the dataset.

print(df.isnull().sum())


#Handle missing values in the individualCount column (e.g., forward fill or impute with median).

df['individualCount'].fillna(df['individualCount'].median(), inplace=True)

df['individualCount'] = df['individualCount'].ffill()






#Ensure all columns are in appropriate formats (e.g., numeric, datetime).


df['individualCount'] = pd.to_numeric(df['individualCount'], errors='coerce')
df['eventDate'] = pd.to_datetime(df['eventDate'])
#Check for any missing values in the dataset.

print(df.isnull().sum())
#Check for duplicates.

print(df.duplicated().sum())


#Plot the time series to visualize trends.

plt.plot(df['eventDate'], df['individualCount'])
plt.xlabel('Date')
plt.ylabel('Individual Count')
plt.title('Individual Count Over Time')





#Decompose the time series to examine seasonality, trend, and residuals using seasonal decomposition (statsmodels).



decomposition = seasonal_decompose(df.set_index('eventDate')['individualCount'], model='additive', period=12)
decomposition.plot()


#Plot ACF and PACF to understand if there are any patterns (seasonality or cyclic behavior).
plot_acf(df['individualCount'].dropna())
plot_pacf(df['individualCount'].dropna())
#Check for stationarity using the Augmented Dickey-Fuller test.

result = adfuller(df['individualCount'].dropna())
print('ADF Statistic: %f' % result[0])
print('p-value: %f' % result[1])
for key, value in result[4].items():
    print('Critical Value (%s): %f' % (key, value))
    #Check for any missing values in the dataset.

print(df.isnull().sum())
#Handle missing values in the individualCount column (e.g., forward fill or impute with median).

df['individualCount'].fillna(df['individualCount'].median(), inplace=True)
#Ensure all columns are in appropriate formats (e.g., numeric, datetime).

df['individualCount'] = pd.to_numeric(df['individualCount'], errors='coerce')

df['eventDate'] = pd.to_datetime(df['eventDate'])

#Perform the ADF test to check for stationarity.

result = adfuller(df['individualCount'].dropna())
print('ADF Statistic: %f' % result[0])
print('p-value: %f' % result[1])
for key, value in result[4].items():
    print('Critical Value (%s): %f' % (key, value))



#If non-stationary, perform differencing or transformations (e.g., log transform).

df['individualCount'] = np.log(df['individualCount'])
result = adfuller(df['individualCount'].dropna())
print('ADF Statistic: %f' % result[0])
print('p-value: %f' % result[1])
for key, value in result[4].items():
    print('Critical Value (%s): %f' % (key, value))


#Build ARIMA/SARIMA models if needed for forecasting.

model = ARIMA(df['individualCount'], order=(1,1,1))
model_fit = model.fit()
print(model_fit.summary())
#Plot the residuals to check for any remaining patterns.
residuals = pd.DataFrame(model_fit.resid)
residuals.plot()
plt.show()
#Check for any autocorrelation in the residuals.

plot_acf(residuals)
plt.show()
#Check for any autocorrelation in the residuals.

plot_pacf(residuals)

