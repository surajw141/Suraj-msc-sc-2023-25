import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from statsmodels.tsa.seasonal import seasonal_decompose
from statsmodels.graphics.tsaplots import plot_acf, plot_pacf
from statsmodels.tsa.stattools import adfuller

# Load dataset
data = pd.read_csv("dataset_11.csv")

# Preprocessing
data['eventDate'] = pd.to_datetime(data['eventDate'])
data.set_index('eventDate', inplace=True)

# Debug: Check for initial missing values in 'individualCount'
print(f"Initial missing values in 'individualCount': {data['individualCount'].isnull().sum()}")

# Improved Handling of Missing Values: Interpolation method
if data['individualCount'].isnull().sum() == len(data):
    print("All values in 'individualCount' are missing. Filling with 0.")
    data['individualCount'] = 0
else:
    # Use interpolation for missing values
    data['individualCount'] = data['individualCount'].interpolate(method='linear')

# Ensure all values are numeric
data['individualCount'] = pd.to_numeric(data['individualCount'], errors='coerce')

# Final validation of missing values
if data['individualCount'].isnull().sum() > 0:
    raise ValueError("Missing values detected in 'individualCount' even after filling!")
else:
    print("No missing values remain in 'individualCount'.")

# Exploratory plots
# 1. Plot for Individual Count Time Series
plt.figure(figsize=(10, 5))
plt.plot(data['individualCount'], label="Individual Count")
plt.title("Individual Count Over Time")
plt.xlabel("Date")
plt.ylabel("Individual Count")
plt.legend()
plt.show()

# 2. Rolling Mean (Trend) Visualization
data['rolling_mean'] = data['individualCount'].rolling(window=12).mean()
plt.figure(figsize=(10, 5))
plt.plot(data['individualCount'], label="Individual Count")
plt.plot(data['rolling_mean'], label="12-Month Rolling Mean", color='red')
plt.title("Individual Count with Rolling Mean")
plt.xlabel("Date")
plt.ylabel("Individual Count")
plt.legend()
plt.show()

# Decomposition (Trend, Seasonal, Residual)
try:
    decomposed = seasonal_decompose(data['individualCount'], model='additive', period=12)
    decomposed.plot()
    plt.show()
except ValueError as e:
    print(f"Decomposition error: {e}")

# ADF Test (Stationarity Check)
try:
    result = adfuller(data['individualCount'].dropna())
    print(f"ADF Statistic: {result[0]}")
    print(f"p-value: {result[1]}")
    print("Critical Values:")
    for key, value in result[4].items():
        print(f"   {key}: {value}")
except Exception as e:
    print(f"ADF Test error: {e}")

# Autocorrelation and PACF (Plotting)
try:
    plot_acf(data['individualCount'].dropna(), lags=50)
    plt.show()

    plot_pacf(data['individualCount'].dropna(), lags=50)
    plt.show()
except Exception as e:
    print(f"Autocorrelation/PACF error: {e}")

# Yearly Plot: Number of Observations per Year
data['year'] = data.index.year
yearly_counts = data.groupby('year')['gbifID'].count()
plt.figure(figsize=(10, 5))
yearly_counts.plot(title="Observations by Year")
plt.xlabel("Year")
plt.ylabel("Number of Observations")
plt.show()

# Additional Analysis (Optional)
# Integrate additional data for correlation analysis
# Placeholder: Assuming you have an external dataset like 'external_data.csv'
# external_data = pd.read_csv("external_data.csv")
# Merge with the original data if necessary, e.g., by 'eventDate'
# data = pd.merge(data, external_data, on='eventDate', how='left')




